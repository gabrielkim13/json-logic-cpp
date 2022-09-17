#include "json_logic.h"

#include <algorithm>

#include "nlohmann/json.hpp"

#include "exception.h"

using namespace nlohmann;

namespace json_logic
{
    json JsonLogic::operation_logic_and(const json& values, const json& data)
    {
		if (values.size() < 2)
			throw JsonLogicException(
				__FUNCTION__,
				"Expected 2 or more arguments, but received " + std::to_string(values.size())
			);

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
