/*
 * TP_ExecutorTest.cpp
 *
 *  Created on: Nov 27, 2014
 *      Author: root
 */

#include "TP_ExecutorTest.h"

CTP_ExecutorTest::CTP_ExecutorTest() {
    // TODO Auto-generated constructor stub
    m_executorTemp = NULL;
}

CTP_ExecutorTest::~CTP_ExecutorTest() {
    // TODO Auto-generated destructor stub
}

void CTP_ExecutorTest::SetUp()
{
    m_executorTemp = new CTP_ExecutorTemp;
}

void CTP_ExecutorTest::TearDown()
{
    if(m_executorTemp) {
        delete m_executorTemp;
        m_executorTemp = NULL;
    }
}

void CTP_ExecutorTest::SetUpTestCase()
{

}

void CTP_ExecutorTest::TearDownTestCase()
{

}

TEST_F(CTP_ExecutorTest, Core)
{
    EXPECT_EQ(m_executorTemp->testCore(), 0);
}

TEST_F(CTP_ExecutorTest, execute)
{
    std::vector<CTP_Task*> tasks;
    for(int i = 0; i < 10; ++i) {
        CMyTask2* task = new CMyTask2;
        EXPECT_EQ(m_executorTemp->execute(task), 0);
        tasks.push_back(task);
    }

    CMyTask2* task = new CMyTask2;
    EXPECT_EQ(m_executorTemp->execute(task), -10);

    for(int i = 0; i < 10; ++i) {
        delete tasks[i];
    }
    delete task;
}

TEST_F(CTP_ExecutorTest, multiExecute)
{
    std::vector<CTP_Task*> tasks;
    for(int i = 0; i < 10; ++i) {
        CMyTask2* task = new CMyTask2;
        tasks.push_back(task);
    }

    EXPECT_EQ(m_executorTemp->execute(tasks), 10);

    for(int i = 0; i < 10; ++i) {
        delete tasks[i];
    }
    tasks.clear();
    CMyTask2* task = new CMyTask2;
    tasks.push_back(task);
    EXPECT_EQ(m_executorTemp->execute(tasks), 0);
    delete task;
}

TEST_F(CTP_ExecutorTest, getWorker)
{
    EXPECT_NE(m_executorTemp->testGetWorker(), (CTP_Worker*)NULL);
}
