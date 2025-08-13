#ifndef FORNECEDORES_HPP
#define FORNECEDORES_HPP

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

class FornecedoresViews{
public:
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
    FornecedoresViews(Session& sess, Cookie& cook) : sessao(sess), cookieMiddleware(cook) {};

private:
    Session& sessao;
    Cookie& cookieMiddleware;
    void Post(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
    void Get(Poco::Net::HTTPServerResponse& response);
};



#endif // FORNECEDORES_HPP