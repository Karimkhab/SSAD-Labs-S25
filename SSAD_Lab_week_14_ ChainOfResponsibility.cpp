#include <iostream>
#include <string>

using namespace std;

// TODO: Create Handler interface with setNext() and handle() methods
class Handler {
public:
    virtual ~Handler() {}
    virtual Handler* setNext(Handler*) = 0;
    virtual bool handle(string) = 0;
    // TODO: Add pure virtual methods for setNext() and handle()
};

class AbstractHandler : public Handler {
private:
    Handler* nextHandler = nullptr;
public:
    Handler* setNext(Handler* nextHand) override {
        this->nextHandler = nextHand;
        return nextHand;
    }

    bool handle(string request) override {
        if (nextHandler) {
            return nextHandler->handle(request);
        }
        return false;
    }
};

class AuthenticationHandler : public AbstractHandler {
public:
    bool handle(string request) override {
        if (request != "valid") {
            cout << "Authentication failed.\n";
            return false;
        }
        cout << "Authentication passed.\n";
        return AbstractHandler::handle(request);
    }
};

class RoleCheckHandler : public AbstractHandler {
public:
    bool handle(string request) override {
        if (request == "admin") {
            cout << "Role check: Admin privileges granted.\n";
            return true;
        }
        cout << "Role check: Standard user.\n";
        return AbstractHandler::handle(request);
    }
};

void processRequest(const string& request, Handler* handler) {
    cout << "Processing: " << request << endl;
    if (!handler->handle(request)) {
        cout << "Request denied.\n" << endl;
    } else {
        cout << "Request approved.\n" << endl;
    }
}

int main() {
    Handler* roleCheck = new RoleCheckHandler();
    Handler* auth = new AuthenticationHandler();

    auth->setNext(roleCheck);

    processRequest("valid", auth);
    processRequest("invalid", auth);
    processRequest("admin", auth);

    delete auth;
    delete roleCheck;

    return 0;
}
