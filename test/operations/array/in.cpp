#include <iostream>

#include "gtest/gtest.h"
#include "nlohmann/json.hpp"

#include "fixture.h"

using namespace nlohmann;

class OperationArrayStringIn : public JsonLogicTest
{
};

TEST_F(OperationArrayStringIn, PrimitiveArrayTrue)
{
	const auto logic = R"(
		{
			"in": [
				2,
				[1, 2, 3]
			]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_TRUE(result);
}

TEST_F(OperationArrayStringIn, PrimitiveArrayFalse)
{
	const auto logic = R"(
		{
			"in": [
				42,
				[1, 2, 3]
			]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_FALSE(result);
}

TEST_F(OperationArrayStringIn, VariableArrayTrue)
{
	const auto logic = R"(
		{
			"in": [
				{ "var": ["data.search"] },
				{ "var": ["data.container"] }
			]
		}
	)"_json;

	const auto data = R"(
		{
			"data": {
				"search": 2,
				"container": [1, 2, 3]
			}
		}
	)"_json;

	const auto result = json_logic_->Apply(logic, data);

	EXPECT_TRUE(result);
}

TEST_F(OperationArrayStringIn, VariableArrayFalse)
{
	const auto logic = R"(
		{
			"in": [
				{ "var": ["data.search"] },
				{ "var": ["data.container"] }
			]
		}
	)"_json;

	const auto data = R"(
		{
			"data": {
				"search": 42,
				"container": [1, 2, 3]
			}
		}
	)"_json;

	const auto result = json_logic_->Apply(logic, data);

	EXPECT_FALSE(result);
}

TEST_F(OperationArrayStringIn, PrimitiveStringTrue)
{
	const auto logic = R"(
		{
			"in": [
				"Spring",
				"Springfield"
			]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_TRUE(result);
}

TEST_F(OperationArrayStringIn, PrimitiveStringFalse)
{
	const auto logic = R"(
		{
			"in": [
				"Sprint",
				"Springfield"
			]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_FALSE(result);
}

TEST_F(OperationArrayStringIn, VariableStringTrue)
{
	const auto logic = R"(
		{
			"in": [
				{ "var": ["data.search"] },
				{ "var": ["data.container"] }
			]
		}
	)"_json;

	const auto data = R"(
		{
			"data": {
				"search": "Spring",
				"container": "Springfield"
			}
		}
	)"_json;

	const auto result = json_logic_->Apply(logic, data);

	EXPECT_TRUE(result);
}

TEST_F(OperationArrayStringIn, VariableStringFalse)
{
	const auto logic = R"(
		{
			"in": [
				{ "var": ["data.search"] },
				{ "var": ["data.container"] }
			]
		}
	)"_json;

	const auto data = R"(
		{
			"data": {
				"search": "Sprint",
				"container": "Springfield"
			}
		}
	)"_json;

	const auto result = json_logic_->Apply(logic, data);

	EXPECT_FALSE(result);
}
