
//
//    FILE: dht11_test.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.01
// PURPOSE: DHT library test sketch for DHT11 && Arduino
//     URL:
//
// Released to the public domain
//

#include <dht.h>

dht DHT;

#define DHT11_PIN 5

const int PIN_LED_1 = 2;
const int PIN_RELAY_1 = 7;
const int PIN_CO2 = A0;
const int PIN_RELAY_2 = 6;
int x = 3;
int sum = 0;
int m[10];

void setup()
{
  x = 51;
//  Serial1.begin(9600);
//  Serial1.println("Hello galileo");
  Serial.begin(115200);
  Serial.println("DHT TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT_LIB_VERSION);
  Serial.println();
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)");
  pinMode(PIN_RELAY_1, OUTPUT);
  pinMode(PIN_RELAY_2, OUTPUT);
  digitalWrite(PIN_RELAY_1, HIGH);
  
float t = 25; //sum_t;
float h = 20; //sum_h;
for(int i = 0; i < 10; i++) {
   m[i] == t;
   sum += t;
}
 Serial.println(sum);
}

void loop()
{
  
  // READ DATA
  Serial.print("DHT11, \t");
  int chk = DHT.read11(DHT11_PIN);
  switch (chk)
  {
    case DHTLIB_OK:  
		Serial.print("OK,\t"); 
		break;
    case DHTLIB_ERROR_CHECKSUM: 
		Serial.print("Checksum error,\t"); 
		break;
    case DHTLIB_ERROR_TIMEOUT: 
		Serial.print("Time out error,\t"); 
		break;
    case DHTLIB_ERROR_CONNECT:
        Serial.print("Connect error,\t");
        break;
    case DHTLIB_ERROR_ACK_L:
        Serial.print("Ack Low error,\t");
        break;
    case DHTLIB_ERROR_ACK_H:
        Serial.print("Ack High error,\t");
        break;
    default: 
		Serial.print("Unknown error,\t"); 
		break;
  }
  // DISPLAY DATA 
//  int sum_h = 0;
//  int sum_t = 0;
 
  
//  for (int i = 0; i < 5; i++) {
//    Serial.println(massiv[i]);
//    
//  Serial.print(DHT.humidity, 1);
//  Serial.print(",\t");
//  Serial.println(DHT.temperature, 1);

  
  
//  sum_h += DHT.humidity;
//  sum_t += DHT.temperature;
  
delay(1000);
int r = (int)Serial.read();
float t = DHT.temperature;//sum_t / 5; //DHT.temperature;
float h = DHT.humidity; //sum_h / 5;//DHT.humidity;
float c = analogRead(PIN_CO2);

if ((r == 49) || (r == 50) || (r == 51))
  x = r;
 
  Serial.print(h, 1);
  Serial.print(",\t");
  Serial.print(t, 1);
  Serial.print(",\t");
  Serial.print(c, 1);
  Serial.print(",\t");
  if (x == 49)
  Serial.println("OFF");
  if (x == 50)
  Serial.println("ON");
  
 if (x == 51)
  Serial.println("AUTO");

if (x == 49) {
  digitalWrite( PIN_RELAY_1, LOW );
  digitalWrite( PIN_RELAY_2, LOW );
}
  else 
  if (x == 50) {
    digitalWrite( PIN_RELAY_1, HIGH);
    digitalWrite( PIN_RELAY_2, HIGH );
  }
  else {
 
sum -= m[0];
for(int i = 0; i < 9; i++ ) {
    m[i] = m[i + 1]; 
  }
  m[9] = t;
  sum += t;  
 
 //float vl = h - t;
 //Serial1.println(vl);

//if (t > 23) {
//  digitalWrite( PIN_RELAY_1, HIGH);
//  digitalWrite( PIN_RELAY_2, LOW );
//}
//else {
//  if (c > 320){
//  digitalWrite( PIN_RELAY_1, HIGH);
//  digitalWrite( PIN_RELAY_2, LOW );
//  }


}
 if (c > 400) {
   if ((t > 24) || (h > 35)) {
     digitalWrite( PIN_RELAY_2, HIGH);
    digitalWrite( PIN_RELAY_1, HIGH );
}else {
    digitalWrite( PIN_RELAY_2, HIGH);
    digitalWrite( PIN_RELAY_1, LOW );
  }
 }
  else
  if ((t > 24) || (h > 35)) {
    digitalWrite( PIN_RELAY_1, HIGH );
    digitalWrite( PIN_RELAY_2, LOW );
  }
  else {
    digitalWrite( PIN_RELAY_1, LOW );
    digitalWrite( PIN_RELAY_2, LOW );
  }
  
}  
 
}
//
// END OF FILE
//
