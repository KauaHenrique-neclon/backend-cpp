#ifndef SESSION_HPP
#define SESSION_HPP

#include <string>
#include <unordered_map>
#include "../model/login/loginModel.hpp"

class Session {
public:
    Session();
    
    bool Login(const std::string& username, const std::string& password);
    
    void Logout();
    
    bool IsAuthenticated() const;

    bool AccessPage(const std::string& page);
    const Usuario& getUsuario() const { return usuario; }

private:
    bool authenticated;
    Usuario usuario;
    LoginModel* loginModel;
};

#endif // SESSION_HPP
