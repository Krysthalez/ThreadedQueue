#include <iostream>
#include <thread>

#include "event.h"
#include "wifi.h"
#include "guardian.h"

using std::string;

int main(int argc, char *argv[])
{
    std::cout << "Type <q> to stop" << std::endl;

    Arduino::Wifi _wifi{};
    Arduino::Wifi *p_wifi{&_wifi};

    if (!p_wifi)
    {
        std::cout << "Failed to create pointer to _wifi, exiting" << std::endl;
        return -1;
    }

    string _input;
    std::mutex _printLocker;
    TKS::WifiGuardian _guardian(p_wifi);

    TKS::EventHandler<WIFI_STATUS> OnWifiStatusChange(
        [&_guardian, &_printLocker](WIFI_STATUS newStatus)
        {
            std::lock_guard<std::mutex> lock(_printLocker);

            std::cout << "New wifi connection status: " << newStatus << std::endl;

            if (newStatus == WIFI_STATUS::WL_CONNECTED)
            {
                // send the message
            }
            else if (newStatus == WIFI_STATUS::WL_CONNECTION_LOST)
            {
                // log connection error
            }
        });

    std::cout << "Subscribing to OnWifiStatusChange event" << std::endl;
    _guardian.StatusChange += OnWifiStatusChange;
    _guardian.Start();

    do
    {
        std::getline(std::cin, _input);

        if (_input == "+")
        {
            std::cout << "Connecting wifi" << std::endl;
            p_wifi->connect();
        }
        else if (_input == "-")
        {
            std::cout << "Disconnecting wifi" << std::endl;
            p_wifi->disconnect();
        }

    } while (_input != "q");

    _guardian.StatusChange -= OnWifiStatusChange;
    _guardian.Stop();
    p_wifi = nullptr;

    std::cout << "Exiting" << std::endl;

    return 0;
}
