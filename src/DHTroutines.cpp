#include <DHTroutines.h>


DHTsensor::DHTsensor(float * _temperature, float * _humidity):
dht(*(new DHT(DHT_PIN, DHT22)))
{
  temperature = _temperature;
  humidity = _humidity;
}

bool DHTsensor::setup()
{
  dht.begin();
  return true;
}

  /*---------> readDHT
  Read temperature and humidity data from DHT sensor
*/
bool DHTsensor::readDHT() {

  bool result = false;

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (isnan(t) || isnan(h)) {
    result = false;
  }
  else{
      *temperature = t;
      *humidity = h;
      result = true;
  }

//  switch (DHT.read22(am2301_PIN)){
//    case DHTLIB_OK:{
//
//      temp = DHT.temperature;
//      humid = DHT.humidity;
//
//      //Out of range error:
//      if ((temp <= -80) || (temp > 60)) {
//        result = 0;
//      } else {
//        result  = 1;
//      }
//      break;}
//
//    case DHTLIB_ERROR_CHECKSUM:
//      //Checksum error
//      result = -1;
//      break;
//
//    case DHTLIB_ERROR_TIMEOUT:
//      //Timeout error:
//      result = -2;
//      break;
//
//    default:
//      //Unknown error:
//      result = -3;
//      break;
//  }
  return result;
}
