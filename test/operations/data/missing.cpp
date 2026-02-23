#include <vector>

#include "gtest/gtest.h"

#include "nlohmann/json.hpp"

#include "fixture.h"

using namespace nlohmann;

class OperationDataMissing : public JsonLogicTest
{
};

TEST_F(OperationDataMissing, SimpleKeys)
{
    const auto logic = R"(
		{
			"missing": ["a", "b", "c", "d"]
		}
	)"_json;

    const auto data = R"(
		{
			"a": 1,
			"c": 3
		}
	)"_json;

    const auto result = json_logic_->Apply(logic, data);

    std::vector<std::string> expected_result{"b", "d"};
    EXPECT_EQ(result, expected_result);
}

TEST_F(OperationDataMissing, SimpleKeysAllPresent)
{
    const auto logic = R"(
		{
			"missing": ["a", "b", "c", "d"]
		}
	)"_json;

    const auto data = R"(
		{
			"a": 1,
            "b": 2,
			"c": 3,
			"d": 4
		}
	)"_json;

    const auto result = json_logic_->Apply(logic, data);

    std::vector<std::string> expected_result{};
    EXPECT_EQ(result, expected_result);
}

TEST_F(OperationDataMissing, SimpleKeysRepeatedKeys)
{
    const auto logic = R"(
		{
			"missing": ["a", "b", "b", "c", "c", "d"]
		}
	)"_json;

    const auto data = R"(
		{
			"a": 1,
			"c": 3
		}
	)"_json;

    const auto result = json_logic_->Apply(logic, data);

    std::vector<std::string> expected_result{"b", "d"};
    EXPECT_EQ(result, expected_result);
}

TEST_F(OperationDataMissing, NestedKeys)
{
    const auto logic = R"(
		{
			"missing": ["a.x", "a.y", "a.z", "b.x", "b.y", "b.z"]
		}
	)"_json;

    const auto data = R"(
		{
			"a": {
                "x": 1,
                "z": 3
            },
			"b": {
                "x": 1,
                "y": 2
            }
		}
	)"_json;

    const auto result = json_logic_->Apply(logic, data);

    std::vector<std::string> expected_result{"a.y", "b.z"};
    EXPECT_EQ(result, expected_result);
}

TEST_F(OperationDataMissing, OrderPreservationNonAlphabetic)
{
    const auto logic = R"(
        {
        "missing": ["zebra", "apple", "banana", "dog", "cat"]
        }
    )"_json;

    const auto data = R"(
        {
        "apple": 1,
        "dog": 4
        }
    )"_json;

    const auto result = json_logic_->Apply(logic, data);

    std::vector<std::string> expected_result{"zebra", "banana", "cat"};
    EXPECT_EQ(result, expected_result);
}

TEST_F(OperationDataMissing, OrderPreservationReversedKeys)
{
    const auto logic = R"(
        {
        "missing": ["z", "y", "x", "w", "v"]
        }
    )"_json;

    const auto data = R"(
        {
        "y": 2,
        "w": 4
        }
    )"_json;

    const auto result = json_logic_->Apply(logic, data);

    std::vector<std::string> expected_result{"z", "x", "v"};
    EXPECT_EQ(result, expected_result);
}
