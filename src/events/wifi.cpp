#include "wifi.h"

#include <iostream>

Arduino::Wifi::Wifi()
{
    this->setStatus(WIFI_STATUS::WL_IDLE_STATUS);
}

WIFI_STATUS Arduino::Wifi::status()
{
    return this->m_status;
}

void Arduino::Wifi::connect()
{
    this->setStatus(WIFI_STATUS::WL_CONNECTED);
}

void Arduino::Wifi::disconnect()
{
    this->setStatus(WIFI_STATUS::WL_DISCONNECTED);
}

void Arduino::Wifi::setStatus(WIFI_STATUS newStatus)
{
    m_status = newStatus;
}

std::ostream &operator<<(std::ostream &os, const WIFI_STATUS &obj)
{
    os << static_cast<std::underlying_type<WIFI_STATUS>::type>(obj);
    return os;
}
