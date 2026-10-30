#ifndef TTWEENS_H
#define TTWEENS_H

#include <math.h>
#include <stdlib.h>

typedef enum TTEasingStyle {
    TT_EASE_LINEAR,
    TT_EASE_SINE,
    TT_EASE_QUAD,
    TT_EASE_CUBIC,
    TT_EASE_QUART,
    TT_EASE_QUINT
} TTEasingStyle;

typedef enum TTEasingDirection {
    TT_EASE_IN,
    TT_EASE_OUT,
    TT_EASE_INOUT
} TTEasingDirection;

typedef struct TTweenInfo {
    float duration;
    TTEasingStyle style;
    TTEasingDirection direction;
} TTweenInfo;

typedef struct TTween {
    float* p; 
    float start;
    float goal;
    float elapsed;
    float duration;
    TTweenInfo info;
    struct TTween* next;
} TTween;

void TTweenFloat(float* p, float goal, TTweenInfo info);
void TTweenStep(float dt);

#ifdef TTWEENS_IMPLEMENTATION

static TTween* tweens;

void TTweenFloat(float* p, float goal, TTweenInfo info) {
    TTween** pp = &tweens;

    while (*pp) {
        TTween* tween = *pp;

        if (tween->p == p) {
            *pp = tween->next;
            free(tween);
            continue;
        }

        pp = &tween->next;
    }

    TTween* tween = (TTween *) calloc(1, sizeof(TTween));

    if (!tween) return;

    *tween = (TTween) {
        .p = p,
        .start = *p,
        .goal = goal,
        .elapsed = 0.0f,
        .duration = info.duration,
        .info = info,
        .next = tweens,
    };

    tweens = tween;
}

static float TTweenEaseIn(TTEasingStyle style, float t) {
    switch (style) {
        case TT_EASE_LINEAR:
            return t;

        case TT_EASE_SINE:
            return 1.0f - cosf(t * 1.57079632679f);

        case TT_EASE_QUAD:
            return t * t;

        case TT_EASE_CUBIC:
            return t * t * t;

        case TT_EASE_QUART: {
            float t2 = t * t;
            return t2 * t2;
        }

        case TT_EASE_QUINT: {
            float t2 = t * t;
            return t2 * t2 * t;
        }
    }

    return t;
}

static float TTweenEase(TTEasingStyle style, TTEasingDirection direction, float t) {
    if (t <= 0.0f) return 0.0f;
    if (t >= 1.0f) return 1.0f;

    switch (direction) {
        case TT_EASE_IN:
            return TTweenEaseIn(style, t);

        case TT_EASE_OUT:
            return 1.0f - TTweenEaseIn(style, 1.0f - t);

        case TT_EASE_INOUT:
            if (t < 0.5f) return TTweenEaseIn(style, t * 2.0f) * 0.5f;

            return 1.0f - TTweenEaseIn(style, 2.0f - t * 2.0f) * 0.5f;
    }

    return t;
}

void TTweenStep(float dt) {
    TTween** pp = &tweens;

    while (*pp) {
        TTween* tween = *pp;
        tween->elapsed += dt;

        float t;
        if (tween->duration <= 0.0f) {
            t = 1.0f;
        } else {
            t = tween->elapsed / tween->duration;

            if (t > 1.0f) t = 1.0f;
        }

        float eased = TTweenEase(tween->info.style, tween->info.direction, t);

        *tween->p = tween->start + (tween->goal - tween->start) * eased;
        if (t >= 1.0f) {
            *pp = tween->next;
            free(tween);
        } else {
            pp = &tween->next;
        }
    }
}

#endif
#endif