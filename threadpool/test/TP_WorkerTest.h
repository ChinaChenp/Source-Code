#ifndef TP_WORKERTEST_H_
#define TP_WORKERTEST_H_

#include "TP_Worker.h"

#include <gtest/gtest.h>

class CMyTask : public CTP_Task {
public:
    CMyTask() {m_data = 0;}
    virtual ~CMyTask() {}

    int handle(int threadid) {
        m_data = threadid;

        return m_data;
    }

private:
    int m_data;
};

class CTP_WorkerTemp : public CTP_Worker {
public:
    CTP_WorkerTemp(TP_WORKER_HANDLE_S* workerHandle) : CTP_Worker(workerHandle)
    {m_workerHandle = workerHandle;}
    virtual ~CTP_WorkerTemp(){}

    int testCore(){
        CTP_Task* task = new CMyTask();
        setTask(task);
        //Core();
        //int result = task->getResult();
        int result = 0;
        delete task;
        return result;
    }

    int testShutdown(){
        shutdown();
        return 0;
    }

    int testSetTask(){
        setTask(NULL);
        return 0;
    }

    int testSaveWorker(){
        if(m_workerHandle->m_workerIndex > 0)
            --m_workerHandle->m_workerIndex;
        saveWorker();
        return m_workerHandle->m_workerIndex;
    }

    TP_WORKER_HANDLE_S* m_workerHandle;
};

class CTP_WorkerTest : public testing::Test {
public:
    CTP_WorkerTest();
    virtual ~CTP_WorkerTest();

    virtual void SetUp();
    virtual void TearDown();
    static void SetUpTestCase();
    static void TearDownTestCase();

    CTP_WorkerTemp* m_workerTemp;
    TP_WORKER_HANDLE_S* m_workerHandle;
};

#endif /* TP_WORKERTEST_H_ */
