/*
 * AhLock.cpp
 *
 *  Created on: 2012-10-23
 *      Author: root
 */

#include "TP_Lock.h"

#include <stdexcept>
#include <errno.h>

CTP_Lock::CTP_Lock() {
	// TODO Auto-generated constructor stub

	if( 0 != pthread_cond_init(&m_stCond, 0)) {
		throw std::runtime_error("pthread_cond_init error.");
	}

}

CTP_Lock::~CTP_Lock() {
	// TODO Auto-generated destructor stub
	destroyCond();
}

CTP_MtLock::CTP_MtLock(void* pLock)
{
	if(pLock) {
		m_pLock = pLock;
	} else {
		m_pAttr = new pthread_mutexattr_t;
		if(!initAttr()) {
			throw std::runtime_error("initialization mutex lock attribute error.");
		}

		m_pLock = new pthread_mutex_t;
		if(!initLock()) {
			throw std::runtime_error("initialization mutex lock error.");
		}
	}
}

CTP_MtLock::~CTP_MtLock()
{
	destroyAttr();
	destroyLock();

	if(m_pLock) {
		delete (pthread_mutex_t*)m_pLock;
		m_pLock = NULL;
	}

	if(m_pAttr) {
		delete (pthread_mutexattr_t*)m_pAttr;
		m_pAttr = NULL;
	}
}

bool CTP_MtLock::initLock()
{
	return !pthread_mutex_init((pthread_mutex_t*)m_pLock, (pthread_mutexattr_t*)m_pAttr);
}

bool CTP_MtLock::mtLock()
{
	if(!m_pLock) {
		//AH_ERROR("pLock is NULL.\n");
		return false;
	}

	return !pthread_mutex_lock((pthread_mutex_t*)m_pLock);
}

bool CTP_MtLock::mtUnlock()
{
	if(!m_pLock) {
		//AH_ERROR("pLock is NULL.\n");
		return false;
	}

	return !pthread_mutex_unlock((pthread_mutex_t*)m_pLock);
}

void CTP_MtLock::mtWait()
{
	if(!m_pLock) {
		//AH_ERROR("pLock is NULL.\n");
		return;
	}

	pthread_cond_wait(&m_stCond, (pthread_mutex_t*)CTP_Lock::m_pLock);
}

void CTP_MtLock::mtNotify()
{
	pthread_cond_signal(&m_stCond);
}

bool CTP_MtLock::initAttr()
{
	if(!m_pAttr) {
		//AH_ERROR("m_pAttr is NULL.\n");
		return false;
	}
	return !pthread_mutexattr_init((pthread_mutexattr_t*)m_pAttr);
}


bool CTP_MtLock::destroyAttr()
{
	if(!m_pAttr) {
		//AH_ERROR("m_pAttr is NULL.\n");
		return false;
	}
	return !pthread_mutexattr_destroy((pthread_mutexattr_t*)m_pAttr);
}

bool CTP_MtLock::setProcessShare()
{
	if(!m_pAttr) {
		//AH_ERROR("m_pstAttr is NULL.\n");
		return false;
	}
	return !pthread_mutexattr_setpshared((pthread_mutexattr_t*)m_pAttr, PTHREAD_PROCESS_SHARED);
}

bool CTP_MtLock::destroyLock()
{
	if(!m_pLock) {
		//AH_ERROR("pLock is NULL.\n");
		return false;
	}
	return !pthread_mutex_destroy((pthread_mutex_t*)m_pLock);
}

/*
 * 1 busy 0 success   other error.
 */
int CTP_MtLock::mtTryLock()
{
	if(!m_pLock) {
		//AH_ERROR("pLock is NULL.\n");
		return TP_FAILURE;
	}

	//0success  1busy
	int ret = pthread_mutex_trylock((pthread_mutex_t*)m_pLock);

	return ret;
}

CTP_RWLock::CTP_RWLock(void* pLock)
{
	if(pLock) {
		m_pLock = pLock;
	} else {
		m_pAttr = new pthread_rwlockattr_t;
		if(!initAttr()) {
			throw std::runtime_error("initialization rwlock attribute error.");
		}

		m_pLock = (pthread_rwlock_t*)new pthread_rwlock_t;
		if(!initLock()) {
			throw std::runtime_error("initialization rwlock error.");
		}
	}
}

CTP_RWLock::~CTP_RWLock()
{
	destroyAttr();
	destroyLock();

	if(m_pLock) {
		delete (pthread_rwlock_t*)m_pLock;
		m_pLock = NULL;
	}

	if(m_pAttr) {
		delete (pthread_rwlockattr_t*)m_pAttr;
		m_pAttr = NULL;
	}
}

bool CTP_RWLock::initLock()
{
	return !pthread_rwlock_init((pthread_rwlock_t*)m_pLock, (pthread_rwlockattr_t*)m_pAttr);
}

bool CTP_RWLock::initAttr()
{
	if(!m_pAttr) {
		//AH_ERROR("m_pstAttr is NULL.\n");
		return false;
	}
	return !pthread_rwlockattr_init((pthread_rwlockattr_t*)m_pAttr);
}

bool CTP_RWLock::destroyAttr()
{
	if(!m_pAttr) {
		//AH_ERROR("m_pstAttr is NULL.\n");
		return false;
	}
	return !pthread_rwlockattr_destroy((pthread_rwlockattr_t*)m_pAttr);
}

bool CTP_RWLock::destroyLock()
{
	if(!m_pLock) {
		//AH_ERROR("pLock is NULL.\n");
		return false;
	}
	return !pthread_rwlock_destroy((pthread_rwlock_t*)m_pLock);
}

bool CTP_RWLock::readLock()
{
	if (NULL == m_pLock) {
		//AH_ERROR("pLock is NULL.\n");
		return false;
	}
	return !pthread_rwlock_rdlock((pthread_rwlock_t*)CTP_Lock::m_pLock);
}

bool CTP_RWLock::writeLock()
{
	if (NULL == m_pLock) {
		//AH_ERROR("pLock is NULL.\n");
		return false;
	}
	return !pthread_rwlock_wrlock((pthread_rwlock_t*)CTP_Lock::m_pLock);
}

bool CTP_RWLock::rwUnLock()
{
	if (NULL == m_pLock) {
		//AH_ERROR("pLock is NULL.\n");
		return false;
	}
	return !pthread_rwlock_unlock((pthread_rwlock_t*)CTP_Lock::m_pLock);
}
