#include <Adafruit_GPS.h>
#include <DueTimer.h>

Adafruit_GPS GPS(&Serial1);

typedef union
{
 float number;
 uint8_t bytes[4];
} FLOATUNION_t;


// Interrupt is called once a millisecond, looks for any new GPS data, and stores it
void GPSUpdate(){
  char c = GPS.read();
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
  delay(1000);
  DEBUG_PRINTLN(PMTK_Q_RELEASE);  // Ask for firmware version
  DEBUG_PRINTLN("End GPS Setup");
  Timer2.attachInterrupt(GPSUpdate);
  Timer2.start(1000);
}

byte* GPSGetData(){
  if (GPS.newNMEAreceived()) {  
    if (!GPS.parse(GPS.lastNMEA()))
      return {}; //return null if parse fails
  }
  
  byte arr[12] = {}; // byte array ready for sending
  arr[0] = (byte)(int)GPS.fix;
  DEBUG_PRINT("Fix: "); 
  DEBUG_PRINTLN(GPS.fix);
  arr[1] = (byte)(int)GPS.fixquality;
  DEBUG_PRINT("Fix Quality: "); 
  DEBUG_PRINTLN(GPS.fixquality);
  if (GPS.fix) {
    // use float and byte array union data type to turn float into byte array
    DEBUG_PRINT("Latitude: "); 
    DEBUG_PRINTLN2(GPS.latitudeDegrees, 5);
    lat.number = GPS.latitudeDegrees;    
    arr[2] = lat.bytes[0];
    arr[3] = lat.bytes[1];
    arr[4] = lat.bytes[2];
    arr[5] = lat.bytes[3];

    DEBUG_PRINT("Longitude: "); 
    DEBUG_PRINTLN2(GPS.longitudeDegrees, 5);
    lon.number = GPS.longitudeDegrees;
    arr[6] = lon.bytes[0];
    arr[7] = lon.bytes[1];
    arr[8] = lon.bytes[2];
    arr[9] = lon.bytes[3];
    
    arr[10] = (byte)(int)GPS.altitude;
    DEBUG_PRINT("Altitude: "); 
    DEBUG_PRINTLN(GPS.altitude);
    arr[11] = (byte)(int)GPS.satellites;
    DEBUG_PRINT("Satellites: "); 
    DEBUG_PRINTLN(GPS.satellites);
  }
  return arr;
}
