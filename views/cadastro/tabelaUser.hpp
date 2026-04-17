#ifndef TABELAUSER_HPP
#define TABELAUSER_HPP




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
#include "../../session/sessao.hpp"
#include "../../model/cadastrar/cadastrarModel.hpp"




class TabelaUserView {
public: 
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
    TabelaUserView(Session& sess) : sessao(sess) {};

private:
    Session& sessao;
    void Get(Poco::Net::HTTPServerResponse& response);
};




#endif // TABELAUSER_HPP