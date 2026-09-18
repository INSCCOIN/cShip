#include "dock.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static void world_bay(float *bx, float *by)
{
    float c = cosf(st.rot), s = sinf(st.rot);
    *bx = st.x + st.bayx * c - st.bayy * s;
    *by = st.y + st.bayx * s + st.bayy * c;
}

void phys_step(float dt, int thrust, int yaw, int rcsx, int rcsy, int damp)
{
    float c, s, spd, bx, by, dx, dy, drot;
    if (outcome)
        return;
    if (yaw)
        ship.om += yaw * 2.8f * dt;
    if (damp)
        ship.om *= 0.85f;
    if (thrust && ship.fuel > 0) {
        c = cosf(ship.rot);
        s = sinf(ship.rot);
        ship.vx += c * 55.f * dt;
        ship.vy += s * 55.f * dt;
        ship.fuel -= 18.f * dt;
    }
    if (ship.fuel > 0 && (rcsx || rcsy)) {
        c = cosf(ship.rot);
        s = sinf(ship.rot);
        ship.vx += (-s * (float)rcsx + c * 0) * 28.f * dt;
        ship.vy += (c * (float)rcsx + s * 0) * 28.f * dt;
        /* rcsy along heading */
        ship.vx += c * (float)rcsy * 28.f * dt;
        ship.vy += s * (float)rcsy * 28.f * dt;
        ship.fuel -= 8.f * dt;
    }
    if (ship.fuel < 0)
        ship.fuel = 0;
    ship.vy += grav * dt;
    ship.rot += ship.om * dt;
    ship.x += ship.vx * dt;
    ship.y += ship.vy * dt;
    st.rot += st.om * dt;
    st.x += st.vx * dt;
    st.y += st.vy * dt;
    if (ship.x < 8 || ship.y < 28 || ship.x > 472 || ship.y > 300) {
        outcome = 2;
        log_line("crash bounds");
        return;
    }
    dx = ship.x - st.x;
    dy = ship.y - st.y;
    c = cosf(-st.rot);
    s = sinf(-st.rot);
    {
        float lx = dx * c - dy * s, ly = dx * s + dy * c;
        int in_hull = fabsf(lx) < st.hw && fabsf(ly) < st.hh;
        int in_bay = fabsf(lx - st.bayx) < st.bayw * 0.5f && fabsf(ly - st.bayy) < st.bayh * 0.5f;
        spd = sqrtf(ship.vx * ship.vx + ship.vy * ship.vy);
        if (in_hull && !in_bay) {
            outcome = 2;
            log_line("crash hull");
            return;
        }
        world_bay(&bx, &by);
        dx = ship.x - bx;
        dy = ship.y - by;
        drot = ship.rot - st.rot;
        while (drot > M_PI)
            drot -= 2.f * (float)M_PI;
        while (drot < -M_PI)
            drot += 2.f * (float)M_PI;
        if (in_bay && spd < levels[level_i].vdock && fabsf(drot) < 0.35f) {
            hold += dt;
            if (hold > 0.4f) {
                outcome = 1;
                log_line("docked");
            }
        } else
            hold = 0;
    }
    tsec += dt;
}
