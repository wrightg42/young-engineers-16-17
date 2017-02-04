// Movement for the Bot

#define left1 22
#define left2 23
#define right1 52
#define right2 53

void MovementSetup(){
  DEBUG_PRINTLN("Movement Setup Begin");
  pinMode(left1, OUTPUT);
  pinMode(left2, OUTPUT);
  pinMode(right1, OUTPUT);
  pinMode(right2, OUTPUT);
  Stop();
  DEBUG_PRINTLN("Movement Setup End");   
}

void Stop(){
  digitalWrite(left1, HIGH);
  digitalWrite(right2, HIGH);
  digitalWrite(left1, HIGH);
  digitalWrite(right2, HIGH);   
}

void Left(){  // dist in arbitrary units
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);
}


void Right(){  // dist in arbitrary units
  digitalWrite(left1, LOW);
  digitalWrite(left2, HIGH);
  digitalWrite(right1, LOW);
  digitalWrite(right2, HIGH);
}


void Forward(){  // dist in arbitrary units
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);   
  digitalWrite(right1, LOW);
  digitalWrite(right2, HIGH);
}


void Backward(){  // dist in arbitrary units
  digitalWrite(left1, LOW);
  digitalWrite(left2, HIGH);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);
}
