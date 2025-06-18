#include "gauge.h"
#include "colors.h"
#include <Arduino.h>
#include <ctype.h>

#define BAR_WIDTH
#define BAR_HEIGHT

Gauge::Gauge(lv_obj_t *parent, const char *label, const char *unit_param) {
  container = lv_obj_create(parent);
  lv_obj_remove_style_all(container);
  lv_obj_clear_flag(container, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_scrollbar_mode(container, LV_SCROLLBAR_MODE_OFF);
  lv_obj_set_layout(container, LV_LAYOUT_FLEX);
  lv_obj_set_flex_flow(container, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(container, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_END,
                        LV_FLEX_ALIGN_CENTER);
  lv_obj_set_style_pad_all(container, 0, 0);
  lv_obj_set_style_pad_row(container, 0, 0);
  lv_obj_set_width(container, lv_pct(100));

  label_obj = lv_label_create(container);
  int i = 0;
  if (label)
    for (; label[i] && i < 31; ++i)
      base_label[i] = toupper((unsigned char)label[i]);
  base_label[i] = '\0';
  unit = unit_param ? unit_param : "";
  lv_label_set_text(label_obj, base_label);
  lv_obj_set_style_text_color(label_obj, WHITE, 0);
  lv_obj_set_style_text_font(label_obj, &lv_font_montserrat_14, 0);
  lv_obj_set_style_text_align(label_obj, LV_TEXT_ALIGN_RIGHT, 0);
  lv_obj_set_width(label_obj, lv_pct(100));
  lv_obj_set_style_pad_bottom(label_obj, 0, 0);
  lv_obj_set_style_pad_right(label_obj, 0, 0);
  lv_obj_set_style_pad_top(label_obj, 0, 0);
  lv_obj_set_style_translate_y(label_obj, 24, 0);

  lv_obj_t *row = lv_obj_create(container);
  lv_obj_remove_style_all(row);
  lv_obj_clear_flag(row, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_scrollbar_mode(row, LV_SCROLLBAR_MODE_OFF);
  lv_obj_set_layout(row, LV_LAYOUT_FLEX);
  lv_obj_set_flex_flow(row, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(row, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_END,
                        LV_FLEX_ALIGN_CENTER);
  lv_obj_set_style_pad_column(row, 2, 0);
  lv_obj_set_style_pad_row(row, 0, 0);
  lv_obj_set_width(row, LV_SIZE_CONTENT);

  for (int n = 0; n < 10; ++n) {
    lv_obj_t *bar = lv_obj_create(row);
    lv_obj_remove_style_all(bar);
    lv_obj_clear_flag(bar, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(bar, 3, 0);
    lv_obj_set_size(bar, BAR_WIDTH, BAR_HEIGHT);
    lv_obj_set_style_bg_opa(bar, LV_OPA_COVER, 0);
    lv_color_t dark, light;

    if (n < 4) {
      dark = GREEN_DARK;
      light = GREEN;
    } else if (n < 7) {
      dark = YELLOW_DARK;
      light = YELLOW;
    } else {
      dark = RED_DARK;
      light = RED;
    }

    dark_colors[n] = dark;
    light_colors[n] = light;
    lv_obj_set_style_bg_color(bar, dark, 0);
    bars[n] = bar;
  }

  setValue(0.f);
}

void Gauge::setValue(float norm) {
  norm = constrain(norm, 0.0f, 1.0f);
  int active = (int)(norm * 10 + 0.5f);

  char buf[48];
  if (unit && unit[0])
    snprintf(buf, sizeof(buf), "%s %.2f%s", base_label, norm, unit);
  else
    snprintf(buf, sizeof(buf), "%s %.2f", base_label, norm);
  lv_label_set_text(label_obj, buf);

  for (int n = 0; n < 10; ++n)
    lv_obj_set_style_bg_color(bars[n],
                              n < active ? light_colors[n] : dark_colors[n], 0);
}
