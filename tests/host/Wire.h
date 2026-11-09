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

#pragma once

#include <Arduino.h>

class TwoWire {
public:
	bool acknowledges = true;

	// Accept an address probe without accessing hardware.
	void beginTransmission(uint8_t) {
	}

	// Simulate either an acknowledged address or a missing OLED.
	int endTransmission() {
		return acknowledges ? 0 : 2;
	}
};

extern TwoWire Wire;
