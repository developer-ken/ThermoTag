#ifndef _H_ESPNOWENHANCER_
#define _H_ESPNOWENHANCER_

#include <Arduino.h>
class ESPNowCom
{
public:
    bool Transmit(const uint8_t *target_addr, uint8_t *data, uint8_t len);
    void (*OnReceive)(uint8_t *data, uint8_t len);
    bool Receive(uint8_t *src_addr, uint8_t *data, uint8_t len);
    bool AddPeer(uint8_t *peer_addr);
    bool RemovePeer(uint8_t *peer_addr);
private:
};

class ESPNowHost : ESPNowCom
{
    public:
    private:
};

#endif