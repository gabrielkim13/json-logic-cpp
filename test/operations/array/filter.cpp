#include <vector>

#include "gtest/gtest.h"
#include "nlohmann/json.hpp"

#include "fixture.h"

using namespace nlohmann;

class OperationArrayFilter : public JsonLogicTest
{
};

TEST_F(OperationArrayFilter, PrimitiveSimpleOperation)
{
	const auto logic = R"(
		{
			"filter": [
				[1, 2, 3, 4, 5],
				{ "%": [{ "var": [""] }, 2] }
			]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	const std::vector<int> expected_result{1, 3, 5};

	EXPECT_EQ(result, expected_result);
}

TEST_F(OperationArrayFilter, PrimitiveComposedOperation)
{
	const auto logic = R"(
		{
			"filter": [
				[1, 2, 3, 4, 5],
				{
					"and": [
						{ "%": [{ "var": [""] }, 2] },
						{ ">": [{ "var": [""] }, 2] }
					]
				}
			]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	const std::vector<int> expected_result{3, 5};

	EXPECT_EQ(result, expected_result);
}

TEST_F(OperationArrayFilter, VariableSimpleOperation)
{
	const auto logic = R"(
		{
			"filter": [
				{ "var": ["data.foo"] },
				{ "%": [{ "var": [""] }, 2] }
			]
		}
	)"_json;

	const auto data = R"(
		{
			"data": {
				"foo": [1, 2, 3, 4, 5]
			}
		}
	)"_json;

	const auto result = json_logic_->Apply(logic, data);

	const std::vector<int> expected_result{1, 3, 5};

	EXPECT_EQ(result, expected_result);
}

TEST_F(OperationArrayFilter, VariableComposedOperation)
{
	const auto logic = R"(
		{
			"filter": [
				{ "var": ["data.foo"] },
				{
					"and": [
						{ "%": [{ "var": [""] }, 2] },
						{ ">": [{ "var": [""] }, 2] }
					]
				}
			]
		}
	)"_json;

	const auto data = R"(
		{
			"data": {
				"foo": [1, 2, 3, 4, 5]
			}
		}
	)"_json;

	const auto result = json_logic_->Apply(logic, data);

	const std::vector<int> expected_result{3, 5};

	EXPECT_EQ(result, expected_result);
}
