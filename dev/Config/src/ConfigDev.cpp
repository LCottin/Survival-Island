#include "ConfigDev.hpp"

static inline constexpr int32_t MAXIMUM_FRAMERATE_LIMIT = 30U;

namespace ConfigDev
{
    string   tilesetImgPath;
    string   playerImgPath;
    string   NPCImgPath;
    int32_t  framerateLimit;
    uint32_t tileSize;

    void loadConfig()
    {
        ifstream configFile("../dev/devConfig.json");
        json config;

        if (configFile.is_open() == false)
        {
            throw runtime_error("Failed to open configUser file.");
        }

        try
        {
            config = json::parse(configFile);

            try
            {
                tilesetImgPath = config["tilesetImgPath"].get<string>();
            }
            catch(const exception& e)
            {
                throw runtime_error("Failed to get tileset image path.");
            }

            try
            {
                playerImgPath = config["playerImgPath"].get<string>();
            }
            catch(const exception& e)
            {
                throw runtime_error("Failed to get player image path.");
            }

            try
            {
                NPCImgPath = config["NPCImgPath"].get<string>();
            }
            catch(const exception& e)
            {
                throw runtime_error("Failed to get NPC image path.");
            }

            try
            {
                framerateLimit = config["framerateLimit"].get<int32_t>();
                if (framerateLimit < -1)
                {
                    framerateLimit = -1;
                }
                if (framerateLimit > MAXIMUM_FRAMERATE_LIMIT)
                {
                    framerateLimit = MAXIMUM_FRAMERATE_LIMIT;
                }
            }
            catch(const exception& e)
            {
                throw runtime_error("Failed to get framerate limit.");
            }

            try
            {
                tileSize = config["tileSize"].get<uint32_t>();
            }
            catch(const exception& e)
            {
                throw runtime_error("Failed to get tile size.");
            }
        }
        catch (const exception& e)
        {
            throw runtime_error("Failed to parse configUser file.");
        }
    }
}
