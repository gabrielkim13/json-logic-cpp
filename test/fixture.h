#ifndef JSON_LOGIC_CPP_TEST_FIXTURE_H
#define JSON_LOGIC_CPP_TEST_FIXTURE_H

#include "gtest/gtest.h"

#include "json_logic.h"

using namespace json_logic;

class JsonLogicTest : public testing::Test
{
protected:
	IJsonLogic* json_logic_;

	void SetUp() override
	{
		json_logic_ = JsonLogic::GetInstance();
	}
};

#endif //JSON_LOGIC_CPP_TEST_FIXTURE_H
