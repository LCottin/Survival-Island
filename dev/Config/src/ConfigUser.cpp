#include "ConfigUser.hpp"

static inline constexpr char           DEFAULT_WINDOW_TITLE[] = "Empty title";
static inline constexpr GameDifficulty DEFAULT_DIFFICULTY     = GameDifficulty::EASY;
static inline constexpr Keyboard::Key  DEFAULT_UP_KEY         = Keyboard::Key::Up;
static inline constexpr Keyboard::Key  DEFAULT_DOWN_KEY       = Keyboard::Key::Down;
static inline constexpr Keyboard::Key  DEFAULT_LEFT_KEY       = Keyboard::Key::Left;
static inline constexpr Keyboard::Key  DEFAULT_RIGHT_KEY      = Keyboard::Key::Right;
static inline constexpr Keyboard::Key  DEFAULT_PAUSE_KEY      = Keyboard::Key::Escape;

static string toLowerCase(const string& str)
{
    string result = str;
    transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return tolower(c); });
    return result;
}

/* Mapping from lowercase string to Keyboard::Key */
static const unordered_map<std::string, Keyboard::Key> keyMapping =
{
    {toLowerCase("A"), Keyboard::Key::A},
    {toLowerCase("B"), Keyboard::Key::B},
    {toLowerCase("C"), Keyboard::Key::C},
    {toLowerCase("D"), Keyboard::Key::D},
    {toLowerCase("E"), Keyboard::Key::E},
    {toLowerCase("F"), Keyboard::Key::F},
    {toLowerCase("G"), Keyboard::Key::G},
    {toLowerCase("H"), Keyboard::Key::H},
    {toLowerCase("I"), Keyboard::Key::I},
    {toLowerCase("J"), Keyboard::Key::J},
    {toLowerCase("K"), Keyboard::Key::K},
    {toLowerCase("L"), Keyboard::Key::L},
    {toLowerCase("M"), Keyboard::Key::M},
    {toLowerCase("N"), Keyboard::Key::N},
    {toLowerCase("O"), Keyboard::Key::O},
    {toLowerCase("P"), Keyboard::Key::P},
    {toLowerCase("Q"), Keyboard::Key::Q},
    {toLowerCase("R"), Keyboard::Key::R},
    {toLowerCase("S"), Keyboard::Key::S},
    {toLowerCase("T"), Keyboard::Key::T},
    {toLowerCase("U"), Keyboard::Key::U},
    {toLowerCase("V"), Keyboard::Key::V},
    {toLowerCase("W"), Keyboard::Key::W},
    {toLowerCase("X"), Keyboard::Key::X},
    {toLowerCase("Y"), Keyboard::Key::Y},
    {toLowerCase("Z"), Keyboard::Key::Z},

    {toLowerCase("Left"),  Keyboard::Key::Left},
    {toLowerCase("Right"), Keyboard::Key::Right},
    {toLowerCase("Up"),    Keyboard::Key::Up},
    {toLowerCase("Down"),  Keyboard::Key::Down},

    {toLowerCase("Esc"),   Keyboard::Key::Escape},
    {toLowerCase("Enter"), Keyboard::Key::Enter},
    {toLowerCase("Space"), Keyboard::Key::Space},
    {toLowerCase("Lctrl"), Keyboard::Key::LControl},
    {toLowerCase("Tab"),   Keyboard::Key::Tab},
};

namespace ConfigUser
{
    string         windowTitle;
    GameDifficulty difficulty;
    Keyboard::Key  upKey;
    Keyboard::Key  downKey;
    Keyboard::Key  leftKey;
    Keyboard::Key  rightKey;
    Keyboard::Key  pauseKey;

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

            try
            {
                string pauseKeyString = toLowerCase(config["pauseKey"].get<string>());

                auto key = keyMapping.find(pauseKeyString);
                if (key != keyMapping.end())
                {
                    pauseKey = key->second;
                }
                else
                {
                    /* Not critical value, hardcoded default */
                    cerr << "Warning: Unknown key '" << pauseKeyString << "'. Using default." << std::endl;
                    pauseKey = DEFAULT_PAUSE_KEY;
                    toReturn = false;
                }
            }
            catch (const exception& e)
            {
                /* Not critical value, hardcoded default */
                cerr << "Error: Failed to parse pauseKey. Using default." << std::endl;
                pauseKey = DEFAULT_PAUSE_KEY;
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
