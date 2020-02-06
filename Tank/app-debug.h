#ifndef __APP_DEBUG_H__
#define __APP_DEBUG_H__

#include <cstdio>

#ifdef APP_DEBUG
#define LOG_INTO(format, ...) std::printf((format), ##__VA_ARGS__)
#else
#define LOG_INFO(format, ...)
#endif // APP_DEBUG

#endif // __APP_DEBUG_H__
