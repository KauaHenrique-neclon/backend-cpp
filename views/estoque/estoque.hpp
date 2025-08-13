#ifndef ESTOQUE_HPP
#define ESTOQUE_HPP


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
#include "../../model/estoque/estoqueModel.hpp"
#include "../../middleware/cookie.hpp"
#include "../../../middleware/cookie.hpp"


class EstoqueViews{
public:
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
    EstoqueViews(Session& sess, Cookie& cook) : sessao(sess), cookieMiddleware(cook) {};

private:
    Session& sessao;
    Cookie& cookieMiddleware;
    void Get(Poco::Net::HTTPServerResponse& response);
};

#endif // ESTOQUE_HPP