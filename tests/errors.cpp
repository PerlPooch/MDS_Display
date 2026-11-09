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

#include <MDS_Display.h>
#include <cassert>
#include <cstdio>
#include <cstring>

uint32_t nowMillis = 0;
TwoWire Wire;

// Verify failure replacement, error persistence during queries/ticks, and successful recovery.
int main() {
	using Error = MDS_Display::Error;

	MDS_Display oled;
	assert(!oled.ready());
	assert(oled.error() == Error::None);
	assert(!*oled.lastError());

	Wire.acknowledges = false;
	assert(!oled.begin());
	assert(!oled.ready());
	assert(oled.error() == Error::DeviceNotFound);
	assert(*oled.lastError());

	const String missingDevice = oled.lastError();
	oled.D("Ignored while unavailable");
	oled.clear();
	assert(oled.clearMessage());
	nowMillis += 6000;
	oled.tick();
	assert(oled.device());
	assert(!oled.ready());
	assert(oled.error() == Error::DeviceNotFound);
	assert(missingDevice == oled.lastError());

	Wire.acknowledges = true;
	oled.device()->initializes = false;
	assert(!oled.begin());
	assert(!oled.ready());
	assert(oled.error() == Error::InitializationFailed);
	assert(*oled.lastError());
	assert(missingDevice != oled.lastError());

	nowMillis += 6000;
	oled.tick();
	oled.clear();
	assert(oled.error() == Error::InitializationFailed);

	oled.device()->initializes = true;
	assert(oled.begin());
	assert(oled.ready());
	assert(oled.error() == Error::None);
	assert(!*oled.lastError());

	oled.D("Ready");
	nowMillis += 6000;
	oled.tick();
	assert(oled.error() == Error::None);
	assert(!*oled.lastError());

	Wire.acknowledges = false;
	assert(!oled.begin());
	assert(!oled.ready());
	assert(oled.error() == Error::DeviceNotFound);

	Wire.acknowledges = true;
	assert(oled.begin());
	assert(oled.error() == Error::None);
	assert(!*oled.lastError());

	puts("PASS: missing OLED, initialization failure, error replacement/persistence, and recovery clearing.");
}
