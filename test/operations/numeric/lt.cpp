#include <iostream>

#include "gtest/gtest.h"
#include "nlohmann/json.hpp"

#include "fixture.h"

using namespace nlohmann;

class OperationNumericLt : public JsonLogicTest
{
};

TEST_F(OperationNumericLt, PrimitiveLtTrue)
{
    const auto logic = R"(
        {
            "<": [1, 2]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_TRUE(result);
}

TEST_F(OperationNumericLt, PrimitiveEqualFalse)
{
    const auto logic = R"(
        {
            "<": [2, 2]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_FALSE(result);
}

TEST_F(OperationNumericLt, PrimitiveFalse)
{
    const auto logic = R"(
        {
            "<": [2, 1]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_FALSE(result);
}

TEST_F(OperationNumericLt, PrimitiveBetweenTrue)
{
    const auto logic = R"(
        {
            "<": [1, 2, 3]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_TRUE(result);
}

TEST_F(OperationNumericLt, PrimitiveBetweenFalse1)
{
    const auto logic = R"(
        {
            "<": [1, 1, 3]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_FALSE(result);
}

TEST_F(OperationNumericLt, PrimitiveBetweenFalse2)
{
    const auto logic = R"(
        {
            "<": [1, 3, 3]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_FALSE(result);
}

TEST_F(OperationNumericLt, VariablesLtTrue)
{
    const auto logic = R"(
        {
            "<": [
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

    EXPECT_TRUE(result);
}

TEST_F(OperationNumericLt, VariablesEqualFalse)
{
    const auto logic = R"(
        {
            "<": [
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

    EXPECT_FALSE(result);
}

TEST_F(OperationNumericLt, VariablesFalse)
{
    const auto logic = R"(
        {
            "<": [
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

    EXPECT_FALSE(result);
}

TEST_F(OperationNumericLt, VariablesBetweenTrue)
{
    const auto logic = R"(
        {
            "<": [
                { "var": ["data.foo"] },
                { "var": ["data.bar"] },
                { "var": ["data.baz"] }
            ]
        }
    )"_json;

    const auto data = R"(
        {
            "data": {
                "foo": 1,
                "bar": 2,
                "baz": 3
            }
        }
    )"_json;

    const auto result = json_logic_->Apply(logic, data);

    EXPECT_TRUE(result);
}

TEST_F(OperationNumericLt, VariablesBetweenFalse1)
{
    const auto logic = R"(
        {
            "<": [
                { "var": ["data.foo"] },
                { "var": ["data.bar"] },
                { "var": ["data.baz"] }
            ]
        }
    )"_json;

    const auto data = R"(
        {
            "data": {
                "foo": 1,
                "bar": 1,
                "baz": 3
            }
        }
    )"_json;

    const auto result = json_logic_->Apply(logic, data);

    EXPECT_FALSE(result);
}

TEST_F(OperationNumericLt, VariablesBetweenFalse2)
{
    const auto logic = R"(
        {
            "<": [
                { "var": ["data.foo"] },
                { "var": ["data.bar"] },
                { "var": ["data.baz"] }
            ]
        }
    )"_json;

    const auto data = R"(
        {
            "data": {
                "foo": 1,
                "bar": 3,
                "baz": 3
            }
        }
    )"_json;

    const auto result = json_logic_->Apply(logic, data);

    EXPECT_FALSE(result);
}

TEST_F(OperationNumericLt, StringCastToNumber)
{
    const auto logic = R"(
        {
            "<": ["5", "10"]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_TRUE(result);
}
