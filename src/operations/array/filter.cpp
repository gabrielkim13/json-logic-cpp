#include "json_logic.h"

#include <algorithm>

#include "nlohmann/json.hpp"

using namespace nlohmann;

namespace json_logic
{
    json JsonLogic::operation_array_filter(const json& values, const json& data)
    {
		if (values.size() != 2)
			throw JsonLogicException(
				__FUNCTION__,
				"Expected 2 arguments, but received " + std::to_string(values.size())
			);

		const auto array = Apply(values[0], data);
		const auto logic = values[1];

		if (!array.is_array())
			throw JsonLogicException(__FUNCTION__, "First argument must be an array");

		if (!IsLogic(logic))
			throw JsonLogicException(__FUNCTION__, "Second argument must be a logic object");

		auto result = json::array();

		std::copy_if(
			array.begin(),
			array.end(),
			std::back_inserter(result),
			[&logic, this](const json& item)
			{
			  return Truthy(Apply(logic, item));
			}
		);

		return result;
    }
}
