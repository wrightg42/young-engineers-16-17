#define left1 4
#define left2 5
#define right1 6
#define right2 7

#define left1bias 255
#define left2bias 255
#define right1bias 230
#define right2bias 230


void MovementSetup() {
  DEBUG_PRINTLN("Movement Setup Begin");
  pinMode(left1, OUTPUT);
  pinMode(left2, OUTPUT);
  pinMode(right1, OUTPUT);
  pinMode(right2, OUTPUT);
  Stop();
  DEBUG_PRINTLN("Movement Setup End");
}

void Stop() {

  digitalWrite(left1, LOW);
  digitalWrite(right1, LOW);
  digitalWrite(left2, LOW);
  digitalWrite(right2, LOW);
}

void Right() {
#ifdef DONTMOVE
  return;
#endif
  analogWrite(left1, left1bias - 20);
  digitalWrite(left2, LOW);
  analogWrite(right1, right1bias);
  digitalWrite(right2, LOW);
}


void Left() {
#ifdef DONTMOVE
  return;
#endif
  digitalWrite(left1, LOW);
  analogWrite(left2, left2bias);
  digitalWrite(right1, LOW);
  analogWrite(right2, right2bias);
}


void Forward() {
#ifdef DONTMOVE
  return;
#endif
  analogWrite(left1, left1bias);
  digitalWrite(left2, LOW);
  digitalWrite(right1, LOW);
  analogWrite(right2, right2bias);
}


void Backward() {
#ifdef DONTMOVE
  return;
#endif
  digitalWrite(left1, LOW);
  analogWrite(left2, left2bias);
  analogWrite(right1, right1bias);
  digitalWrite(right2, LOW);
}
