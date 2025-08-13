#ifndef CONTROLE_PONTO_HPP
#define CONTROLE_PONTO_HPP

#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <string>
#include <Poco/StreamCopier.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Object.h>
#include "../../../model/empresa/modelPonto/modelPonto.hpp"
#include "../../../session/sessao.hpp"
#include "../../../middleware/cookie.hpp"


class ControleDePontoViews{
public:
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
    ControleDePontoViews(Session& sess, Cookie& cook) : sessao_(sess), cookie_(cook) {};

private:
    Session& sessao_;
    Cookie& cookie_;
    void Post(Poco::Net::HTTPServerRequest& resquest, Poco::Net::HTTPServerResponse& response);
};



#endif // CONTROLE_PONTO_HPP