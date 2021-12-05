#include <vector>

#include "gtest/gtest.h"
#include "json.hpp"

#include "fixture.h"

using namespace nlohmann;

class OperationArrayMap : public JsonLogicTest
{
};

TEST_F(OperationArrayMap, PrimitiveSimpleOperation)
{
	const auto logic = R"(
		{
			"map": [
				[1, 2, 3],
				{ "*": [{ "var": [""] }, 2] }
			]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	const std::vector<int> expected_result{2, 4, 6};

	EXPECT_EQ(result, expected_result);
}

TEST_F(OperationArrayMap, PrimitiveComposedOperation)
{
	const auto logic = R"(
		{
			"map": [
				[1, 2, 3],
				{
					"==": [
						{ "%": [{ "var": [""] }, 2] },
						1
					]
				}
			]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	const std::vector<bool> expected_result{true, false, true};

	EXPECT_EQ(result, expected_result);
}

TEST_F(OperationArrayMap, VariableSimpleOperation)
{
	const auto logic = R"(
		{
			"map": [
				{ "var": ["data.foo"] },
				{ "*": [{ "var": [""] }, 2] }
			]
		}
	)"_json;

	const auto data = R"(
		{
			"data": {
				"foo": [1, 2, 3]
			}
		}
	)"_json;

	const auto result = json_logic_->Apply(logic, data);

	const std::vector<int> expected_result{2, 4, 6};

	EXPECT_EQ(result, expected_result);
}

TEST_F(OperationArrayMap, VariableComposedOperation)
{
	const auto logic = R"(
		{
			"map": [
				{ "var": ["data.foo"] },
				{
					"==": [
						{ "%": [{ "var": [""] }, 2] },
						1
					]
				}
			]
		}
	)"_json;

	const auto data = R"(
		{
			"data": {
				"foo": [1, 2, 3]
			}
		}
	)"_json;

	const auto result = json_logic_->Apply(logic, data);

	const std::vector<bool> expected_result{true, false, true};

	EXPECT_EQ(result, expected_result);
}
