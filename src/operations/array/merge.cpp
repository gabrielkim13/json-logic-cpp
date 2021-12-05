#include "json_logic.h"

#include <vector>

#include "json.hpp"

using namespace nlohmann;

namespace json_logic
{
    json JsonLogic::operation_array_merge(const json& values, const json& data)
    {
        if (values.empty()) return json::array();

        std::vector<json> result{};

		for (const auto& value : values)
		{
			const auto applied_value = Apply(value, data);

			if (applied_value.is_array())
			{
				for (const auto& e : applied_value)
				{
					result.push_back(e);
				}
			}
			else
			{
				result.push_back(applied_value);
			}
		}

		return result;
    }
}
