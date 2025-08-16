#ifndef ORCAMENTO_HPP
#define ORCAMENTO_HPP

#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <string>
#include <Poco/StreamCopier.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Object.h>
#include "../../model/empresa/financas/financasModel.hpp"
#include "../../../session/sessao.hpp"
#include "../../../middleware/cookie.hpp"

class OrcamentoViews{
public:
   void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
   OrcamentoViews();
private:
    void Get(Poco::Net::HTTPServerResponse& response);
    void Post(Poco::Net::HTTPServerRequest& resquet, Poco::Net::HTTPServerResponse& response);
};


#endif // ORCAMENTO_HPP