#include "json_logic.h"

#include "json.hpp"

#include "exception.h"

using namespace nlohmann;

namespace json_logic
{
    json JsonLogic::operation_numeric_min(const json& values, const json& data)
    {
        if (values.empty())
            throw JsonLogicException(__FUNCTION__, "Expected at least 1 argument");

		auto min = Apply(values.front(), data);

		for (auto it = std::next(values.begin()); it != values.end(); ++it)
		{
			const auto value = Apply(it.value(), data);

			if (!value.is_number()) continue;

			min = value < min ? value : min;
		}

		return min;
    }
}
