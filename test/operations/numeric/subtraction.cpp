#include <iostream>

#include "gtest/gtest.h"
#include "nlohmann/json.hpp"

#include "fixture.h"

using namespace nlohmann;

class OperationNumericSubtraction : public JsonLogicTest
{
};

TEST_F(OperationNumericSubtraction, Primitive2Operands)
{
    const auto logic = R"(
        {
            "-": [4, 2]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_EQ(result, 2);
}

TEST_F(OperationNumericSubtraction, PrimitiveNumberToNegative)
{
    const auto logic = R"(
        {
            "-": 42
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_EQ(result, -42);
}

TEST_F(OperationNumericSubtraction, Variable2Operands)
{
    const auto logic = R"(
        {
            "-": [
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

    EXPECT_EQ(result, 2);
}

TEST_F(OperationNumericSubtraction, VariableNumberToNegative)
{
    const auto logic = R"(
        {
            "-": { "var": ["data.foo"] }
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

    EXPECT_EQ(result, -42);
}
