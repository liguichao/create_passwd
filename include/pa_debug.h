#ifndef __PA_DEBUG_H
#define __PA_DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

	/*includes ----------------------- */
#include <stdio.h>

#define		__PA_ASSERT__
#define		__PA_ERROR__
#if 1
#define		__PA_DEBUG__
#define		__PA_INFO__
#define		__PA_PRINT__
#endif

#undef PA_ASSERT					   /* undef it, just in case */
#ifdef __PA_ASSERT__				   /* debugging assertions */
#define PA_ASSERT(expr) \
	if (!(expr)) { \
		printf("[%s %s %d] " "\033[1;31m", __FILE__, __func__, __LINE__); \
		printf("Assertion failed! (%s)\n", #expr); \
		printf("\033[m" "\r\n"); \
		return -1;\
	}
#else
#define PA_ASSERT(expr)
#endif								   /* end of __PA_ASSERT__ */

#undef PA_ERROR						   /* undef it, just in case */
#ifdef __PA_ERROR__
#define PA_ERROR(fmt, args...) \
	do{ \
		printf("[%s %d] " "\033[1;31m",__FUNCTION__,__LINE__); \
		printf(fmt, ## args); \
		printf("\033[m" "\r\n"); \
	}while(0)
#else
#define PA_ERROR(fmt, args...)		   /* not debugging: nothing */
#endif								   /* end of __PA_ERROR__ */

#undef PA_DEBUG						   /* undef it, just in case */
#ifdef __PA_DEBUG__
#define PA_DEBUG(fmt, args...) \
	do{ \
		printf("[%s %d] " "\033[1;34m",__FUNCTION__,__LINE__); \
		printf(fmt, ## args); \
		printf("\033[m" "\r\n"); \
	}while(0)
#else
#define PA_DEBUG(fmt, args...)		   /* not debugging: nothing */
#endif								   /* end of __PA_DEBUG__ */

#undef PA_INFO						   /* undef it, just in case */
#ifdef __PA_INFO__
#define PA_INFO(fmt, args...) \
	do{ \
		printf("[%s %d] " "\033[1;32m",__FUNCTION__,__LINE__); \
		printf(fmt, ## args); \
		printf("\033[m" "\r\n"); \
	}while(0)
#else
#define PA_INFO(fmt, args...)		   /* not debugging: nothing */
#endif								   /* end of __PA_INFO__ */

	int pa_print_hex(const unsigned char *p_data, unsigned int len);
	int pa_print_data(const int *p_data, unsigned int len);
	int pa_print_string(const char *p_data);

#ifdef __cplusplus
}
#endif
#endif								   /* END OF  __PA_DEBUG_H */
