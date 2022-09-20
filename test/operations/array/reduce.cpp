#include <vector>

#include "gtest/gtest.h"
#include "nlohmann/json.hpp"

#include "fixture.h"

using namespace nlohmann;

class OperationArrayReduce : public JsonLogicTest
{
};

TEST_F(OperationArrayReduce, PrimitiveSimpleOperation)
{
	const auto logic = R"(
		{
			"reduce": [
				[1, 2, 3],
				{ "+": [{ "var": ["current"] }, { "var": ["accumulator"] }] },
				10
			]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_EQ(result, 16);
}

TEST_F(OperationArrayReduce, PrimitiveComposedOperation)
{
	const auto logic = R"(
		{
			"reduce": [
				[1, 2, 3],
				{
					"+": [
						{ "var": ["accumulator"] },
						{ "%": [{ "var": ["current"] }, 2] }
					]
				},
				10
			]
		}
	)"_json;

	const auto result = json_logic_->Apply(logic);

	EXPECT_EQ(result, 12);
}

TEST_F(OperationArrayReduce, VariableSimpleOperation)
{
	const auto logic = R"(
		{
			"reduce": [
				{ "var": ["data.foo"] },
				{ "+": [{ "var": ["current"] }, { "var": ["accumulator"] }] },
				{ "var": ["data.init"] }
			]
		}
	)"_json;

	const auto data = R"(
		{
			"data": {
				"foo": [1, 2, 3],
				"init": 10
			}
		}
	)"_json;

	const auto result = json_logic_->Apply(logic, data);

	EXPECT_EQ(result, 16);
}

TEST_F(OperationArrayReduce, VariableComposedOperation)
{
	const auto logic = R"(
		{
			"reduce": [
				{ "var": ["data.foo"] },
				{
					"+": [
						{ "var": ["accumulator"] },
						{ "%": [{ "var": ["current"] }, 2] }
					]
				},
				{ "var": ["data.init"] }
			]
		}
	)"_json;

	const auto data = R"(
		{
			"data": {
				"foo": [1, 2, 3],
				"init": 10
			}
		}
	)"_json;

	const auto result = json_logic_->Apply(logic, data);

	EXPECT_EQ(result, 12);
}
