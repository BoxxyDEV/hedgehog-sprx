#pragma once

#include <stdint.h>

extern "C"
{
	int _sys_printf(const char *fmt, ...);
#define printf _sys_printf
	int _sys_snprintf(char *buffer, size_t len, const char *fmt, ...);
#define snprintf _sys_snprintf
	int _sys_sprintf(char *buffer, const char *fmt, ...);
#define sprintf _sys_sprintf
	int _sys_vsnprintf(char* buffer, std::size_t buf_size, const char* format, va_list arg);
#define vsnprintf _sys_vsnprintf
	void* _sys_malloc(size_t size);
#define malloc _sys_malloc
	void _sys_free(void* ptr);
#define free _sys_free

}