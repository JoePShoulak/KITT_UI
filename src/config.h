#ifndef CONFIG_H
#define CONFIG_H

#include <button.h>
#include <indicator.h>
#include <Arduino_GigaDisplay.h>

// ==== Layout constants ====
#define SPACING 20
#define GRID_HEIGHT 800
#define POPUP_WIDTH 300
#define POPUP_HEIGHT 220

// ==== Button panel configuration ====
#define BUTTON_COUNT 8
#define PANEL_BUTTON_SIZE ((GRID_HEIGHT - SPACING * 6) / (BUTTON_COUNT / 2))
#define PANEL_GRID_WIDTH (PANEL_BUTTON_SIZE * 2 + SPACING * 3)
#define PANEL_GRID_HEIGHT (PANEL_BUTTON_SIZE * (BUTTON_COUNT / 2) + SPACING * 6)

// ==== Visualiser configuration ====
#define CIRCLE_DIAMETER 60
#define COLUMN_WIDTH (CIRCLE_DIAMETER * 6 / 5)
#define CENTER_WIDTH ((480 - CIRCLE_DIAMETER * 2 - SPACING * 4) * 9 / 10)
#define GRID_WIDTH (COLUMN_WIDTH * 2 + CENTER_WIDTH + SPACING * 4)
#define BUTTON_HEIGHT 85
#define VISUALISER_HEIGHT (GRID_HEIGHT - BUTTON_HEIGHT * 3 - SPACING * 5)

// ==== Global UI references ====
class VoiceTile;
class GaugeTile;

extern VoiceTile *voiceTile;
extern GaugeTile *gaugeTile;
extern GaugeTile *leftGaugeTile;
extern Button *motor_btn;
extern Button *blackout_btn;
extern Button *btn48v;
extern Button *inverter_btn;
extern bool blackout;
extern GigaDisplayBacklight backlight;
extern lv_obj_t *blackout_overlay;

#endif
