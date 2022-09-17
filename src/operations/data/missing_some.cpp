#include "json_logic.h"

#include <set>
#include <string>

#include "nlohmann/json.hpp"

#include "exception.h"

using namespace nlohmann;

namespace json_logic
{
    json JsonLogic::operation_data_missing_some(const json& values, const json& data)
    {
        if (values.size() != 2)
            throw JsonLogicException(
				__FUNCTION__,
                "Expected 2 arguments, but received " + std::to_string(values.size())
            );

        const auto minimum_required_found_keys = values[0];
        const auto search_values = values[1];

        if (!search_values.is_array())
            throw JsonLogicException(__FUNCTION__, "Second argument must be an array");

        std::set<std::string> found_keys{};
        std::set<std::string> missing_keys{};

        for (const auto& value : search_values)
        {
            if (!value.is_string()) continue;

            const std::string key{value};

            // Quando o var não encontra algum membro e não tem um valor padrão, ele lança uma exceção.
            try
            {
                const auto logic = json{{"var", json{key}}};

                Apply(logic, data);

                found_keys.insert(key);
            }
            catch (...)
            {
                missing_keys.insert(key);
            }
        }

        if (found_keys.size() >= minimum_required_found_keys)
            return json::array();

        return missing_keys;
    }
}
