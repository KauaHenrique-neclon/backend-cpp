#ifndef PEDIDOS_HPP
#define PEDIDOS_HPP

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
#include "../../../model/estoque/estoqueModel.hpp"
#include <Poco/RegularExpression.h>
#include "../../../session/sessao.hpp"

class PedidosViews {
public:
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
    PedidosViews(Session& sess) : sessao(sess) {};

private:
    Session& sessao;
    void Post(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
    void Get(Poco::Net::HTTPServerResponse& response);
};


#endif // PEDIDOS_HPP