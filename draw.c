#include "dock.h"
#include "fb.h"
#include <math.h>
#include <stdio.h>

void ship_draw(int camx, int camy, int thrust)
{
    float c = cosf(ship.rot), s = sinf(ship.rot);
    int x = (int)ship.x - camx, y = (int)ship.y - camy;
    int x0 = x + (int)(10 * c), y0 = y + (int)(10 * s);
    int x1 = x + (int)(-7 * c - 5 * s), y1 = y + (int)(-7 * s + 5 * c);
    int x2 = x + (int)(-7 * c + 5 * s), y2 = y + (int)(-7 * s - 5 * c);
    uint16_t col = outcome == 2 ? rgb565(200, 40, 40) : rgb565(240, 240, 255);
    line(x0, y0, x1, y1, col);
    line(x0, y0, x2, y2, col);
    line(x1, y1, x2, y2, col);
    if (thrust && ship.fuel > 0 && !outcome) {
        int xe = x + (int)(-12 * c), ye = y + (int)(-12 * s);
        line(x1, y1, xe, ye, rgb565(255, 140, 20));
        line(x2, y2, xe, ye, rgb565(255, 80, 0));
    }
}

void station_draw(int camx, int camy)
{
    float c = cosf(st.rot), s = sinf(st.rot);
    int k;
    float cx[4], cy[4];
    float hx = st.hw, hy = st.hh;
    uint16_t hull = rgb565(160, 160, 170), bay = rgb565(220, 180, 40);
    cx[0] = -hx;
    cy[0] = -hy;
    cx[1] = hx;
    cy[1] = -hy;
    cx[2] = hx;
    cy[2] = hy;
    cx[3] = -hx;
    cy[3] = hy;
    for (k = 0; k < 4; k++) {
        float wx = st.x + cx[k] * c - cy[k] * s;
        float wy = st.y + cx[k] * s + cy[k] * c;
        float wx2 = st.x + cx[(k + 1) & 3] * c - cy[(k + 1) & 3] * s;
        float wy2 = st.y + cx[(k + 1) & 3] * s + cy[(k + 1) & 3] * c;
        line((int)wx - camx, (int)wy - camy, (int)wx2 - camx, (int)wy2 - camy, hull);
    }
    {
        float bx[4] = {st.bayx - st.bayw * 0.5f, st.bayx + st.bayw * 0.5f,
                       st.bayx + st.bayw * 0.5f, st.bayx - st.bayw * 0.5f};
        float by[4] = {st.bayy - st.bayh * 0.5f, st.bayy - st.bayh * 0.5f,
                       st.bayy + st.bayh * 0.5f, st.bayy + st.bayh * 0.5f};
        for (k = 0; k < 4; k++) {
            float wx = st.x + bx[k] * c - by[k] * s;
            float wy = st.y + bx[k] * s + by[k] * c;
            float wx2 = st.x + bx[(k + 1) & 3] * c - by[(k + 1) & 3] * s;
            float wy2 = st.y + bx[(k + 1) & 3] * s + by[(k + 1) & 3] * c;
            line((int)wx - camx, (int)wy - camy, (int)wx2 - camx, (int)wy2 - camy, bay);
        }
    }
}

void hud_draw(void)
{
    char b[80];
    float spd = sqrtf(ship.vx * ship.vx + ship.vy * ship.vy);
    int fw;
    uint16_t face = rgb565(40, 40, 55), wh = rgb565(230, 230, 230);
    uint16_t go = rgb565(80, 220, 80), bad = rgb565(230, 70, 70);
    fill(0, 0, (int)FB_W, 22, face);
    fill(0, (int)FB_H - 18, (int)FB_W, 18, face);
    snprintf(b, sizeof b, "cDock  L%d %s", level_i + 1, levels[level_i].name);
    text(4, 4, b, wh);
    snprintf(b, sizeof b, "v %.0f  fuel %.0f  t %.1f", spd, ship.fuel, tsec);
    text(4, (int)FB_H - 14, b, wh);
    fw = (int)(ship.fuel * 1.2f);
    if (fw < 0)
        fw = 0;
    if (fw > 120)
        fw = 120;
    fill((int)FB_W - 128, 6, 120, 8, rgb565(20, 20, 20));
    fill((int)FB_W - 128, 6, fw, 8, ship.fuel < 20 ? bad : go);
    if (outcome == 1)
        text((int)FB_W / 2 - 30, (int)FB_H / 2, "DOCKED  n next", go);
    else if (outcome == 2)
        text((int)FB_W / 2 - 36, (int)FB_H / 2, "CRASH  r retry", bad);
    else if (paused)
        text((int)FB_W / 2 - 18, (int)FB_H / 2, "PAUSE", wh);
}
