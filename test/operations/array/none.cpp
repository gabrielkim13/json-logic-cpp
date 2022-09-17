#include <iostream>

#include "gtest/gtest.h"
#include "nlohmann/json.hpp"

#include "fixture.h"

using namespace nlohmann;

class OperationArrayNone : public JsonLogicTest
{
};

TEST_F(OperationArrayNone, PrimitiveTrue)
{
	const auto logic = R"(
		{
			"none": [
				[1, 2, 3],
				{ "<": [{ "var": [""] }, 1] }
			]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_TRUE(result);
}

TEST_F(OperationArrayNone, PrimitiveFalse)
{
	const auto logic = R"(
		{
			"none": [
				[1, 2, 3],
				{ "<": [{ "var": [""] }, 2] }
			]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_FALSE(result);
}

TEST_F(OperationArrayNone, DataTrue)
{
	const auto logic = R"(
		{
			"none": [
				{ "var": ["data"] },
				{ "<": [{ "var": ["foo.bar"] }, 1] }
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

TEST_F(OperationArrayNone, DataFalse)
{
	const auto logic = R"(
		{
			"none": [
				{ "var": ["data"] },
				{ "<": [{ "var": ["foo.bar"] }, 2] }
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
