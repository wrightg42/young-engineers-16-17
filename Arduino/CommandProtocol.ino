void ProcessCommand(int command) {
  switch (command) {
    case 0:
      DEBUG_PRINTLN("Stop");
      Stop();
      break;
    case 3:
      DEBUG_PRINTLN("Forward");
      Forward();
      break;
    case 5:
      DEBUG_PRINTLN("Backward");
      Backward();
      break;
    case 6:
      DEBUG_PRINTLN("Left");
      Left();
      break;
    case 9:
      DEBUG_PRINTLN("Right");
      Right();
      break;
    case 10:
      DEBUG_PRINTLN("GPS requested");
      SendGPS();
      break;
    case 12:
      DEBUG_PRINTLN("PI tried to send GPS data");
      break;
    case 15:
      DEBUG_PRINTLN("Radio requested");
      SendRadioScan();
      break;
    case 17:
      DEBUG_PRINTLN("PI tried to send 433 data");
      break;
    default:
      DEBUG_PRINT("Unrecognised command: ");
      DEBUG_PRINTLN(command);
      break;
  }
}
