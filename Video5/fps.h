#ifndef FPS_H
#define FPS_H

#include "main.h"

struct Fps {
        Uint64 last_time;
        double target_duration;
        double carry_delay;
        double max_delay;
        Uint64 fps_last_time;
        Uint64 fps_counter;
        bool fps_display;
};

bool fps_new(struct Fps **fps);
void fps_free(struct Fps **fps);
void fps_display_toggle(struct Fps *f);
void fps_increase_speed(struct Fps *f);
void fps_decrease_speed(struct Fps *f);
void fps_update(struct Fps *f);

#endif
