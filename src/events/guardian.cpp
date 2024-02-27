#include "guardian.h"
#include "event.h"
#include "wifi.h"

#include <iostream>
#include <thread>

TKS::WifiGuardian::WifiGuardian(Arduino::Wifi *wifi)
{
    m_wifi = wifi;
    m_previousStatus = wifi->status();
}

void TKS::WifiGuardian::Start()
{
    this->Start(DEFAULT_WAIT_MS);
}

void TKS::WifiGuardian::Start(unsigned int milisecondInterval)
{
    this->m_milisecondInterval = milisecondInterval;
    this->m_isRunning = true;
    m_thread = std::thread([this]()
                           { init(); });
}

void TKS::WifiGuardian::Stop()
{
    if (!m_isRunning)
        return;

    m_isRunning = false;

    if (m_thread.joinable())
        m_thread.join();
}

void TKS::WifiGuardian::init()
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
