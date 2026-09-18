#include "dock.h"
#include "fb.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
    int run = 1;
    if (fb_open() < 0) {
        fprintf(stderr, "cDock needs /dev/fb0\n");
        return 1;
    }
    log_init();
    input_open((int)FB_W, (int)FB_H);
    level_load(0);
    while (run) {
        int keys[12];
        int mx, my, click, thrust, yaw, rcsx, rcsy;
        memset(keys, 0, sizeof keys);
        input_poll(keys, &mx, &my, &click);
        if (keys[0])
            run = 0;
        if (keys[1])
            paused ^= 1;
        if (keys[2])
            level_load(level_i);
        if (keys[3] && outcome == 1)
            level_load((level_i + 1) % NLEVEL);
        thrust = keys[4];
        yaw = keys[6] - keys[5];
        rcsx = keys[8] - keys[7];
        rcsy = keys[9] - keys[10];
        if (!paused)
            phys_step(1.f / 30.f, thrust, yaw, rcsx, rcsy, keys[11]);
        fill(0, 0, (int)FB_W, (int)FB_H, rgb565(6, 8, 18));
        {
            int i;
            for (i = 0; i < 40; i++)
                px((i * 97 + level_i * 13) % (int)FB_W, (i * 53 + 11) % (int)FB_H, rgb565(80, 80, 100));
        }
        station_draw(0, 0);
        ship_draw(0, 0, thrust);
        hud_draw();
        usleep(33000);
    }
    input_close();
    fb_close();
    log_close();
    return 0;
}
