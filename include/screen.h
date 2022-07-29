#pragma once

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

static constexpr int ScreenAddr = 0x3c;

Adafruit_SSD1306 Screen(128, 32, &Wire, -1);