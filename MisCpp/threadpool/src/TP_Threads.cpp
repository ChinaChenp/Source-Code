#include "TP_Threads.h"

#include <stdexcept>
#include <errno.h>

CTP_Threads::CTP_Threads()
{
	if (TP_SUCCESS != initAttribute()) {
		throw std::runtime_error("initialize thread attribute error.");
	}
	//m_pvPara = NULL;
}

CTP_Threads::~CTP_Threads()
{

}

void CTP_Threads::setRoutine(void* (fpFun)(void*))
{
	m_fpFun = fpFun;
}

//void CAhThreads::SetParameter(void* pvPara)
//{
//	m_pvPara = pvPara;
//}

pthread_t CTP_Threads::createThead(void* pvPara)
{
	if (0 != pthread_create(&m_iID, &m_stAttr, m_fpFun, (void*)pvPara)) {
		TP_ERROR("Create new thread error [%s].\n", strerror(errno));
		return 0;
	}

	m_vecID.push_back(m_iID);
	m_fpFun = NULL;
	initAttribute();

	return m_iID;
}

void CTP_Threads::jionALLThreads()
{
	for(u_int i = 0; i < m_vecID.size(); ++i) {
		pthread_join(m_vecID[i], NULL);
	}
}

void CTP_Threads::jionThread()
{
	pthread_join(m_iID, NULL);
}

int CTP_Threads::setThreadDetach()
{
	if (0 != pthread_attr_setdetachstate(&m_stAttr, PTHREAD_CREATE_DETACHED)) {
		TP_ERROR("%s\n", strerror(errno));
		return TP_FAILURE;
	}

	return TP_SUCCESS;
}

int CTP_Threads::initAttribute()
{
	if (0 != pthread_attr_init(&m_stAttr)) {
		TP_ERROR("%s\n", strerror(errno));
		return TP_FAILURE;
	}

	return TP_SUCCESS;
}

void CTP_Threads::setAttribute(void* pAttr)
{
	memcpy((void*)&m_stAttr, pAttr, sizeof(pthread_attr_t));

	return;
}

int CTP_Threads::destroyThread()
{
	if (0 != pthread_cancel(m_iID)) {
		TP_ERROR("%s\n", strerror(errno));
		return TP_FAILURE;
	}

	return TP_SUCCESS;
}

int CTP_Threads::destroyALLThreads()
{
	for(u_int i = 0; i < m_vecID.size(); ++i) {

		if (0 != pthread_cancel(m_vecID[i])) {
			TP_ERROR("%s\n", strerror(errno));
			return TP_FAILURE;
		}
	}

	return TP_SUCCESS;
}

