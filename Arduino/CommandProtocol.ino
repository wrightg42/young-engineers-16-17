// parse input

void setup()  
{   
  Serial.begin(9600);
  Serial.println("wroks");
  GPSSetup();
}


int senddata(int array){
}

void processCommand(byte* comm)
{
  int operator = comm[0]
  if (operator%2){
    halt();
  }
  else{
    switch (operator/2){
    case 0:
      halt();
      break;
    case 1:
      forward();
      break;
    case 2:
      backward();
      break;
    case 3:
      left();
      break;
    case 4:
      right();
      break;
    case 5:
      byte data[] = GPSGetData();
      byte data[] = {12} + data
      //sendData(data);
      break;
    case 6:
      break;
    case 7:
      break;
    case 8;
      break;
    }
  }
}

