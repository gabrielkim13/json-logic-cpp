#include "json_logic.h"

#include <iostream>

#include "nlohmann/json.hpp"

#include "exception.h"

using namespace nlohmann;

namespace json_logic
{
    json JsonLogic::operation_misc_log(const json& values, const json& data)
    {
		if (values.size() != 1)
			throw JsonLogicException(
				__FUNCTION__,
				"Expected 1 argument, but received " + std::to_string(values.size())
			);

		auto value = Apply(values.front(), data);

		std::cout << value.dump() << std::endl;

        return value;
    }
}
