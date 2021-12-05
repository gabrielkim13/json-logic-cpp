#include "json_logic.h"

#include "json.hpp"

#include "exception.h"

using namespace nlohmann;

namespace json_logic
{
    json JsonLogic::operation_logic_truthy(const json& values, const json& data)
    {
		if (values.size() != 1)
			throw JsonLogicException(
				__FUNCTION__,
				"Expected 1 argument, but received " + std::to_string(values.size())
			);

		return Truthy(Apply(values.front(), data));
    }
}
