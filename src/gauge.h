#ifndef GAUGE_H
#define GAUGE_H

#include <lvgl.h>

struct GaugeData
{
  const char *label;
  const char *unit;
  // int min;
  // int max;
  // bool reversed;
};

class Gauge
{
  lv_obj_t *container;
  lv_obj_t *bars[10];
  lv_color_t dark_colors[10];
  lv_color_t light_colors[10];
  lv_obj_t *label_obj;
  const char *label;
  const char *unit;

public:
  Gauge(lv_obj_t *parent, GaugeData data);
  void setValue(float norm); // 0..1
  lv_obj_t *getObj() const { return container; }
};

#endif
