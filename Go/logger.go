package log

import (
	"bufio"
	"bytes"
	"errors"
	"fmt"
	"os"
	"runtime"
	"strconv"
	"strings"
	"time"
)

type RotateState int

const (
	RotateMinute RotateState = iota
	RotateHour
	RotateDay
)

func (r *RotateState) check(now, last time.Time) bool {
	switch {
	case *r == RotateMinute && now.Minute() != last.Minute():
		return true
	case *r == RotateHour && now.Hour() != last.Hour():
		return true
	case *r == RotateDay && now.Day() != last.Day():
		return true
	}
	return false
}

func (r *RotateState) suffixName(t time.Time) string {
	switch {
	case *r == RotateMinute:
		return fmt.Sprintf("%02d%02d%02d", t.Day(), t.Hour(), t.Minute())
	case *r == RotateHour:
		return fmt.Sprintf("%02d%02d", t.Day(), t.Hour())
	case *r == RotateDay:
		return fmt.Sprintf("%02d", t.Day())
	}
	return ""
}

type LogLevel int

const (
	DebugLog LogLevel = iota
	InfoLog
	WarningLog
	ErrorLog
	FatalLog
	NumsLevel = 5
)

var LogLevelName = []string{
	DebugLog:   "DEBUG",
	InfoLog:    "INFO",
	WarningLog: "WARNING",
	ErrorLog:   "ERROR",
	FatalLog:   "FATAL",
}

func (s *LogLevel) getLevel() LogLevel {
	return *s
}

func (s *LogLevel) getLevelName(level LogLevel) (string, bool) {
	for i, name := range LogLevelName {
		if LogLevel(i) == level {
			return name, true
		}
	}
	return "", false
}

func (s *LogLevel) logLevelByName(v string) (int, bool) {
	v = strings.ToUpper(v)
	for i, name := range LogLevelName {
		if name == v {
			return i, true
		}
	}
	return 0, false
}

func (s *LogLevel) checkLevelValid(level LogLevel) bool {
	if level >= DebugLog && level < NumsLevel {
		return true
	}
	return false
}

type asyncBuffer struct {
	time time.Time
	buf  *bytes.Buffer
}

type AsyncLog struct {
	writer       *bufio.Writer
	logdir       string // /home/log/
	logname      string // passport
	needfilenum  bool   // add log.go:80
	logfd        *os.File
	lasttime     time.Time
	buffer       chan *asyncBuffer
	loglevel     LogLevel
	rotatestatus RotateState
	stackdepth   int // stack depth
}

// init
var (
	gPid     = strconv.Itoa(os.Getpid())
	gHost, _ = os.Hostname()
)

const (
	bufferSize   = 32 * 1024
	ioBufferSize = 256 * 1024
)

func NewAsyncLog(logdir, logname string, level LogLevel,
	rotate RotateState, filenumer bool, depth int) (*AsyncLog, error) {
	now := time.Now()
	l := &AsyncLog{
		logdir:       logdir,
		logname:      logname,
		needfilenum:  filenumer,
		lasttime:     time.Now(),
		buffer:       make(chan *asyncBuffer, bufferSize),
		loglevel:     level,
		rotatestatus: rotate,
		stackdepth:   depth,
	}

	fd, _, err := l.createFile(now)
	if err != nil {
		return nil, err
	}
	l.logfd = fd
	l.writer = bufio.NewWriterSize(fd, ioBufferSize)

	go l.consumerLog()
	return l, nil
}

func (l *AsyncLog) Debug(args ...interface{}) {
	l.write(DebugLog, bytes.NewBufferString(fmt.Sprint(args...)))
}

func (l *AsyncLog) Debugf(format string, args ...interface{}) {
	l.write(DebugLog, bytes.NewBufferString(fmt.Sprintf(format, args...)))
}

func (l *AsyncLog) Info(args ...interface{}) {
	l.write(InfoLog, bytes.NewBufferString(fmt.Sprint(args...)))
}

func (l *AsyncLog) Infof(format string, args ...interface{}) {
	l.write(InfoLog, bytes.NewBufferString(fmt.Sprintf(format, args...)))
}

func (l *AsyncLog) Warn(args ...interface{}) {
	l.write(WarningLog, bytes.NewBufferString(fmt.Sprint(args...)))
}

func (l *AsyncLog) Warnf(format string, args ...interface{}) {
	l.write(WarningLog, bytes.NewBufferString(fmt.Sprintf(format, args...)))
}

func (l *AsyncLog) Error(args ...interface{}) {
	l.write(ErrorLog, bytes.NewBufferString(fmt.Sprint(args...)))
}

func (l *AsyncLog) Errorf(format string, args ...interface{}) {
	l.write(ErrorLog, bytes.NewBufferString(fmt.Sprintf(format, args...)))
}

func (l *AsyncLog) Fatal(args ...interface{}) {
	l.write(FatalLog, bytes.NewBufferString(fmt.Sprint(args...)))
}

func (l *AsyncLog) Fatalf(format string, args ...interface{}) {
	l.write(FatalLog, bytes.NewBufferString(fmt.Sprintf(format, args...)))
}

//-------------------------Private-------------------------------------
func (l *AsyncLog) write(level LogLevel, msg *bytes.Buffer) error {
	if !l.loglevel.checkLevelValid(level) {
		return errors.New("log: log level invalid")
	}

	if level < l.loglevel.getLevel() {
		return nil
	}

	now := time.Now()

	outmsg := l.header(now, level, l.stackdepth)
	outmsg.Write(msg.Bytes())
	if msg.Len() == 0 || msg.Bytes()[msg.Len()-1] != '\n' {
		outmsg.WriteByte('\n')
	}

	l.producerLog(&asyncBuffer{now, outmsg})

	return nil
}

func (l *AsyncLog) consumerLog() {
	for {
		select {
		case msg := <-l.buffer:
			l.rotateFile(msg.time)
			l.writer.Write(msg.buf.Bytes()) // ignore error
		case <-time.After(3 * time.Second):
			l.writer.Flush()
		}
	}
}

func (l *AsyncLog) producerLog(msg *asyncBuffer) {
	select {
	case l.buffer <- msg:
		return
	case <-time.After(50 * time.Millisecond):
		// only wakeup
	}
	return
}

func (l *AsyncLog) shortFile(file string) string {
	short := file
	for i := len(file) - 1; i > 0; i-- {
		if file[i] == '/' {
			short = file[i+1:]
			break
		}
	}
	return short
}

func (l *AsyncLog) header(t time.Time, level LogLevel, depth int) *bytes.Buffer {
	file, line := "???", -1
	if l.needfilenum {
		var ok bool
		_, file, line, ok = runtime.Caller(2 + depth)
		if !ok {
			file = "???"
			line = -1
		} else {
			file = l.shortFile(file)
		}
	}
	return l.formatHeader(t, file, level, line)
}

func (l *AsyncLog) formatHeader(t time.Time, file string, level LogLevel, line int) *bytes.Buffer {
	result := bytes.NewBuffer(nil)
	// datetime
	datetime := t.Format("2006-01-02T15:04:05.000000+08:00")
	result.Write([]byte(datetime))
	result.WriteByte(' ')

	// host
	result.Write([]byte(gHost))
	result.WriteByte(' ')

	// tag
	result.Write([]byte(l.logname))

	// pid
	result.WriteByte('[')
	result.Write([]byte(gPid))
	result.Write([]byte("]: "))

	// level
	logname, _ := l.loglevel.getLevelName(level)
	logname = "[" + logname + "]"
	result.Write([]byte(logname))
	result.WriteByte(' ')

	// file
	if file != "???" && line != -1 {
		result.Write([]byte(file))
		result.Write([]byte(":"))
		// line
		result.Write([]byte(strconv.Itoa(line)))
		result.WriteByte(' ')
	}

	return result
}

func (l *AsyncLog) logName(t time.Time) string {
	head := fmt.Sprintf("%s.log.%04d%02d",
		l.logname,
		t.Year(),
		t.Month(),
	)

	suffix := l.rotatestatus.suffixName(t)
	return head + suffix
}

func (l *AsyncLog) createFile(t time.Time) (*os.File, string, error) {
	if l.logname == "" || l.logdir == "" {
		return nil, "", errors.New("log: log name or log dir is empty")
	}

	logname := ""
	if l.logdir[len(l.logdir)-1] == '/' {
		logname = l.logdir + l.logName(t)
	} else {
		logname = l.logdir + "/" + l.logName(t)
	}

	fd, err := os.OpenFile(logname, os.O_WRONLY|os.O_APPEND|os.O_CREATE, 0644)
	if err != nil {
		return nil, "", err
	}
	return fd, logname, nil
}

func (l *AsyncLog) rotateFile(t time.Time) {
	if l.logfd != nil {
		if l.rotatestatus.check(t, l.lasttime) {
			fd, _, err := l.createFile(t)
			if err != nil {
				l.exit(err)
				return
			}

			l.writer.Flush()
			l.logfd.Sync()
			l.logfd.Close()

			l.writer = bufio.NewWriterSize(fd, ioBufferSize)
			l.logfd = fd
			l.lasttime = t
		}
	}
}

func (l *AsyncLog) exit(err error) {
	fmt.Fprintf(os.Stderr, "log: exiting because of error: %s\n", err)
	os.Exit(2)
}

//var glog *AsyncLog
//
//func main() {
//	var err error
//	glog, err = NewAsyncLog("./log", "test", DebugLog, RotateMinute, false, 0)
//	if err != nil {
//		fmt.Println("new log error")
//		return
//	}
//
//	number, err := strconv.Atoi(os.Args[1])
//
//	thread_num, _ := strconv.Atoi(os.Args[2])
//	chans := make(chan bool, thread_num)
//	fmt.Println("start time: ", time.Now().UnixNano())
//	for i := 0; i < thread_num; i++ {
//		go func(id, num int, c chan bool) {
//			for j := 0; j < num; j++ {
//				//s := "-------------------------"
//				glog.Debug("------------------------------------------")
//				shit := 123.9
//				slice := []byte{'1', '2', '3', '4'}
//				type info struct {
//					Name  string
//					Age   int
//					Score float32
//				}
//				info1 := info{
//					"chenping",
//					28,
//					100.0,
//				}
//
//				mp := map[string]interface{}{
//					"Score": 123456.8,
//					"need":  "you",
//					"age":   123456789,
//				}
//				glog.Debugf("string %s, float %#v, slice %v, struct %, map %v", "----------------",
//					shit, slice, info1, mp)
//				glog.Info("info------------------------------------------")
//				glog.Infof("infof------------------------------------------")
//				glog.Warn("warn------------------------------------------")
//				glog.Warnf("warnf------------------------------------------")
//				glog.Error("error------------------------------------------")
//				glog.Errorf("errorf------------------------------------------")
//				glog.Fatal("fatal------------------------------------------")
//				glog.Fatalf("fatalf------------------------------------------")
//			}
//			c <- true
//		}(i, number, chans)
//	}
//
//	count := 0
//	for c := range chans {
//		fmt.Println(c)
//		count++
//		if count >= thread_num {
//			break
//		}
//	}
//
//	//glog.Error("-----------------------------------------done")
//	fmt.Println("end time: ", time.Now().UnixNano())
//	time.Sleep(4 * time.Second)
//	fmt.Println("all done.............................")
//}
