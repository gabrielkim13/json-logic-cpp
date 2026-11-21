#include "json_logic.h"

#include <cmath>

#include "nlohmann/json.hpp"

using namespace nlohmann;

namespace json_logic
{
    json JsonLogic::operation_numeric_modulo(const json& values, const json& data) const
    {
        if (values.size() != 2)
            throw JsonLogicException(
				__FUNCTION__,
                "Expected 2 arguments, but received " + std::to_string(values.size())
            );

        const auto a = CastToNumber(Apply(values[0], data));
        const auto b = CastToNumber(Apply(values[1], data));

        // Same as JavaScript's %: works on decimals, keeps the sign of the
        // dividend, and gives NaN (not undefined behavior) for a zero divisor.
        return std::fmod(a.get<double>(), b.get<double>());
    }
}
