#ifndef CADASTRAR_HPP
#define CADASTRAR_HPP

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
#include "../../model/cadastrar/cadastrarModel.hpp"



class CadastrarView {
public:
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
    CadastrarView(Session& sess) : sessao(sess) {};

private:
    Session& sessao;
    void Post(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
    void Get(Poco::Net::HTTPServerResponse& response);
};


#endif // CADASTRAR_HPP