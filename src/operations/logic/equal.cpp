#include "json_logic.h"

#include <cmath>
#include <string>

#include "nlohmann/json.hpp"

using namespace nlohmann;

namespace json_logic
{
	static bool strict_equal(const json& lhs, const json& rhs);
	static bool abstract_equal(const json& lhs, const json& rhs);

	static bool double_equal(double lhs, double rhs);
	static bool directional_abstract_equal(const json& lhs, const json& rhs);

    json JsonLogic::operation_logic_strict_equal(const json& values, const json& data) const
    {
        if (values.size() != 2)
            throw JsonLogicException(
				__FUNCTION__,
                "Expected 2 arguments, but received " + std::to_string(values.size())
            );

        const auto a = Apply(values[0], data);
        const auto b = Apply(values[1], data);

        return strict_equal(a, b);
    }

    json JsonLogic::operation_logic_abstract_equal(const json& values, const json& data) const
    {
        if (values.size() != 2)
            throw JsonLogicException(
				__FUNCTION__,
                "Expected 2 arguments, but received " + std::to_string(values.size())
            );

        const auto a = Apply(values[0], data);
        const auto b = Apply(values[1], data);

        return abstract_equal(a, b);
    }

	static inline bool strict_equal(const json& lhs, const json& rhs)
	{
		return lhs.type_name() == rhs.type_name() && lhs == rhs;
	}

	static inline bool abstract_equal(const json& lhs, const json& rhs)
	{
		return directional_abstract_equal(lhs, rhs) || directional_abstract_equal(rhs, lhs);
	}

	static inline bool double_equal(double lhs, double rhs)
	{
		return std::abs(lhs - rhs) < std::numeric_limits<double>::epsilon();
	}

	static bool directional_abstract_equal(const json& lhs, const json& rhs)
	{
		if (!lhs.is_number()) return lhs == rhs;

		// a === b
		if (strict_equal(lhs, rhs)) return true;

		// 0 == false -> true
		if (lhs == 0 && rhs == false) return true;

		// 1 == true -> true
		if (lhs == 1 && rhs == true) return true;

		// 42 == "42.0" -> true
		if (rhs.is_string() && double_equal(lhs.get<double>(), std::stod(rhs.get<std::string>()))) return true;

		// 0 == [] -> true
		if (rhs.is_array() && rhs.empty() && lhs == 0) return true;

		// 42 == [42] -> true
		if (rhs.is_array() && rhs.size() == 1 && lhs == rhs.front()) return true;

		return false;
	}
}
