#include "json_logic.h"

#include <exception>
#include <string>

#include "nlohmann/json.hpp"

#include "exception.h"

using namespace nlohmann;

namespace json_logic
{
    static json cast_to_number(const json& value);

    json JsonLogic::operation_numeric_addition(const json& values, const json& data)
    {
		if (values.empty())
			throw JsonLogicException(
				__FUNCTION__,
				"Expected 1 or more arguments, but received " + std::to_string(values.size())
			);

        if (values.size() == 1) return cast_to_number(Apply(values.front(), data));

        double sum{0.0};

        for (const auto& value : values)
        {
            const auto applied_value = Apply(value, data);

            if (!applied_value.is_number())
                throw JsonLogicException(__FUNCTION__, "All arguments must be numbers");

            sum += applied_value.get<double>();
        }

        return sum;
    }

    static inline json cast_to_number(const json& value)
    {
        // +42 -> 42
        if (value.is_number()) return value;

        // +false -> 0
        // +true -> 1
        if (value.is_boolean()) return value ? 1 : 0;

        // +[] -> 0
        // +[42] -> 1
        if (value.is_array()) return value.empty() ? 0 : 1;

        try
        {
            // +"42.0" -> 42.0
            if (value.is_string()) return std::stod(value.get<std::string>());
        }
        catch (const std::exception& ex)
        {
            throw JsonLogicException(__FUNCTION__, ex.what());
        }

        throw JsonLogicException(__FUNCTION__, "Invalid cast to a number");
    }
}
