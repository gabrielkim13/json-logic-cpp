#include "gtest/gtest.h"

#include "json.hpp"

#include "fixture.h"

using namespace nlohmann;

class OperationDataVar : public JsonLogicTest
{
};

TEST_F(OperationDataVar, SimpleMemberAccessNumber)
{
    const auto logic = R"(
		{
			"var": ["foo"]
		}
	)"_json;

    const auto data = R"(
		{
			"foo": 42
		}
	)"_json;

    const auto result = json_logic_->Apply(logic, data);

    EXPECT_EQ(result, 42);
}

TEST_F(OperationDataVar, SimpleMemberAccessString)
{
    const auto logic = R"(
		{
			"var": ["foo"]
		}
	)"_json;

    const auto data = R"(
		{
			"foo": "bar"
		}
	)"_json;

    const auto result = json_logic_->Apply(logic, data);

    EXPECT_EQ(result, "bar");
}

TEST_F(OperationDataVar, SimpleMemberAccessObject)
{
    const auto logic = R"(
		{
			"var": ["foo"]
		}
	)"_json;

    const auto data = R"(
		{
			"foo": {
				"key": "value"
			}
		}
	)"_json;

    const auto result = json_logic_->Apply(logic, data);

    EXPECT_EQ(result.at("key"), "value");
}

TEST_F(OperationDataVar, SimpleMemberAccessArray)
{
    const auto logic = R"(
		{
			"var": ["foo"]
		}
	)"_json;

    const auto data = R"(
		{
			"foo": [1, 2, 3]
		}
	)"_json;

    const auto result = json_logic_->Apply(logic, data);

    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 2);
    EXPECT_EQ(result[2], 3);
}

TEST_F(OperationDataVar, SimpleMemberAccessNestedOperationOrTrue)
{
    const auto logic = R"(
		{
			"or": [
				{ "var": ["foo"] },
				{ "var": ["bar"] }
			]
		}
	)"_json;

    const auto data = R"(
		{
			"foo": true,
			"bar": false
		}
	)"_json;

    const auto result = json_logic_->Apply(logic, data);

    EXPECT_TRUE(result);
}

TEST_F(OperationDataVar, SimpleMemberAccessNestedOperationOrFalse)
{
    const auto logic = R"(
		{
			"or": [
				{ "var": ["foo"] },
				{ "var": ["bar"] }
			]
		}
	)"_json;

    const auto data = R"(
		{
			"foo": false,
			"bar": false
		}
	)"_json;

    const auto result = json_logic_->Apply(logic, data);

    EXPECT_FALSE(result);
}

TEST_F(OperationDataVar, NestedMemberAccessObject)
{
    const auto logic = R"(
		{
			"var": ["foo.bar.baz"]
		}
	)"_json;

    const auto data = R"(
		{
			"foo": {
				"bar": {
					"baz": 42
				}
			}
		}
	)"_json;

    const auto result = json_logic_->Apply(logic, data);

    EXPECT_EQ(result, 42);
}

TEST_F(OperationDataVar, NestedMemberAccessArray)
{
    const auto logic = R"(
		{
			"var": ["foo.1.bar.baz"]
		}
	)"_json;

    const auto data = R"(
		{
			"foo": [
				{ "bar": { "baz": 1 } },
				{ "bar": { "baz": 2 } },
				{ "bar": { "baz": 3 } }
			]
		}
	)"_json;

    const auto result = json_logic_->Apply(logic, data);

    EXPECT_EQ(result, 2);
}

TEST_F(OperationDataVar, ThrowExceptionWhenMemberNotFound)
{
    const auto logic = R"(
		{
			"var": ["foo.1.xyz"]
		}
	)"_json;

    const auto data = R"(
		{
			"foo": [
				{ "bar": 1 },
				{ "bar": 2 },
				{ "bar": 3 }
			]
		}
	)"_json;

    EXPECT_THROW({ json_logic_->Apply(logic, data); }, JsonLogicException);
}

TEST_F(OperationDataVar, ThrowExceptionWhenArrayIndexNotFound)
{
    const auto logic = R"(
		{
			"var": ["foo.3.bar"]
		}
	)"_json;

    const auto data = R"(
		{
			"foo": [
				{ "bar": 1 },
				{ "bar": 2 },
				{ "bar": 3 }
			]
		}
	)"_json;

    EXPECT_THROW({ json_logic_->Apply(logic, data); }, JsonLogicException);
}

TEST_F(OperationDataVar, DefaultValueWhenMemberNotFound)
{
    const auto logic = R"(
		{
			"var": ["foo.1.xyz", 42]
		}
	)"_json;

    const auto data = R"(
		{
			"foo": [
				{ "bar": 1 },
				{ "bar": 2 },
				{ "bar": 3 }
			]
		}
	)"_json;

    const auto result = json_logic_->Apply(logic, data);

    EXPECT_EQ(result, 42);
}

TEST_F(OperationDataVar, DefaultValueWhenArrayIndexNotFound)
{
    const auto logic = R"(
		{
			"var": ["foo.3.bar", 42]
		}
	)"_json;

    const auto data = R"(
		{
			"foo": [
				{ "bar": 1 },
				{ "bar": 2 },
				{ "bar": 3 }
			]
		}
	)"_json;

    const auto result = json_logic_->Apply(logic, data);

    EXPECT_EQ(result, 42);
}
