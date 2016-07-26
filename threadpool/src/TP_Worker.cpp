#include "TP_Worker.h"

CTP_Worker::CTP_Worker(TP_WORKER_HANDLE_S* workerHandle)
 : m_workerHandle(workerHandle)
{
    m_isShutdown = 1;
    m_threadId = m_workerHandle->m_count++;
    m_workerHandle->m_freeWorks.push_back(NULL);
    m_workerHandle->m_allWorks.push_back(this);
    m_task = NULL;
}

CTP_Worker::~CTP_Worker() {

    //shutdown();
}

void CTP_Worker::Core()
{
    int ret = 0;

    while(m_isShutdown) {

        m_workerLock.mtLock();
        if(m_task == NULL) {
            m_workerLock.mtWait();
        }

        if(m_task == NULL) {
            m_workerLock.mtUnlock();
            continue;
        }

        m_task->taskStart();
        ret = m_task->handle(m_threadId);
        m_task->setResult(ret);
        m_task->taskEnd();

        m_workerLock.mtUnlock();
        saveWorker();
    }
    //m_isShutdown = -1;
}

void CTP_Worker::shutdown()
{
    m_workerLock.mtLock();
    m_isShutdown = 0;
    m_workerLock.mtNotify();
    m_workerLock.mtUnlock();
}

void CTP_Worker::setTask(CTP_Task* task)
{
    m_workerLock.mtLock();
    m_task = task;
    m_workerLock.mtNotify();
    m_workerLock.mtUnlock();
}

void CTP_Worker::saveWorker()
{
    m_workerHandle->m_executorLock.mtLock();

    m_workerHandle->m_freeWorks[m_workerHandle->m_workerIndex] = this;
    m_workerHandle->m_workerIndex++;
    m_task = NULL;

    m_workerHandle->m_executorLock.mtNotify();
    m_workerHandle->m_executorLock.mtUnlock();

}
