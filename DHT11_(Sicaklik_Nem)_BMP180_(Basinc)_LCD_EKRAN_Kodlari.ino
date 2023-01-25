#include <dht11.h>
#include <Versalino.h>
#include <Wire.h>
#include <SFE_BMP180.h>
SFE_BMP180 bmp180;  // bmp180 adında bir sensör nesnesi oluştur


#include <LiquidCrystal.h>
#include <dht11.h> // dht11 kütüphanesini ekliyoruz.
#define DHT11PIN 7 // DHT11PIN olarak Dijital 13 ü belirliyoruz.
LiquidCrystal lcd( 12, 11, 5, 4, 3, 2);
dht11 DHT11;

void setup()
{
  Serial.begin(9600);
  
  bmp180.begin();
  lcd.begin(16, 2);
}

void loop()
{

  // -------------------------[ BMP180 ]-------------------------------
    char durum;  // Sensörden okunan durum
    double T, P, T_Son, P_Son;  // Sıcaklık ve basınç değişkenleri
    bool basarili = false;  // Sensör çalışıyor mu bilgisi değişkeni
    durum = bmp180.startTemperature();
    if (durum != 0) {
      durum = bmp180.getTemperature(T);
      if (durum != 0) {
        durum = bmp180.startPressure(3);
        if (durum != 0) {
          durum = bmp180.getPressure(P, T);
          if (durum != 0) {
            T_Son = T;
            P_Son = P;
            Serial.print("Basınç: ");
            Serial.print(P);
            Serial.println(" hPa");
            Serial.print("Sıcaklık: ");
            Serial.print(T);
            Serial.println(" C");
          }
        }
      }
    }  

  // -------------------------[ DHT11 ]-------------------------------
  
  
  // Bir satır boşluk bırakıyoruz serial monitörde.

  // Sensörün okunup okunmadığını konrol ediyoruz. 
  // chk 0 ise sorunsuz okunuyor demektir. Sorun yaşarsanız
  // chk değerini serial monitörde yazdırıp kontrol edebilirsiniz.
  int chk = DHT11.read(DHT11PIN);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Sicaklik: ");
  lcd.print((float)DHT11.temperature);
  lcd.setCursor(10,1);
  lcd.print("Derece"); 
   
  delay(1000);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Nem: ");
  lcd.print("% "); 
  lcd.print((float)DHT11.humidity);

  lcd.setCursor(0,1);
  lcd.print("Basinc: ");
  lcd.print((float)P_Son);
   
  delay(1000);
  
}
