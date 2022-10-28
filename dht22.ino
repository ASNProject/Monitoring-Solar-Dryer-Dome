void dht22(){
  float h = dht.readHumidity();
  Firebase.setInt(firebaseData, "/Humidity", h);
  Serial.print("hum ");
  Serial.print(h);
  Serial.print(" ");
  float t = dht.readTemperature();
  Firebase.setInt(firebaseData, "/Temperature", t);
  lcd.setCursor(8,0);
  lcd.print("S2:");
  lcd.setCursor(11,0);
  lcd.print(t);
  lcd.setCursor(15,0);
  lcd.print("C");
  time_t epochTime = timeClient.getEpochTime();
  struct tm *ptm = gmtime ((time_t *)&epochTime);
  int Day = ptm->tm_mday;
  int Month = ptm->tm_mon+1;
  int Year = ptm->tm_year+1900;
  String dmy = "/Temp/"+String(Day)+"-"+ String(Month)+"-" + String(Year) + "/" + String(timeClient.getHours()); 
  String dmy2 = "/Hum/"+String(Day)+"-"+ String(Month)+"-" + String(Year) + "/" + String(timeClient.getHours());
  Firebase.setInt(firebaseData, dmy , t);
  Firebase.setInt(firebaseData, dmy2 , h);
  Serial.print("hum ");
  Serial.println(t);
  delay(1000);
}
