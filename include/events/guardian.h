#ifndef __GUARDIAN_H__
#define __GUARDIAN_H__

#include <iostream>
#include <thread>

#include "wifi.h"
#include "event.h"

#define DEFAULT_WAIT_MS 1000

namespace TKS
{
    class WifiGuardian
    {
    public:
        TKS::Event<WIFI_STATUS> StatusChange;
        WifiGuardian(Arduino::Wifi *wifi);
        void Start();
        void Start(unsigned int milisecondInterval);
        void Stop();

    protected:
        void init();

    private:
        Arduino::Wifi *m_wifi;
        std::thread m_thread;

        WIFI_STATUS m_previousStatus = WIFI_STATUS::WL_IDLE_STATUS;
        unsigned int m_milisecondInterval = DEFAULT_WAIT_MS;
        bool m_isRunning = false;
    };
}

#endif
