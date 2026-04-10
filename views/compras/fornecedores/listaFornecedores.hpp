#ifndef LISTA_FORNECEDORES_HPP
#define LISTA_FORNECEDORES_HPP

// includes
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
#include <Poco/RegularExpression.h>
#include "../../../session/sessao.hpp"
#include "../../../middleware/cookie.hpp"
#include "../../../model/estoque/estoqueModel.hpp"



class ListaFornecedoresViews{
    public:
        void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
        // construtor
        ListaFornecedoresViews(Session& sess, Cookie& cook) : sessao(sess), cookieMiddleware(cook) {};
    private:
        Session& sessao;
        Cookie& cookieMiddleware;
        void Get(Poco::Net::HTTPServerResponse& response);
};



#endif // LISTA_FORNECEDORES_HPP