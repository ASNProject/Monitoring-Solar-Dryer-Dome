#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <BH1750.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const long utcOffsetInSeconds = 25200;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "id.pool.ntp.org", utcOffsetInSeconds);

BH1750 GY302;

#include "DHT.h"
#define DHTTYPE DHT22
const int DHTPin = D8;
DHT dht(DHTPin, DHTTYPE);

const int sensorIn = A0;
int mVperAmp = 66;

double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;

const char* ssid = "MSDD";
const char* password = "1234567890";

FirebaseData firebaseData;
FirebaseData firebaseData2;

unsigned long interval=1000;
unsigned long previousMillis=0;

float adc_voltage = 0.0;
float in_voltage = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
float ref_voltage = 5.0;
int adc_value = 0;

void setup(){
  Serial.begin(115200);
  pinMode(DHTPin, INPUT);
  dht.begin();
  Wire.begin(D2,D1);
  GY302.begin();
  lcd.begin();
  lcd.backlight();
  timeClient.begin();
  pinMode(A0, INPUT);
  konekWifi();
  Firebase.begin("https://monitoring-95d93-default-rtdb.firebaseio.com/", "9yWBCeXQvPEwi2Ku5ABOFwSHnnT0a7vsmbIPn3Gb");
}

void konekWifi() {
  WiFi.begin(ssid, password);
  float c = 0;
  float n = 0;
  //memulai menghubungkan ke wifi router
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("."); //status saat mengkoneksikan
    Firebase.setString(firebaseData, "Status", "Not Connected");
  lcd.setCursor(12,1);
  lcd.print("|");
  lcd.setCursor(13,1);
  lcd.print("OFF");
  }

  Firebase.setString(firebaseData, "Status", "Connected");
  Serial.println("Sukses terkoneksi wifi!");
  Serial.println("IP Address:"); //alamat ip lokal
  Serial.println(WiFi.localIP());
  lcd.setCursor(12,1);
  lcd.print("|");
  lcd.setCursor(13,1);
  lcd.print("ON ");
}
void loop(){
  timeClient.update();
  time_t epochTime = timeClient.getEpochTime();
  dht22();
  acs712();
 lightsensor();
}
