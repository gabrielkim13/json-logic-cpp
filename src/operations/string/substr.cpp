#include "json_logic.h"

#include <string>

#include "nlohmann/json.hpp"

using namespace nlohmann;

namespace json_logic
{
    json JsonLogic::operation_string_substr(const json& values, const json& data)
    {
		if (values.size() < 2 || values.size() > 3)
			throw JsonLogicException(
				__FUNCTION__,
				"Expected 2 or 3 arguments, but received " + std::to_string(values.size())
			);

        const auto value1 = Apply(values[0], data);
        const auto value2 = Apply(values[1], data);

		if (!value1.is_string())
			throw JsonLogicException(__FUNCTION__, "First argument must be a string");

		if (!value2.is_number_integer())
			throw JsonLogicException(__FUNCTION__, "Second argument (start index) must be an integer");

		const auto str = value1.get<std::string>();
		const auto start_index = value2.get<int>() >= 0 ? value2.get<int>() : str.length() + value2.get<int>();

		if (start_index >= str.length())
			throw JsonLogicException(
				__FUNCTION__,
				"Start index must be a positive integer less than the string's length"
			);

		auto substr_length = std::string::npos;

		if (values.size() == 3)
		{
			const auto value3 = Apply(values[2], data);

			if (!value3.is_number_integer())
				throw JsonLogicException(
					__FUNCTION__,
					"Third argument (substr length) must be an integer"
				);

			substr_length = value3.get<int>() >= 0 ? value3.get<int>() : str.length() - start_index + value3.get<int>();

			if (substr_length >= str.length() - start_index)
				throw JsonLogicException(
					__FUNCTION__,
					"Substr length must be a positive integer less than the string's length minus the start index"
				);
		}

		return str.substr(start_index, substr_length);
    }
}
