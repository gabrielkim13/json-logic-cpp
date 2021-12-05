#include <iostream>

#include "gtest/gtest.h"
#include "json.hpp"

#include "fixture.h"

using namespace nlohmann;

class OperationLogicNot : public JsonLogicTest
{
};

TEST_F(OperationLogicNot, PrimitiveTrue)
{
	const auto logic = R"(
		{
			"!": [false]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_TRUE(result);
}

TEST_F(OperationLogicNot, PrimitiveFalse)
{
	const auto logic = R"(
		{
			"!": [true]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_FALSE(result);
}

TEST_F(OperationLogicNot, NumberTrue)
{
	const auto logic = R"(
		{
			"!": [0]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_TRUE(result);
}

TEST_F(OperationLogicNot, NumberFalse)
{
	const auto logic = R"(
		{
			"!": [-1]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_FALSE(result);
}

TEST_F(OperationLogicNot, ArrayTrue)
{
	const auto logic = R"(
		{
			"!": [[]]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_TRUE(result);
}

TEST_F(OperationLogicNot, ArrayFalse)
{
	const auto logic = R"(
		{
			"!": [[0]]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_FALSE(result);
}

TEST_F(OperationLogicNot, StringTrue)
{
	const auto logic = R"(
		{
			"!": [""]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_TRUE(result);
}

TEST_F(OperationLogicNot, StringFalse)
{
	const auto logic = R"(
		{
			"!": ["0"]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_FALSE(result);
}

TEST_F(OperationLogicNot, NestedTrue)
{
	const auto logic = R"(
		{
			"!": [{ "!": [true] }]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_TRUE(result);
}

TEST_F(OperationLogicNot, NestedFalse)
{
	const auto logic = R"(
		{
			"!": [{ "!": [false] }]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_FALSE(result);
}
