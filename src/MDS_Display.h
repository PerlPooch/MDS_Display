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
	enum class Error {
		None,
		DeviceNotFound,
		InitializationFailed
	};

	// Select the OLED bus, address, orientation, and transfer clock.
	explicit MDS_Display(
		TwoWire& wire = Wire, uint8_t address = 0x3C, uint8_t rotation = 2, uint32_t clock = 100000);

	// Initialize the OLED after the caller has initialized the shared I2C bus.
	bool begin();

	// Scroll one blank line into the display and return true for callback compatibility.
	bool clearMessage();

	// Clear the OLED and diagnostic lines, then restart the scrolling interval.
	void clear();

	// Append a diagnostic line, redraw the OLED, and restart the scrolling interval.
	void D(const String& message);

	// Scroll one blank line when the initialized display reaches its timeout.
	void tick();

	// Report whether OLED initialization succeeded, without probing current device health.
	bool ready() const {
		return ready_;
	}

	// Return the last initialization failure; queries and display updates leave it unchanged.
	Error error() const {
		return error_;
	}

	// Describe the recorded error, or return an empty string when error() is None.
	const char* lastError() const;

	// Borrow the underlying OLED device for drawing outside the diagnostic line buffer.
	Adafruit_SSD1306* device() {
		return &display_;
	}

private:
	static constexpr uint8_t Lines = 4;
	static constexpr uint32_t Timeout = 5000;
	TwoWire& wire_;
	Adafruit_SSD1306 display_;
	uint8_t address_;
	uint8_t rotation_;
	bool ready_ = false;
	Error error_ = Error::None;
	String lines_[Lines];
	uint32_t lastScroll_ = 0;
};
