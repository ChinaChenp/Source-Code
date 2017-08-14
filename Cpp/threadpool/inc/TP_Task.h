#ifndef TP_TASK_H_
#define TP_TASK_H_

#include "TP_Lock.h"

#define TP_TASK_STATUS      -100

class CTP_Task {
public:
    CTP_Task();
    virtual ~CTP_Task();

    virtual int handle(int threadid) = 0;
    int getResult();
    void setResult(int result);
    void taskStart();
    void taskEnd();

protected:
    int m_result;
    CTP_MtLock m_resultLock;
};

#endif /* TP_TASK_H_ */
