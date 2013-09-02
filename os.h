#ifndef OS_H_INCLUDED
#define OS_H_INCLUDED

namespace OS
{
    unsigned long getTime();
    int init();
    void refresh();
    void deinit();
}

#ifdef _WIN32
#include "oswin.h"
#else
#include "oslinux.h"
#endif

#endif // OS_H_INCLUDED
