#include <Adafruit_GPS.h>
#include <DueTimer.h>

Adafruit_GPS GPS(&Serial1);

typedef union
{
  float number;
  uint8_t bytes[4];
} FLOATUNION_t;

FLOATUNION_t lat;
FLOATUNION_t lon;

void GPSUpdate(){
  char c = GPS.read();
}

void GPSSetup()
{
  DEBUG_PRINTLN("Begin GPS Setup");
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  GPS.sendCommand(PGCMD_ANTENNA);  // Request updates on antenna status
  delay(1000);
  Timer2.attachInterrupt(GPSUpdate);
  Timer2.start(1000);
  DEBUG_PRINTLN("End GPS Setup");
}

void SendGPS() {
  byte byteGPSData[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };;
  GetGPSData(&byteGPSData[0]);
  int gpsData[13] = { 12 };
  for (int i = 0; i < 12; i++) {
    gpsData[i + 1] = byteGPSData[i];
  }
  delayMicroseconds(10000); // Delay 10ms, giving pi time to swap to read mode
  NRFSend(gpsData, 13);
}

void GetGPSData(byte *pdata) {  
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA())) {
      return;
    }
  }
  
  pdata[0] = (byte)(int)GPS.fix;
  DEBUG_PRINT("Fix: ");
  DEBUG_PRINTLN(GPS.fix);

  pdata[1] = (byte)(int)GPS.fixquality;
  DEBUG_PRINT("Fix Quality: ");
  DEBUG_PRINTLN(GPS.fixquality);

  if (GPS.fix) {
    // use float and byte array union data type to turn float into byte array
    DEBUG_PRINT("Latitude: ");
    DEBUG_PRINTLN2(GPS.latitudeDegrees, 7);
    lat.number = GPS.latitudeDegrees;
    pdata[2] = lat.bytes[0];
    pdata[3] = lat.bytes[1];
    pdata[4] = lat.bytes[2];
    pdata[5] = lat.bytes[3];

    DEBUG_PRINT("Longitude: ");
    DEBUG_PRINTLN2(GPS.longitudeDegrees, 7);
    lon.number = GPS.longitudeDegrees;
    pdata[6] = lon.bytes[0];
    pdata[7] = lon.bytes[1];
    pdata[8] = lon.bytes[2];
    pdata[9] = lon.bytes[3];

    pdata[10] = (byte)(int)GPS.altitude;
    DEBUG_PRINT("Altitude: ");
    DEBUG_PRINTLN(GPS.altitude);

    pdata[11] = (byte)(int)GPS.satellites;
    DEBUG_PRINT("Satellites: ");
    DEBUG_PRINTLN(GPS.satellites);
  }
}
