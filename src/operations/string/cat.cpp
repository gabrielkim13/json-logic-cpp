#include "json_logic.h"

#include <string>

#include "nlohmann/json.hpp"

using namespace nlohmann;

namespace json_logic
{
    json JsonLogic::operation_string_cat(const json& values, const json& data)
    {
		if (values.size() < 2)
			throw JsonLogicException(
				__FUNCTION__,
				"Expected 2 or more arguments, but received " + std::to_string(values.size())
			);

        std::string result{};

		for (const auto& value : values)
		{
			const auto applied_value = Apply(value, data);

			if (!applied_value.is_string())
				throw JsonLogicException(__FUNCTION__, "All arguments must be strings");

			result += applied_value;
		}

		return result;
    }
}
