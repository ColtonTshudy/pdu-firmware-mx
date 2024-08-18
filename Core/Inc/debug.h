/**
 * @file debug.h
 * @author your name (you@domain.com)
 * @brief Definition of macros and functions related to debugging.
 * @version 0.1
 * @date 2024-08-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */

// Comment this out to disable printing of debug messages to LPUART1
#define DEBUG_MODE

#ifdef DEBUG_MODE
#	define LOG_DBG(_fmt, ...)                                                                     \
		do                                                                                         \
		{                                                                                          \
			printf(" [LOG] " _fmt "\r\n", ##__VA_ARGS__);                                          \
		} while(0)
#else
#	define LOG(_fmt, ...)
#endif