/*
 * TP_ExecutorTest.h
 *
 *  Created on: Nov 27, 2014
 *      Author: root
 */

#ifndef TP_EXECUTORTEST_H_
#define TP_EXECUTORTEST_H_

#include "TP_Executor.h"

#include <gtest/gtest.h>

class CMyTask2 : public CTP_Task {
public:
    CMyTask2() {m_data = 0;}
    virtual ~CMyTask2() {}

    int handle(int threadid) {
        m_data = threadid;

        return m_data;
    }

private:
    int m_data;
};

class CTP_ExecutorTemp : public CTP_Executor{
public:
    CTP_ExecutorTemp()
    :CTP_Executor(10,10)
    {}
    virtual ~CTP_ExecutorTemp(){}

    int testCore(){
        CMyTask2* task = new CMyTask2;
        execute(task);
        shutdown();
        Core();
        int result = task->getResult();
        delete task;
        return result;
    }

    int testExecute(CTP_Task* task){
        return execute(task);
    }

    int testExecute(std::vector<CTP_Task*>& tasks){
        return execute(tasks);
    }

    CTP_Worker* testGetWorker(){
        return getWorker();
    }
};

class CTP_ExecutorTest  : public testing::Test{
public:
    CTP_ExecutorTest();
    virtual ~CTP_ExecutorTest();

    virtual void SetUp();
    virtual void TearDown();
    static void SetUpTestCase();
    static void TearDownTestCase();

    CTP_ExecutorTemp* m_executorTemp;
};

#endif /* TP_EXECUTORTEST_H_ */
