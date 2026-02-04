#include "json_logic.h"

#include "nlohmann/json.hpp"

using namespace nlohmann;

namespace json_logic
{
    json JsonLogic::operation_logic_strict_different(const json& values, const json& data) const
    {
        if (values.size() != 2)
            throw JsonLogicException(
				__FUNCTION__,
                "Expected 2 arguments, but received " + std::to_string(values.size())
            );

        return !operations_.at("===")(values, data);
    }

    json JsonLogic::operation_logic_abstract_different(const json& values, const json& data) const
    {
        if (values.size() != 2)
            throw JsonLogicException(
				__FUNCTION__,
                "Expected 2 arguments, but received " + std::to_string(values.size())
            );

        return !operations_.at("==")(values, data);
    }
}
