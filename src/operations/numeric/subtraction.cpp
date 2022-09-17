#include "json_logic.h"

#include "nlohmann/json.hpp"

#include "exception.h"

using namespace nlohmann;

namespace json_logic
{
    json JsonLogic::operation_numeric_subtraction(const json& values, const json& data)
    {
        if (values.empty() || values.size() > 2)
            throw JsonLogicException(
				__FUNCTION__,
                "Expected 1 or 2 arguments, but received " + std::to_string(values.size())
            );

        const auto a = Apply(values[0], data);

        if (values.size() == 1 && a.is_number()) return -a.get<double>();

        const auto b = Apply(values[1], data);

        if (!a.is_number() || !b.is_number())
            throw JsonLogicException(__FUNCTION__, "All arguments must be numbers");

        return a.get<double>() - b.get<double>();
    }
}
