#include <vector>

#include "gtest/gtest.h"

#include "nlohmann/json.hpp"

#include "fixture.h"

using namespace nlohmann;

class OperationDataMissingSome : public JsonLogicTest
{
};

TEST_F(OperationDataMissingSome, SimpleKeysFoundMinimum)
{
    const auto logic = R"(
		{
			"missing_some": [2, ["a", "b", "c", "d"]]
		}
	)"_json;

    const auto data = R"(
		{
			"a": 1,
			"c": 3
		}
	)"_json;

    const auto result = json_logic_->Apply(logic, data);

    std::vector<std::string> expected_result{};
    EXPECT_EQ(result, expected_result);
}

TEST_F(OperationDataMissingSome, SimpleKeysNotFoundMinimum)
{
    const auto logic = R"(
		{
			"missing_some": [3, ["a", "b", "c", "d"]]
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

TEST_F(OperationDataMissingSome, SimpleRepeatedKeysFoundMinimum)
{
    const auto logic = R"(
		{
			"missing_some": [2, ["a", "b", "b", "c", "c", "d"]]
		}
	)"_json;

    const auto data = R"(
		{
			"a": 1,
			"c": 3
		}
	)"_json;

    const auto result = json_logic_->Apply(logic, data);

    std::vector<std::string> expected_result{};
    EXPECT_EQ(result, expected_result);
}

TEST_F(OperationDataMissingSome, SimpleRepeatedKeysNotFoundMinimum)
{
    const auto logic = R"(
		{
			"missing_some": [3, ["a", "b", "b", "c", "c", "d"]]
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

TEST_F(OperationDataMissingSome, NestedKeysFoundMinimum)
{
    const auto logic = R"(
		{
			"missing_some": [4, ["a.x", "a.y", "a.z", "b.x", "b.y", "b.z"]]
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

    std::vector<std::string> expected_result{};
    EXPECT_EQ(result, expected_result);
}

TEST_F(OperationDataMissingSome, NestedKeysNotFoundMinimum)
{
    const auto logic = R"(
		{
			"missing_some": [5, ["a.x", "a.y", "a.z", "b.x", "b.y", "b.z"]]
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

TEST_F(OperationDataMissingSome, OrderPreservationNonAlphabetic)
{
    const auto logic = R"(
        {
        "missing_some": [3, ["zebra", "dog", "apple", "banana", "cat"]]
        }
    )"_json;

    const auto data = R"(
        {
        "dog": 4,
        "apple": 1
        }
    )"_json;

    const auto result = json_logic_->Apply(logic, data);

    std::vector<std::string> expected_result{"zebra", "banana", "cat"};
    EXPECT_EQ(result, expected_result);
}

TEST_F(OperationDataMissingSome, OrderPreservationReversedKeys)
{
    const auto logic = R"(
        {
        "missing_some": [3, ["z", "y", "x", "w", "v"]]
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
