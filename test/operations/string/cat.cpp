#include <iostream>

#include "gtest/gtest.h"
#include "nlohmann/json.hpp"

#include "fixture.h"

using namespace nlohmann;

class OperationStringCat : public JsonLogicTest
{
};

TEST_F(OperationStringCat, Primitive)
{
	const auto logic = R"(
		{
			"cat": [
				"I love",
				" pie"
			]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_EQ(result, "I love pie");
}

TEST_F(OperationStringCat, Variable)
{
	const auto logic = R"(
		{
			"cat": [
				"I love ",
				{ "var": ["filling"] },
				" pie"
			]
		}
	)"_json;

	const auto data = R"(
		{
			"filling": "apple"
		}
	)"_json;

	const auto result = json_logic_->Apply(logic, data);

	EXPECT_EQ(result, "I love apple pie");
}
