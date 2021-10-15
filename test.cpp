#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include <iostream>
#include <nlohmann/json-schema.hpp>
#include <nlohmann/json.hpp>
#include <sstream>

using nlohmann::json;
using nlohmann::json_schema::json_validator;

int main (){
  json j
      = {{"id", "AA"},
         {"data",
          {{{"x", 0.0}, {"values", {0, 1}}},
           {{"x", 1.0}, {"values", {1, 2}}}}}};

  json schema=R"(
{
         "properties": {
                  "data": {
                           "allOf": [
                                    {
                                             "contains": {
                                                      "properties": {
                                                               "x": {
                                                                        "maximum": 0,
                                                                        "minimum": 0
                                                               }
                                                      }
                                             }
                                    },
                                    {
                                             "contains": {
                                                      "properties": {
                                                               "x": {
                                                                        "maximum": 1,
                                                                        "minimum": 1
                                                               }
                                                      }
                                             }
                                    }
                           ],
                           "description": "Array of Interpolation Points with Initial Values",
                           "items": {
                                    "description": "Interpolation Point with Initial Values",
                                    "properties": {
                                             "values": {
                                                      "description": "Initial Values at Interpolation Point x",
                                                      "items": {
                                                               "type": "number"
                                                      },
                                                      "maxItems": 2,
                                                      "minItems": 2,
                                                      "type": "array"
                                             },
                                             "x": {
                                                      "description": "Interpolation Point",
                                                      "type": "number"
                                             }
                                    },
                                    "required": [
                                             "x",
                                             "values"
                                    ],
                                    "type": "object"
                           },
                           "maxItems": 2,
                           "minItems": 2,
                           "type": "array"
                  },
                  "id": {
                           "description": "component id",
                           "type": "string"
                  }
         },
         "required": [
                  "id",
                  "data"
         ],
         "type": "object"
}
)"_json;


  // check that the schema itself is valid:
  json_validator validator;

  try {
    validator.set_root_schema(schema);
  } catch (const std::exception &e) {
    std::cout << "Couldn't validate the data, because the schema itself is faulty: "
      << e.what() << "\n";
  }

  //validate:
  try{
    validator.validate(j);
  } catch (const std::exception &e) {
    std::cout
        << "Couldn't validate the data: "
        << e.what() << "\n";
    }
  }
