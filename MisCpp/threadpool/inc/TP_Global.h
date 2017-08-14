#ifndef	_TP_GLOBAL_H
#define	_TP_GLOBAL_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define	TP_UINT				    unsigned int
#define	TP_UCHAR				unsigned char
#define	TP_ULONG				unsigned long
#define	TP_USHORT				unsigned short
#define	TP_ULONGLONG			unsigned long long

#define	TP_BYTE16			16
#define	TP_BYTE32			32
#define	TP_BYTE64			64

#define	TP_BYTE128			128
#define	TP_BYTE256			256
#define	TP_BYTE512			512

#define	TP_KBYTES1			1024
#define	TP_KBYTES2			2048
#define	TP_KBYTES4			4096
#define	TP_KBYTES8			8192

#define	TP_BUFFER			512
#define	TP_PACKET			1024

/*system error number*/
#define	TP_SUCCESS			0
#define	TP_FAILURE			-1

/*net socket error number*/
#define TP_TIMEOUT			-2		//timeout
#define TP_PROTERR			-3		//protocol error
#define TP_CNNTERR			-4		//connect error

#define	TP_INFO(format, args...)	do {	\
	fprintf(stdout, "[INFO] %s %04d: ", __FILE__, __LINE__);	\
	fprintf(stdout, format, ##args);				\
} while (0)

#define	TP_WARN(format, args...)	do {				\
	fprintf(stdout, "[WARN] %s %04d: ", __FILE__, __LINE__);	\
	fprintf(stdout, format, ##args);				\
} while (0)

#define	TP_PRINT(format, args...)	do {				\
	fprintf(stdout, format, ##args);				\
	fflush(stdout);							\
} while (0)

#define	TP_ERROR(format, args...)	do {				\
	fprintf(stderr, "[ERROR] %s %04d: ", __FILE__, __LINE__);	\
	fprintf(stderr, format, ##args);				\
} while (0)

#define	TP_DEBUG(format, args...)	do {				\
	fprintf(stdout, "[DEBUG] %s %04d: ", __FILE__, __LINE__);	\
	fprintf(stdout, format, ##args);				\
	fflush(stdout);							\
} while (0)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TP_GLOBAL_H */
