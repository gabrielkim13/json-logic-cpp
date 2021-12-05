#include <iostream>

#include "gtest/gtest.h"
#include "json.hpp"

#include "fixture.h"

using namespace nlohmann;

class OperationNumericDivision : public JsonLogicTest
{
};

TEST_F(OperationNumericDivision, Primitive2Operands)
{
    const auto logic = R"(
        {
            "/": [42, 2]
        }
    )"_json;

    const auto result = json_logic_->Apply(logic);

    EXPECT_EQ(result, 21);
}

TEST_F(OperationNumericDivision, Variable2Operands)
{
    const auto logic = R"(
        {
            "/": [
                { "var": ["data.foo"] },
                { "var": ["data.bar"] }
            ]
        }
    )"_json;

    const auto data = R"(
        {
            "data": {
                "foo": 42,
                "bar": 2
            }
        }
    )"_json;

    const auto result = json_logic_->Apply(logic, data);

    EXPECT_EQ(result, 21);
}
