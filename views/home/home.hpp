#ifndef HOME_HPP
#define HOME_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/JSON/Object.h"
#include "../../session/sessao.hpp"
#include "../../middleware/cookie.hpp"


using namespace Poco;
using namespace Poco::Net;
using namespace Poco::JSON;


class HomeClassBase {
public:
    virtual void render(HTTPServerResponse& response) = 0;
    virtual ~HomeClassBase() {}
};


class HomeClass : public HomeClassBase {
public:
    void render(HTTPServerResponse& response) override;
    HomeClass(Session& sess) : session(sess) {};
private:
    Session& session;
};

#endif // HOME_HPP
