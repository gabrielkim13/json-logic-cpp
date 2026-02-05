#include "json_logic.h"

#include <algorithm>

#include "nlohmann/json.hpp"

using namespace nlohmann;

namespace json_logic
{
    json JsonLogic::operation_logic_and(const json& values, const json& data) const
    {
        return std::all_of(
            values.begin(),
            values.end(),
            [data, this](const json& value)
            {
                return Truthy(Apply(value, data));
            }
        );
    }
}
