#include "json_logic.h"

#include "nlohmann/json.hpp"

using namespace nlohmann;

namespace json_logic
{
    json JsonLogic::operation_numeric_multiplication(const json& values, const json& data) const
    {
        if (values.size() < 2)
            throw JsonLogicException(
				__FUNCTION__,
                "Expected 2 or more arguments, but received " + std::to_string(values.size())
            );

        double product{1.0};

        for (const auto& value : values)
        {
            const auto applied_value = Apply(value, data);

            if (!applied_value.is_number())
                throw JsonLogicException(__FUNCTION__, "All arguments must be numbers");

            product *= applied_value.get<double>();
        }

        return product;
    }
}
