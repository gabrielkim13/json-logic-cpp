#include "json_logic.h"

#include "nlohmann/json.hpp"

using namespace nlohmann;

namespace json_logic
{
    json JsonLogic::operation_numeric_max(const json& values, const json& data)
    {
        if (values.empty())
            throw JsonLogicException(__FUNCTION__, "Expected at least 1 argument");

        auto max = Apply(values.front(), data);

        for (auto it = std::next(values.begin()); it != values.end(); ++it)
        {
            const auto value = Apply(it.value(), data);

            if (!value.is_number()) continue;

            max = value > max ? value : max;
        }

        return max;
    }
}
