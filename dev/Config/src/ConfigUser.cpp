#include "ConfigUser.hpp"

static inline constexpr char           DEFAULT_WINDOW_TITLE[] = "Empty title";
static inline constexpr GameDifficulty DEFAULT_DIFFICULTY     = GameDifficulty::EASY;
static inline constexpr Keyboard::Key  DEFAULT_UP_KEY         = Keyboard::Key::Up;
static inline constexpr Keyboard::Key  DEFAULT_DOWN_KEY       = Keyboard::Key::Down;
static inline constexpr Keyboard::Key  DEFAULT_LEFT_KEY       = Keyboard::Key::Left;
static inline constexpr Keyboard::Key  DEFAULT_RIGHT_KEY      = Keyboard::Key::Right;

namespace ConfigUser
{
    string         windowTitle;
    GameDifficulty difficulty;
    Keyboard::Key  upKey;
    Keyboard::Key  downKey;
    Keyboard::Key  leftKey;
    Keyboard::Key  rightKey;

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

            try
            {
                string upKeyString = toLowerCase(config["upKey"].get<string>());

                auto key = keyMapping.find(upKeyString);
                if (key != keyMapping.end())
                {
                    upKey = key->second;
                }
                else
                {
                    /* Not critical value, hardcoded default */
                    cerr << "Warning: Unknown key '" << upKeyString << "'. Using default." << std::endl;
                    upKey    = DEFAULT_UP_KEY;
                    toReturn = false;
                }
            }
            catch (const exception& e)
            {
                /* Not critical value, hardcoded default */
                cerr << "Error: Failed to parse upKey. Using default." << std::endl;
                upKey    = DEFAULT_UP_KEY;
                toReturn = false;
            }

            try
            {
                string downKeyString = toLowerCase(config["downKey"].get<string>());

                auto key = keyMapping.find(downKeyString);
                if (key != keyMapping.end())
                {
                    downKey = key->second;
                }
                else
                {
                    /* Not critical value, hardcoded default */
                    cerr << "Warning: Unknown key '" << downKeyString << "'. Using default." << std::endl;
                    downKey  = DEFAULT_DOWN_KEY;
                    toReturn = false;
                }
            }
            catch (const exception& e)
            {
                /* Not critical value, hardcoded default */
                cerr << "Error: Failed to parse downKey. Using default." << std::endl;
                downKey  = DEFAULT_DOWN_KEY;
                toReturn = false;
            }

            try
            {
                string leftKeyString = toLowerCase(config["leftKey"].get<string>());

                auto key = keyMapping.find(leftKeyString);
                if (key != keyMapping.end())
                {
                    leftKey = key->second;
                }
                else
                {
                    /* Not critical value, hardcoded default */
                    cerr << "Warning: Unknown key '" << leftKeyString << "'. Using default." << std::endl;
                    leftKey  = DEFAULT_LEFT_KEY;
                    toReturn = false;
                }
            }
            catch (const exception& e)
            {
                /* Not critical value, hardcoded default */
                cerr << "Error: Failed to parse leftKey. Using default." << std::endl;
                leftKey  = DEFAULT_LEFT_KEY;
                toReturn = false;
            }

            try
            {
                string rightKeyString = toLowerCase(config["rightKey"].get<string>());

                auto key = keyMapping.find(rightKeyString);
                if (key != keyMapping.end())
                {
                    rightKey = key->second;
                }
                else
                {
                    /* Not critical value, hardcoded default */
                    cerr << "Warning: Unknown key '" << rightKeyString << "'. Using default." << std::endl;
                    rightKey = DEFAULT_RIGHT_KEY;
                    toReturn = false;
                }
            }
            catch (const exception& e)
            {
                /* Not critical value, hardcoded default */
                cerr << "Error: Failed to parse rightKey. Using default." << std::endl;
                rightKey = DEFAULT_UP_KEY;
                toReturn = false;
            }
        }
        catch (const exception& e)
        {
            throw runtime_error("Failed to parse configUser file.");
        }

        configFile.close();

        return toReturn;
    }
}
