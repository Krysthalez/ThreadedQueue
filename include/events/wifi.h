#ifndef __WIFI_H__
#define __WIFI_H__

#include <iostream>

enum class WIFI_STATUS
{
    WL_DISCONNECTED = 0,
    WL_CONNECTED = 1,
    WL_IDLE_STATUS = 400,
    WL_NO_SHIELD = 401,
    WL_CONNECT_FAILED = 402,
    WL_NO_SSID_AVAIL = 403,
    WL_SCAN_COMPLETED = 404,
    WL_CONNECTION_LOST = 406
};

std::ostream &operator<<(std::ostream &os, const WIFI_STATUS &obj);

namespace Arduino
{
    class Wifi
    {
    public:
        Wifi();
        WIFI_STATUS status();
        void connect();
        void disconnect();

    private:
        WIFI_STATUS m_status;
        void setStatus(WIFI_STATUS newStatus);
    };
}

#endif
