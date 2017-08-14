#include "TP_Time.h"

CTP_Time::CTP_Time()
{
	memset(&m_stOn, '\0', sizeof(struct timeval));
	memset(&m_stOff, '\0', sizeof(struct timeval));
}

CTP_Time::~CTP_Time()
{
}

void CTP_Time::timeOn()
{
	gettimeofday(&m_stOn, NULL);

	return;
}

void CTP_Time::timeOff()
{
	gettimeofday(&m_stOff, NULL);
	if (m_stOff.tv_usec == m_stOn.tv_usec) {
		m_uiSeconds = m_stOff.tv_sec - m_stOn.tv_sec;
		m_uiMicSeconds = 0;
	}
	else if (m_stOff.tv_usec > m_stOn.tv_usec) {
		m_uiSeconds = m_stOff.tv_sec - m_stOn.tv_sec;
		m_uiMicSeconds = m_stOff.tv_usec - m_stOn.tv_usec;
	}
	else {
		m_uiSeconds = m_stOff.tv_sec - m_stOn.tv_sec - 1;
		m_uiMicSeconds = 1000000L - m_stOn.tv_usec + m_stOff.tv_usec;
	}
	return;
}

void CTP_Time::displayTime()
{
	printf("Second: %d MicorSecond: %d\n", m_uiSeconds, m_uiMicSeconds);
	return;
}
