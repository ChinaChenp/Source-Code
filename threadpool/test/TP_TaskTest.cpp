/*
 * TP_TaskTest.cpp
 *
 *  Created on: Nov 27, 2014
 *      Author: root
 */

#include "TP_TaskTest.h"

CTP_TaskTemp::CTP_TaskTemp() {
    // TODO Auto-generated constructor stub

}

CTP_TaskTemp::~CTP_TaskTemp() {
    // TODO Auto-generated destructor stub
}

CTP_TaskTest::CTP_TaskTest(){
    m_taskTemp = NULL;
}

CTP_TaskTest::~CTP_TaskTest(){
    /*if(m_taskTemp) {
        delete m_taskTemp;
        m_taskTemp = NULL;
    }*/
}

void CTP_TaskTest::SetUp()
{
    m_taskTemp = new CTP_TaskTemp();
}

void CTP_TaskTest::TearDown()
{
    if(m_taskTemp) {
        delete m_taskTemp;
        m_taskTemp = NULL;
    }
}

void CTP_TaskTest::SetUpTestCase()
{

}

void CTP_TaskTest::TearDownTestCase()
{

}

TEST_F(CTP_TaskTest, getResult)
{
    m_taskTemp->setResult(10);
    EXPECT_EQ(m_taskTemp->getResult(), 10);

    m_taskTemp->setResult(1);
    EXPECT_EQ(m_taskTemp->getResult(), 1);
}

TEST_F(CTP_TaskTest, handle)
{
    EXPECT_EQ(m_taskTemp->handle(5), 5);
}
