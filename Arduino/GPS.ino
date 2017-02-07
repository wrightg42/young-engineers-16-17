/*#include <Adafruit_GPS.h>
//#include <SoftwareSerial.h>

//HardwareSerial mySerial = Serial2;


Adafruit_GPS GPS(&Serial2);

#define GPSECHO  false // turn echoing to serial off

boolean usingInterrupt = false;
void useInterrupt(boolean); // Func prototype keeps Arduino 0023 happy

typedef union
{
 float number;
 uint8_t bytes[4];
} FLOATUNION_t;




// Interrupt is called once a millisecond, looks for any new GPS data, and stores it
SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
}

void useInterrupt(boolean v) {
  if (v) {
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
  } else {
    // do not call the interrupt function COMPA anymore
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
  }
}

FLOATUNION_t lat;
FLOATUNION_t lon;


void GPSSetup()  
{   
  DEBUG_PRINTLN("Begin GPS Setup");
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  GPS.sendCommand(PGCMD_ANTENNA);  // Request updates on antenna status, comment out to keep quiet
  useInterrupt(true);
  DEBUG_PRINTLN(PMTK_Q_RELEASE);  // Ask for firmware version
  DEBUG_PRINTLN("End GPS Setup");
}

byte* GPSGetData(){
  if (GPS.newNMEAreceived()) {  
    if (!GPS.parse(GPS.lastNMEA()))
      return {}; //return null if parse fails
  }
  
  byte arr[12] = {}; // byte array ready for sending
  arr[0] = (byte)(int)GPS.fix;
  arr[1] = (byte)(int)GPS.fixquality;
  if (GPS.fix) {
    // use float and byte array union data type to turn float into byte array 
    lat.number = GPS.latitudeDegrees;    
    arr[2] = lat.bytes[0];
    arr[3] = lat.bytes[1];
    arr[4] = lat.bytes[2];
    arr[5] = lat.bytes[3];
    
    lon.number = GPS.longitudeDegrees;
    arr[6] = lon.bytes[0];
    arr[7] = lon.bytes[1];
    arr[8] = lon.bytes[2];
    arr[9] = lon.bytes[3];
    
    arr[10] = (byte)(int)GPS.altitude;
    arr[11] = (byte)(int)GPS.satellites;
  }
  return arr;
}*/
