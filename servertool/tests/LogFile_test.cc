#include "LogFile.h"
#include "Logging.h"

boost::scoped_ptr<basetool::LogFile> g_logFile;

void outputFunc(const char* msg, int len)
{
  g_logFile->append(msg, len);
}

void flushFunc()
{
  g_logFile->flush();
}

int main(int argc, char* argv[])
{
  char name[256];
  strncpy(name, argv[1], 256);
  g_logFile.reset(new basetool::LogFile(name, 2000*1000*1000));
  //g_logFile.reset(new basetool::LogFile(::basename(name), 2000*1000*1000));
  basetool::Logger::setOutput(outputFunc);
  basetool::Logger::setFlush(flushFunc);

  basetool::string line = "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  for (int i = 0; i < 500*10000; ++i)
  {
    LOG_INFO << line << i;

    //usleep(1000);
  }
}
