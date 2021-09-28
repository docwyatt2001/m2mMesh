void loggingLevelView()
{
    if(drawWholeUi)
    {
      moveToXy(80,24);
      eraseScreen();
      moveToXy(25,1);
      drawTitle(F("Logging configuration"));
      printAtXy(3,2, F("L - ----------- NODES_TO_LOG----------- "));
      printAtXy(3,3, F("K - ----------- ALL_SENT_PACKETS ------ "));
      printAtXy(3,4, F("J - ----------- ALL_RECEIVED_PACKETS -- "));
      printAtXy(3,5, F("I - ----------- WIFI_POWER_MANAGEMENT - "));
      printAtXy(3,6, F("H - ----------- BUFFER_MANAGEMENT----- "));
      printAtXy(3,7, F("G - ----------- SCANNING -------------- "));
      printAtXy(3,8, F("F - ----------- PEER_MANAGEMENT ------- "));
      printAtXy(3,9, F("E - ----------- USER_DATA_SEND -------- "));
      printAtXy(3,10,F("D - ----------- USER_DATA_RECEIVED ---- "));
      printAtXy(3,11,F("C - ----------- USER_DATA_FORWARDING -- "));
      printAtXy(3,12,F("B - ----------- NHS_SEND -------------- "));
      printAtXy(3,13,F("A - ----------- NHS_RECEIVED ---------- "));
      printAtXy(3,14,F("9 - ----------- NHS_FORWARDING -------- "));
      printAtXy(3,15,F("8 - ----------- OGM_SEND -------------- "));
      printAtXy(3,16,F("7 - ----------- OGM_RECEIVED ---------- "));
      printAtXy(3,17,F("6 - ----------- OGM_FORWARDING -------- "));
      printAtXy(3,18,F("5 - ----------- ELP_SEND -------------- "));
      printAtXy(3,19,F("4 - ----------- ELP_RECEIVED ---------- "));
      printAtXy(3,20,F("3 - ----------- ELP_FORWARDING -------- "));
      printAtXy(3,21,F("2 - ----------- INFORMATION------------ "));
      printAtXy(3,22,F("1 - ----------- WARNINGS -------------- "));
      printAtXy(3,23,F("0 - ----------- ERRORS ---------------- "));
      moveToXy(1,24);
      inverseOn();Serial.print('0');inverseOff();inverseOn();Serial.print('-');Serial.print('l');inverseOff();Serial.print(F(" toggle logging | "));
      Serial.print(F("Change "));inverseOn();Serial.print('v');inverseOff();Serial.print(F("iew"));
    }
    if(drawWholeUi || loggingLevelChanged == true)
    {
      loggingLevelChanged = false;
      drawWholeUi = false;
      if(logAllNodes)
      {
        printAtXy(43,2, F("All         "));
      }
      else
      {
        uint8_t originatorMac[6]; //temporary MAC address
        m2mMesh.macAddress(currentlyViewedOriginator,originatorMac); //retrieve MAC address
        moveToXy(43,2);
        Serial.printf("%02x/%02x:%02x:%02x:%02x:%02x:%02x",currentlyViewedOriginator,originatorMac[0],originatorMac[1],originatorMac[2],originatorMac[3],originatorMac[4],originatorMac[5]);
      }
      for(uint8_t i = 0; i<21 ;i++)
      {
        moveToXy(43,23-i);
        if(loggingLevel & uint32_t(pow(2, i)))
        {
          Serial.print(F("Logging"));
        }
        else
        {
          Serial.print(F("       "));
        }
      }
    }
}
