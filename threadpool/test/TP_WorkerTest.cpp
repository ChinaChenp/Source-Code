#include "TP_WorkerTest.h"

CTP_WorkerTest::CTP_WorkerTest() {
    // TODO Auto-generated constructor stub
    m_workerTemp = NULL;
}

CTP_WorkerTest::~CTP_WorkerTest() {
    // TODO Auto-generated destructor stub
}

void CTP_WorkerTest::SetUp()
{
    m_workerHandle = new TP_WORKER_HANDLE_S;
    m_workerTemp = new CTP_WorkerTemp(m_workerHandle);
}

void CTP_WorkerTest::TearDown()
{
    if(m_workerTemp) {
        delete m_workerTemp;
        m_workerTemp = NULL;
    }

    if(m_workerHandle) {
        delete m_workerHandle;
        m_workerHandle = NULL;
    }
}

void CTP_WorkerTest::SetUpTestCase()
{

}

void CTP_WorkerTest::TearDownTestCase()
{

}

TEST_F(CTP_WorkerTest, Core)
{
    EXPECT_EQ(m_workerTemp->testCore(), 0);
}

TEST_F(CTP_WorkerTest, shutdown)
{
    EXPECT_EQ(m_workerTemp->testShutdown(), 0);
}

TEST_F(CTP_WorkerTest, setTask)
{
    EXPECT_EQ(m_workerTemp->testSetTask(), 0);
}

TEST_F(CTP_WorkerTest, saveWorker)
{
    EXPECT_EQ(m_workerTemp->testSaveWorker(), 1);
}
