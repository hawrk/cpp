#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <string>
#include <nlohmann/json.hpp>

class JsonParser {
public:
    nlohmann::json parse(const std::string& jsonString);
};

#endif // JSON_PARSER_H