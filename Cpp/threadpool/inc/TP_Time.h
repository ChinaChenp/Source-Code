#ifndef _TP_TIME_H
#define	_TP_TIME_H

#include "TP_Global.h"

#include <sys/time.h>
#include <stdio.h>
#include <string.h>

class CTP_Time
{
public:
    CTP_Time();
	virtual ~CTP_Time();

	void timeOn();
	void timeOff();
	void displayTime();
	u_int getSeconds(){return m_uiSeconds;};
	u_int getMicSeconds(){return m_uiMicSeconds;};
	struct timeval getTimeval(){return m_stOn;};

private:
	struct timeval m_stOn;
	struct timeval m_stOff;

	u_int m_uiSeconds;
	u_int m_uiMicSeconds;
};

#endif /* _TP_TIME_H */
