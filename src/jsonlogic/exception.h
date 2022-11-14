#ifndef JSON_LOGIC_CPP_EXCEPTION_H
#define JSON_LOGIC_CPP_EXCEPTION_H

#include <exception>
#include <sstream>
#include <string>
#include <utility>

namespace json_logic
{
    class JsonLogicException : public std::exception
    {
    private:
        const std::string what_;

    public:
        explicit JsonLogicException(std::string what) : what_{std::move(what)}
        {
        }

        explicit JsonLogicException(const std::string& operation_name, const std::string& what) :
            what_{"[" + operation_name + "] " + what}
        {
        }

        [[nodiscard]] const char* what() const noexcept override
        {
            return what_.c_str();
        }
    };
}

#endif //JSON_LOGIC_CPP_EXCEPTION_H
