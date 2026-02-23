#include "json_logic.h"

#include "nlohmann/json.hpp"

using namespace nlohmann;

namespace json_logic
{
    json JsonLogic::operation_numeric_min(const json& values, const json& data) const
    {
        if (values.empty())
            throw JsonLogicException(__FUNCTION__, "Expected at least 1 argument");

        auto min = CastToNumber(Apply(values.front(), data));

		for (auto it = std::next(values.begin()); it != values.end(); ++it)
		{
            const auto value = CastToNumber(Apply(it.value(), data));
			min = value < min ? value : min;
		}

		return min;
    }
}
