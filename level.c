#include "dock.h"
#include <stdio.h>
#include <string.h>

Ship ship;
Station st;
int level_i, paused, outcome;
float hold, tsec, grav;

const Level levels[NLEVEL] = {
    {"1 wide bay", 80, 160, 0, 100, 320, 160, 70, 40, 36, 28, -70, 0, 0, 0, 0, 18},
    {"2 tight", 70, 200, 0.2f, 90, 340, 140, 60, 36, 22, 22, -62, 0, 0, 0, 0, 14},
    {"3 drifter", 60, 80, 0, 90, 300, 200, 64, 38, 28, 24, -66, 0, 12, 0, 0, 16},
    {"4 side bay", 90, 240, -0.4f, 85, 300, 100, 50, 50, 24, 22, 0, 52, 0, 0, 0, 14},
    {"5 spinner", 50, 260, 0.5f, 80, 280, 120, 55, 40, 24, 20, -58, 0, 6, 0.25f, 8, 13},
};

void level_load(int i)
{
    const Level *L;
    if (i < 0)
        i = 0;
    if (i >= NLEVEL)
        i = NLEVEL - 1;
    level_i = i;
    L = &levels[i];
    memset(&ship, 0, sizeof ship);
    memset(&st, 0, sizeof st);
    ship.x = L->sx;
    ship.y = L->sy;
    ship.rot = L->srot;
    ship.fuel = L->fuel;
    st.x = L->tx;
    st.y = L->ty;
    st.hw = L->tw;
    st.hh = L->th;
    st.bayx = L->bayx;
    st.bayy = L->bayy;
    st.bayw = L->bayw;
    st.bayh = L->bayh;
    st.vx = L->tvx;
    st.om = L->tom;
    grav = L->grav;
    hold = 0;
    tsec = 0;
    outcome = 0;
    paused = 0;
    {
        char b[80];
        snprintf(b, sizeof b, "level %d %s", i + 1, L->name);
        log_line(b);
    }
}
