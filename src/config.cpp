#include "config.h"
#include <glibmm/fileutils.h>
#include <vector>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>
#include "tools/string.h"

using namespace gpc;

void config::load()
{
    std::string fileLocation = getFileLocation();
    std::vector<std::string> lines;

    try
    {
        lines = tools::string::split(Glib::file_get_contents(fileLocation), "\n");
    }
    catch (const Glib::FileError &e)
    {
        std::cerr << e.what() << std::endl;
        if (e.code() == Glib::FileError::NO_SUCH_ENTITY)
        {
            std::cout << "Creating '" << fileLocation << "'..." << std::endl;
            save();
        }
        return;
    }

    for (std::string line : lines)
    {
        line = tools::string::trim(line);

        if (line.length() < 1 || line[0] != '#' || line.find('=') != std::string::npos)
        {
            std::vector<std::string> configLine = tools::string::split(line, "=");
            if (configLine.size() == 2)
            {
                std::string key = tools::string::trim(configLine[0]);
                std::string value = tools::string::trim(configLine[1]);

                if (value.length() > 0 && value[0] == '"')
                    value = tools::string::trim(value, "\"");

                setValue(key, value);
            }
        }
    }
}

void config::save()
{
    std::string fileLocation = getFileLocation();
    std::string contents;
    getValues(contents);

    try
    {
        Glib::file_set_contents(fileLocation, contents);
    }
    catch (const Glib::FileError &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

std::string config::getFileLocation()
{
    char *homeDir;
    if ((homeDir = getenv("HOME")) == NULL)
        homeDir = getpwuid(getuid())->pw_dir;

    std::string fileLocation(homeDir);

    if (fileLocation.back() != '/')
        fileLocation += "/";

    fileLocation += ".config/gnome-phone-companion.conf";

    return fileLocation;
}

void config::setValue(const std::string &key, const std::string &value)
{
    if (key == "port")
        port = atoi(value.c_str());

    if (key == "bind")
        bind = value;

    if (key == "auth")
        auth = value;

    if (key == "log")
        log = stringToLogLevel(value);

    if (key == "logDate")
        logDate = value == "True";

    if (key == "logTime")
        logTime = value == "True";
}

void config::getValues(std::string &values)
{
    values = "# gnome-phone-companion Version " + version + "\n\n";
    values += "version = " + tools::string::addQuotes(version) + "\n";
    values += "port = " + std::to_string(port) + "\n";
    values += "bind = " + tools::string::addQuotes(bind) + "\n";
    values += "auth = " + tools::string::addQuotes(auth) + "\n";
    values += "log = " + tools::string::addQuotes(logLevelToString(log)) + "\n";
    values += "logDate = " + std::string(logDate ? "True" : "False") + "\n";
    values += "logTime = " + std::string(logTime ? "True" : "False");
}

std::string config::logLevelToString(config::logLevel level)
{
    switch (level)
    {
    case config::logLevel::NONE:
        return "None";
    case config::logLevel::ERROR:
        return "Error";
    case config::logLevel::WARNING:
        return "Warning";
    case config::logLevel::INFO:
        return "Info";
    default:
        return "Unknown";
    }
}

config::logLevel config::stringToLogLevel(std::string level)
{
    if (level == "None")
        return config::logLevel::NONE;
    else if (level == "Error")
        return config::logLevel::ERROR;
    else if (level == "Warning")
        return config::logLevel::WARNING;
    else if (level == "Info")
        return config::logLevel::INFO;
    else
        return config::logLevel::UNKNOWN;
}
