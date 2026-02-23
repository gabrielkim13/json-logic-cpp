#include <iostream>

#include "gtest/gtest.h"
#include "nlohmann/json.hpp"

#include "fixture.h"

using namespace nlohmann;

class OperationNumericLte : public JsonLogicTest
{
};

TEST_F(OperationNumericLte, PrimitiveLtTrue)
{
    const auto logic = R"(
        {
            "<=": [1, 2]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_TRUE(result);
}

TEST_F(OperationNumericLte, PrimitiveEqualTrue)
{
    const auto logic = R"(
        {
            "<=": [2, 2]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_TRUE(result);
}

TEST_F(OperationNumericLte, PrimitiveFalse)
{
    const auto logic = R"(
        {
            "<=": [2, 1]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_FALSE(result);
}

TEST_F(OperationNumericLte, PrimitiveBetweenTrue1)
{
    const auto logic = R"(
        {
            "<=": [1, 2, 3]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_TRUE(result);
}

TEST_F(OperationNumericLte, PrimitiveBetweenTrue2)
{
    const auto logic = R"(
        {
            "<=": [1, 1, 3]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_TRUE(result);
}

TEST_F(OperationNumericLte, PrimitiveBetweenTrue3)
{
    const auto logic = R"(
        {
            "<=": [1, 3, 3]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_TRUE(result);
}

TEST_F(OperationNumericLte, PrimitiveBetweenFalse1)
{
    const auto logic = R"(
        {
            "<=": [1, 0, 3]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_FALSE(result);
}

TEST_F(OperationNumericLte, PrimitiveBetweenFalse2)
{
    const auto logic = R"(
        {
            "<=": [1, 4, 3]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_FALSE(result);
}

TEST_F(OperationNumericLte, VariablesLtTrue)
{
    const auto logic = R"(
        {
            "<=": [
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

TEST_F(OperationNumericLte, VariablesEqualTrue)
{
    const auto logic = R"(
        {
            "<=": [
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

TEST_F(OperationNumericLte, VariablesFalse)
{
    const auto logic = R"(
        {
            "<=": [
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

TEST_F(OperationNumericLte, VariablesBetweenTrue1)
{
    const auto logic = R"(
        {
            "<=": [
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

TEST_F(OperationNumericLte, VariablesBetweenTrue2)
{
    const auto logic = R"(
        {
            "<=": [
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

    EXPECT_TRUE(result);
}

TEST_F(OperationNumericLte, VariablesBetweenTrue3)
{
    const auto logic = R"(
        {
            "<=": [
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

    EXPECT_TRUE(result);
}

TEST_F(OperationNumericLte, VariablesBetweenFalse1)
{
    const auto logic = R"(
        {
            "<=": [
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
                "bar": 0,
                "baz": 3
            }
        }
    )"_json;

    const auto result = json_logic_->Apply(logic, data);

    EXPECT_FALSE(result);
}

TEST_F(OperationNumericLte, VariablesBetweenFalse2)
{
    const auto logic = R"(
        {
            "<=": [
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
                "bar": 4,
                "baz": 3
            }
        }
    )"_json;

    const auto result = json_logic_->Apply(logic, data);

    EXPECT_FALSE(result);
}

TEST_F(OperationNumericLte, StringCastToNumber)
{
    const auto logic = R"(
        {
            "<=": ["5", "10"]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_TRUE(result);
}
