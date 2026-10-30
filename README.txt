TinyTweens
==========

A tiny tweening library written in C.

TinyTweens allows you to smoothly animate float values over time using
different easing styles and directions.

GETTING STARTED
---------------

Include tweens.h in your project.

    #include "tweens.h"

In exactly one source file, define TTWEENS_IMPLEMENTATION before
including the header:

    #define TTWEENS_IMPLEMENTATION
    #include "tweens.h"

Other source files can include tweens.h normally.

BASIC USAGE
-----------

Create a float:

    float x = 0.0f;

Start a tween:

    TTweenFloat(&x, 100.0f, (TTweenInfo) {
        .duration = 1.0f,
        .style = TT_EASE_QUINT,
        .direction = TT_EASE_OUT
    });

Update active tweens every frame:

    TTweenStep(deltaTime);

TTweenFloat arguments:

    TTweenFloat(float* p, float goal, TTweenInfo info);

    p       - Pointer to the float being animated.
    goal    - Target value.
    info    - Tween configuration.

TWEEN INFO
----------

TTweenInfo contains the following fields:

    float duration;
    TTEasingStyle style;
    TTEasingDirection direction;

duration:
    Animation duration in seconds.

style:
    Easing function used for interpolation.

direction:
    Determines how the easing function is applied.

EASING STYLES
-------------

TT_EASE_LINEAR
    Linear interpolation.

TT_EASE_SINE
    Sine-based easing.

TT_EASE_QUAD
    Quadratic easing.

TT_EASE_CUBIC
    Cubic easing.

TT_EASE_QUART
    Quartic easing.

TT_EASE_QUINT
    Quintic easing.

EASING DIRECTIONS
-----------------

TT_EASE_IN
    Starts slowly and accelerates.

TT_EASE_OUT
    Starts quickly and decelerates.

TT_EASE_INOUT
    Starts slowly, accelerates, then decelerates.

CANCELLING TWEENS
-----------------

Starting a new tween on a float that already has an active tween
automatically cancels the previous tween.

The new tween starts from the float's current value.

Example:

    float x = 0.0f;

    TTweenFloat(&x, 100.0f, info);

    // The previous tween is cancelled.
    TTweenFloat(&x, 200.0f, info);

UPDATING TWEENS
---------------

Call TTweenStep once per frame, passing dt.

Example using raylib:

    TTweenStep(GetFrameTime());

EXAMPLE
-------

A complete raylib example is available in the examples directory.

COMPILATION
-----------

When using math functions from libm on Linux, link with -lm.

Example:

    cc main.c -o example -lraylib -lm

LICENSE
-------

MIT.