#ifndef GATEWAY_H
#define GATEWAY_H

#include <string>
#include <nlohmann/json.hpp>

class Gateway {
public:
    Gateway();
    nlohmann::json handleRequest(const nlohmann::json& request);
};

#endif // GATEWAY_H