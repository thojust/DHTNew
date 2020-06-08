//
//    FILE: dhtnew_array.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
// PURPOSE: DHTNEW library test sketch for Arduino
//     URL: https://github.com/RobTillaart/DHTNew

// HISTORY:
// 0.1.0    2020-04-25 initial version
// 0.1.1    2020-04-30 replaced humidity and temperature with functions
// 0.1.2    2020-06-08 improved error handling
//
// FRONT left to right
// pin 1 : VCC
// pin 2 : DATA
// pin 3 : NC
// PIN 4 : GND

#include <dhtnew.h>

DHTNEW kitchen(2);
DHTNEW living(3);
DHTNEW outside(4);

DHTNEW ar[3] = { kitchen, living, outside };

void setup()
{
  Serial.begin(115200);
  Serial.println("dhtnew_test.ino");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHTNEW_LIB_VERSION);
  Serial.println();

  for (int idx = 0; idx < 3; idx++)
  {
    test(idx);
  }
}

void loop()
{
}

void test(int idx)
{
  // READ DATA
  uint32_t start = micros();
  int chk = ar[idx].read();
  uint32_t stop = micros();

  switch (chk)
  {
    case DHTLIB_OK:
      Serial.print("OK,\t");
      break;
    case DHTLIB_ERROR_CHECKSUM:
      Serial.print("Checksum error,\t");
      break;
    case DHTLIB_ERROR_TIMEOUT_A:
      Serial.print("Time out A error,\t");
      break;
    case DHTLIB_ERROR_TIMEOUT_C:
      Serial.print("Time out C error,\t");
      break;
    case DHTLIB_ERROR_TIMEOUT_D:
      Serial.print("Time out D error,\t");
      break;
    case DHTLIB_ERROR_SENSOR_NOT_READY:
      Serial.print("Sensor not ready,\t");
      break;
    case DHTLIB_ERROR_BIT_SHIFT:
      Serial.print("Bit shift error,\t");
      break;
    default:
      Serial.print("Unknown: ");
      Serial.print(chk);
      Serial.print(",\t");
      break;
  }

  // DISPLAY DATA
  Serial.print(ar[idx].getHumidity(), 1);
  Serial.print(",\t");
  Serial.print(ar[idx].getTemperature(), 1);
  Serial.print(",\t");
  uint32_t duration = stop - start;
  Serial.print(duration);
  Serial.print(",\t");
  Serial.println(ar[idx].getType());
  delay(500);
}

// -- END OF FILE --
