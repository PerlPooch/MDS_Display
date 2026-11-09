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

#include <Wire.h>

constexpr uint8_t SSD1306_SWITCHCAPVCC = 2;
constexpr uint8_t SSD1306_WHITE = 1;

class Adafruit_SSD1306 {
public:
	bool initializes = true;

	// Accept the production device's geometry, bus, reset, and clock arguments.
	Adafruit_SSD1306(int, int, TwoWire*, int, uint32_t, uint32_t) {
	}

	// Simulate success or failure independently of the I2C address probe.
	bool begin(uint8_t, uint8_t, bool, bool) {
		return initializes;
	}

	// Accept orientation without rendering pixels.
	void setRotation(uint8_t) {
	}

	// Accept the configured font size.
	void setTextSize(uint8_t) {
	}

	// Accept the configured text color.
	void setTextColor(uint8_t) {
	}

	// Accept the configured wrapping mode.
	void setTextWrap(bool) {
	}

	// Represent a framebuffer clear without hardware access.
	void clearDisplay() {
	}

	// Accept the requested text cursor position.
	void setCursor(int, int) {
	}

	// Represent an OLED transfer without hardware access.
	void display() {
	}

	// Accept a diagnostic line without rendering it.
	void println(const String&) {
	}
};
