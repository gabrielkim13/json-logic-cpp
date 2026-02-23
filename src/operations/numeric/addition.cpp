#include "json_logic.h"

#include <exception>
#include <string>

#include "nlohmann/json.hpp"

using namespace nlohmann;

namespace json_logic
{
    json JsonLogic::operation_numeric_addition(const json& values, const json& data) const
    {
		if (values.empty())
			throw JsonLogicException(
				__FUNCTION__,
				"Expected 1 or more arguments, but received " + std::to_string(values.size())
			);

        if (values.size() == 1) return CastToNumber(Apply(values.front(), data));

        double sum{0.0};

        for (const auto& value : values)
        {
            const auto applied_value = CastToNumber(Apply(value, data));
            sum += applied_value.get<double>();
        }

        return sum;
    }
}
