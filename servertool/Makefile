CC = g++

TARGET   = libbasetool.so libbasetool.a
INCLUDES = ./ 
LIBFLAGS = -lpthread -lrt -lz -lboost_unit_test_framework 
TESTDIR  =./tests/
	 
CXXFLAGS = -g\
		   -Wall\
		   -DCHECK_PTHREAD_RETURN_VALUE\
		   -D_FILE_OFFSET_BITS=64\
		   -Wextra\
		   -Werror\
		   -Wconversion\
		   -Wno-unused-parameter\
		   -Wold-style-cast\
		   -Woverloaded-virtual\
		   -Wpointer-arith\
		   -Wshadow\
		   -Wwrite-strings\
		   -O2\

SOURCES = $(FILES)
OBJS = $(patsubst %.cc, %.o, $(wildcard *.cc))

%.o:%.cc
	$(CC) $(CXXFLAGS) -I$(INCLUDES) -fPIC -c $< -o $@

TESTS= AsyncLogging_test \
	   BoundedBlockingQueue_test\
	   FileUtil_test\
	   Logging_test\
	   ThreadLocalSingleton_test\
	   Atomic_test\
       Fork_test\
	   LogStream_bench_test\
	   Singleton_test\
	   ThreadLocal_test\
	   BlockingQueue_bench_test\
	   Date_test\
	   LogStream_test\
	   SingletonThreadLocal_test\
	   BlockingQueue_test\
	   Exception_test\
	   LogFile_test\
	   Mutex_test\
	   Thread_bench_test\
	   Thread_test\
	   ProcessInfo_test\
	   Timestamp_test\
	   ThreadPool_test\
	   Conf_test\
	   Random_test\
	   #GzipFile_test\

all:$(TARGET) $(TESTS)
	
libbasetool.so: $(OBJS)
	$(CC) -shared $(LDFLAGS) $(OBJS) -o $@
libbasetool.a:$(OBJS)                                                                                                                                                               
	ar -cru $@ $^

AsyncLogging_test: $(OBJS) 
	$(CC) $(LDFLAGS) $(OBJS) $(TESTDIR)/AsyncLogging_test.cc -o $@ -I$(INCLUDES) $(LIBFLAGS) $(CXXFLAGS)
BoundedBlockingQueue_test: $(OBJS) 
	$(CC) $(LDFLAGS) $(OBJS) $(TESTDIR)/BoundedBlockingQueue_test.cc -o $@ -I$(INCLUDES) $(LIBFLAGS) $(CXXFLAGS)
FileUtil_test: $(OBJS) 
	$(CC) $(LDFLAGS) $(OBJS) $(TESTDIR)/FileUtil_test.cc -o $@ -I$(INCLUDES) $(LIBFLAGS) $(CXXFLAGS)
Logging_test: $(OBJS) 
	$(CC) $(LDFLAGS) $(OBJS) $(TESTDIR)/Logging_test.cc -o $@ -I$(INCLUDES) $(LIBFLAGS) $(CXXFLAGS)
ThreadLocalSingleton_test: $(OBJS) 
	$(CC) $(LDFLAGS) $(OBJS) $(TESTDIR)/ThreadLocalSingleton_test.cc -o $@ -I$(INCLUDES) $(LIBFLAGS) $(CXXFLAGS)
Atomic_test: $(OBJS) 
	$(CC) $(LDFLAGS) $(OBJS) $(TESTDIR)/Atomic_test.cc -o $@ -I$(INCLUDES) $(LIBFLAGS) $(CXXFLAGS)
Fork_test: $(OBJS) 
	$(CC) $(LDFLAGS) $(OBJS) $(TESTDIR)/Fork_test.cc -o $@ -I$(INCLUDES) $(LIBFLAGS) $(CXXFLAGS)
LogStream_bench_test: $(OBJS) 
	$(CC) $(LDFLAGS) $(OBJS) $(TESTDIR)/LogStream_bench_test.cc -o $@ -I$(INCLUDES) $(LIBFLAGS) $(CXXFLAGS)
Singleton_test: $(OBJS) 
	$(CC) $(LDFLAGS) $(OBJS) $(TESTDIR)/Singleton_test.cc -o $@ -I$(INCLUDES) $(LIBFLAGS) $(CXXFLAGS)
ThreadLocal_test: $(OBJS) 
	$(CC) $(LDFLAGS) $(OBJS) $(TESTDIR)/ThreadLocal_test.cc -o $@ -I$(INCLUDES) $(LIBFLAGS) $(CXXFLAGS)
BlockingQueue_bench_test: $(OBJS) 
	$(CC) $(LDFLAGS) $(OBJS) $(TESTDIR)/BlockingQueue_bench_test.cc -o $@ -I$(INCLUDES) $(LIBFLAGS) $(CXXFLAGS)
Date_test: $(OBJS) 
	$(CC) $(LDFLAGS) $(OBJS) $(TESTDIR)/Date_test.cc -o $@ -I$(INCLUDES) $(LIBFLAGS) $(CXXFLAGS)
#GzipFile_test: $(OBJS) 
#	$(CC) $(LDFLAGS) $(OBJS) $(TESTDIR)/GzipFile_test.cc -o $@ -I$(INCLUDES) $(LIBFLAGS)
LogStream_test: $(OBJS) 
	$(CC) $(LDFLAGS) $(OBJS) $(TESTDIR)/LogStream_test.cc -o $@ -I$(INCLUDES) $(LIBFLAGS) $(CXXFLAGS)
SingletonThreadLocal_test: $(OBJS) 
	$(CC) $(LDFLAGS) $(OBJS) $(TESTDIR)/SingletonThreadLocal_test.cc -o $@ -I$(INCLUDES) $(LIBFLAGS) $(CXXFLAGS)
BlockingQueue_test: $(OBJS) 
	$(CC) $(LDFLAGS) $(OBJS) $(TESTDIR)/BlockingQueue_test.cc -o $@ -I$(INCLUDES) $(LIBFLAGS) $(CXXFLAGS)
Exception_test: $(OBJS) 
	$(CC) $(LDFLAGS) $(OBJS) $(TESTDIR)/Exception_test.cc -o $@ -I$(INCLUDES) $(LIBFLAGS) $(CXXFLAGS)
LogFile_test: $(OBJS) 
	$(CC) $(LDFLAGS) $(OBJS) $(TESTDIR)/LogFile_test.cc -o $@ -I$(INCLUDES) $(LIBFLAGS) $(CXXFLAGS)
Mutex_test: $(OBJS) 
	$(CC) $(LDFLAGS) $(OBJS) $(TESTDIR)/Mutex_test.cc -o $@ -I$(INCLUDES) $(LIBFLAGS) $(CXXFLAGS)
Thread_bench_test: $(OBJS) 
	$(CC) $(LDFLAGS) $(OBJS) $(TESTDIR)/Thread_bench_test.cc -o $@ -I$(INCLUDES) $(LIBFLAGS) $(CXXFLAGS)
Thread_test: $(OBJS) 
	$(CC) $(LDFLAGS) $(OBJS) $(TESTDIR)/Thread_test.cc -o $@ -I$(INCLUDES) $(LIBFLAGS) $(CXXFLAGS)
ProcessInfo_test: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(TESTDIR)/ProcessInfo_test.cc -o $@ -I$(INCLUDES) $(LIBFLAGS) $(CXXFLAGS)
Timestamp_test: $(OBJS) 
	$(CC) $(LDFLAGS) $(OBJS) $(TESTDIR)/Timestamp_test.cc -o $@ -I$(INCLUDES) $(LIBFLAGS) $(CXXFLAGS)
ThreadPool_test: $(OBJS) 
	$(CC) $(LDFLAGS) $(OBJS) $(TESTDIR)/ThreadPool_test.cc -o $@ -I$(INCLUDES) $(LIBFLAGS) $(CXXFLAGS)
Conf_test: $(OBJS) 
	$(CC) $(LDFLAGS) $(OBJS) $(TESTDIR)/Conf_test.cc -o $@ -I$(INCLUDES) $(LIBFLAGS) $(CXXFLAGS)
Random_test: $(OBJS) 
	$(CC) $(LDFLAGS) $(OBJS) $(TESTDIR)/Random_test.cc -o $@ -I$(INCLUDES) $(LIBFLAGS) $(CXXFLAGS)
	@mv *test ./tests/
	@rm *.o -rf
	@echo "''''''''''''''''''''''''''''''''''''''''all ok''''''''''''''''''''''''''''''''''''''''''''''''"
clean:
	@rm -f $(TARGET) *.o ./tests/*test *.rpm 
