#include "json_logic.h"

#include "nlohmann/json.hpp"

using namespace nlohmann;

namespace json_logic
{
    json JsonLogic::operation_numeric_subtraction(const json& values, const json& data) const
    {
        if (values.empty() || values.size() > 2)
            throw JsonLogicException(
				__FUNCTION__,
                "Expected 1 or 2 arguments, but received " + std::to_string(values.size())
            );

        const auto a = CastToNumber(Apply(values[0], data));

        if (values.size() == 1) return -a.get<double>();

        const auto b = CastToNumber(Apply(values[1], data));

        return a.get<double>() - b.get<double>();
    }
}
