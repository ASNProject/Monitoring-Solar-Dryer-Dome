void acs712(){
   // Read the Analog Input
   adc_value = analogRead(sensorIn);
   
   // Determine voltage at ADC input
   adc_voltage  = (adc_value * ref_voltage) / 1024.0; 
   
   // Calculate voltage at divider input
   in_voltage = adc_voltage / (R2/(R1+R2)) ; 
   
   // Print results to Serial Monitor to 2 decimal places
  Serial.print("Input Voltage = ");
  Serial.println(in_voltage, 2);
  

    Firebase.setInt(firebaseData, "/Watt", in_voltage);
    lcd.setCursor(0,0);
    lcd.print("S1:");
    lcd.setCursor(3,0);
    lcd.print(in_voltage, 2);
    lcd.setCursor(6,0);
    lcd.print("V");
    int dates = timeClient.getMinutes();
    int det = timeClient.getSeconds();
    
      time_t epochTime = timeClient.getEpochTime();
      struct tm *ptm = gmtime ((time_t *)&epochTime);
      int Day = ptm->tm_mday;
      int Month = ptm->tm_mon+1;
      int Year = ptm->tm_year+1900;
      String dmy = "/Voltage/"+String(Day)+"-"+ String(Month)+"-" + String(Year) + "/" + String(timeClient.getHours()); 
      Firebase.setInt(firebaseData, dmy , in_voltage);
    
    //Firebase.setInt(firebaseData, dmy , in_voltage);
    Serial.println(timeClient.getHours());
    delay(500);

 }

 
