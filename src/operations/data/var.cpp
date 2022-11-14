#include "json_logic.h"

#include <exception>
#include <sstream>
#include <string>
#include <vector>

#include "nlohmann/json.hpp"

using namespace nlohmann;

namespace json_logic
{
    json JsonLogic::operation_data_var(const json& values, const json& data) // NOLINT(readability-convert-member-functions-to-static)
    {
        json current = data;

        if (values.empty() || values.size() > 2)
			throw JsonLogicException(
				__FUNCTION__,
				"Expected 1 or 2 arguments, but received " + std::to_string(values.size())
			);

        const auto key = values.front().get<std::string>();

        if (key.empty()) return current;

        std::stringstream key_stream{key};
        std::string token{};
        std::vector<std::string> tokens{};

        while (std::getline(key_stream, token, '.')) tokens.push_back(token);

        try
        {
            for (const auto& t: tokens)
            {
                if (t.empty()) return current;

                try
                {
                    const auto index{std::stoi(t)};

                    if (!current.is_array())
                        throw JsonLogicException(__FUNCTION__, "Data object is not an array, but index was provided");

                    if (index >= current.size())
                        throw JsonLogicException(__FUNCTION__, "Array index out of bounds");

                    current = current[index];
                }
                catch (std::invalid_argument& ex)
                {
                    if (!current.contains(t))
                        throw JsonLogicException(__FUNCTION__, "Data object does not contain specified member " + t);

                    current = current.at(t);
                }
                catch (std::exception& ex)
                {
                    throw JsonLogicException(ex.what());
                }
            }
        }
        catch (...)
        {
            if (values.size() == 2) return Apply(values[1], data);

            throw;
        }

        return current;
    }
}
