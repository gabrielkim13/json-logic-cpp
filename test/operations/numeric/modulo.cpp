#include <iostream>

#include "gtest/gtest.h"
#include "json.hpp"

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
