#ifndef CDOCK_H
#define CDOCK_H

enum { NLEVEL = 5 };

typedef struct {
    float x, y, vx, vy, rot, om, fuel;
} Ship;

typedef struct {
    float x, y, vx, vy, rot, om;
    float hw, hh;     /* hull half-size */
    float bayx, bayy; /* bay center in station local */
    float bayw, bayh;
} Station;

typedef struct {
    const char *name;
    float sx, sy, srot, fuel;
    float tx, ty, tw, th, bayw, bayh, bayx, bayy;
    float tvx, tom, grav;
    float vdock;
} Level;

extern Ship ship;
extern Station st;
extern int level_i, paused, outcome; /* 0 fly 1 docked 2 crash */
extern float hold, tsec, grav;
extern const Level levels[NLEVEL];

void log_init(void);
void log_line(const char *s);
void log_close(void);

void input_open(int w, int h);
void input_close(void);
int input_poll(int *keys, int *mx, int *my, int *click);

void level_load(int i);
void phys_step(float dt, int thrust, int yaw, int rcsx, int rcsy, int damp);
void ship_draw(int camx, int camy, int thrust);
void station_draw(int camx, int camy);
void hud_draw(void);

#endif
