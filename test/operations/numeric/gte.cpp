#include <iostream>

#include "gtest/gtest.h"
#include "json.hpp"

#include "fixture.h"

using namespace nlohmann;

class OperationNumericGte : public JsonLogicTest
{
};

TEST_F(OperationNumericGte, PrimitiveGtTrue)
{
    const auto logic = R"(
        {
            ">=": [2, 1]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_TRUE(result);
}
TEST_F(OperationNumericGte, PrimitiveEqualTrue)
{
    const auto logic = R"(
        {
            ">=": [2, 2]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_TRUE(result);
}

TEST_F(OperationNumericGte, PrimitiveFalse)
{
    const auto logic = R"(
        {
            ">=": [1, 2]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_FALSE(result);
}

TEST_F(OperationNumericGte, VariablesGtTrue)
{
    const auto logic = R"(
        {
            ">=": [
                { "var": ["data.foo"] },
                { "var": ["data.bar"] }
            ]
        }
    )"_json;

    const auto data = R"(
        {
            "data": {
                "foo": 2,
                "bar": 1
            }
        }
    )"_json;

    const auto result = json_logic_->Apply(logic, data);

    EXPECT_TRUE(result);
}

TEST_F(OperationNumericGte, VariablesEqualTrue)
{
    const auto logic = R"(
        {
            ">=": [
                { "var": ["data.foo"] },
                { "var": ["data.bar"] }
            ]
        }
    )"_json;

    const auto data = R"(
        {
            "data": {
                "foo": 2,
                "bar": 2
            }
        }
    )"_json;

    const auto result = json_logic_->Apply(logic, data);

    EXPECT_TRUE(result);
}

TEST_F(OperationNumericGte, VariablesFalse)
{
    const auto logic = R"(
        {
            ">=": [
                { "var": ["data.foo"] },
                { "var": ["data.bar"] }
            ]
        }
    )"_json;

    const auto data = R"(
        {
            "data": {
                "foo": 1,
                "bar": 2
            }
        }
    )"_json;

    const auto result = json_logic_->Apply(logic, data);

    EXPECT_FALSE(result);
}
