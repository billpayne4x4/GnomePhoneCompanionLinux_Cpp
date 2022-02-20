#ifndef DEBUG_H
#define DEBUG_H

#include "../config.h"
#include <iostream>
#include <streambuf>
#include <glibmm/datetime.h>

namespace gpc
{
    namespace tools
    {
        struct debug
        {
        public:
            config::logLevel level;

            debug(config::logLevel level) : level{level}
            {
                if (canLog())
                {
                    if (config::logDate || config::logTime)
                    {
                        std::cout << "[";
                        std::string format;

                        if (config::logDate)
                            format += "%d/%m/%Y";

                        if (config::logTime)
                            format += std::string(format == "" ? "" : " ") + "%H:%M:%S";

                        std::cout << Glib::DateTime::create_now_local().format(format);
                        std::cout << "] ";
                    }
                    std::cout << config::logLevelToString(level) << ": ";
                }
            };
            virtual ~debug()
            {
                std::cout << std::endl;
            }

            template <class T>
            debug &operator<<(T message)
            {
                if (canLog())
                {
                    std::cout << message;
                }
                return *this;
            }

        protected:
        private:
            bool canLog()
            {
                return (int)level > 0 && (int)level >= (int)config::log;
            }
        };
    }
}

#endif // DEBUG_H