#include <iostream>

#include "gtest/gtest.h"
#include "json.hpp"

#include "fixture.h"

using namespace nlohmann;

class OperationLogicTruthy : public JsonLogicTest
{
};

TEST_F(OperationLogicTruthy, PrimitiveTrue)
{
	const auto logic = R"(
		{
			"!!": [true]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_TRUE(result);
}

TEST_F(OperationLogicTruthy, PrimitiveFalse)
{
	const auto logic = R"(
		{
			"!!": [false]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_FALSE(result);
}

TEST_F(OperationLogicTruthy, NumberTrue)
{
	const auto logic = R"(
		{
			"!!": [-1]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_TRUE(result);
}

TEST_F(OperationLogicTruthy, NumberFalse)
{
	const auto logic = R"(
		{
			"!!": [0]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_FALSE(result);
}

TEST_F(OperationLogicTruthy, ArrayTrue)
{
	const auto logic = R"(
		{
			"!!": [[0]]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_TRUE(result);
}

TEST_F(OperationLogicTruthy, ArrayFalse)
{
	const auto logic = R"(
		{
			"!!": [[]]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_FALSE(result);
}

TEST_F(OperationLogicTruthy, StringTrue)
{
	const auto logic = R"(
		{
			"!!": ["0"]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_TRUE(result);
}

TEST_F(OperationLogicTruthy, StringFalse)
{
	const auto logic = R"(
		{
			"!!": [""]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_FALSE(result);
}

TEST_F(OperationLogicTruthy, NestedTrue)
{
	const auto logic = R"(
		{
			"!!": [{ "!!": [true] }]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_TRUE(result);
}

TEST_F(OperationLogicTruthy, NestedFalse)
{
	const auto logic = R"(
		{
			"!!": [{ "!!": [false] }]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_FALSE(result);
}
