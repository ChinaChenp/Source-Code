#ifndef WORKER_H_
#define WORKER_H_

#include "TP_Lock.h"
#include "TP_Time.h"
#include "TP_Task.h"
#include "TP_WorkerHandle.h"

#include <vector>
#include <queue>



class CTP_Worker {
public:
    CTP_Worker(TP_WORKER_HANDLE_S* workerHandle);
    virtual ~CTP_Worker();

    void Core();
    void shutdown();
    void setTask(CTP_Task* task);

protected:
    void saveWorker();

private:
    TP_WORKER_HANDLE_S* m_workerHandle;
    u_int m_threadId;
    int m_isShutdown;
    CTP_MtLock m_workerLock;

    CTP_Task* m_task;
};

#endif /* WORKER_H_ */
