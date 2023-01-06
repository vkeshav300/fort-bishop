#pragma once

// Animation Structure
struct Animation
{
    // Animation properties
    int index;
    int frames;
    int ms_delay;

    // Constructors
    Animation() {}

    Animation(int i, int f, int d) : index(i), frames(f), ms_delay(d) {}
};