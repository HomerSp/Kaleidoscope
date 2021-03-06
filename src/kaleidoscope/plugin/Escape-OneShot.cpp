/* -*- mode: c++ -*-
 * Kaleidoscope-Escape-OneShot -- Turn ESC into a key that cancels OneShots, if
 * active. Copyright (C) 2016, 2017, 2018  Keyboard.io, Inc
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

#include <Kaleidoscope-Escape-OneShot.h>
#include <Kaleidoscope-OneShot.h>

#include "kaleidoscope/Runtime.h"
#include "kaleidoscope/keyswitch_state.h"

namespace kaleidoscope {
namespace plugin {

bool EscapeOneShot::did_escape_;

EventHandlerResult EscapeOneShot::onKeyswitchEvent(Key &mapped_key,
                                                   KeyAddr key_addr,
                                                   uint8_t keyState) {
  if (mapped_key != Key_Escape || (keyState & INJECTED))
    return EventHandlerResult::OK;

  if ((!::OneShot.isActive() || ::OneShot.isPressed()) &&
      !::OneShot.isSticky()) {
    return EventHandlerResult::OK;
  }

  if (did_escape_) mapped_key = Key_NoKey;
  did_escape_ = !keyToggledOff(keyState);

  ::OneShot.cancel(true);
  return EventHandlerResult::EVENT_CONSUMED;
}

}  // namespace plugin
}  // namespace kaleidoscope

kaleidoscope::plugin::EscapeOneShot EscapeOneShot;
