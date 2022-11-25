#pragma once

struct Animation {
    int index;
    int frames;
    int ms_delay;

    Animation() {}

    Animation(int i, int f, int d) {
        index = i;
        frames = f;
        ms_delay = d;
    }
};