#pragma once
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>

class CORSHandler : public Poco::Net::HTTPRequestHandler {
public:
    CORSHandler(Poco::Net::HTTPRequestHandler* next) : _next(next) {}

    void handleRequest(Poco::Net::HTTPServerRequest& request,
                       Poco::Net::HTTPServerResponse& response) override {

        // Aplica CORS
        response.set("Access-Control-Allow-Origin", "*");
        response.set("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        response.set("Access-Control-Allow-Headers", "Content-Type");


        if(request.getMethod() == Poco::Net::HTTPRequest::HTTP_OPTIONS) {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
            response.send();
            return;
        }


        _next->handleRequest(request, response);
    }

private:
    Poco::Net::HTTPRequestHandler* _next;
}; onde eu coloco isso? no middleware°?