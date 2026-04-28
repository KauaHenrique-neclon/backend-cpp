#ifndef DADOS_HOME_HPP
#define DADOS_HOME_HPP


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
#include "../../middleware/cookie.hpp"
#include "../../model/dados/modelDados.hpp"


class DadosHomeViews{
    public:
        void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
        DadosHomeViews(Session& sess, Cookie& cook) : sessao(sess), cookieMiddleware(cook) {};
    
    private:
        Session& sessao;
        Cookie& cookieMiddleware;
        void Get(Poco::Net::HTTPServerResponse& response);
};



#endif // DADOS_HOME_HPP