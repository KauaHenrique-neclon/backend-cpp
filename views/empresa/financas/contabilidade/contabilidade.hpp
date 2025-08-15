#ifndef CONTABILIDADE_HPP
#define CONTABILIDADE_HPP


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


class ContabilidadeViews{
public:
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
    ContabilidadeViews(Session& sess, Cookie& cook) : sessao_(sess), cookie_(cook) {};
private:
    Session& sessao_;
    Cookie& cookie_;
    void Post(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
};

class ContabilidadeGetViews{
public:
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
    ContabilidadeGetViews(Session& sess, Cookie& cook) : sessao_(sess), cookie_(cook) {};
private:
    Session& sessao_;
    Cookie& cookie_;
    void Get(Poco::Net::HTTPServerResponse& response);
};


#endif // CONTABILIDADE_HPP