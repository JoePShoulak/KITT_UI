#include "button.h"
#include <Arduino.h>

static void btn_event_cb(lv_event_t *e)
{
  Button *self = static_cast<Button *>(lv_event_get_user_data(e));
  self->eventHandler(e);
}

Button::Button(lv_obj_t *parent_grid, const ButtonData &data, uint8_t grid_col, uint8_t grid_row)
    : label(data.label), callback(data.callback), validate(data.validate), toggleable(data.toggleable), severe(data.severe)
{

  // determine colors based on behaviour
  if (toggleable)
  {
    color_off = severe ? RED_DARK : YELLOW_DARK;
    color_on = severe ? RED : YELLOW;
  }
  else
  {
    color_off = severe ? ORANGE : GREEN;
    color_on = severe ? ORANGE : GREEN;
  }

  toggled = data.start_active && toggleable;

  set_style();

  btn = lv_btn_create(parent_grid);
  lv_obj_add_style(btn, &style, 0);
  lv_obj_set_style_bg_color(btn, toggled ? color_on : color_off, 0);
  lv_obj_set_grid_cell(btn, LV_GRID_ALIGN_STRETCH, grid_col, 1, LV_GRID_ALIGN_STRETCH, grid_row, 1);

  label_obj = lv_label_create(btn);
  lv_label_set_text(label_obj, label);
  lv_obj_center(label_obj);
  lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, this);
}

Button::Button(lv_obj_t *parent_grid, const ButtonData &data, uint8_t grid_col, uint8_t grid_row, lv_color_t color_off, lv_color_t color_on)
    : label(data.label), callback(data.callback), validate(data.validate), toggleable(data.toggleable), severe(data.severe), color_off(color_off), color_on(color_on)
{
  toggled = data.start_active && toggleable;

  set_style();

  btn = lv_btn_create(parent_grid);
  lv_obj_add_style(btn, &style, 0);
  lv_obj_set_style_bg_color(btn, toggled ? color_on : color_off, 0);

  lv_obj_set_grid_cell(btn, LV_GRID_ALIGN_STRETCH, grid_col, 1, LV_GRID_ALIGN_STRETCH, grid_row, 1);

  label_obj = lv_label_create(btn);
  lv_label_set_text(label_obj, label);
  lv_obj_center(label_obj);

  lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, this);
}

void Button::setCallback(button_callback cb) { callback = cb; }

void Button::setValidate(validate_callback cb) { validate = cb; }

void Button::handlePress()
{
  if (toggleable)
  {
    toggled = !toggled;
    updateVisual();
  }
}

void Button::updateVisual()
{
  lv_obj_set_style_bg_color(btn, toggled ? color_on : color_off, 0);
}

void Button::activate(lv_event_t *e)
{
  if (validate(e))
  {
    handlePress();

    if (callback)
      callback(e);
  }

  updateVisual();
}

void Button::eventHandler(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e);

  if (code == LV_EVENT_PRESSED)
  {
    press_start = millis();
    long_press_handled = false;
  }
  else if (code == LV_EVENT_PRESSING && severe)
  {
    if (!long_press_handled)
    {
      uint32_t elapsed = millis() - press_start;
      lv_opa_t ratio = elapsed >= LONG_PRESS_DURATION ? 255 : (255 * elapsed / LONG_PRESS_DURATION);
      lv_obj_set_style_bg_color(btn, lv_color_mix(WHITE, color_off, ratio), 0);

      if (elapsed >= LONG_PRESS_DURATION)
      {
        activate(e);

        long_press_handled = true;
      }
    }
  }
  else if (code == LV_EVENT_RELEASED || code == LV_EVENT_PRESS_LOST)
  {
    updateVisual();
  }
  else if (code == LV_EVENT_CLICKED && !severe)
  {
    activate(e);
  }
}

void Button::set_style()
{
  lv_style_init(&style);
  lv_style_set_radius(&style, 0);
  lv_style_set_border_width(&style, 0);
  lv_style_set_shadow_width(&style, 0);
  lv_style_set_outline_width(&style, 0);
  lv_style_set_pad_all(&style, 0);
  lv_style_set_text_color(&style, BLACK);
  lv_style_set_text_font(&style, &lv_font_montserrat_14);
}
