#ifndef TP_THREADPOOL_H_
#define TP_THREADPOOL_H_

#include "TP_Executor.h"

class CTP_ThreadPool {
public:
    CTP_ThreadPool(int maxWorkers, int maxQueueSize);
    virtual ~CTP_ThreadPool();

    int execute(CTP_Task* task);
    int execute(std::vector<CTP_Task*>& tasks);
    int getMaxThreadNum();
    int getMaxQueueSize();
    int getFreeThreadNum();
    int getAllThreadNum();
    int getRunThreadNum();

private:
    int m_maxWorkers;
    int m_maxQueueSize;

    CTP_Executor* m_executor;
    CTP_Threads m_threadsManager;
};

#endif /* TP_THREADPOOL_H_ */
