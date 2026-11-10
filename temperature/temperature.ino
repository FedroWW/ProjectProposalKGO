/*------------------------------------------------*/
// Подключение библиотек для работы с OLED дисплеем
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Подключение библиотек для работы с датчиком DS18B20
#include <OneWire.h>
#include <DallasTemperature.h>
/*------------------------------------------------*/

#define OLED_RESET 7
Adafruit_SSD1306 display(OLED_RESET); // создаём объект "дисплей"

// Пин, к которому подключен датчик температуры (A2 работает как цифровой)
#define ONE_WIRE_BUS A2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
/*------------------------------------------------*/

void setup() {
  // Инициализация дисплея по интерфейсу I2C, адрес 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay(); // очистка дисплея
  display.setTextSize(2); // установка размера шрифта (2 для лучшей читаемости)
  display.setTextColor(WHITE); // установка цвета текста
  display.setCursor(0, 0); // установка курсора в позицию X = 0; Y = 0
  display.println("Hello!"); 
  display.display(); // вывод на экран
  delay(1500); // небольшая пауза, чтобы увидеть приветствие

  // Инициализация библиотеки датчика температуры
  sensors.begin();
}
/*------------------------------------------------*/

void loop() {
  // Запрашиваем температуру у всех датчиков на шине
  sensors.requestTemperatures(); 
  
  // Получаем температуру в градусах Цельсия (индекс 0 - первый найденный датчик на шине)
  float temperatureC = sensors.getTempCByIndex(0);
  
  // Проверяем, не отключен ли датчик (ошибка чтения, например, обрыв провода)
  if (temperatureC == DEVICE_DISCONNECTED_C) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.println("Error:");
    display.println("No sensor");
    display.display();
  } else {
    // Очищаем дисплей перед новым выводом, чтобы цифры не накладывались друг на друга
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.print("T: ");
    display.print(temperatureC);
    display.print(" C");
    
    // Выводим обновленные данные на экран
    display.display();
  }
  
  delay(1000); // Обновляем показания раз в секунду (1000 мс)
}
/*------------------------------------------------*/
