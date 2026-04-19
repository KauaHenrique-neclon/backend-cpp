#ifndef APROVAR_PEDIDO_HPP
#define APROVAR_PEDIDO_HPP


#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <Poco/StreamCopier.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Object.h>
#include <Poco/RegularExpression.h>
#include "../../../session/sessao.hpp"
#include "../../../middleware/cookie.hpp"
#include "../../../model/compras/comprasModel.hpp"

class AprovarPedidoViews {
    public:
        void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
        AprovarPedidoViews(Session& sess, Cookie& cook) : sessao(sess), cookieMiddleware(cook)  {};
    
    private:
        Session& sessao;
        Cookie& cookieMiddleware;
        void Get(Poco::Net::HTTPServerResponse& response);
        void Post(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
};


#endif  // APROVAR_PEDIDO_HPP