#include "json_logic.h"

#include "nlohmann/json.hpp"

using namespace nlohmann;

namespace json_logic
{
    json JsonLogic::operation_array_none(const json& values, const json& data)
    {
        return !operations_["some"](values, data);
    }
}
