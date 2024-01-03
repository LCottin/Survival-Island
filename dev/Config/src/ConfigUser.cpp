#include "ConfigUser.hpp"

static inline constexpr char           DEFAULT_WINDOW_TITLE[] = "Empty title";
static inline constexpr GameDifficulty DEFAULT_DIFFICULTY     = GameDifficulty::EASY;

namespace ConfigUser
{
    string   windowTitle;
    GameDifficulty difficulty;

    bool loadConfig()
    {
        ifstream configFile("../userConfig.json");
        json config;
        bool toReturn = true;

        if (configFile.is_open() == false)
        {
            throw runtime_error("Failed to open configUser file.");
        }

        try
        {
            config = json::parse(configFile);

            try
            {
                windowTitle = config["windowTitle"].get<string>();
            }
            catch (const exception& e)
            {
                /* Not critical value, hardcoded default */
                windowTitle = DEFAULT_WINDOW_TITLE;
                toReturn    = false;
            }

            try
            {
                difficulty = config["difficulty"].get<GameDifficulty>();
                if (difficulty > GameDifficulty::HARD)
                {
                    difficulty = GameDifficulty::HARD;
                }
            }
            catch (const exception& e)
            {
                /* Not critical value, hardcoded default */
                difficulty = DEFAULT_DIFFICULTY;
                toReturn   = false;
            }
        }
        catch (const exception& e)
        {
            throw runtime_error("Failed to parse configUser file.");
        }

        return toReturn;
    }
}
