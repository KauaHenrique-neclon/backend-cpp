#include <Poco/Net/HTTPRequestHandler.h>
#include "../../middleware/cookie.hpp"
#include <unordered_map>
#include <functional>
#include <Poco/Net/HTTPRequestHandler.h>

// importanto views
#include "../../views/login/login.hpp"



// importando cookies
#include "session/sessao.hpp"
#include "middleware/cookie.hpp"



using namespace Poco;
using namespace Poco::Net;

class LoginPage : public HTTPRequestHandler{
public:
    void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) override{
        LoginView login;
        login.handleRequest(request, response);
    }
};



class LogoutPage : public HTTPRequestHandler {
public:
    void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) override {
        Session sessao;
        sessao.Logout();
        response.setStatus(HTTPServerResponse::HTTP_OK);
        response.setContentType("application/json");
        response.send() << R"({"message":"Logout realizado"})";
    }
};


using RouteMap = std::unordered_map<std::string, std::function<Poco::Net::HTTPRequestHandler*()>>;

inline void registerLoginRoutes(RouteMap& routes) {
    routes["/login"] = []() -> HTTPRequestHandler* {
        return new LoginPage();
    };
    routes["/logout"] = []() -> HTTPRequestHandler* {
        return new LogoutPage();
    };
}