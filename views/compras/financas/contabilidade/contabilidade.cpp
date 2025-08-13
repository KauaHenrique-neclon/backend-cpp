#include "contabilidade.hpp"


void Contabilidade::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response){
    if(request.getMethod() == Poco::Net::HTTPServerRequest::HTTP_GET){
        Get(response);
    }else if(request.getMethod() == Poco::Net::HTTPServerRequest::HTTP_POST){
        Post(request, response);
    }else{
        response.setStatus(Poco::Net::HTTPServerResponse::HTTP_NOT_IMPLEMENTED);
        response.send();
    }
}

void Contabilidade::Post(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response){

}

void Contabilidade::Get(Poco::Net::HTTPServerResponse& response){

}