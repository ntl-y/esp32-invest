#include <Arduino.h>
#include <U8g2lib.h>
#include <WiFi.h>
#include <HTTPClient.h>


#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

const char* ssid = "Honor 9";
const char* password = "qwerty1234";

String serverName = "http://192.168.1.1:8999/";

U8G2_ST7565_ZOLEN_128X64_F_4W_SW_SPI u8g2(U8G2_R0,/* clock=*/ 27, /* data=*/ 26, /* cs=*/ 13, /* dc=*/ 14, /* reset=*/ 12);

void setup(void) {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Подключение к Wi-Fi...");
  }
  Serial.println("Подключено к Wi-Fi!");
  Serial.println(WiFi.localIP());

  HTTPClient http;
  http.begin(serverName);

    // Отправляем GET-запрос
  int httpCode = http.GET();

  if (httpCode > 0) {
    // Если ответ успешный
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload); // Выводим ответ на Serial Monitor
    }
  } else {
    Serial.println("Ошибка при отправке GET-запроса!");
  }

  http.end(); // Завершаем сеанс HTTP

  u8g2.begin();
  u8g2.sendF("ca", 0xa0, 0x41);
}

void loop(void) {
  u8g2.clearBuffer();				
  u8g2.enableUTF8Print(); 
  u8g2.setFont(u8g2_font_6x13B_t_cyrillic);	
  u8g2.setCursor(4, 22);
  u8g2.setContrast (80);
   u8g2.print("Привет");
    u8g2.setFont(u8g2_font_cu12_t_cyrillic);
    u8g2.setCursor(4, 42);
    u8g2.print("Тест 123 test");
  u8g2.sendBuffer();					
  delay(1000);
}