#include <Poco/Net/HTTPRequestHandler.h>
#include "../../middleware/cookie.hpp"
#include <unordered_map>
#include <functional>
#include <Poco/Net/HTTPRequestHandler.h>

// importanto views
#include "../../views/cadastro/cadastrar.hpp"

// importando cookies
#include "session/sessao.hpp"
#include "middleware/cookie.hpp"


using namespace Poco;
using namespace Poco::Net;



class CadastrarPage : public HTTPRequestHandler{
public:
    void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) override{
        Session sessao;
        Cookie cookie(sessao);
    }
};



using RouteMap = std::unordered_map<std::string, std::function<Poco::Net::HTTPRequestHandler*()>>;

inline void registerCadastroRoutes(RouteMap& routes) {
    routes["/cadastrar"] = []() -> HTTPRequestHandler* {
        return new CadastrarPage();
    };
}
