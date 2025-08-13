
#ifndef COOKIE_HPP
#define COOKIE_HPP

#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPCookie.h>
#include <iostream>
#include <string>
#include "../session/sessao.hpp"

class Cookie {
public:
    Cookie(Session& sess) : sessao(sess) {}
    
    void cookieMiddleware(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
        if (sessao.IsAuthenticated()) {
            Poco::Net::HTTPCookie cookie("session_id", "valor");
            cookie.setPath("/");
            cookie.setSecure(true);
            cookie.setHttpOnly(true);
            response.addCookie(cookie);
        } else {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED);
            response.send() << "Acesso não autorizado";
        }
    }
private:
    Session& sessao;
};

#endif // COOKIE_HPP
