
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

// If using software serial, keep this line enabled
// (you can change the pin numbers to match your wiring):
SoftwareSerial mySerial(3, 2); // CHANGE THIS TO THE HARDWARE ONE FO


// If using hardware serial (e.g. Arduino Mega), comment out the
// above SoftwareSerial line, and enable this line instead
// (you can change the Serial number to match your wiring):

//HardwareSerial mySerial = Serial1;


Adafruit_GPS GPS(&mySerial);


// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences. 
#define GPSECHO  false

// this keeps track of whether we're using the interrupt
// off by default!
boolean usingInterrupt = false;
void useInterrupt(boolean); // Func prototype keeps Arduino 0023 happy

typedef union
{
 float number;
 uint8_t bytes[4];
} FLOATUNION_t;

void GPSSetup()  
{   
  // connect at 115200 so we can read the GPS fast enough and echo without dropping chars
  // also spit it out
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  // Request updates on antenna status, comment out to keep quiet
  GPS.sendCommand(PGCMD_ANTENNA);
  // the nice thing about this code is you can have a timer0 interrupt go off
  // every 1 millisecond, and read data from the GPS for you. that makes the
  // loop code a heck of a lot easier!
  useInterrupt(true);
  delay(1000);
  // Ask for firmware version
  mySerial.println(PMTK_Q_RELEASE);
}


// Interrupt is called once a millisecond, looks for any new GPS data, and stores it
SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
  // if you want to debug, this is a good time to do it!
}

void useInterrupt(boolean v) {
  if (v) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
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

void GPSGetData(){
  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {  
    if (!GPS.parse(GPS.lastNMEA()))
      return;  // we can fail to parse a sentence in which case we should just wait for another
  }
  
  byte array[12] = {}; //byte array ready for sending
  array[0] = (byte)(int)GPS.fix;
  array[1] = (byte)(int)GPS.fixquality;
  if (GPS.fix) {
    lat.number = GPS.latitudeDegrees;    //use float and byte array union data type that i found on stack overflow to turn into byte array 
    array[2] = lat.bytes[0]
    array[3] = lat.bytes[1]
    array[4] = lat.bytes[2]
    array[5] = lat.bytes[3]
    
    lon.number = GPS.longitudeDegrees;
    array[6] = long.bytes[0];
    array[7] = long.bytes[1];
    array[8] = long.bytes[2];
    array[9] = long.bytes[3];
    
    
    
    array[10] = (byte)(int)GPS.altitude;
    array[11] = (byte)(int)GPS.satellites;
  }
  return arr;
}
