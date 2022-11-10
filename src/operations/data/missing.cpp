#include "json_logic.h"

#include <set>
#include <string>

#include "nlohmann/json.hpp"

using namespace nlohmann;

namespace json_logic
{
    json JsonLogic::operation_data_missing(const json& values, const json& data)
    {
		if (values.empty())
			throw JsonLogicException(
				__FUNCTION__,
				"Expected 1 or more arguments, but received " + std::to_string(values.size())
			);

        std::set<std::string> missing_keys{};

        for (const auto& value : values)
        {
            if (!value.is_string()) continue;

            const std::string key{value};

            // Quando o var não encontra algum membro e não tem um valor padrão, ele lança uma exceção.
            try
            {
                const auto logic = json{{"var", json{key}}};

                Apply(logic, data);
            }
            catch (...)
            {
                missing_keys.insert(key);
            }
        }

        return missing_keys;
    }
}
