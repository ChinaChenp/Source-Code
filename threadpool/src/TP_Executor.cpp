/*
 * TP_Executor.cpp
 *
 *  Created on: Oct 27, 2014
 *      Author: root
 */

#include "TP_Executor.h"

CTP_Executor::CTP_Executor(int maxWorkers, int maxQueueSize)
 : m_maxWorkers(maxWorkers), m_maxQueueSize(maxQueueSize)
{
    m_maxWorkers = m_maxWorkers > 0 ? m_maxWorkers : 2;
    m_isShutdown = 1;
    m_workerNum = 0;
}

CTP_Executor::~CTP_Executor() {

    for(size_t i = 0; i < m_workerHandle.m_allWorks.size(); ++i) {
        if(m_workerHandle.m_allWorks[i]) {
            ((CTP_Worker*)m_workerHandle.m_allWorks[i])->shutdown();
        }
    }

    m_threadsManager.jionALLThreads();

    for(size_t i = 0; i < m_workerHandle.m_allWorks.size(); ++i) {
        if(m_workerHandle.m_allWorks[i]) {
            delete ((CTP_Worker*)m_workerHandle.m_allWorks[i]);
            m_workerHandle.m_allWorks[i] = NULL;
        }
    }
}

void CTP_Executor::Core()
{
    std::queue<CTP_Task*> task_queue;
    CTP_Task* task = NULL;
    CTP_Worker* worker = NULL;

    while(m_isShutdown) {
        m_queueLock.mtLock();

        if(m_blockQueue.empty()) {
            m_queueLock.mtWait();
        }

        if(m_blockQueue.empty()) {
            m_queueLock.mtUnlock();
            continue;
        }

        while(!m_blockQueue.empty()) {
            task_queue.push(m_blockQueue.front());
            m_blockQueue.pop();
        }
        m_queueLock.mtUnlock();

        while(!task_queue.empty()) {
            task = task_queue.front();
            task_queue.pop();
            
            worker = getWorker();
            worker->setTask(task);
        }
    }

    m_queueLock.mtLock();
    while(!m_blockQueue.empty()) {
        task = m_blockQueue.front();
        m_blockQueue.pop();

        worker = getWorker();
        worker->setTask(task);
    }
    m_queueLock.mtUnlock();
}

int CTP_Executor::execute(CTP_Task* task)
{
    m_queueLock.mtLock();

    if((int)m_blockQueue.size() >= m_maxQueueSize) {
        m_queueLock.mtUnlock();
        return TP_QUEUE_FULL;
    }
    m_blockQueue.push(task);

    m_queueLock.mtNotify();
    m_queueLock.mtUnlock();

    return TP_SUCCESS;
}

int CTP_Executor::execute(std::vector<CTP_Task*>& tasks)
{
    m_queueLock.mtLock();

    for(size_t i = 0; i < tasks.size(); ++i) {
        if((int)m_blockQueue.size() >= m_maxQueueSize) {
            if(i > 0)
                m_queueLock.mtNotify();
            m_queueLock.mtUnlock();
            return i;
        }
        m_blockQueue.push(tasks[i]);
    }

    m_queueLock.mtNotify();
    m_queueLock.mtUnlock();

    return tasks.size();
}

void CTP_Executor::shutdown()
{
    m_queueLock.mtLock();
    m_isShutdown = 0;
    m_queueLock.mtNotify();
    m_queueLock.mtUnlock();
}

int CTP_Executor::getQueueSize()
{
    return m_blockQueue.size();
}

CTP_Worker* CTP_Executor::getWorker()
{
    CTP_Worker* worker = NULL;
    m_workerHandle.m_executorLock.mtLock();
    if(m_workerHandle.m_workerIndex <= 0 && m_workerNum >= m_maxWorkers) {
        m_workerHandle.m_executorLock.mtWait();//wait worker complete.
    }

    if(m_workerHandle.m_workerIndex > 0) {
        worker = (CTP_Worker*)m_workerHandle.m_freeWorks[--m_workerHandle.m_workerIndex];
        m_workerHandle.m_freeWorks[m_workerHandle.m_workerIndex] = NULL;
    } else {
        worker = new CTP_Worker(&m_workerHandle);
        m_threadsManager.setRoutine(TPStartRoutine<CTP_Worker>);
        m_threadsManager.createThead(worker);
        m_workerNum ++;
    }
    m_workerHandle.m_executorLock.mtUnlock();

    return worker;
}

int CTP_Executor::getFreeThreadNum()
{
    int total = m_workerHandle.m_freeWorks.size();
    int freeNum = 0;
    for(int i = 0; i < total; ++i) {
        if(m_workerHandle.m_freeWorks[i] != NULL) {
            ++freeNum;
        }
    }

    return freeNum;
}

int CTP_Executor::getAllThreadNum()
{
    return m_workerHandle.m_allWorks.size();
}

int CTP_Executor::getRunThreadNum()
{
    int total = m_workerHandle.m_freeWorks.size();
    int ranNum = 0;
    for(int i = 0; i < total; ++i) {
        if(m_workerHandle.m_freeWorks[i] == NULL) {
            ++ranNum;
        }
    }

    return ranNum;
}
