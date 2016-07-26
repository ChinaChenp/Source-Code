#include "TP_Task.h"

CTP_Task::CTP_Task() {
    // TODO Auto-generated constructor stub

    m_result = TP_TASK_STATUS;
}

CTP_Task::~CTP_Task() {
    // TODO Auto-generated destructor stub
}

int CTP_Task::getResult()
{
    m_resultLock.mtLock();

    if(m_result == TP_TASK_STATUS) {
        m_resultLock.mtWait();
    }

    int result = m_result;
    m_result = TP_TASK_STATUS;

    m_resultLock.mtUnlock();

    return result;
}

void CTP_Task::setResult(int result)
{
    m_result = result;
}

void CTP_Task::taskStart()
{
    m_resultLock.mtLock();
}

void CTP_Task::taskEnd()
{
    m_resultLock.mtNotify();
    m_resultLock.mtUnlock();
}
