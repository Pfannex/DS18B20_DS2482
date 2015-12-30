# DS18B20_DS2482
**DS2482 - I2C to 1-Wire bridge used with ESP8266 WIFI on ARDUINO**

```

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

void setup() {
  
  Serial.begin(115200);
  Wire.begin(13, 12);           //Start I²C pin 12=SCL 13=SDA
  DS2482.reset();
  Serial.println("");
  Serial.println("");

//search for devices and print address = true  
  DevicesCount = DS2482.devicesCount(true);

  DS18B20_devices.begin();
  Serial.println("");
}

void loop() {
 
  for (uint8_t i = 0; i < DevicesCount; i++){
    DS18B20_devices.requestTemperaturesByIndex(i);
    Serial.print("device #");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(DS18B20_devices.getTempCByIndex(i));
  }
  Serial.println("");
  delay(5000);

}
```
