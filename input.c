#include "dock.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>

static struct termios oldt;
static int raw;

void input_open(int w, int h)
{
    struct termios t;
    (void)w;
    (void)h;
    tcgetattr(0, &oldt);
    t = oldt;
    t.c_lflag &= ~(ICANON | ECHO);
    t.c_cc[VMIN] = 0;
    t.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &t);
    raw = 1;
}

void input_close(void)
{
    if (raw)
        tcsetattr(0, TCSANOW, &oldt);
}

int input_poll(int *keys, int *mx, int *my, int *click)
{
    unsigned char buf[16];
    int n, i;
    *mx = *my = *click = 0;
    n = read(0, buf, sizeof buf);
    if (n <= 0)
        return 0;
    for (i = 0; i < n; i++) {
        unsigned char c = buf[i];
        if (c == 'q' || c == 'Q')
            keys[0] |= 1;
        else if (c == 'p' || c == 'P')
            keys[1] ^= 1;
        else if (c == 'r' || c == 'R')
            keys[2] = 1;
        else if (c == 'n' || c == 'N')
            keys[3] = 1;
        else if (c == 'w' || c == 'W' || c == ' ')
            keys[4] = 1;
        else if (c == 'a' || c == 'A')
            keys[5] = 1;
        else if (c == 'd' || c == 'D')
            keys[6] = 1;
        else if (c == 'j' || c == 'J')
            keys[7] = 1;
        else if (c == 'l' || c == 'L')
            keys[8] = 1;
        else if (c == 'i' || c == 'I')
            keys[9] = 1;
        else if (c == 'k' || c == 'K')
            keys[10] = 1;
        else if (c == 's' || c == 'S')
            keys[11] = 1;
        else if (c == 0x1b && i + 2 < n && buf[i + 1] == '[') {
            if (buf[i + 2] == 'A')
                keys[4] = 1;
            if (buf[i + 2] == 'D')
                keys[5] = 1;
            if (buf[i + 2] == 'C')
                keys[6] = 1;
            i += 2;
        }
    }
    return 1;
}
