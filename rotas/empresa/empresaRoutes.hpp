#include <Poco/Net/HTTPRequestHandler.h>
#include "../../middleware/cookie.hpp"
#include <unordered_map>
#include <functional>
#include <Poco/Net/HTTPRequestHandler.h>

// importanto views


// importando cookies
#include "session/sessao.hpp"
#include "middleware/cookie.hpp"


using namespace Poco;
using namespace Poco::Net;

using RouteMap = std::unordered_map<std::string, std::function<Poco::Net::HTTPRequestHandler*()>>;

inline void registerEmpresaRoutes(RouteMap& routes) {

}