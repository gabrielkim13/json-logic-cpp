#include "json_logic.h"

#include "nlohmann/json.hpp"

#include "exception.h"

using namespace nlohmann;

namespace json_logic
{
    json JsonLogic::operation_numeric_modulo(const json& values, const json& data)
    {
        if (values.size() != 2)
            throw JsonLogicException(
				__FUNCTION__,
                "Expected 2 arguments, but received " + std::to_string(values.size())
            );

        const auto a = Apply(values[0], data);
        const auto b = Apply(values[1], data);

        if (!a.is_number_integer() || !b.is_number_integer())
            throw JsonLogicException(__FUNCTION__, "All arguments must be integers");

        return a.get<int>() % b.get<int>();
    }
}
