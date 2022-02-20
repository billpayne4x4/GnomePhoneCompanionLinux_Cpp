#ifndef STRINGTOOLS_H
#define STRINGTOOLS_H

#include <iostream>
#include <vector>

namespace gpc
{
    namespace tools
    {
        class string
        {
        public:
            static std::vector<std::string> split(const std::string &str, const std::string &delimiter)
            {
                std::vector<std::string> strings;
                std::string::size_type pos = 0;
                std::string::size_type prev = 0;

                while ((pos = str.find(delimiter, prev)) != std::string::npos)
                {
                    strings.push_back(str.substr(prev, pos - prev));
                    prev = pos + 1;
                }

                strings.push_back(str.substr(prev));

                return strings;
            }

            static std::string trim(const std::string &str, const std::string &clean = " \t\r")
            {
                const std::size_t strBegin = str.find_first_not_of(clean);

                if (strBegin == std::string::npos)
                    return "";

                const std::size_t strEnd = str.find_last_not_of(clean);
                const std::size_t strRange = strEnd - strBegin + 1;

                return str.substr(strBegin, strRange);
            }

            static std::string addQuotes(const std::string &str)
            {
                return "\"" + str + "\"";
            }

        protected:
        private:
        };
    }
}

#endif // STRINGTOOLS_H