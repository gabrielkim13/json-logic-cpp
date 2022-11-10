#include "json_logic.h"

#include "nlohmann/json.hpp"

using namespace nlohmann;

namespace json_logic
{
    json JsonLogic::operation_logic_not(const json& values, const json& data)
    {
		if (values.size() != 1)
			throw JsonLogicException(
				__FUNCTION__,
				"Expected 1 argument, but received " + std::to_string(values.size())
			);

		return !operations_["!!"](values, data);
    }
}
