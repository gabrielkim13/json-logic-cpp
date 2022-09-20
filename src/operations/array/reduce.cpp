#include "json_logic.h"

#include <algorithm>
#include <execution>

#include "nlohmann/json.hpp"

#include "exception.h"

using namespace nlohmann;

namespace json_logic
{
    json JsonLogic::operation_array_reduce(const json& values, const json& data)
    {
		if (values.size() != 3)
			throw JsonLogicException(
				__FUNCTION__,
				"Expected 3 arguments, but received " + std::to_string(values.size())
			);

		const auto array = Apply(values[0], data);
		const auto logic = values[1];
		const auto init = Apply(values[2], data);

		if (!array.is_array())
			throw JsonLogicException(__FUNCTION__, "First argument must be an array");

		if (!IsLogic(logic))
			throw JsonLogicException(__FUNCTION__, "Second argument must be a logic object");

		auto result = std::reduce(
			std::execution::par,
			array.begin(),
			array.end(),
			init,
			[&logic, this](const json& accumulator, const json& current)
			{
			  return Apply(logic, json{{"accumulator", accumulator}, {"current", current}});
			}
		);

		return result;
    }
}
