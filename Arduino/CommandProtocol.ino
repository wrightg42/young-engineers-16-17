void ProcessCommand(int command) {
  if (command % 2) {
    Stop();
    DEBUG_PRINTLN("Corrupted message");
  }  else {
    switch (command / 2) {
      case 0:
        DEBUG_PRINTLN("Stop");
        Stop();
        break;
      case 1:
        DEBUG_PRINTLN("Forward");
        Forward();
        break;
      case 2:
        DEBUG_PRINTLN("Backward");
        Backward();
        break;
      case 3:
        DEBUG_PRINTLN("Left");
        Left();
        break;
      case 4:
        DEBUG_PRINTLN("Right");
        Right();
        break;
      case 5:
        DEBUG_PRINTLN("GPS requested");
        break;
      case 6:
        DEBUG_PRINTLN("PI tried to send GPS data");
        break;
      case 7:
        DEBUG_PRINTLN("Radio requested");
        ScanRadio();
        break;
      case 8:
        DEBUG_PRINTLN("PI tried to send 433 data");
        break;
      default:
        DEBUG_PRINT("Unrecognised command: ");
        DEBUG_PRINTLN(command);
        break;
    }
  }
}
