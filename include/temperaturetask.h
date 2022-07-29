#pragma once

#include <Arduino.h>
#include <DallasTemperature.h>
#include <Fonts/FreeSerif18pt7b.h>
#include <Fonts/FreeSerif9pt7b.h>
#include <OneWire.h>
#include <Wire.h>

#include "task.h"

class TemperatureTask : public Task {
 public:
  TemperatureTask(const byte pin)
      : Task(1000 / 25), _oneWire(pin), _sensor(&_oneWire) {}

  void init() final {
    _sensor.begin();
    _sensor.setResolution(12);
  }

 private:
  void run() final {
    _sensor.requestTemperatures();
    show();
  }

  void show() {
    static const GFXfont &Font = FreeSerif18pt7b;
    const auto t = _sensor.getTempCByIndex(0);
    Screen.setFont(&Font);
    constexpr int degreeOffset = 30;
    Screen.setCursor(0, degreeOffset);
    Screen.print(t, 1);
    Screen.setCursor(Screen.getCursorX(), degreeOffset / 3);
    Screen.print(".");
    Screen.setCursor(Screen.getCursorX(), degreeOffset);
    Screen.print("C");
  }

 private:
  OneWire _oneWire;
  DallasTemperature _sensor;
};