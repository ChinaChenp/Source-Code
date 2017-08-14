#include "TP_ThreadPoolTest.h"

CTP_ThreadPoolTest::CTP_ThreadPoolTest() {
    // TODO Auto-generated constructor stub
    m_threadPool = NULL;
}

CTP_ThreadPoolTest::~CTP_ThreadPoolTest() {
    // TODO Auto-generated destructor stub
}

void CTP_ThreadPoolTest::SetUp()
{
    m_threadPool = new CTP_ThreadPool(10, 10);
}

void CTP_ThreadPoolTest::TearDown()
{
    if(m_threadPool) {
        delete m_threadPool;
        m_threadPool = NULL;
    }
}

void CTP_ThreadPoolTest::SetUpTestCase()
{

}

void CTP_ThreadPoolTest::TearDownTestCase()
{

}

TEST_F(CTP_ThreadPoolTest, execute)
{
    CMyTask1* task = new CMyTask1;
    EXPECT_EQ(m_threadPool->execute(task), 0);

    EXPECT_EQ(task->getResult(), 1);
    delete task;
}

TEST_F(CTP_ThreadPoolTest, multiExecute)
{
    std::vector<CTP_Task*> tasks;
    for(int i = 0; i < 10; ++i) {
        CMyTask1* task = new CMyTask1;
        tasks.push_back(task);
    }

    EXPECT_EQ(m_threadPool->execute(tasks), 10);

    for(int i = 0; i < 10; ++i) {
        EXPECT_EQ(tasks[i]->getResult(), 1);
        delete tasks[i];
    }
}

TEST_F(CTP_ThreadPoolTest, getAllThreadNum)
{
    EXPECT_EQ(m_threadPool->getAllThreadNum(), 0);
}

TEST_F(CTP_ThreadPoolTest, getFreeThreadNum)
{
    EXPECT_EQ(m_threadPool->getFreeThreadNum(), 0);
}

TEST_F(CTP_ThreadPoolTest, getMaxQueueSize)
{
    EXPECT_EQ(m_threadPool->getMaxQueueSize(), 10);
}

TEST_F(CTP_ThreadPoolTest, getMaxThreadNum)
{
    EXPECT_EQ(m_threadPool->getMaxThreadNum(), 10);
}

TEST_F(CTP_ThreadPoolTest, getRunThreadNum)
{
    EXPECT_EQ(m_threadPool->getRunThreadNum(), 0);
}
