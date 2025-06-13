#include "voice_synth.h"

#include "config.h"
#include "voice_tile.h"
// Provide access to the audio player.  The real header lives in the
// GigaAudio library but may not be present when building the UI in
// isolation.  A forward declaration is provided in ``voice_synth.h``.
#if __has_include(<Arduino_GigaAudio.h>)
#  include <Arduino_GigaAudio.h>
#elif __has_include(<GigaAudio.h>)
#  include <GigaAudio.h>
#endif
#include <stdlib.h>

void voice_anim_cb(lv_timer_t *t) {
  static float level = 0.f;
  static float target = 0.f;
  static int hold = 0;
  static bool was_playing = false;
  AudioClass *audio = t ? static_cast<AudioClass *>(t->user_data) : nullptr;
  bool playing = audio && audio->isPlaying();

  if (!playing) {
    if (was_playing && voiceTile) {
      if (voiceTile->getIndicator(0))
        voiceTile->getIndicator(0)->toggle(false);
      if (voiceTile->getVisualiser())
        voiceTile->getVisualiser()->startFade();
    }
    was_playing = false;
    target = 0.f;
    level = 0.f;
    return;
  }

  if (!was_playing && voiceTile && voiceTile->getIndicator(0))
    voiceTile->getIndicator(0)->toggle(true);
  was_playing = true;

  if (--hold <= 0) {
    if (target > 0.05f) {
      target = 0.f;                   // short pause between words
      hold = 2 + rand() % 3;          // 100-200 ms
    } else {
      target = 0.3f + (rand() % 70) / 100.f; // new burst 0.3-1.0
      hold = 2 + rand() % 5;         // 100-300 ms
    }
  }

  level += (target - level) * 0.25f; // smooth towards target

  if (voiceTile && voiceTile->getVisualiser())
    voiceTile->getVisualiser()->setLevel(level);
}
