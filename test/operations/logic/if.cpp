#include <iostream>

#include "gtest/gtest.h"
#include "nlohmann/json.hpp"

#include "fixture.h"

using namespace nlohmann;

class OperationLogicIf : public JsonLogicTest
{
};

TEST_F(OperationLogicIf, PrimitiveTrue)
{
    const auto logic = R"(
		{
			"if": [
				true,
				"true",
				"false"
			]
		}
	)"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_EQ(result, "true");
}

TEST_F(OperationLogicIf, PrimitiveFalse)
{
    const auto logic = R"(
		{
			"if": [
				false,
				"true",
				"false"
			]
		}
	)"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_EQ(result, "false");
}

TEST_F(OperationLogicIf, SuboperationTrue)
{
    const auto logic = R"(
		{
			"if": [
				{ "===": [42, 42] },
				"true",
				"false"
			]
		}
	)"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_EQ(result, "true");
}

TEST_F(OperationLogicIf, SuboperationFalse)
{
    const auto logic = R"(
		{
			"if": [
				{ "===": [-1, 42] },
				"true",
				"false"
			]
		}
	)"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_EQ(result, "false");
}

TEST_F(OperationLogicIf, SuboperationWithVariablesTrue)
{
    const auto logic = R"(
		{
			"if": [
				{ "var": ["data.condition"] },
				{ "var": ["data.result"] },
				"false"
			]
		}
	)"_json;

    const auto data = R"(
		{
			"data": {
				"condition": true,
				"result": "true"
			}
		}
	)"_json;

    const auto result = json_logic_->Apply(logic, data);

    EXPECT_EQ(result, "true");
}

TEST_F(OperationLogicIf, SuboperationWithVariablesFalse)
{
	const auto logic = R"(
		{
			"if": [
				{ "var": ["data.condition"] },
				"true",
				{ "var": ["data.result"] }
			]
		}
	)"_json;

	const auto data = R"(
		{
			"data": {
				"condition": false,
				"result": "false"
			}
		}
	)"_json;

	const auto result = json_logic_->Apply(logic, data);

	EXPECT_EQ(result, "false");
}

TEST_F(OperationLogicIf, MultipleElseIf1)
{
	const auto logic = R"(
		{
			"if": [
				{ "===": [{ "var": ["data.foo"] }, 1] }, "one",
				{ "===": [{ "var": ["data.foo"] }, 2] }, "two",
				{ "===": [{ "var": ["data.foo"] }, 3] }, "three",
				"zero"
			]
		}
	)"_json;

	const auto data = R"(
		{
			"data": {
				"foo": 1
			}
		}
	)"_json;

	const auto result = json_logic_->Apply(logic, data);

	EXPECT_EQ(result, "one");
}

TEST_F(OperationLogicIf, MultipleElseIf2)
{
	const auto logic = R"(
		{
			"if": [
				{ "===": [{ "var": ["data.foo"] }, 1] }, "one",
				{ "===": [{ "var": ["data.foo"] }, 2] }, "two",
				{ "===": [{ "var": ["data.foo"] }, 3] }, "three",
				"zero"
			]
		}
	)"_json;

	const auto data = R"(
		{
			"data": {
				"foo": 2
			}
		}
	)"_json;

	const auto result = json_logic_->Apply(logic, data);

	EXPECT_EQ(result, "two");
}

TEST_F(OperationLogicIf, MultipleElseIf3)
{
	const auto logic = R"(
		{
			"if": [
				{ "===": [{ "var": ["data.foo"] }, 1] }, "one",
				{ "===": [{ "var": ["data.foo"] }, 2] }, "two",
				{ "===": [{ "var": ["data.foo"] }, 3] }, "three",
				"zero"
			]
		}
	)"_json;

	const auto data = R"(
		{
			"data": {
				"foo": 3
			}
		}
	)"_json;

	const auto result = json_logic_->Apply(logic, data);

	EXPECT_EQ(result, "three");
}

TEST_F(OperationLogicIf, MultipleElseIf0)
{
	const auto logic = R"(
		{
			"if": [
				{ "===": [{ "var": ["data.foo"] }, 1] }, "one",
				{ "===": [{ "var": ["data.foo"] }, 2] }, "two",
				{ "===": [{ "var": ["data.foo"] }, 3] }, "three",
				"zero"
			]
		}
	)"_json;

	const auto data = R"(
		{
			"data": {
				"foo": -1
			}
		}
	)"_json;

	const auto result = json_logic_->Apply(logic, data);

	EXPECT_EQ(result, "zero");
}
