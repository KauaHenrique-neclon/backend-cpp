#ifndef REMOVER_PRODUTO_HPP
#define REMOVER_PRODUTO_HPP

#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <iostream>
#include <string>
#include <Poco/StreamCopier.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Object.h>
#include "../../../model/estoque/estoqueModel.hpp"
#include "../../../middleware/cookie.hpp"


class RemoverProdutoViews{
    public:
        void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
        //RemoverProdutoViews();
    
    private:
        //Session& sessao;
        //Cookie& cookieMiddleware;
        void Get(Poco::Net::HTTPServerResponse& response);
        void Post(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
};



#endif // REMOVER_PRODUTO_HPP