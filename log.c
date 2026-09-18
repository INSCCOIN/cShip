#include "dock.h"
#include <stdio.h>
#include <unistd.h>

#define LOGPATH "/home/cdock.log"
static FILE *f;

void log_init(void)
{
    unlink(LOGPATH);
    f = fopen(LOGPATH, "w");
    log_line("cDock start");
}

void log_line(const char *s)
{
    if (!f)
        return;
    fprintf(f, "%s\n", s);
    fflush(f);
}

void log_close(void)
{
    if (!f)
        return;
    log_line("cDock exit");
    fclose(f);
    f = NULL;
}
