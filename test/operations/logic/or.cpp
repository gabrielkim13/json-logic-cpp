#include <iostream>

#include "gtest/gtest.h"
#include "nlohmann/json.hpp"

#include "fixture.h"

using namespace nlohmann;

class OperationLogicOr : public JsonLogicTest
{
};

TEST_F(OperationLogicOr, PrimitiveTrue)
{
	const auto logic = R"(
		{
			"or": [
				false,
				true,
				false
			]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_TRUE(result);
}

TEST_F(OperationLogicOr, PrimitiveFalse)
{
	const auto logic = R"(
		{
			"or": [
				false,
				false,
				false
			]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_FALSE(result);
}

TEST_F(OperationLogicOr, NestedTrue)
{
	const auto logic = R"(
		{
			"or": [
				{
					"or": [
						true,
						false
					]
				},
				{
					"or": [
						false,
						false
					]
				},
				false
			]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_TRUE(result);
}

TEST_F(OperationLogicOr, NestedFalse)
{
	const auto logic = R"(
		{
			"or": [
				{
					"or": [
						false,
						false
					]
				},
				{
					"or": [
						false,
						false
					]
				},
				false
			]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_FALSE(result);
}
