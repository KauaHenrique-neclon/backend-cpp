#ifndef CADASTRAR_FUNC_HPP
#define CADASTRAR_FUNC_HPP


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
#include "../../../model/empresa/cadastrarFunc/cadastrarFunc.hpp"
#include "../../../middleware/cookie.hpp"


class CadastrarFuncionarioViews{
public:
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
    CadastrarFuncionarioViews(Session& sess, Cookie& cook) : sessao(sess), cookieMiddleware(cook) {};
private:
    Session& sessao;
    Cookie& cookieMiddleware;
    void Get(Poco::Net::HTTPServerResponse& response);
    void Post(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
};


#endif // CADASTRAR_FUNC_HPP