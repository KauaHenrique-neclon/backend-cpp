#ifndef APROVACAO_HPP
#define APROVACAO_HPP

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
#include "model/cadastrar/cadastrarModel.hpp"

class AprovacaoViews {
public:
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

private:
    void Post(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
    void Get(Poco::Net::HTTPServerResponse& response);
    
};



#endif // APROVACAO_HPP