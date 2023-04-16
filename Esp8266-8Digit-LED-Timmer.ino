#include <SPI.h>
#include <ESP8266WiFi.h>                    // Needed for EPS8266
#include "MAX7219_8_Digit_Driver.h"
#include <NTPClient.h>
#include <WiFiUdp.h>

// MAX7219 items
#define Number_MAX7219 2        // 2 chips = 24 digits
#define MAX7219_CS  15          // pin the MAX7219's CS pin is connected to
#define Default_Brightness 3    // brightness level 0-15

MAX7219_8_Digit_Driver My_Display(MAX7219_CS, Number_MAX7219);
const char *ssid     = "Haizz";
const char *password = "11235813";
time_t epochTime;
// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

void setup() {

  Serial.begin(115200); 
    // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  timeClient.begin();
  timeClient.setTimeOffset(25200);
  Serial.println("Init done"); 

}

void loop() {
  timeClient.update();
  epochTime = timeClient.getEpochTime();

  doTimming();
  delay(1000);
}

void doTimming(){
  Serial.print("Epoch Time: ");
  Serial.println(epochTime);
  
  String formattedTime = timeClient.getFormattedTime();
  Serial.print("Formatted Time: ");
  Serial.println(formattedTime);  

  int currentHour = timeClient.getHours();
  Serial.print("Hour: ");
  Serial.println(currentHour);  

  int currentMinute = timeClient.getMinutes();
  Serial.print("Minutes: ");
  Serial.println(currentMinute); 
   
  int currentSecond = timeClient.getSeconds();
  Serial.print("Seconds: ");
  Serial.println(currentSecond);  

  String output = String(currentHour);
//  output = "3.14159265358979323846264";
  Serial.println(output);
  My_Display.String_To_Buffer((currentHour < 10 ? String("0") + String(currentHour) : String(currentHour)) + String("-")
    + (currentMinute < 10 ? String("0") + String(currentMinute) : String(currentMinute))  + String("-")
    + (currentSecond < 10 ? String("0") + String(currentSecond) : String(currentSecond))
    + String("11111111"), Default_Brightness);
}
