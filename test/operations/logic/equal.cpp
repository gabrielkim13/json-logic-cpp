#include <iostream>

#include "gtest/gtest.h"
#include "nlohmann/json.hpp"

#include "fixture.h"

using namespace nlohmann;

class OperationLogicEqual : public JsonLogicTest
{
};

TEST_F(OperationLogicEqual, PrimitiveTrue)
{
	const auto logic = R"(
		{
			"===": [42, 42]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_TRUE(result);
}

TEST_F(OperationLogicEqual, PrimitiveFalse)
{
	const auto logic = R"(
		{
			"===": [0, 42]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_FALSE(result);
}

TEST_F(OperationLogicEqual, NestedTrue)
{
	const auto logic = R"(
		{
			"===": [
				{ "===": [42, 42] },
				{ "===": ["foo", "foo"] }
			]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_TRUE(result);
}

TEST_F(OperationLogicEqual, NestedFalse)
{
	const auto logic = R"(
		{
			"===": [
				{ "===": [42, 14] },
				{ "===": ["foo", "foo"] }
			]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_FALSE(result);
}

TEST_F(OperationLogicEqual, NestedOperandsTrue)
{
	const auto logic = R"(
		{
			"===": [
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

	EXPECT_TRUE(result);
}

TEST_F(OperationLogicEqual, NestedOperandsFalse)
{
	const auto logic = R"(
		{
			"===": [
				{ "var": ["data.foo"] },
				{ "var": ["data.bar"] }
			]
		}
	)"_json;

	const auto data = R"(
		{
			"data": {
				"foo": 42,
				"bar": 14
			}
		}
	)"_json;

	const auto result = json_logic_->Apply(logic, data);

	EXPECT_FALSE(result);
}

TEST_F(OperationLogicEqual, AbstractStrictEqual)
{
	// Igualdade abstrata (==)
	EXPECT_TRUE(json_logic_->Apply(R"({ "==": [0, 0] })"_json));
	EXPECT_TRUE(json_logic_->Apply(R"({ "==": [0, false] })"_json));
	EXPECT_TRUE(json_logic_->Apply(R"({ "==": [0, "0"] })"_json));
	EXPECT_TRUE(json_logic_->Apply(R"({ "==": [0, []] })"_json));
	EXPECT_TRUE(json_logic_->Apply(R"({ "==": [0, [0]] })"_json));
	EXPECT_FALSE(json_logic_->Apply(R"({ "==": [0, [0, 42]] })"_json));

	EXPECT_TRUE(json_logic_->Apply(R"({ "==": [1, 1] })"_json));
	EXPECT_TRUE(json_logic_->Apply(R"({ "==": [1, true] })"_json));
	EXPECT_TRUE(json_logic_->Apply(R"({ "==": [1, "1"] })"_json));
	EXPECT_FALSE(json_logic_->Apply(R"({ "==": [1, []] })"_json));
	EXPECT_TRUE(json_logic_->Apply(R"({ "==": [1, [1]] })"_json));
	EXPECT_FALSE(json_logic_->Apply(R"({ "==": [1, [1, 42]] })"_json));

	EXPECT_TRUE(json_logic_->Apply(R"({ "==": [42, 42] })"_json));
	EXPECT_FALSE(json_logic_->Apply(R"({ "==": [42, true] })"_json));
	EXPECT_TRUE(json_logic_->Apply(R"({ "==": [42, "42"] })"_json));
	EXPECT_FALSE(json_logic_->Apply(R"({ "==": [42, []] })"_json));
	EXPECT_TRUE(json_logic_->Apply(R"({ "==": [42, [42]] })"_json));
	EXPECT_FALSE(json_logic_->Apply(R"({ "==": [42, [42, 42]] })"_json));

	// Igualdade rigorosa (===)
	EXPECT_TRUE(json_logic_->Apply(R"({ "===": [0, 0] })"_json));
	EXPECT_FALSE(json_logic_->Apply(R"({ "===": [0, false] })"_json));
	EXPECT_FALSE(json_logic_->Apply(R"({ "===": [0, "0"] })"_json));
	EXPECT_FALSE(json_logic_->Apply(R"({ "===": [0, []] })"_json));
	EXPECT_FALSE(json_logic_->Apply(R"({ "===": [0, [0]] })"_json));
	EXPECT_FALSE(json_logic_->Apply(R"({ "===": [0, [0, 42]] })"_json));

	EXPECT_TRUE(json_logic_->Apply(R"({ "===": [1, 1] })"_json));
	EXPECT_FALSE(json_logic_->Apply(R"({ "===": [1, true] })"_json));
	EXPECT_FALSE(json_logic_->Apply(R"({ "===": [1, "1"] })"_json));
	EXPECT_FALSE(json_logic_->Apply(R"({ "===": [1, []] })"_json));
	EXPECT_FALSE(json_logic_->Apply(R"({ "===": [1, [1]] })"_json));
	EXPECT_FALSE(json_logic_->Apply(R"({ "===": [1, [1, 42]] })"_json));

	EXPECT_TRUE(json_logic_->Apply(R"({ "===": [42, 42] })"_json));
	EXPECT_FALSE(json_logic_->Apply(R"({ "===": [42, true] })"_json));
	EXPECT_FALSE(json_logic_->Apply(R"({ "===": [42, "42"] })"_json));
	EXPECT_FALSE(json_logic_->Apply(R"({ "===": [42, []] })"_json));
	EXPECT_FALSE(json_logic_->Apply(R"({ "===": [42, [42]] })"_json));
	EXPECT_FALSE(json_logic_->Apply(R"({ "===": [42, [42, 42]] })"_json));
}
