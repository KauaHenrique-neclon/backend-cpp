#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPResponse.h>

class CORSHandler : public Poco::Net::HTTPRequestHandler {
public:
    CORSHandler(Poco::Net::HTTPRequestHandler* next) : _next(next) {}
    ~CORSHandler() { delete _next; }

    void handleRequest(Poco::Net::HTTPServerRequest& request,
                       Poco::Net::HTTPServerResponse& response) override {

        response.set("Access-Control-Allow-Origin", "*");
        response.set("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        response.set("Access-Control-Allow-Headers", "Content-Type");

        if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_OPTIONS) {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
            response.send();
            return;
        }

        _next->handleRequest(request, response);
    }

private:
    Poco::Net::HTTPRequestHandler* _next;
};