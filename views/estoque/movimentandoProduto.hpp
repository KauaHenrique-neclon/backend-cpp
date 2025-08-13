#ifndef REMOVER_PRODUTO_HPP
#define REMOVER_PRODUTO_HPP

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
#include "../../session/sessao.hpp"


class RemoverProduto{
public:
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
    //RemoverProduto(Session& sess) : sessao(sess) {};
private:
    Session& sessao;
    void Post(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
    void Get(Poco::Net::HTTPServerResponse& response);
};



#endif // REMOVER_PRODUTO_HPP