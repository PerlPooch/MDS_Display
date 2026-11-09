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

#include "MDS_Display.h"

// Select the OLED bus, address, orientation, and transfer clock.
MDS_Display::MDS_Display(TwoWire& wire, uint8_t address, uint8_t rotation, uint32_t clock)
	: wire_(wire), display_(128, 32, &wire, -1, clock, clock), address_(address), rotation_(rotation) {
}

// Check for the OLED and initialize its display buffer and text layout.
bool MDS_Display::begin() {
	ready_ = false;
	wire_.beginTransmission(address_);
	if (wire_.endTransmission() != 0) {
		error_ = Error::DeviceNotFound;
		return false;
	}

	if (!display_.begin(SSD1306_SWITCHCAPVCC, address_, true, false)) {
		error_ = Error::InitializationFailed;
		return false;
	}
	display_.setRotation(rotation_);
	display_.setTextSize(1);
	display_.setTextColor(SSD1306_WHITE);
	display_.setTextWrap(false);
	ready_ = true;
	error_ = Error::None;
	clear();
	return true;
}

// Clear the OLED and diagnostic lines, then restart the scrolling interval.
void MDS_Display::clear() {
	if (!ready_)
		return;

	for (auto& line : lines_)
		line = "";
	display_.clearDisplay();
	display_.setCursor(0, 0);
	display_.display();
	lastScroll_ = millis();
}

// Append a diagnostic line, redraw the OLED, and restart the scrolling interval.
void MDS_Display::D(const String& message) {
	if (!ready_)
		return;

	for (uint8_t i = 0; i < Lines - 1; ++i)
		lines_[i] = lines_[i + 1];

	lines_[Lines - 1] = message;
	display_.clearDisplay();
	display_.setCursor(0, 0);
	for (const auto& line : lines_)
		display_.println(line);
	display_.display();
	lastScroll_ = millis();
}

// Scroll one blank line into the display and return true for callback compatibility.
bool MDS_Display::clearMessage() {
	D("");
	return true;
}

// Scroll one blank line when the initialized display reaches its timeout.
void MDS_Display::tick() {
	if (ready_ && uint32_t(millis() - lastScroll_) >= Timeout)
		clearMessage();
}

// Return diagnostic text for the currently recorded initialization error.
const char* MDS_Display::lastError() const {
	switch (error_) {
		case Error::None:
			return "";

		case Error::DeviceNotFound:
			return "OLED did not acknowledge its I2C address";

		case Error::InitializationFailed:
			return "SSD1306 initialization failed";
	}

	return "Unknown display error";
}
