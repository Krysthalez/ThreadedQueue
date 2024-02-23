#ifndef __WIFI_H__
#define __WIFI_H__

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

std::ostream &operator<<(std::ostream &os, const WIFI_STATUS &obj)
{
    os << static_cast<std::underlying_type<WIFI_STATUS>::type>(obj);
    return os;
}

namespace Arduino
{
    class Wifi
    {
    public:
        Wifi()
        {
            this->setStatus(WIFI_STATUS::WL_IDLE_STATUS);
        }

        WIFI_STATUS status()
        {
            return this->m_status;
        }

        void connect()
        {
            this->setStatus(WIFI_STATUS::WL_CONNECTED);
        }

        void disconnect()
        {
            this->setStatus(WIFI_STATUS::WL_DISCONNECTED);
        }

    private:
        WIFI_STATUS m_status;

        void setStatus(WIFI_STATUS newStatus)
        {
            m_status = newStatus;
        }
    };
}

#endif
