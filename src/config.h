#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>

namespace gpc
{
    class config
    {
    public:
        enum logLevel : int
        {
            UNKNOWN = -1,
            NONE = 0,
            ERROR = 1,
            WARNING = 3,
            INFO = 4
        };

        static void load();
        static void save();
        static std::string logLevelToString(config::logLevel level);
        static logLevel stringToLogLevel(std::string level);

        inline static const std::string version = "0.1";
        inline static const std::string resourcePrefix{"/gnomePhoneCompanion/"};
        inline static int port = 32145;
        inline static std::string bind = "0.0.0.0";
        inline static std::string auth = "";
        inline static logLevel log = logLevel::INFO;
        inline static bool logDate = true;
        inline static bool logTime = true;

    protected:
    private:
        static std::string getFileLocation();
        static void setValue(const std::string &key, const std::string &value);
        static void getValues(std::string &values);
    };
}

#endif // CONFIG_H