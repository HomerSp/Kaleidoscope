/* -*- mode: c++ -*-
 * Kaleidoscope-Hardware-OLKB-Planck -- Planck hardware support for Kaleidoscope
 * Copyright (C) 2018  Keyboard.io, Inc
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#ifdef ARDUINO_AVR_PLANCK

#include <Arduino.h>
#define HARDWARE_IMPLEMENTATION kaleidoscope::hardware::olkb::Planck

#include "kaleidoscope/driver/keyscanner/ATMegaKeyScannerDescription.h"
#include "kaleidoscope/driver/keyscanner/ATMegaKeyScanner.h"
#include "kaleidoscope/driver/bootloader/avr/HalfKay.h"
#include "kaleidoscope/hardware/avr/AVRDeviceDescription.h"
#include "kaleidoscope/hardware/avr/AVRDevice.h"

namespace kaleidoscope {
namespace hardware {
namespace olkb {

struct PlanckDeviceDescription : kaleidoscope::hardware::avr::AVRDeviceDescription {
  typedef struct PlanckKeyScannerDescription : public kaleidoscope::driver::keyscanner::ATMegaKeyScannerDescription {
    ATMEGA_KEYSCANNER_DESCRIPTION(
      ROW_PIN_LIST({ PIN_D0, PIN_D5, PIN_B5, PIN_B6 }),
      COL_PIN_LIST({ PIN_F1, PIN_F0, PIN_B0, PIN_C7, PIN_F4, PIN_F5, PIN_F6, PIN_F7, PIN_D4, PIN_D6, PIN_B4, PIN_D7 })
    );
  } KeyScannerDescription;
  typedef kaleidoscope::driver::keyscanner::ATMegaKeyScanner<KeyScannerDescription> KeyScanner;
  typedef kaleidoscope::driver::bootloader::avr::HalfKay BootLoader;
};

class Planck: public kaleidoscope::hardware::avr::AVRDevice<PlanckDeviceDescription> {
 public:
  Planck() {}
};

#define PER_KEY_DATA(dflt,                                                       \
         R0C0, R0C1, R0C2, R0C3, R0C4, R0C5, R0C6, R0C7, R0C8, R0C9, R0C10, R0C11, \
         R1C0, R1C1, R1C2, R1C3, R1C4, R1C5, R1C6, R1C7, R1C8, R1C9, R1C10, R1C11, \
         R2C0, R2C1, R2C2, R2C3, R2C4, R2C5, R2C6, R2C7, R2C8, R2C9, R2C10, R2C11, \
         R3C0, R3C1, R3C2, R3C3, R3C4, R3C5, R3C6, R3C7, R3C8, R3C9, R3C10, R3C11  \
  )                                                                                \
         R0C0, R0C1, R0C2, R0C3, R0C4, R0C5, R0C6, R0C7, R0C8, R0C9, R0C10, R0C11, \
         R1C0, R1C1, R1C2, R1C3, R1C4, R1C5, R1C6, R1C7, R1C8, R1C9, R1C10, R1C11, \
         R2C0, R2C1, R2C2, R2C3, R2C4, R2C5, R2C6, R2C7, R2C8, R2C9, R2C10, R2C11, \
         R3C0, R3C1, R3C2, R3C3, R3C4, R3C5, R3C6, R3C7, R3C8, R3C9, R3C10, R3C11

}

}
}

#include "kaleidoscope/hardware/key_indexes.h"

extern kaleidoscope::hardware::olkb::Planck &Planck;

#endif
