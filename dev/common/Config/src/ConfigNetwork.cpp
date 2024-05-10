#include "ConfigNetwork.hpp"

namespace ConfigNetwork
{
    uint16_t port;
    string   ipAddress;
    bool     configLoaded = false;

    void loadConfig(const string &configName)
    {
        if (configLoaded == false)
        {
            configLoaded = true;
            ifstream configFile("../dev/common/networkConfig.json");

            if (configFile.is_open() == false)
            {
                throw runtime_error("Failed to open networkConfig file.");
            }

            try
            {
                const json config = json::parse(configFile);
                json networkData;

                if ((config.is_null() == true) || (config.empty() == true))
                {
                    throw runtime_error("File networkConfig.json is empty.");
                }
                else
                {
                    networkData = config[configName];
                    if (networkData == nullptr)
                    {
                        throw runtime_error("Failed to get network config name" + configName);
                    }
                }

                try
                {
                    port = networkData["port"].get<uint16_t>();
                }
                catch(const exception& e)
                {
                    throw runtime_error("Failed to get network port.");
                }

                try
                {
                    ipAddress = networkData["ipAddress"].get<string>();
                }
                catch(const exception& e)
                {
                    throw runtime_error("Failed to get ip address.");
                }
            }
            catch (const exception& e)
            {
                throw runtime_error("Failed to parse configUser file.");
            }

            configFile.close();
        }
    }
}
