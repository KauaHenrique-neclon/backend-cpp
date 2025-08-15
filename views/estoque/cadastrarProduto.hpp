#ifndef CADASTRAR_PRODUTO_HPP
#define CADASTRAR_PRODUTO_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include "Poco/StreamCopier.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/JSON/Object.h"
#include <Poco/Net/HTTPResponse.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Object.h>
#include "../../model/estoque/estoqueModel.hpp"
#include "../../middleware/cookie.hpp"


class CadastrarProdutoView {
public:
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
    CadastrarProdutoView(Session& sess, Cookie& cook) : sessao(sess), cookieMiddleware(cook) {};

private:
    Session& sessao;
    Cookie& cookieMiddleware;
    void Post(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
};

#endif // CADASTRAR_PRODUTO_HPP