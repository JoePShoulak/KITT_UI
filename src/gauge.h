#ifndef GAUGE_H
#define GAUGE_H

#include <lvgl.h>

enum class GaugeMode
{
  NORMAL,
  REVERSED,
  CENTERED
};

struct GaugeData
{
  const char *label;
  const char *unit;
  int min;
  int max;
  GaugeMode mode;
};

class Gauge
{
  lv_obj_t *container;
  lv_obj_t *bars[10];
  lv_color_t dark_colors[10];
  lv_color_t light_colors[10];
  lv_obj_t *label_obj;

  // data
  const char *label;
  const char *unit;
  int _min;
  int _max;
  GaugeMode mode;
  float value;

public:
  Gauge(lv_obj_t *parent, GaugeData data);
  void setValue(float val);
  float getValue();
  lv_obj_t *getObj() const { return container; }
  float drunken_walk();
};

#endif
