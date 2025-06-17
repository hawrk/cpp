#include "json_parser.h"
#include <nlohmann/json.hpp>
#include <stdexcept>

using json = nlohmann::json;

JsonParser::JsonParser() {}

json JsonParser::parse(const std::string& jsonString) {
    try {
        return json::parse(jsonString);
    } catch (const json::parse_error& e) {
        throw std::runtime_error("JSON parse error: " + std::string(e.what()));
    }
}