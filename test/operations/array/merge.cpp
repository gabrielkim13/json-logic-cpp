#include <iostream>

#include "gtest/gtest.h"
#include "nlohmann/json.hpp"

#include "fixture.h"

using namespace nlohmann;

class OperationArrayMerge : public JsonLogicTest
{
};

TEST_F(OperationArrayMerge, PrimitiveArrays)
{
	const auto logic = R"(
		{
			"merge": [
				[1, 2],
				[3, "4", 5],
				[6],
				[7, { "a": 8 }, 9]
			]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	const std::vector<json> expected_result{1, 2, 3, "4", 5, 6, 7, json{{"a", 8}}, 9};

	EXPECT_EQ(result, expected_result);
}

TEST_F(OperationArrayMerge, PrimitiveMixed)
{
	const auto logic = R"(
		{
			"merge": [
				[1, 2],
				3,
				["4", 5],
				6,
				[7],
				{ "a": 8 },
				[9]
			]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	const std::vector<json> expected_result{1, 2, 3, "4", 5, 6, 7, json{{"a", 8}}, 9};

	EXPECT_EQ(result, expected_result);
}

TEST_F(OperationArrayMerge, VariableArrays)
{
	const auto logic = R"(
		{
			"merge": [
				[1, 2],
				{ "var": ["data.b"] },
				{ "var": ["data.c"] },
				[7, { "a": 8 }, 9]
			]
		}
	)"_json;

	const auto data = R"(
		{
			"data": {
				"b": [3, "4", 5],
				"c": [6]
			}
		}
	)"_json;

	const auto result = json_logic_->Apply(logic, data);

	const std::vector<json> expected_result{1, 2, 3, "4", 5, 6, 7, json{{"a", 8}}, 9};

	EXPECT_EQ(result, expected_result);
}

TEST_F(OperationArrayMerge, VariableMixed)
{
	const auto logic = R"(
		{
			"merge": [
				[1, 2],
				{ "var": ["data.b"] },
				{ "var": ["data.c"] },
				6,
				{ "var": ["data.e"] },
				{ "a": 8 },
				[9]
			]
		}
	)"_json;

	const auto data = R"(
		{
			"data": {
				"b": 3,
				"c": ["4", 5],
				"e": [7]
			}
		}
	)"_json;

	const auto result = json_logic_->Apply(logic, data);

	const std::vector<json> expected_result{1, 2, 3, "4", 5, 6, 7, json{{"a", 8}}, 9};

	EXPECT_EQ(result, expected_result);
}
