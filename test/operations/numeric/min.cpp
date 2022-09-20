#include <iostream>

#include "gtest/gtest.h"
#include "nlohmann/json.hpp"

#include "fixture.h"

using namespace nlohmann;

class OperationNumericMin : public JsonLogicTest
{
};

TEST_F(OperationNumericMin, Primitive)
{
    const auto logic = R"(
        {
            "min": [4, -3, 5, 12, -2, 8]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_EQ(result, -3);
}

TEST_F(OperationNumericMin, IgnoreNonNumbers)
{
    const auto logic = R"(
        {
            "min": [4, -3, 5, "12", -2, {}]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_EQ(result, -3);
}

TEST_F(OperationNumericMin, Nested)
{
    const auto logic = R"(
        {
            "min": [
                4,
                -3,
                { "min": [5, -8, 9, 14, -99] },
                12,
                -2,
                8
            ]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_EQ(result, -99);
}

TEST_F(OperationNumericMin, NestedOperands)
{
    const auto logic = R"(
        {
            "min": [
                4,
                -3,
                { "min": [5, -8, 9, 14, -99] },
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
                "foo": -420
            }
        }
    )"_json;

    const auto result = json_logic_->Apply(logic, data);

    EXPECT_EQ(result, -420);
}
