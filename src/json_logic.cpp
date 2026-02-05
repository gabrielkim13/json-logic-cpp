#include "json_logic.h"

#include <algorithm>

#include "nlohmann/json.hpp"

#define MAKE_OPERATION(operation) [this](const json& values, const json& data) { return operation(values, data); }

using namespace nlohmann;

namespace json_logic
{
	JsonLogic* JsonLogic::singleton_ = nullptr;

	JsonLogic::JsonLogic()
	{
		operations_.insert({"var", MAKE_OPERATION(operation_data_var)});
		operations_.insert({"missing", MAKE_OPERATION(operation_data_missing)});
		operations_.insert({"missing_some", MAKE_OPERATION(operation_data_missing_some)});

		operations_.insert({"if", MAKE_OPERATION(operation_logic_if)});
		operations_.insert({"==", MAKE_OPERATION(operation_logic_abstract_equal)});
		operations_.insert({"===", MAKE_OPERATION(operation_logic_strict_equal)});
		operations_.insert({"!=", MAKE_OPERATION(operation_logic_abstract_different)});
		operations_.insert({"!==", MAKE_OPERATION(operation_logic_strict_different)});
		operations_.insert({"!", MAKE_OPERATION(operation_logic_not)});
		operations_.insert({"!!", MAKE_OPERATION(operation_logic_truthy)});
		operations_.insert({"or", MAKE_OPERATION(operation_logic_or)});
		operations_.insert({"and", MAKE_OPERATION(operation_logic_and)});

		operations_.insert({">", MAKE_OPERATION(operation_numeric_gt)});
		operations_.insert({">=", MAKE_OPERATION(operation_numeric_gte)});
		operations_.insert({"<", MAKE_OPERATION(operation_numeric_lt)});
		operations_.insert({"<=", MAKE_OPERATION(operation_numeric_lte)});
		operations_.insert({"max", MAKE_OPERATION(operation_numeric_max)});
		operations_.insert({"min", MAKE_OPERATION(operation_numeric_min)});
		operations_.insert({"+", MAKE_OPERATION(operation_numeric_addition)});
		operations_.insert({"-", MAKE_OPERATION(operation_numeric_subtraction)});
		operations_.insert({"*", MAKE_OPERATION(operation_numeric_multiplication)});
		operations_.insert({"/", MAKE_OPERATION(operation_numeric_division)});
		operations_.insert({"%", MAKE_OPERATION(operation_numeric_modulo)});

		operations_.insert({"map", MAKE_OPERATION(operation_array_map)});
		operations_.insert({"reduce", MAKE_OPERATION(operation_array_reduce)});
		operations_.insert({"filter", MAKE_OPERATION(operation_array_filter)});
		operations_.insert({"all", MAKE_OPERATION(operation_array_all)});
		operations_.insert({"none", MAKE_OPERATION(operation_array_none)});
		operations_.insert({"some", MAKE_OPERATION(operation_array_some)});
		operations_.insert({"merge", MAKE_OPERATION(operation_array_merge)});

		operations_.insert({"in", MAKE_OPERATION(operation_array_string_in)});

		operations_.insert({"cat", MAKE_OPERATION(operation_string_cat)});
		operations_.insert({"substr", MAKE_OPERATION(operation_string_substr)});

		operations_.insert({"log", MAKE_OPERATION(operation_misc_log)});
	}

	JsonLogic* JsonLogic::GetInstance()
	{
		if (singleton_ == nullptr) singleton_ = new JsonLogic();

		return singleton_;
	}

	json JsonLogic::Apply(const json& logic, const json& data) const // NOLINT(google-default-arguments)
	{
		if (logic.is_array())
		{
			auto result = json::array();

			std::transform(
				logic.begin(),
				logic.end(),
				std::back_inserter(result),
				[&data, this](const json& logic_element)
				{
				  return Apply(logic_element, data);
				}
			);

			return result;
		}

		if (!IsLogic(logic)) return logic;

		const auto op{GetOperator(logic)};
		auto values = GetValues(logic);

		if (!values.is_array())
		{
			values = json::array({values});
		}

		/**
		* In JsonLogic, operation names are treated as keywords and will result in one of the known operations being
		* invoked with the provided logic and data objects. Logic objects with unrecognized operations are treated as
		* "useless statements" that just returns its own values, such as:
		*
		* myLogic; // Returns myLogic.
		*
		* This is an important behaviour for the operation_array_merge, which can receive arbitrary JSON objects in its
		* parameters and is expected to just return them as elements of a flattened array.
		*/
		const auto operation_it = operations_.find(op);

		if (operation_it != operations_.end())
		{
			return operation_it->second(values, data);
		}

		return logic;
	}

	[[maybe_unused]] void JsonLogic::AddOperation(const std::string& name, const Operation& operation)
	{
		operations_.insert({name, operation});
	}

	[[maybe_unused]] void JsonLogic::RmOperation(const std::string& name)
	{
		operations_.erase(name);
	}

	bool JsonLogic::IsLogic(const json& logic)
	{
		return logic.is_object() && logic.size() == 1;
	}

	std::string JsonLogic::GetOperator(const json& logic)
	{
		return logic.begin().key();
	}

	const json& JsonLogic::GetValues(const json& logic)
	{
		return logic.at(GetOperator(logic));
	}

	bool JsonLogic::Truthy(const json& value)
	{
		if (value.is_boolean()) return value.get<bool>();

		if (value.is_number() && value != 0) return true;
		if (value.is_array() && !value.empty()) return true;
		if (value.is_string() && !std::string{value}.empty()) return true;

		return false;
	}
}
