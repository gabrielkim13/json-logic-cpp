#include "gtest/gtest.h"

#include "nlohmann/json.hpp"

#include "fixture.h"

using namespace nlohmann;

class OperationMiscLog : public JsonLogicTest
{
protected:
    std::streambuf *cout_rdbuf;
    std::stringstream test_rdbuf;

    void SpyCout()
    {
        cout_rdbuf = std::cout.rdbuf();
        std::cout.rdbuf(test_rdbuf.rdbuf());
    }

    void UnspyCout()
    {
        std::cout.rdbuf(cout_rdbuf);
    }
};

TEST_F(OperationMiscLog, Primitive)
{
    const auto logic = R"(
		{
			"log": "apple"
		}
	)"_json;

    SpyCout();

	const auto result = json_logic_->Apply(logic);
	const auto log = test_rdbuf.str();

    UnspyCout();

	EXPECT_EQ(result, "apple");
	EXPECT_EQ(log, "\"apple\"\n");
}

TEST_F(OperationMiscLog, Variable)
{
    const auto logic = R"(
		{
			"log": [{ "var": ["data"] }]
		}
	)"_json;

	const auto data = R"(
		{
			"data": {
				"foo": "apple"
			}
		}
	)"_json;

    SpyCout();

    const auto result = json_logic_->Apply(logic, data);
    const auto log = test_rdbuf.str();

    UnspyCout();

	const auto expected_result = json{{"foo", "apple"}};

	EXPECT_EQ(result, expected_result);
	EXPECT_EQ(log, "{\"foo\":\"apple\"}\n");
}

TEST_F(OperationMiscLog, Operation)
{
    const auto logic = R"(
		{
			"log": [
				{
					"*": [
						{ "var": ["data.foo"] },
						{ "var": ["data.bar"] }
					]
				}
			]
		}
	)"_json;

	const auto data = R"(
		{
			"data": {
				"foo": 21,
				"bar": 2
			}
		}
	)"_json;

    SpyCout();

    const auto result = json_logic_->Apply(logic, data);
    const auto log = test_rdbuf.str();

    UnspyCout();

	EXPECT_EQ(result, 42);
	EXPECT_EQ(log, "42.0\n");
}
