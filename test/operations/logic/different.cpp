#include <iostream>

#include "gtest/gtest.h"
#include "json.hpp"

#include "fixture.h"

using namespace nlohmann;


class OperationLogicDifferent : public JsonLogicTest
{
};


TEST_F(OperationLogicDifferent, PrimitiveTrue)
{
	const auto logic = R"(
		{
			"!==": [41, 42]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_TRUE(result);
}

TEST_F(OperationLogicDifferent, PrimitiveFalse)
{
	const auto logic = R"(
		{
			"!==": [42, 42]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_FALSE(result);
}

TEST_F(OperationLogicDifferent, NestedTrue)
{
	const auto logic = R"(
		{
			"!==": [
				{ "!==": [42, 41] },
				{ "!==": ["foo", "foo"] }
			]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_TRUE(result);
}

TEST_F(OperationLogicDifferent, NestedFalse)
{
	const auto logic = R"(
		{
			"!==": [
				{ "!==": [42, 42] },
				{ "!==": ["foo", "foo"] }
			]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_FALSE(result);
}

TEST_F(OperationLogicDifferent, NestedOperandsTrue)
{
	const auto logic = R"(
		{
			"!==": [
				{ "var": ["data.foo"] },
				{ "var": ["data.bar"] }
			]
		}
	)"_json;

	const auto data = R"(
		{
			"data": {
				"foo": 41,
				"bar": 42
			}
		}
	)"_json;

	const auto result = json_logic_->Apply(logic, data);

	EXPECT_TRUE(result);
}

TEST_F(OperationLogicDifferent, NestedOperandsFalse)
{
	const auto logic = R"(
		{
			"!==": [
				{ "var": ["data.foo"] },
				{ "var": ["data.bar"] }
			]
		}
	)"_json;

	const auto data = R"(
		{
			"data": {
				"foo": 42,
				"bar": 42
			}
		}
	)"_json;

	const auto result = json_logic_->Apply(logic, data);

	EXPECT_FALSE(result);
}

TEST_F(OperationLogicDifferent, AbstractStrictDifferent)
{
	// Igualdade abstrata (==)
	EXPECT_FALSE(json_logic_->Apply(R"({ "!=": [0, 0] })"_json));
	EXPECT_FALSE(json_logic_->Apply(R"({ "!=": [0, false] })"_json));
	EXPECT_FALSE(json_logic_->Apply(R"({ "!=": [0, "0"] })"_json));
	EXPECT_FALSE(json_logic_->Apply(R"({ "!=": [0, []] })"_json));
	EXPECT_FALSE(json_logic_->Apply(R"({ "!=": [0, [0]] })"_json));
	EXPECT_TRUE(json_logic_->Apply(R"({ "!=": [0, [0, 42]] })"_json));

	EXPECT_FALSE(json_logic_->Apply(R"({ "!=": [1, 1] })"_json));
	EXPECT_FALSE(json_logic_->Apply(R"({ "!=": [1, true] })"_json));
	EXPECT_FALSE(json_logic_->Apply(R"({ "!=": [1, "1"] })"_json));
	EXPECT_TRUE(json_logic_->Apply(R"({ "!=": [1, []] })"_json));
	EXPECT_FALSE(json_logic_->Apply(R"({ "!=": [1, [1]] })"_json));
	EXPECT_TRUE(json_logic_->Apply(R"({ "!=": [1, [1, 42]] })"_json));

	EXPECT_FALSE(json_logic_->Apply(R"({ "!=": [42, 42] })"_json));
	EXPECT_TRUE(json_logic_->Apply(R"({ "!=": [42, true] })"_json));
	EXPECT_FALSE(json_logic_->Apply(R"({ "!=": [42, "42"] })"_json));
	EXPECT_TRUE(json_logic_->Apply(R"({ "!=": [42, []] })"_json));
	EXPECT_FALSE(json_logic_->Apply(R"({ "!=": [42, [42]] })"_json));
	EXPECT_TRUE(json_logic_->Apply(R"({ "!=": [42, [42, 42]] })"_json));

	// Igualdade rigorosa (===)
	EXPECT_FALSE(json_logic_->Apply(R"({ "!==": [0, 0] })"_json));
	EXPECT_TRUE(json_logic_->Apply(R"({ "!==": [0, false] })"_json));
	EXPECT_TRUE(json_logic_->Apply(R"({ "!==": [0, "0"] })"_json));
	EXPECT_TRUE(json_logic_->Apply(R"({ "!==": [0, []] })"_json));
	EXPECT_TRUE(json_logic_->Apply(R"({ "!==": [0, [0]] })"_json));
	EXPECT_TRUE(json_logic_->Apply(R"({ "!==": [0, [0, 42]] })"_json));

	EXPECT_FALSE(json_logic_->Apply(R"({ "!==": [1, 1] })"_json));
	EXPECT_TRUE(json_logic_->Apply(R"({ "!==": [1, true] })"_json));
	EXPECT_TRUE(json_logic_->Apply(R"({ "!==": [1, "1"] })"_json));
	EXPECT_TRUE(json_logic_->Apply(R"({ "!==": [1, []] })"_json));
	EXPECT_TRUE(json_logic_->Apply(R"({ "!==": [1, [1]] })"_json));
	EXPECT_TRUE(json_logic_->Apply(R"({ "!==": [1, [1, 42]] })"_json));

	EXPECT_FALSE(json_logic_->Apply(R"({ "!==": [42, 42] })"_json));
	EXPECT_TRUE(json_logic_->Apply(R"({ "!==": [42, true] })"_json));
	EXPECT_TRUE(json_logic_->Apply(R"({ "!==": [42, "42"] })"_json));
	EXPECT_TRUE(json_logic_->Apply(R"({ "!==": [42, []] })"_json));
	EXPECT_TRUE(json_logic_->Apply(R"({ "!==": [42, [42]] })"_json));
	EXPECT_TRUE(json_logic_->Apply(R"({ "!==": [42, [42, 42]] })"_json));
}
