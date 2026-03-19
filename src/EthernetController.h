#pragma once

#include <Arduino.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <SPI.h>

class EthernetController {
public:
  void init();
  bool isReady();
  void updateLinkStatus();
  void sendUdpCommand(const char *command);

private:
  EthernetUDP udp_;
  bool ethernetInitialized_ = false;
  bool linkUp_ = false;
};
