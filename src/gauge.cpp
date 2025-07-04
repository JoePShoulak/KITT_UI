#include <Arduino.h>
#include <ctype.h>
#include "gauge.h"
#include "colors.h"

#define BAR_WIDTH 30
#define BAR_HEIGHT 40

Gauge::Gauge(lv_obj_t *parent, GaugeData data) : label(data.label), unit(data.unit), _min(data.min), _max(data.max), mode(data.mode)
{
    container = lv_obj_create(parent);
    lv_obj_remove_style_all(container);
    lv_obj_clear_flag(container, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_scrollbar_mode(container, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_layout(container, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(container, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_all(container, 0, 0);
    lv_obj_set_style_pad_row(container, 0, 0);
    lv_obj_set_width(container, lv_pct(100));

    label_obj = lv_label_create(container);
    lv_label_set_text(label_obj, label);
    lv_obj_set_style_text_color(label_obj, WHITE, 0);
    lv_obj_set_style_text_font(label_obj, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_align(label_obj, LV_TEXT_ALIGN_LEFT, 0);
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
    lv_obj_set_flex_align(row, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_column(row, 10, 0);
    lv_obj_set_style_pad_row(row, 0, 0);
    lv_obj_set_width(row, LV_SIZE_CONTENT);

    for (int n = 0; n < 10; ++n)
    {
        lv_obj_t *bar = lv_obj_create(row);
        lv_obj_remove_style_all(bar);
        lv_obj_clear_flag(bar, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_style_radius(bar, 3, 0);
        lv_obj_set_size(bar, BAR_WIDTH, BAR_HEIGHT);
        lv_obj_set_style_bg_opa(bar, LV_OPA_COVER, 0);
        lv_color_t dark, light;

        switch (mode)
        {
        default:
        case GaugeMode::NORMAL:
            if (n < 4)
            {
                dark = GREEN_DARK;
                light = GREEN;
            }
            else if (n < 7)
            {
                dark = YELLOW_DARK;
                light = YELLOW;
            }
            else
            {
                dark = RED_DARK;
                light = RED;
            }
            break;
        case GaugeMode::REVERSED:
            if (n < 3)
            {
                dark = RED_DARK;
                light = RED;
            }
            else if (n < 6)
            {
                dark = YELLOW_DARK;
                light = YELLOW;
            }
            else
            {
                dark = GREEN_DARK;
                light = GREEN;
            }
            break;
        case GaugeMode::CENTERED:
            if (n < 1)
            {
                dark = RED_DARK;
                light = RED;
            }
            else if (n < 3)
            {
                dark = YELLOW_DARK;
                light = YELLOW;
            }
            else if (n < 7)
            {
                dark = GREEN_DARK;
                light = GREEN;
            }
            else if (n < 9)
            {
                dark = YELLOW_DARK;
                light = YELLOW;
            }
            else
            {
                dark = RED_DARK;
                light = RED;
            }
            break;
        }

        dark_colors[n] = dark;
        light_colors[n] = light;
        lv_obj_set_style_bg_color(bar, dark, 0);
        bars[n] = bar;
    }

    setValue(_min + (_max - _min) / 2);
}

void Gauge::setValue(float val)
{
    value = constrain(val, _min, _max);
    int active = (int)((value - _min) / (_max - _min) * 10);

    char buf[48];

    snprintf(buf, sizeof(buf), (_max - _min < 100) ? "%s   %.2f%s" : "%s   %.f%s", label, value, unit);

    lv_label_set_text(label_obj, buf);

    for (int n = 0; n < 10; ++n)
        lv_obj_set_style_bg_color(bars[n], n < active ? light_colors[n] : dark_colors[n], 0);
}

float Gauge::getValue()
{
    return value;
}

float Gauge::drunken_walk()
{
    float step_max = sqrt(_max - _min);
    float step = rand() % (2 * (int)step_max + 1) - step_max;
    setValue(value + step);
}
