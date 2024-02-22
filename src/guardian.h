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
    private:
        Arduino::Wifi *m_wifi;
        std::thread m_thread;

        WIFI_STATUS m_previousStatus = WIFI_STATUS::WL_IDLE_STATUS;
        unsigned int m_milisecondInterval = DEFAULT_WAIT_MS;
        bool m_isRunning = false;

    public:
        TKS::Event<WIFI_STATUS> StatusChange;

        WifiGuardian(Arduino::Wifi *wifi)
        {
            m_wifi = wifi;
            m_previousStatus = wifi->status();
            m_thread = std::thread([this](){ init(); });
        }

        void Start()
        {
            this->Start(DEFAULT_WAIT_MS);
        }

        void Start(unsigned int milisecondInterval)
        {
            this->m_milisecondInterval = milisecondInterval;
            this->m_isRunning = true;
        }

        void Stop()
        {
            if (!m_isRunning)
            {
                return;
            }

            m_isRunning = false;

            if (m_thread.joinable())
            {
                m_thread.join();
            }
        }

    protected:
        void init()
        {
            std::cout << "WifiGuardian thread started" << std::endl;

            while (m_isRunning)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(m_milisecondInterval));
                std::cout << "Checking wifi status" << std::endl;

                if (m_wifi == nullptr)
                {
                    std::cout << "ERROR: m_wifi is nullptr, breaking loop" << std::endl;
                    break;
                }

                WIFI_STATUS newStatus = m_wifi->status();
                if (newStatus != m_previousStatus)
                {
                    StatusChange(newStatus);
                    m_previousStatus = newStatus;
                }
            }
        }
    };
}

#endif
