#include <Poco/Net/HTTPRequestHandler.h>
#include "../../middleware/cookie.hpp"
#include <unordered_map>
#include <functional>
#include <Poco/Net/HTTPRequestHandler.h>


// importando cookies
#include "session/sessao.hpp"
#include "middleware/cookie.hpp"


// importando Views
#include "../../views/home/dadosHome.hpp"


using namespace Poco;
using namespace Poco::Net;


class HomeViewsPage : public HTTPRequestHandler {
    public:
        void handleRequest(HTTPServerRequest &request, HTTPServerResponse &response){
            try{
                Session sessao;
                Cookie cookie(sessao);
                /*if (!sessao.IsAuthenticated()) {
                    response.setStatus(HTTPServerResponse::HTTP_UNAUTHORIZED);
                    response.send() << "A sessão não está ativa.";
                    return;
                }*/
                DadosHomeViews dadosHomeViews(sessao, cookie);
                dadosHomeViews.handleRequest(request, response);
            }catch(std::exception& e){
                response.setStatus(HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
                response.send() << "Erro interno do servidor.";
            }
        }
};


using RouteMap = std::unordered_map<std::string, std::function<Poco::Net::HTTPRequestHandler *()>>;

inline void registerHomeRoutes(RouteMap &routes)
{ 
    routes["/home"] = []() -> HTTPRequestHandler * {
        return new HomeViewsPage();
    };
};