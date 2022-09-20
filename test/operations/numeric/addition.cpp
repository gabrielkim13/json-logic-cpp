#include <iostream>

#include "gtest/gtest.h"
#include "nlohmann/json.hpp"

#include "fixture.h"

using namespace nlohmann;

class OperationNumericAddition : public JsonLogicTest
{
};

TEST_F(OperationNumericAddition, Primitive2Operands)
{
    const auto logic = R"(
        {
            "+": [4, 2]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_EQ(result, 6);
}

TEST_F(OperationNumericAddition, PrimitiveManyOperands)
{
    const auto logic = R"(
        {
            "+": [2, 2, 2, 2, 2]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_EQ(result, 10);
}

TEST_F(OperationNumericAddition, PrimitiveNumberCastToNumber)
{
    const auto logic = R"(
        {
            "+": 42
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_EQ(result, 42);
}

TEST_F(OperationNumericAddition, PrimitiveBooleanFalseCastToNumber)
{
    const auto logic = R"(
        {
            "+": false
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_EQ(result, 0);
}

TEST_F(OperationNumericAddition, PrimitiveBooleanTrueCastToNumber)
{
    const auto logic = R"(
        {
            "+": true
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_EQ(result, 1);
}

TEST_F(OperationNumericAddition, PrimitiveArrayEmptyCastToNumber)
{
    const auto logic = R"(
        {
            "+": [[]]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_EQ(result, 0);
}

TEST_F(OperationNumericAddition, PrimitiveArrayNotEmptyCastToNumber)
{
    const auto logic = R"(
        {
            "+": [[42]]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_EQ(result, 1);
}

TEST_F(OperationNumericAddition, PrimitiveStringCastToNumber)
{
    const auto logic = R"(
        {
            "+": "42"
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_EQ(result, 42);
}

TEST_F(OperationNumericAddition, Variable2Operands)
{
    const auto logic = R"(
        {
            "+": [
                { "var": ["data.foo"] },
                { "var": ["data.bar"] }
            ]
        }
    )"_json;

    const auto data = R"(
        {
            "data": {
                "foo": 4,
                "bar": 2
            }
        }
    )"_json;

    const auto result = json_logic_->Apply(logic, data);

    EXPECT_EQ(result, 6);
}

TEST_F(OperationNumericAddition, VariableManyOperands)
{
    const auto logic = R"(
        {
            "+": [
                { "var": ["data.foo"] },
                { "var": ["data.bar"] },
                { "var": ["data.baz"] }
            ]
        }
    )"_json;

    const auto data = R"(
        {
            "data": {
                "foo": 2,
                "bar": 3,
                "baz": 4
            }
        }
    )"_json;

    const auto result = json_logic_->Apply(logic, data);

    EXPECT_EQ(result, 9);
}

TEST_F(OperationNumericAddition, VariableStringCastToNumber)
{
    const auto logic = R"(
        {
            "+": { "var": ["data.foo"] }
        }
    )"_json;

    const auto data = R"(
        {
            "data": {
                "foo": "42"
            }
        }
    )"_json;

    const auto result = json_logic_->Apply(logic, data);

    EXPECT_EQ(result, 42);
}
