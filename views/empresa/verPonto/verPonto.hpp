#ifndef VER_PONTO_HPP
#define VER_PONTO_HPP

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <string>
#include <Poco/StreamCopier.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Object.h>
#include "../../model/empresa/modelPonto/modelPonto.hpp"
#include "../../../session/sessao.hpp"
#include "../../../middleware/cookie.hpp"

class VerPontoViews{
public:
    void handleResquest(Poco::Net::HTTPServerRequest& resquet, Poco::Net::HTTPServerResponse& response);
    VerPontoViews();
private:
    void Get(Poco::Net::HTTPServerResponse& response);
    void Post(Poco::Net::HTTPServerRequest& resquet, Poco::Net::HTTPServerResponse& response);
};


#endif // VER_PONTO_HPP