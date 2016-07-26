#ifndef TP_EXECUTOR_H_
#define TP_EXECUTOR_H_

#include "TP_Threads.h"
#include "TP_Worker.h"
#include "TP_WorkerHandle.h"

#define TP_QUEUE_FULL        -10

class CTP_Executor {
public:
    CTP_Executor(int maxWorkers, int maxQueueSize);
    virtual ~CTP_Executor();

    void Core();
    int execute(CTP_Task* task);
    int execute(std::vector<CTP_Task*>& tasks);
    void shutdown();
    int getQueueSize();
    int getFreeThreadNum();
    int getAllThreadNum();
    int getRunThreadNum();

protected:
    CTP_Worker* getWorker();
private:
    int m_maxWorkers;
    int m_maxQueueSize;

    std::queue<CTP_Task*> m_blockQueue;
    CTP_MtLock m_queueLock;

    int m_workerNum;
    int m_isShutdown;
    CTP_Threads m_threadsManager;
    TP_WORKER_HANDLE_S m_workerHandle;
};

#endif /* TP_EXECUTOR_H_ */
