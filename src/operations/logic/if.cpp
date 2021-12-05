#include "json_logic.h"

#include "json.hpp"

#include "exception.h"

using namespace nlohmann;

namespace json_logic
{
    json JsonLogic::operation_logic_if(const json& values, const json& data)
    {
        if (values.size() < 3 || values.size() % 2 == 0)
            throw JsonLogicException(
				__FUNCTION__,
                "Expected 3 or more odd number of arguments, but received " + std::to_string(values.size())
            );

        for (auto it = values.begin(); it != std::prev(values.end()); std::advance(it, 2))
        {
            if (Truthy(Apply(it.value(), data)))
			{
                return Apply(std::next(it).value(), data);
			}
        }

        return Apply(values.back(), data);
    }
}
