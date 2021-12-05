#include <iostream>

#include "gtest/gtest.h"
#include "json.hpp"

#include "fixture.h"

using namespace nlohmann;

class OperationLogicAnd : public JsonLogicTest
{
};

TEST_F(OperationLogicAnd, PrimitiveTrue)
{
	const auto logic = R"(
		{
			"and": [
				true,
				true,
				true
			]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_TRUE(result);
}

TEST_F(OperationLogicAnd, PrimitiveFalse)
{
	const auto logic = R"(
		{
			"and": [
				true,
				true,
				false
			]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_FALSE(result);
}

TEST_F(OperationLogicAnd, NestedTrue)
{
	const auto logic = R"(
		{
			"and": [
				{
					"and": [
						true,
						true
					]
				},
				{
					"and": [
						true,
						true
					]
				},
				true
			]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_TRUE(result);
}

TEST_F(OperationLogicAnd, NestedFalse)
{
	const auto logic = R"(
		{
			"and": [
				{
					"and": [
						true,
						true
					]
				},
				{
					"and": [
						true,
						false
					]
				},
				true
			]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_FALSE(result);
}
