#ifndef JSON_LOGIC_CPP_JSON_LOGIC_H
#define JSON_LOGIC_CPP_JSON_LOGIC_H

#include <functional>
#include <string>
#include <unordered_map>

#include "json.hpp"

#include "exception.h"

using namespace nlohmann;

namespace json_logic
{
	using Operation = std::function<json(const json&, const json&)>;

    class IJsonLogic
    {
    public:
        virtual json Apply(const json& logic, const json& data = json::object()) = 0; // NOLINT(google-default-arguments)
    };

	class JsonLogic : public IJsonLogic
	{
	public:
		JsonLogic(JsonLogic& other) = delete;

		void operator=(const JsonLogic& other) = delete;

		static JsonLogic *GetInstance();

		json Apply(const json& logic, const json& data = json::object()) override; // NOLINT(google-default-arguments)
		[[maybe_unused]] void AddOperation(const std::string& name, const Operation& operation);
		[[maybe_unused]] void RmOperation(const std::string& name);

	protected:
		static JsonLogic* singleton_;

		JsonLogic();

		static bool IsLogic(const json& logic);
		static std::string GetOperator(const json& logic);
		static const json& GetValues(const json& logic);

	private:
        std::unordered_map<std::string, Operation> operations_;

		json operation_data_var(const json& values, const json& data);
		json operation_data_missing(const json& values, const json& data);
		json operation_data_missing_some(const json& values, const json& data);

		json operation_logic_if(const json& values, const json& data);
		json operation_logic_abstract_equal(const json& values, const json& data);
		json operation_logic_strict_equal(const json& values, const json& data);
		json operation_logic_abstract_different(const json& values, const json& data);
		json operation_logic_strict_different(const json& values, const json& data);
		json operation_logic_not(const json& values, const json& data);
		json operation_logic_truthy(const json& values, const json& data);
		json operation_logic_or(const json& values, const json& data);
		json operation_logic_and(const json& values, const json& data);

		json operation_numeric_gt(const json& values, const json& data);
		json operation_numeric_gte(const json& values, const json& data);
		json operation_numeric_lt(const json& values, const json& data);
		json operation_numeric_lte(const json& values, const json& data);
		json operation_numeric_max(const json& values, const json& data);
		json operation_numeric_min(const json& values, const json& data);
		json operation_numeric_addition(const json& values, const json& data);
		json operation_numeric_subtraction(const json& values, const json& data);
		json operation_numeric_multiplication(const json& values, const json& data);
		json operation_numeric_division(const json& values, const json& data);
		json operation_numeric_modulo(const json& values, const json& data);

		json operation_array_map(const json& values, const json& data);
		json operation_array_reduce(const json& values, const json& data);
		json operation_array_filter(const json& values, const json& data);
		json operation_array_all(const json& values, const json& data);
		json operation_array_none(const json& values, const json& data);
		json operation_array_some(const json& values, const json& data);
		json operation_array_merge(const json& values, const json& data);

		json operation_array_string_in(const json& values, const json& data);

		json operation_string_cat(const json& values, const json& data);
		json operation_string_substr(const json& values, const json& data);

		json operation_misc_log(const json& values, const json& data);

		static bool Truthy(const json& value);
	};
}

#endif //JSON_LOGIC_CPP_JSON_LOGIC_H
