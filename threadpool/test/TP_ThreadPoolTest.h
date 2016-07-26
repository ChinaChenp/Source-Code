#ifndef TP_THREADPOOLTEST_H_
#define TP_THREADPOOLTEST_H_

#include "TP_ThreadPool.h"

#include <gtest/gtest.h>

class CMyTask1 : public CTP_Task {
public:
    CMyTask1() {m_data = 0;}
    virtual ~CMyTask1() {}

    int handle(int threadid) {
        //m_data = threadid;

        return ++m_data;
    }

private:
    int m_data;
};

class CTP_ThreadPoolTest : public testing::Test {
public:
    CTP_ThreadPoolTest();
    virtual ~CTP_ThreadPoolTest();

    virtual void SetUp();
    virtual void TearDown();
    static void SetUpTestCase();
    static void TearDownTestCase();

    CTP_ThreadPool* m_threadPool;
};

#endif /* TP_THREADPOOLTEST_H_ */
