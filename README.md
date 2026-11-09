# MDS_Display

Four-line diagnostic output for a 128×32 SSD1306 OLED display, with shared I2C bus support.

## Requirements

- **Platforms:** ESP32.
- **Dependencies:** Adafruit SSD1306 and Adafruit GFX Library.

## Installation

Place the `MDS_Display` folder in your Arduino sketchbook's `libraries` directory. Install the required board package and dependencies using the Arduino IDE.

## Example

Display short diagnostic messages on a 128×32 SSD1306 I2C OLED. Install **Adafruit SSD1306** and **Adafruit GFX Library** along with **MDS_Display**.

Set `SDA_PIN` and `SCL_PIN` to match your board and wiring. This example uses I2C address `0x3C` and rotation `0` (unrotated).

```cpp
#include <Wire.h>
#include <MDS_Display.h>

constexpr int SDA_PIN = 21;
constexpr int SCL_PIN = 22;

MDS_Display display(Wire, 0x3C, 0);

void setup() {
    Serial.begin(115200);
    Wire.begin(SDA_PIN, SCL_PIN);

    if (!display.begin()) {
        Serial.println("OLED initialization failed");
        return;
    }

    display.D("Hello, world!");
    display.D("Display ready");
}

void loop() {
    display.tick();
}
```

## Documentation

Detailed design and API documentation: [MDS_Display](https://home.marcspencer.com/mds-display).

## License

Firmware and software: **MPL-2.0**. Documentation and website: **CC BY-SA 4.0**. Any hardware design files and Gerbers: **CERN-OHL-W-2.0**.

## Contributions

Contributions require a Developer Certificate of Origin (DCO) sign-off. Use `git commit -s` to add a `Signed-off-by` line to each contribution commit.

## Initialization API

`begin()` is the initialization method; the former `setup()` name is removed.

Use `device()` to borrow the underlying `Adafruit_SSD1306*` for direct drawing.
The former `getDevice()` name is removed.

## Initialization errors

`error()` returns `MDS_Display::Error::None`, `DeviceNotFound`, or
`InitializationFailed`. `lastError()` describes that code and is empty for `None`.
`DeviceNotFound` means the I2C address did not acknowledge; `InitializationFailed`
means the SSD1306 initialization call failed after the address acknowledged.

A new object has no recorded error. Failed `begin()` calls replace the error;
a successful `begin()` clears it. Queries, drawing, clearing, and scrolling leave
it unchanged. These codes describe initialization, not continuous device health.

Run `sh tests/run.sh` for host checks of initialization failures and recovery.
