#ifndef TP_LOCK_H_
#define TP_LOCK_H_

#include <pthread.h>
#include <assert.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>

#include "TP_Global.h"

#define TP_LOCK_BUSY		1

class CTP_Lock
{
public:
    CTP_Lock();
	virtual ~CTP_Lock();

	virtual void* getLock() { return m_pLock; }
	virtual bool destroyCond(){return !pthread_cond_destroy(&m_stCond);}

	/*virtual void deleteLock()
	{
		if(m_pLock) {
			delete m_pLock;
			m_pLock = NULL;
		}
	}

	virtual void deleteAttr()
	{
		if(m_pAttr) {
			delete m_pAttr;
			m_pAttr = NULL;
		}
	}*/

protected:
	void* m_pLock;
	void* m_pAttr;
	pthread_cond_t m_stCond;
private:
};

class CTP_MtLock : public CTP_Lock
{
public:
    CTP_MtLock(void* pLock = NULL);
	virtual ~CTP_MtLock();

	bool initLock();
	bool initAttr();
	bool destroyAttr();
	bool setProcessShare();
	bool destroyLock();

	bool mtLock();
	int mtTryLock();
	bool mtUnlock();
	void mtWait();
	void mtNotify();
protected:
private:

};

class CTP_RWLock : public CTP_Lock
{
public:
    CTP_RWLock(void* pLock = NULL);
	virtual ~CTP_RWLock();

	bool initLock();
	bool initAttr();
	bool destroyAttr();
	bool destroyLock();

	bool readLock();
	bool writeLock();
	bool rwUnLock();
protected:
private:
};

#endif /* TP_LOCK_H_ */
