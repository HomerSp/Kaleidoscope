/* Kaleidoscope-LEDEffect-Rainbow - Rainbow LED effects for Kaleidoscope.
 * Copyright (C) 2017-2018  Keyboard.io, Inc.
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Kaleidoscope-LEDEffect-Rainbow.h"

namespace kaleidoscope {
namespace plugin {

void LEDRainbowEffect::TransientLEDMode::update(void) {
  if (!Runtime.has_leds)
    return;

  if (!Runtime.hasTimeExpired(rainbow_last_update,
                              rainbow_delay)) {
    return;
  }

  rainbow_last_update = Runtime.millisAtCycleStart();

  cRGB rainbow = hsvToRgb360((rainbow_hue / 10), rainbow_saturation, parent_->rainbow_value);
  ::LEDControl.set_all_leds_to(rainbow);

  rainbow_hue = (rainbow_hue + rainbow_steps) % 3600;
}

void LEDRainbowEffect::TransientLEDMode::setSpeed(uint8_t speed) {
  // We want to use the lowest modifier to get a smooth transition without
  // using too many cpu cycles.
  uint16_t frame_timer = max(speed * 62 / 10, 40);
  uint8_t mod = min((3600 / speed) / 10, 1000 / frame_timer);
  rainbow_steps = (3600 / speed) / mod;
  rainbow_delay = 1000 / mod;
}

void LEDRainbowEffect::brightness(byte brightness) {
  rainbow_value = brightness;
}

void LEDRainbowEffect::update_delay(byte delay) {
  rainbow_update_delay = delay;
}


// ---------

void LEDRainbowWaveEffect::TransientLEDMode::update(void) {
  if (!Runtime.has_leds)
    return;

  if (!Runtime.hasTimeExpired(rainbow_last_update,
                              rainbow_delay)) {
    return;
  }

  rainbow_last_update = Runtime.millisAtCycleStart();

  for (auto led_index : Runtime.device().LEDs().all()) {
    uint16_t led_hue = ((rainbow_hue / 10) + 16 * (led_index.offset() / 4)) % 360;
    cRGB rainbow = hsvToRgb360(led_hue, rainbow_saturation, parent_->rainbow_value);
    ::LEDControl.setCrgbAt(led_index.offset(), rainbow);
  }
  rainbow_hue = (rainbow_hue + rainbow_steps) % 3600;
}

void LEDRainbowWaveEffect::TransientLEDMode::setSpeed(uint8_t speed) {
  // We want to use the lowest modifier to get a smooth transition without
  // using too many cpu cycles.
  uint16_t frame_timer = max(speed * 62 / 10, 40);
  uint8_t mod = min((3600 / speed) / 10, 1000 / frame_timer);
  rainbow_steps = (3600 / speed) / mod;
  rainbow_delay = 1000 / mod;
}

void LEDRainbowWaveEffect::brightness(byte brightness) {
  rainbow_value = brightness;
}

void LEDRainbowWaveEffect::update_delay(byte delay) {
  rainbow_update_delay = delay;
}

}
}

kaleidoscope::plugin::LEDRainbowEffect LEDRainbowEffect;
kaleidoscope::plugin::LEDRainbowWaveEffect LEDRainbowWaveEffect;
