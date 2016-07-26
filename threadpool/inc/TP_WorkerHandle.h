#ifndef TP_WORKERHANDLE_H_
#define TP_WORKERHANDLE_H_

#include "TP_Lock.h"
#include <vector>

typedef struct WorkerHandle {
    u_int m_count;
    int m_workerIndex;
    std::vector<void*> m_freeWorks;
    CTP_MtLock m_executorLock;
    std::vector<void*> m_allWorks;

    WorkerHandle()
    {
        m_count = 0;
        m_workerIndex = 0;
    }
}TP_WORKER_HANDLE_S;


#endif /* TP_WORKERHANDLE_H_ */
