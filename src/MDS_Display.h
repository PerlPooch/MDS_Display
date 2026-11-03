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
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class MDS_Display {
public:
	explicit MDS_Display(TwoWire& wire = Wire, uint8_t address = 0x3C,
		uint8_t rotation = 2, uint32_t clock = 100000);
	// Caller initializes the shared bus before setup().
	bool setup();
	bool clearMessage();
	void clear();
	void D(const String& message);
	void tick();
	bool ready() const { return ready_; }
	Adafruit_SSD1306* getDevice() { return &display_; }
private:
	static constexpr uint8_t Lines = 4;
	static constexpr uint32_t Timeout = 5000;
	TwoWire& wire_;
	Adafruit_SSD1306 display_;
	uint8_t address_;
	uint8_t rotation_;
	bool ready_ = false;
	String lines_[Lines];
	uint32_t lastScroll_ = 0;
};
