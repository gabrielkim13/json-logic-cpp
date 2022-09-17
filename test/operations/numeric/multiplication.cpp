#include <iostream>

#include "gtest/gtest.h"
#include "nlohmann/json.hpp"

#include "fixture.h"

using namespace nlohmann;

class OperationNumericMultiplication : public JsonLogicTest
{
};

TEST_F(OperationNumericMultiplication, Primitive2Operands)
{
    const auto logic = R"(
        {
            "*": [4, 2]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_EQ(result, 8);
}

TEST_F(OperationNumericMultiplication, PrimitiveManyOperands)
{
    const auto logic = R"(
        {
            "*": [2, 2, 2, 2, 2]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_EQ(result, 32);
}

TEST_F(OperationNumericMultiplication, Variable2Operands)
{
    const auto logic = R"(
        {
            "*": [
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

    EXPECT_EQ(result, 8);
}

TEST_F(OperationNumericMultiplication, VariableManyOperands)
{
    const auto logic = R"(
        {
            "*": [
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

    EXPECT_EQ(result, 24);
}
