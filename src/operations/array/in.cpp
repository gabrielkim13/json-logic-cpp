#include "json_logic.h"

#include <algorithm>
#include <string>

#include "nlohmann/json.hpp"

#include "exception.h"

using namespace nlohmann;

namespace json_logic
{
    json JsonLogic::operation_array_string_in(const json& values, const json& data)
    {
		if (values.size() != 2)
			throw JsonLogicException(
				__FUNCTION__,
				"Expected 2 arguments, but received " + std::to_string(values.size())
			);

        const auto search = Apply(values[0], data);
        const auto container = Apply(values[1], data);

		if (container.is_array())
			return std::any_of(
				container.begin(),
				container.end(),
				[&search](const json& item)
				{
					return item == search;
				}
			);

		if (container.is_string())
		{
			if (!search.is_string())
				throw JsonLogicException(
					__FUNCTION__,
					"When the second argument is a string, the first one must also be a string"
				);

			const std::string str{container.get<std::string>()};
			const std::string substr{search.get<std::string>()};

			return str.find(substr) != std::string::npos;
		}

		throw JsonLogicException(__FUNCTION__, "Invalid arguments");
    }
}
