#include "pointing_device.h"
#include "quantum.h"
#include <math.h>

#define TB_LEFT  PAL_LINE(GPIOC, 11U)
#define TB_RIGHT PAL_LINE(GPIOC, 9U)
#define TB_UP    PAL_LINE(GPIOC, 8U)
#define TB_DOWN  PAL_LINE(GPIOC, 10U)

#define TB_DECR -1
#define TB_INCR 1

#define TB_RATE_CUTOFF_MILLIS 1000

enum {
  AXIS_X = 0,
  AXIS_Y,
  NUM_AXES
};

static bool wheel_mode = false;
/* static bool last_wheel_mode = false; */

static int8_t distances[NUM_AXES] = {0.0f, 0.0f};

static void trackball_move(uint8_t axis, int8_t direction) {
  distances[axis] += direction;
}

static void trackball_left(void* arg) {
  (void)arg;
  trackball_move(AXIS_X, TB_DECR);
}

static void trackball_right(void* arg) {
  (void)arg;
  trackball_move(AXIS_X, TB_INCR);
}

static void trackball_up(void* arg) {
  (void)arg;
  trackball_move(AXIS_Y, TB_DECR);
}

static void trackball_down(void* arg) {
  (void)arg;
  trackball_move(AXIS_Y, TB_INCR);
}

void start_interrupts(void) {
  palEnableLineEvent(TB_LEFT, PAL_EVENT_MODE_BOTH_EDGES);
  palEnableLineEvent(TB_RIGHT, PAL_EVENT_MODE_BOTH_EDGES);
  palEnableLineEvent(TB_UP, PAL_EVENT_MODE_BOTH_EDGES);
  palEnableLineEvent(TB_DOWN, PAL_EVENT_MODE_BOTH_EDGES);
}

void stop_interrupts(void) {
  palDisableLineEvent(TB_LEFT);
  palDisableLineEvent(TB_RIGHT);
  palDisableLineEvent(TB_UP);
  palDisableLineEvent(TB_DOWN);
}

void pointing_device_driver_init(void) {
  palSetLineMode(TB_LEFT, PAL_MODE_INPUT_PULLUP);
  palSetLineMode(TB_RIGHT, PAL_MODE_INPUT_PULLUP);
  palSetLineMode(TB_UP, PAL_MODE_INPUT_PULLUP);
  palSetLineMode(TB_DOWN, PAL_MODE_INPUT_PULLUP);

  start_interrupts();

  palSetLineCallback(TB_LEFT, trackball_left, NULL);
  palSetLineCallback(TB_RIGHT, trackball_right, NULL);
  palSetLineCallback(TB_UP, trackball_up, NULL);
  palSetLineCallback(TB_DOWN, trackball_down, NULL);
}

report_mouse_t pointing_device_driver_get_report(report_mouse_t mouse_report) {
  float dx = 2.3f * distances[AXIS_X];
  float dy = 2.3f * distances[AXIS_Y];
  float scale = sqrt(dx*dx + dy*dy);
  float adj_scale = pow(scale, 1.8f);
  mouse_report.x = (int16_t)(dx * adj_scale);
  mouse_report.y = (int16_t)(dy * adj_scale);

  distances[AXIS_X] = 0;
  distances[AXIS_Y] = 0;

  return mouse_report;
}

uint16_t pointing_device_driver_get_cpi(void) {
  return 0;
}

void pointing_device_driver_set_cpi(uint16_t cpi) {

}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  if (!process_record_user(keycode, record)) {
    return false;
  }

  if (keycode == JS_4) {
    wheel_mode = record->event.pressed;
  }

  return true;
}
