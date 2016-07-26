#ifndef TP_THREADS_H_
#define TP_THREADS_H_

#include "TP_Global.h"

#include <pthread.h>
#include <vector>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>

template <class T>
void* TPStartRoutine(void *pvPrms)
{
    ((T *)(pvPrms))->Core();
    return pvPrms;
}

class CTP_Threads{
public:
    CTP_Threads();
	virtual ~CTP_Threads();

	void setRoutine(void* (fpFun)(void*));
	//void SetParameter(void* pvPara);
	pthread_t createThead(void* pvPara);

	void jionALLThreads();
	void jionThread();

	int setThreadDetach();
	int initAttribute();
	void setAttribute(void* pAttr);

	int destroyThread();
	int destroyALLThreads();
protected:

private:
	pthread_t m_iID;
	pthread_attr_t m_stAttr;
	std::vector<pthread_t> m_vecID;
	void* (*m_fpFun)(void *);
};




#endif /* TP_THREADS_H_ */
