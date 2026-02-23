#include <iostream>

#include "gtest/gtest.h"
#include "nlohmann/json.hpp"

#include "fixture.h"

using namespace nlohmann;

class OperationNumericMax : public JsonLogicTest
{
};

TEST_F(OperationNumericMax, Primitive)
{
    const auto logic = R"(
        {
            "max": [4, -3, 5, 12, -2, 8]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_EQ(result, 12);
}

TEST_F(OperationNumericMax, MixedTypesCasted)
{
    const auto logic = R"(
        {
            "max": [4, -3, 5, "12", -2, []]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_EQ(result, 12);
}

TEST_F(OperationNumericMax, Nested)
{
    const auto logic = R"(
        {
            "max": [
                4,
                -3,
                { "max": [5, -8, 9, 14, -99] },
                12,
                -2,
                8
            ]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_EQ(result, 14);
}

TEST_F(OperationNumericMax, NestedOperands)
{
    const auto logic = R"(
        {
            "max": [
                4,
                -3,
                { "max": [5, -8, 9, 14, -99] },
                { "var": ["data.foo"] },
                12,
                -2,
                8
            ]
        }
    )"_json;

    const auto data = R"(
        {
            "data": {
                "foo": 42
            }
        }
    )"_json;

    const auto result = json_logic_->Apply(logic, data);

    EXPECT_EQ(result, 42);
}

TEST_F(OperationNumericMax, StringCastToNumber)
{
    const auto logic = R"(
        {
            "max": ["5", "2", "8", "1"]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_EQ(result, 8);
}
