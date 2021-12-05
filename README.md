# json-logic-cpp

This parser accepts [JsonLogic](http://jsonlogic.com) rules and executes them in C++ programs.

The JsonLogic format is designed to allow you to share rules (logic) between front-end and back-end code (regardless of language difference), even to store logic along with a record in a database.  JsonLogic is documented extensively at [JsonLogic.com](http://jsonlogic.com), including examples of every [supported operation](http://jsonlogic.com/operations.html) and a place to [try out rules in your browser](http://jsonlogic.com/play.html).

The same format can also be executed in JavaScript by the library [json-logic-js](https://github.com/jwadhams/json-logic-js/)

## Examples

### A note about types

This C++ port of JsonLogic makes heavy use of [Niels Lohmann's JSON library](https://github.com/nlohmann/json), such that each and every JSON value, be it a `number`, `string`, `boolean`, `object` or `array`, is treated as the unique type `nlohmann::json`.

In that sense, all operations and the main `IJsonLogic::Apply` method all have the same signature:

```c++
#include "json.hpp" // https://github.com/nlohmann/json

using namespace nlohmann;

json Apply(const json& logic, const json& data);
```

From the previous description and the method signature above, each argument, as well as the method's return type, can be any C++ type (typically `int`, `double`, `std::string`, `std::map` and `std::vector`) and its the caller's responsibility to assert that the values being passed to and received from the `IJsonLogic::Apply` call are the expected types, which can be done by using `nlohmann/json`'s convenience type checker methods.

```c++
// convenience type checkers
json j;

j.is_null();
j.is_boolean();
j.is_number();
j.is_object();
j.is_array();
j.is_string();
```

### Simple

> This is the first example with actual C++ code that can be compiled and run and, as such, it contains `include` statements, the `main` function, etc. For the sake of brevity, some of these "boilerplate" lines of code will be omitted from the next examples.

```c++
#include <iostream>

#include "json_logic.h"

using namespace JsonLogic;

int main()
{
    const IJsonLogic* json_logic = JsonLogic::GetInstance();

    const json logic = R"(
        {
            "==": [1, 1]
        }
    )"_json;

    const json result = json_logic->Apply(logic);

    std::cout << std::boolalpha;
    std::cout << result << std::endl; // true

    return 0;
}
```

This is a simple test, equivalent to `1 == 1`.  A few things about the format:

  1. The operator is always in the "key" position. There is only one key per JsonLogic rule.
  2. The values are typically an array.
  3. Each value can be a string, number, boolean, array, or null

### Compound

Here we're beginning to nest rules.

```c++
const json logic = R"(
    {
        "and": [
            { ">": [3, 1] },
            { "<": [1, 3] }
        ]
    }
)"_json;

json_logic->Apply(logic); // true
```

Which is equivalent to the C++ statement:

```c++
((3 > 1) && (1 < 3));
```

### Data-Driven

Obviously these rules aren't very interesting if they can only take static literal data. Typically `JsonLogic::Apply` will be called with a rule object and a data object. You can use the `var` operator to get attributes of the data object:

```c++
const json logic = R"(
    {
        "var": ["a"]
    }
)"_json;

const json data = R"(
    {
        "a": 1,
        "b": 2
    }
)"_json;

json_logic->Apply(logic, data); // 1
```

If you like, we support [syntactic sugar](https://en.wikipedia.org/wiki/Syntactic_sugar) on unary operators to skip the array around values:

```json
{
    "var": "a"
}
```

You can also use the `var` operator to access an array by numeric index:

```c++
const json logic = R"(
    {
        "var": 1
    }
)"_json;

const json data = R"(
    [
        "apple",
        "banana",
        "carrot"
    ]
)"_json;

json_logic->Apply(logic, data); // "banana"
```

Here's a complex rule that mixes literals and data. The pie isn't ready to eat unless it's cooler than 110 degrees, *and* filled with apples.

```c++
const json logic = R"(
    {
        "and": [
            { "<": [{ "var": "temp" }, 110] },
            { "==": [{ "var": "pie.filling" }, "apple"] }
        ]
    }
)"_json;

const json data = R"(
    {
        "temp": 100,
        "pie": {
            "filling": "apple"
        }
    }
)"_json;

json_logic->Apply(logic, data); // true
```

### Always and Never

Sometimes the rule you want to process is "Always" or "Never".  If the first parameter passed to `JsonLogic::Apply` is a non-object, non-associative-array, it is returned immediately.

```c++
const json data = R"(
    {
        "will_this_be_ignored": true
    }
)"_json;

// Always
json_logic->Apply(true, data); // true

// Never
json_logic->Apply(false, data); // false
```

## Installation

The best way to use this library on your C++ application is via [CMake](https://cmake.org/):

```cmake
cmake_minimum_required(VERSION 3.18)
project(my-app VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# Assuming that json-logic-cpp was added under the lib directory
include_directories(lib/json-logic-cpp/src)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(
        ${PROJECT_NAME}

        jsonlogic
)

add_subdirectory(lib/json-logic-cpp)
```
