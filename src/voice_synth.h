#ifndef VOICE_SYNTH_H
#define VOICE_SYNTH_H

#include "lvgl_wrapper.h"

// Forward declaration from the GigaAudio library
class AudioClass;

/// Timer callback used to drive the voice visualiser.
/// The timer's user data must point to an ``AudioClass`` instance so that
/// the callback can query the current playback state.
void voice_anim_cb(lv_timer_t *t);

#endif
