  
//ESP8266
  #include <ESP8266WiFi.h>
//Tools
  #include <Wire.h>             //I²C

//DS2482
  #include <DS2482.h>
  #include <DS18B20_DS2482.h>
  DS2482 DS2482(0);   // 0 = 0x18
  DS18B20_DS2482 DS18B20_devices(&DS2482);
  DeviceAddress DS18B20_Address;
  int DevicesCount = 0;
  int TemperatueCount = 0;

  unsigned long lastTemp = 0, tempScanInterval = 60 * 1000 * 1000;
  
void setup() {
  
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n\nDS2482-100 Test\n\n");
  delay(1000);

  Serial.print("starting I2C: ");
  Wire.begin(SDA, SCL);           //Start I²C
  Serial.println("ok");
  scanI2C();

  Serial.print("DS2482-100 reset: ");
  DS2482.reset();
  Serial.println("ok");

//search for devices and print address = true  
  Serial.print("DS2482-100 scan: \n");
  DevicesCount = DS2482.devicesCount(true);
  Serial.println("devices: #" + (String)DevicesCount);

  delay(10000);
  Serial.print("DS18B20 begin: ");
  DS18B20_devices.begin();
  Serial.println("ok");
  TemperatueCount = DS18B20_devices.getDeviceCount();
  Serial.println("devices: #" + (String)TemperatueCount);
}

void loop() {
  unsigned long currMicros = micros();
  unsigned long nextTemp;

  nextTemp = lastTemp + tempScanInterval;
  delay(100);
  
  // temperature
  if (nextTemp < currMicros) {
    for (uint8_t i = 0; i < TemperatueCount; i++){
      DS18B20_devices.requestTemperaturesByIndex(i);
      Serial.print("temp #");
      Serial.print(i);
      Serial.print(": ");
      Serial.println(DS18B20_devices.getTempCByIndex(i));
    }

    lastTemp = currMicros;
  }
}

void scanI2C() {
  for(byte address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");
    }    
  }
}
