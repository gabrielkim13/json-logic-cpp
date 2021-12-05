#include <iostream>

#include "gtest/gtest.h"
#include "json.hpp"

#include "fixture.h"

using namespace nlohmann;

class OperationArraySome : public JsonLogicTest
{
};

TEST_F(OperationArraySome, PrimitiveTrue)
{
	const auto logic = R"(
		{
			"some": [
				[1, 2, 3],
				{ "==": [{ "var": [""] }, 2] }
			]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_TRUE(result);
}

TEST_F(OperationArraySome, PrimitiveFalse)
{
	const auto logic = R"(
		{
			"some": [
				[1, 2, 3],
				{ "==": [{ "var": [""] }, 42] }
			]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_FALSE(result);
}

TEST_F(OperationArraySome, DataTrue)
{
	const auto logic = R"(
		{
			"some": [
				{ "var": ["data"] },
				{ "==": [{ "var": ["foo.bar"] }, 2] }
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

TEST_F(OperationArraySome, DataFalse)
{
	const auto logic = R"(
		{
			"some": [
				{ "var": ["data"] },
				{ "==": [{ "var": ["foo.bar"] }, 42] }
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
