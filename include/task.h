#pragma once

#include <Arduino.h>

class Task {
 public:
  Task(const int period) : _period(period), _timer(period) {}
  virtual ~Task() {}

  virtual void init() = 0;

  void update() {
    if (_period > 0) {
      const uint32_t timeLeft = millis() - _timer;
      if (timeLeft >= _period) {
        _timer += _period * (timeLeft / _period);
        run();
      }
    } else {
      run();
    }
  }

 protected:
  virtual void run() = 0;

 private:
  const int _period;
  uint32_t _timer;
};