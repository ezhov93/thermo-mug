
#include <Arduino.h>
#include "screen.h"
#include "temperaturetask.h"


#include "task.h"



TemperatureTask temperatureTask(10);

const auto &FontCap = FreeSerif9pt7b;

void showBattary(int percent) {
  constexpr int width = 10;
  const int height = Screen.height();
  const int startX = Screen.width() - width;
  const int centerX = (startX + width / 2);

  // draw hat
  const int hatHeight = height / 11;
  const int hatWidth = width / 2;
  Screen.fillRect(centerX - hatWidth / 2, 0, hatWidth, hatHeight, WHITE);
  // draw body
  const int bodyHeight = height - hatHeight;
  const int bodyWidth = width;
  Screen.drawRect(startX, hatHeight, bodyWidth, bodyHeight, WHITE);
  // draw bars
  int bars;
  if (percent >= 66) {
    bars = 3;
  } else if (percent >= 33) {
    bars = 2;
  } else if (percent > 0) {
    bars = 1;
  } else {
    bars = 0;
  }
  constexpr int lineWidth = 1;
  constexpr int barsLineOffset = 1;
  constexpr int numberOfBars = 3;
  const int barsWidth = width - (barsLineOffset + lineWidth) * 2;
  const int barsHeight =
      ((bodyHeight - lineWidth * 2) / numberOfBars) - barsLineOffset;
  uint8_t offset = height - barsHeight - barsLineOffset - lineWidth;
  for (uint8_t i = 0; i < bars; i++) {
    Screen.fillRect(centerX - barsWidth / 2, offset, barsWidth, barsHeight,
                    WHITE);
    offset -= barsHeight + barsLineOffset;
  }
}

void setup() {
  Screen.begin(SSD1306_SWITCHCAPVCC, ScreenAddr);
  Screen.setTextColor(SSD1306_WHITE);
  Screen.setRotation(180);
  Screen.clearDisplay();
  Screen.print("Startup system...");
  Screen.display();
  temperatureTask.init();
}

void loop() {
  Screen.clearDisplay();
  temperatureTask.update();
    showBattary(50);
  Screen.display();
}
