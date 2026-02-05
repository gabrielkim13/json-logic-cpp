#include "json_logic.h"

#include "nlohmann/json.hpp"

using namespace nlohmann;

namespace json_logic
{
    json JsonLogic::operation_numeric_lte(const json& values, const json& data) const
    {
        if (values.size() < 2 || values.size() > 3)
            throw JsonLogicException(
                __FUNCTION__,
                "Expected 2 or 3 arguments, but received " + std::to_string(values.size())
            );

        const auto a = Apply(values[0], data);
        const auto b = Apply(values[1], data);

        if (!a.is_number() || !b.is_number())
            throw JsonLogicException(__FUNCTION__, "All arguments must be numbers");

        if (values.size() == 3)
        {
            const auto c = Apply(values[2], data);

            if (!c.is_number())
                throw JsonLogicException(__FUNCTION__, "All arguments must be numbers");

            return a <= b && b <= c;
        }

        return a <= b;
    }
}
