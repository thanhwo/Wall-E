#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String message = "I LOVE YOU";
int x;  // vị trí x hiện tại
int textWidth;

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // 0x3C là địa chỉ I2C mặc định
    Serial.println(F("Không tìm thấy màn hình OLED"));
    while(true);
  }

  display.clearDisplay();
  display.setTextSize(2);      // kích cỡ chữ
  display.setTextColor(SSD1306_WHITE);

  // Tính chiều rộng của chuỗi
  textWidth = message.length() * 12; // chữ size 2 ~ 12 pixels/char
  x = SCREEN_WIDTH; // bắt đầu từ ngoài phải màn hình
}

void loop() {
  display.clearDisplay();

  display.setCursor(x, 26); // khoảng giữa chiều cao màn hình
  display.print(message);
  display.display();

  x--; // di chuyển sang trái

  if (x < -textWidth) { // nếu ra khỏi màn hình bên trái thì reset
    x = SCREEN_WIDTH;
  }

  delay(30); // tốc độ chạy chữ
}
