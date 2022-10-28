void lightsensor(){
  unsigned long currentMillis = millis();
  if ((unsigned long)(currentMillis - previousMillis) >= interval){
      int lux = GY302.readLightLevel();
      lcd.setCursor(0,1);
      lcd.print("S3:");
      lcd.setCursor(3,1);
      lcd.print(lux);
      lcd.setCursor(7,1);
      lcd.print("lux");
      Serial.print("Light: ");
      Serial.print(lux);
      Firebase.setInt(firebaseData, "/Lux", lux);
      Serial.println(" lux");
      time_t epochTime = timeClient.getEpochTime();
      struct tm *ptm = gmtime ((time_t *)&epochTime);
      int Day = ptm->tm_mday;
      int Month = ptm->tm_mon+1;
      int Year = ptm->tm_year+1900;
      String dmy = "/Luxmeter/"+String(Day)+"-"+ String(Month)+"-" + String(Year) + "/" + String(timeClient.getHours()); 
      Firebase.setInt(firebaseData, dmy , lux);
      previousMillis = millis();
  }
}
