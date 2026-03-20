/* Xbox GDK POSIX name thunks — replaces oldnames.lib
 *
 * On desktop Windows, oldnames.lib provides POSIX-compatible function
 * aliases (open -> _open, read -> _read, etc.). The Xbox GDK doesn't
 * ship oldnames.lib, so we provide equivalent thunks here.
 *
 * These functions are marked __declspec(dllexport) so the linker
 * generates __imp_xxx thunks that satisfy dllimport references from
 * other translation units compiled with _CRT_NONSTDC_NO_DEPRECATE.
 *
 * DO NOT include pyconfig.h or Python.h in this file — those define
 * _CRT_NONSTDC_NO_DEPRECATE which causes the CRT headers to declare
 * these names as __declspec(dllimport), conflicting with our exports.
 */

#ifdef _GAMING_XBOX

/* Prevent CRT headers from declaring POSIX names as dllimport */
#define _CRT_DECLARE_NONSTDC_NAMES 0

#include <io.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdarg.h>
#include <wchar.h>
#include <sys/stat.h>
#include <sys/types.h>

__declspec(dllexport) int __cdecl open(const char *path, int oflag, ...) {
    int pmode = 0;
    if (oflag & _O_CREAT) {
        va_list ap;
        va_start(ap, oflag);
        pmode = va_arg(ap, int);
        va_end(ap);
    }
    return _open(path, oflag, pmode);
}

__declspec(dllexport) int __cdecl read(int fd, void *buf, unsigned int count) {
    return _read(fd, buf, count);
}

__declspec(dllexport) int __cdecl write(int fd, const void *buf, unsigned int count) {
    return _write(fd, buf, count);
}

__declspec(dllexport) int __cdecl close(int fd) {
    return _close(fd);
}

__declspec(dllexport) int __cdecl dup(int fd) {
    return _dup(fd);
}

__declspec(dllexport) int __cdecl dup2(int fd1, int fd2) {
    return _dup2(fd1, fd2);
}

__declspec(dllexport) FILE * __cdecl fdopen(int fd, const char *mode) {
    return _fdopen(fd, mode);
}

__declspec(dllexport) int __cdecl fileno(FILE *stream) {
    return _fileno(stream);
}

__declspec(dllexport) int __cdecl isatty(int fd) {
    return _isatty(fd);
}

__declspec(dllexport) long __cdecl lseek(int fd, long offset, int origin) {
    return _lseek(fd, offset, origin);
}

__declspec(dllexport) int __cdecl umask(int pmode) {
    return _umask(pmode);
}

__declspec(dllexport) int __cdecl wcsicmp(const wchar_t *s1, const wchar_t *s2) {
    return _wcsicmp(s1, s2);
}

#endif /* _GAMING_XBOX */
