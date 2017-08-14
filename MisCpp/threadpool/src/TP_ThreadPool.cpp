#include "TP_ThreadPool.h"

CTP_ThreadPool::CTP_ThreadPool(int maxWorkers, int maxQueueSize)
: m_maxWorkers(maxWorkers), m_maxQueueSize(maxQueueSize)
{
    m_executor = new CTP_Executor(m_maxWorkers, m_maxQueueSize);
    m_threadsManager.setRoutine(TPStartRoutine<CTP_Executor>);
    m_threadsManager.createThead(m_executor);
}

CTP_ThreadPool::~CTP_ThreadPool() {
    m_executor->shutdown();
    m_threadsManager.jionALLThreads();

    if(m_executor) {
        delete m_executor;
        m_executor = NULL;
    }
}

int CTP_ThreadPool::execute(CTP_Task* task)
{
    return m_executor->execute(task);
}

int CTP_ThreadPool::execute(std::vector<CTP_Task*>& tasks)
{
    return m_executor->execute(tasks);
}

int CTP_ThreadPool::getMaxThreadNum()
{
    return m_maxWorkers;
}

int CTP_ThreadPool::getMaxQueueSize()
{
    return m_maxQueueSize;
}

int CTP_ThreadPool::getFreeThreadNum()
{
    return m_executor->getFreeThreadNum();
}

int CTP_ThreadPool::getAllThreadNum()
{
    return m_executor->getAllThreadNum();
}

int CTP_ThreadPool::getRunThreadNum()
{
    return m_executor->getRunThreadNum();
}
