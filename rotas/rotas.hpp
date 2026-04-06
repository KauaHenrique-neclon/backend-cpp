#pragma once
#include <unordered_map>
#include <string>
#include <functional>
#include <Poco/Net/HTTPRequestHandler.h>

using RouteMap = std::unordered_map<std::string, std::function<Poco::Net::HTTPRequestHandler*()>>;