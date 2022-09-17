#include <iostream>

#include "gtest/gtest.h"
#include "nlohmann/json.hpp"

#include "fixture.h"

using namespace nlohmann;

class OperationStringSubstr : public JsonLogicTest
{
};

TEST_F(OperationStringSubstr, PrimitiveStartIndexPositiveNoSubstrLength)
{
	const auto logic = R"(
		{
			"substr": ["jsonlogic", 4]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_EQ(result, "logic");
}

TEST_F(OperationStringSubstr, PrimitiveStartIndexNegativeNoSubstrLength)
{
	const auto logic = R"(
		{
			"substr": ["jsonlogic", -5]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_EQ(result, "logic");
}

TEST_F(OperationStringSubstr, PrimitiveStartIndexPositiveSubstrLengthPositive)
{
	const auto logic = R"(
		{
			"substr": ["jsonlogic", 1, 3]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_EQ(result, "son");
}

TEST_F(OperationStringSubstr, PrimitiveStartIndexPositiveSubstrLengthNegative)
{
	const auto logic = R"(
		{
			"substr": ["jsonlogic", 4, -2]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_EQ(result, "log");
}

TEST_F(OperationStringSubstr, VariableStartIndexPositiveNoSubstrLength)
{
	const auto logic = R"(
		{
			"substr": [{ "var": ["data.foo"] }, 4]
		}
	)"_json;

	const auto data = R"(
		{
			"data": {
				"foo": "jsonlogic"
			}
		}
	)"_json;

	const auto result = json_logic_->Apply(logic, data);

	EXPECT_EQ(result, "logic");
}

TEST_F(OperationStringSubstr, VariableStartIndexNegativeNoSubstrLength)
{
	const auto logic = R"(
		{
			"substr": [{ "var": ["data.foo"] }, -5]
		}
	)"_json;

	const auto data = R"(
		{
			"data": {
				"foo": "jsonlogic"
			}
		}
	)"_json;

	const auto result = json_logic_->Apply(logic, data);

	EXPECT_EQ(result, "logic");
}

TEST_F(OperationStringSubstr, VariableStartIndexPositiveSubstrLengthPositive)
{
	const auto logic = R"(
		{
			"substr": [{ "var": ["data.foo"] }, 1, 3]
		}
	)"_json;

	const auto data = R"(
		{
			"data": {
				"foo": "jsonlogic"
			}
		}
	)"_json;

	const auto result = json_logic_->Apply(logic, data);

	EXPECT_EQ(result, "son");
}

TEST_F(OperationStringSubstr, VariableStartIndexPositiveSubstrLengthNegative)
{
	const auto logic = R"(
		{
			"substr": [{ "var": ["data.foo"] }, 4, -2]
		}
	)"_json;

	const auto data = R"(
		{
			"data": {
				"foo": "jsonlogic"
			}
		}
	)"_json;

	const auto result = json_logic_->Apply(logic, data);

	EXPECT_EQ(result, "log");
}
