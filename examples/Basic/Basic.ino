/*
 * ===========================================================================
 * MDS_Display 0.1.0 - https://home.marcspencer.com/mds-display
 *
 * Copyright (c) 2026 Marc D. Spencer.
 * All Rights Reserved under the applicable license.
 * SPDX-License-Identifier: MPL-2.0
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 * ===========================================================================
 */

#include <Wire.h>
#include <MDS_Display.h>

constexpr int SDA_PIN = 21;
constexpr int SCL_PIN = 22;

MDS_Display display(Wire, 0x3C, 0);

void setup() {
    Serial.begin(115200);
    Wire.begin(SDA_PIN, SCL_PIN);

    if (!display.setup()) {
        Serial.println("OLED initialization failed");
        return;
    }

    display.D("Hello, world!");
    display.D("Display ready");
}

void loop() {
    display.tick();
}
