#include "aprovacao.hpp"

void AprovacaoViews::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response){
    if (request.getMethod() == Poco::Net::HTTPServerRequest::HTTP_POST){
        Post(request, response);
    }
    else if (request.getMethod() == Poco::Net::HTTPServerRequest::HTTP_GET){
        Get(response);
    } else{
        response.setStatus(Poco::Net::HTTPServerResponse::HTTP_NOT_IMPLEMENTED);
        response.send();
    }
}


void AprovacaoViews::Post(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response){
    std::string body;
    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(request.stream());
    Poco::JSON::Object::Ptr object = result.extract<Poco::JSON::Object::Ptr>();
}

void AprovacaoViews::Get(Poco::Net::HTTPServerResponse& response){

}