/*
 * TP_TaskTest.h
 *
 *  Created on: Nov 27, 2014
 *      Author: root
 */

#ifndef TP_TASKTEST_H_
#define TP_TASKTEST_H_

#include <gtest/gtest.h>
#include "TP_Task.h"

class CTP_TaskTemp : public CTP_Task{
public:
    CTP_TaskTemp();
    virtual ~CTP_TaskTemp();

    int testGetResult(){
        return getResult();
    }

    virtual int handle(int threadid){
        return threadid;
    }

};

class CTP_TaskTest : public testing::Test {
public:
    CTP_TaskTest();
    virtual ~CTP_TaskTest();

    virtual void SetUp();
    virtual void TearDown();
    static void SetUpTestCase();
    static void TearDownTestCase();

    CTP_TaskTemp* m_taskTemp;
};

#endif /* TP_TASKTEST_H_ */
