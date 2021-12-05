#include <iostream>

#include "gtest/gtest.h"
#include "json.hpp"

#include "fixture.h"

using namespace nlohmann;

class OperationArrayAll : public JsonLogicTest
{
};

TEST_F(OperationArrayAll, PrimitiveTrue)
{
	const auto logic = R"(
		{
			"all": [
				[1, 2, 3],
				{ ">": [{ "var": [""] }, 0] }
			]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_TRUE(result);
}

TEST_F(OperationArrayAll, PrimitiveFalse)
{
	const auto logic = R"(
		{
			"all": [
				[1, 2, 3],
				{ ">": [{ "var": [""] }, 3] }
			]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_FALSE(result);
}

TEST_F(OperationArrayAll, DataTrue)
{
	const auto logic = R"(
		{
			"all": [
				{ "var": ["data"] },
				{ ">": [{ "var": ["foo.bar"] }, 0] }
			]
		}
	)"_json;

	const auto data = R"(
		{
			"data": [
				{ "foo": { "bar": 1 } },
				{ "foo": { "bar": 2 } },
				{ "foo": { "bar": 3 } }
			]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic, data);

	EXPECT_TRUE(result);
}

TEST_F(OperationArrayAll, DataFalse)
{
	const auto logic = R"(
		{
			"all": [
				{ "var": ["data"] },
				{ ">": [{ "var": ["foo.bar"] }, 3] }
			]
		}
	)"_json;

	const auto data = R"(
		{
			"data": [
				{ "foo": { "bar": 1 } },
				{ "foo": { "bar": 2 } },
				{ "foo": { "bar": 3 } }
			]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic, data);

	EXPECT_FALSE(result);
}
