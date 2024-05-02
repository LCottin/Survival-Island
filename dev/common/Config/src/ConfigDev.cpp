#include "ConfigDev.hpp"

static inline constexpr int32_t MAXIMUM_FRAMERATE_LIMIT = 30U;

namespace ConfigDev
{
    string   tilesetImgPath;
    string   playerImgPath;
    string   NPCImgPath;
    string   fontPath;
    int32_t  framerateLimit;
    uint32_t tileSize;
    uint32_t imageSizeTileWidth;
    uint32_t imageSizeTileHeight;
    bool     configLoaded = false;

    void loadConfig()
    {
        if (configLoaded == false)
        {
            configLoaded = true;
            ifstream configFile("../dev/common/devConfig.json");

            if (configFile.is_open() == false)
            {
                throw runtime_error("Failed to open configDev file.");
            }

            try
            {
                const json config = json::parse(configFile);

                if ((config.is_null() == true) || (config.empty() == true))
                {
                    throw runtime_error("File devConfig.json is empty.");
                }

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
                    fontPath = config["fontPath"].get<string>();
                }
                catch(const exception& e)
                {
                    throw runtime_error("Failed to get font path.");
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

                try
                {
                    imageSizeTileWidth = config["imageSizeTileWidth"].get<uint32_t>();
                }
                catch(const exception& e)
                {
                    throw runtime_error("Failed to get width of image size.");
                }

                try
                {
                    imageSizeTileHeight = config["imageSizeTileHeight"].get<uint32_t>();
                }
                catch(const exception& e)
                {
                    throw runtime_error("Failed to get height of image size.");
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
