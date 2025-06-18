#ifndef GAUGE_H
#define GAUGE_H

#include <lvgl.h>

class Gauge {
  lv_obj_t *container;
  lv_obj_t *bars[10];
  lv_color_t dark_colors[10];
  lv_color_t light_colors[10];
  lv_obj_t *label_obj;
  char base_label[32];
  const char *unit;

public:
  Gauge(lv_obj_t *parent, const char *label, const char *unit = "");
  void setValue(float norm); // 0..1
  lv_obj_t *getObj() const { return container; }
};

#endif
