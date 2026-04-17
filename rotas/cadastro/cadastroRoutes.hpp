#include <Poco/Net/HTTPRequestHandler.h>
#include "../../middleware/cookie.hpp"
#include <unordered_map>
#include <functional>
#include <Poco/Net/HTTPRequestHandler.h>

// importanto views
#include "../../views/cadastro/cadastrar.hpp"
#include "../../views/cadastro/tabelaUser.hpp"

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

        /*if (!sessao.IsAuthenticated()) {            
        response.setStatus(Poco::Net::HTTPServerResponse::HTTP_UNAUTHORIZED);
        response.send() << "A sessão não está ativa.";
        return;
        }*/

        CadastrarView cadastrarView(sessao);
        cadastrarView.handleRequest(request, response);
    }
};


class ListaUserPage : public HTTPRequestHandler{
public:
    void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) override{
        Session sessao;
        Cookie cookie(sessao);

        /*if (!sessao.IsAuthenticated()) {            
        response.setStatus(Poco::Net::HTTPServerResponse::HTTP_UNAUTHORIZED);
        response.send() << "A sessão não está ativa.";
        return;
        }*/

        TabelaUserView tabelaUserView(sessao);
        tabelaUserView.handleRequest(request, response);
    }
};




using RouteMap = std::unordered_map<std::string, std::function<Poco::Net::HTTPRequestHandler*()>>;

inline void registerCadastroRoutes(RouteMap& routes) {
    routes["/cadastrar"] = []() -> HTTPRequestHandler* {
        return new CadastrarPage();
    };
    routes["/tabelaUser"] = []() -> HTTPRequestHandler* {
        return new ListaUserPage();
    };
}
