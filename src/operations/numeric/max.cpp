#include "json_logic.h"

#include "nlohmann/json.hpp"

using namespace nlohmann;

namespace json_logic
{
    json JsonLogic::operation_numeric_max(const json& values, const json& data) const
    {
        if (values.empty())
            throw JsonLogicException(__FUNCTION__, "Expected at least 1 argument");

        auto max = CastToNumber(Apply(values.front(), data));

        for (auto it = std::next(values.begin()); it != values.end(); ++it)
        {
            const auto value = CastToNumber(Apply(it.value(), data));
            max = value > max ? value : max;
        }

        return max;
    }
}
