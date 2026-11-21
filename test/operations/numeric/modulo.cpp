#include <cmath>
#include <iostream>

#include "gtest/gtest.h"
#include "nlohmann/json.hpp"

#include "fixture.h"

using namespace nlohmann;

class OperationNumericModulo : public JsonLogicTest
{
};

TEST_F(OperationNumericModulo, Primitive2Operands)
{
    const auto logic = R"(
        {
            "%": [42, 9]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_EQ(result, 6);
}

TEST_F(OperationNumericModulo, Variable2Operands)
{
    const auto logic = R"(
        {
            "%": [
                { "var": ["data.foo"] },
                { "var": ["data.bar"] }
            ]
        }
    )"_json;

    const auto data = R"(
        {
            "data": {
                "foo": 42,
                "bar": 9
            }
        }
    )"_json;

    const auto result = json_logic_->Apply(logic, data);

    EXPECT_EQ(result, 6);
}

TEST_F(OperationNumericModulo, StringCastToNumber)
{
    const auto logic = R"(
        {
            "%": ["17", "5"]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_EQ(result, 2);
}

TEST_F(OperationNumericModulo, DecimalOperands)
{
    EXPECT_EQ(json_logic_->Apply(R"({ "%": [7, 0.5] })"_json), 0);
    EXPECT_EQ(json_logic_->Apply(R"({ "%": [7.5, 2] })"_json), 1.5);
    EXPECT_EQ(json_logic_->Apply(R"({ "%": [5.5, 2.5] })"_json), 0.5);
}

TEST_F(OperationNumericModulo, NegativeOperands)
{
    EXPECT_EQ(json_logic_->Apply(R"({ "%": [-7, 3] })"_json), -1);
    EXPECT_EQ(json_logic_->Apply(R"({ "%": [7, -3] })"_json), 1);
}

TEST_F(OperationNumericModulo, ZeroDivisorIsNaN)
{
    const auto result = json_logic_->Apply(R"({ "%": [7, 0] })"_json);

    ASSERT_TRUE(result.is_number_float());
    EXPECT_TRUE(std::isnan(result.get<double>()));
}
