#include <Arduino.h>
#include "seven_segment.h"
#include "colors.h"
#include "config.h"

// Make the digits wider for a larger speedometer display
#define DW 80
#define DH 160
#define DT 12

static lv_obj_t *create_seg(lv_obj_t *parent, int x, int y, int w, int h, lv_color_t color_off)
{
  lv_obj_t *seg = lv_obj_create(parent);
  lv_obj_remove_style_all(seg);
  lv_obj_set_pos(seg, x, y);
  lv_obj_set_size(seg, w, h);
  lv_obj_set_style_bg_color(seg, color_off, 0);
  lv_obj_set_style_bg_opa(seg, LV_OPA_COVER, 0);
  lv_obj_set_style_border_width(seg, 0, 0);
  lv_obj_set_style_radius(seg, 2, 0);

  return seg;
}

void SevenSegmentDisplay::createDigit(lv_obj_t *parent, int idx)
{
  lv_obj_t *digit = lv_obj_create(parent);
  lv_obj_remove_style_all(digit);
  lv_obj_set_size(digit, DW, DH);
  lv_obj_set_style_bg_opa(digit, LV_OPA_TRANSP, 0);
  lv_obj_set_style_pad_all(digit, 0, 0);

  segments[idx][0] = create_seg(digit, DT, 0, DW - 2 * DT, DT, RED_DARK);               // top
  segments[idx][1] = create_seg(digit, DW - DT, DT, DT, DH / 2 - DT, RED_DARK);         // top-right
  segments[idx][2] = create_seg(digit, DW - DT, DH / 2, DT, DH / 2 - DT, RED_DARK);     // bottom-right
  segments[idx][3] = create_seg(digit, DT, DH - DT, DW - 2 * DT, DT, RED_DARK);         // bottom
  segments[idx][4] = create_seg(digit, 0, DH / 2, DT, DH / 2 - DT, RED_DARK);           // bottom-left
  segments[idx][5] = create_seg(digit, 0, DT, DT, DH / 2 - DT, RED_DARK);               // top-left
  segments[idx][6] = create_seg(digit, DT, DH / 2 - DT / 2, DW - 2 * DT, DT, RED_DARK); // middle
}

SevenSegmentDisplay::SevenSegmentDisplay(lv_obj_t *parent, const char *labelText)
{
  container = lv_obj_create(parent);
  lv_obj_remove_style_all(container);
  lv_obj_set_width(container, lv_pct(100));
  lv_obj_set_height(container, 220);
  lv_obj_set_layout(container, LV_LAYOUT_NONE);
  lv_obj_set_style_pad_all(container, 0, 0);

  lv_obj_t *row = lv_obj_create(container);
  lv_obj_remove_style_all(row);
  lv_obj_set_layout(row, LV_LAYOUT_FLEX);
  lv_obj_set_flex_flow(row, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(row, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  lv_obj_set_style_pad_column(row, 12, 0);
  lv_obj_set_style_pad_all(row, 0, 0);
  lv_obj_set_size(row, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_align(row, LV_ALIGN_TOP_MID, 0, 0);

  for (int i = 0; i < 3; ++i)
    createDigit(row, i);

  label = lv_label_create(container);
  lv_label_set_text(label, labelText);
  lv_obj_set_style_text_color(label, WHITE, 0);
  lv_obj_set_style_text_font(label, &lv_font_montserrat_14, 0);
  lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_LEFT, 0);
  lv_obj_set_width(label, LV_SIZE_CONTENT);
  lv_obj_align_to(label, row, LV_ALIGN_OUT_RIGHT_BOTTOM, SPACING, 0);

  setValue(0);
}

static const uint8_t digit_masks[11] = {
    0b0111111, // 0
    0b0000110, // 1
    0b1011011, // 2
    0b1001111, // 3
    0b1100110, // 4
    0b1101101, // 5
    0b1111101, // 6
    0b0000111, // 7
    0b1111111, // 8
    0b1101111, // 9
    0b0000000  // off
};

void SevenSegmentDisplay::setValue(int value)
{
  value = constrain(value, 0, 999);
  int vals[3] = {value / 100, (value / 10) % 10, value % 10};

  for (int d = 0; d < 3; ++d)
  {
    uint8_t mask = digit_masks[vals[d]];

    if (d == 0 && value < 100)
      mask = digit_masks[-1];

    if (d == 1 && value < 10)
      mask = digit_masks[-1];

    for (int s = 0; s < 7; ++s)
    {
      lv_color_t color = (mask & (1 << s)) ? RED : RED_DARK;
      lv_obj_set_style_bg_color(segments[d][s], color, 0);
    }
  }
}
