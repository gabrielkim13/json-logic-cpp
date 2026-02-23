#include "json_logic.h"

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

        return static_cast<int>(a.get<double>()) % static_cast<int>(b.get<double>());
    }
}
