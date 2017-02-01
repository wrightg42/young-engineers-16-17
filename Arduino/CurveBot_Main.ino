// CurveBot Main



void setup()  
{   
  Serial.begin(9600);
  Serial.println("wroks");
  GPSSetup();
}


int senddata(int array){
}

void loop()
{
  int operator;
  operator = 0; //TODO make equal to first byte of recieved array
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
      break;
    case 6:
      break;
    case 7:
      ReturnData();
      break;
      case 8;
      break;
    }
  }
}

