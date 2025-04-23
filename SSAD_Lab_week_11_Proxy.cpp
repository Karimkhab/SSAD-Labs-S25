#include<iostream>

using namespace std;

class Document{
public:
    virtual void display() = 0;
};

class RealDocument: public Document{
private:
    string password;
    string fileAddres;
public:
//    RealDocument(): fileAddres(""){}
    RealDocument(string password, string fileAddres): password(password), fileAddres(fileAddres){}
    void display(){
        cout<<"Read file: "<<fileAddres<<" ...:\n";
        cout<<"   File display.\n";
    }

    string &getPassword(){
        return password;
    }
};

class SecureDocumentProxy: public Document{
private:
    string password;
    RealDocument document;
public:
    SecureDocumentProxy(RealDocument document): document(document){}
    SecureDocumentProxy(RealDocument document, string password): document(document), password(password){}
    bool checkAccess(){
        return this->password == document.getPassword();
    }

    void setPassword(const string &password) {
        SecureDocumentProxy::password = password;
    }

    void display(){
        if (this->password.empty()){
            cout<<"Please write password.\n";
            return;
        }
        if (checkAccess()){
            document.display();
            return;
        }
        cout<<"File cannot be display: Use correct password\n";
    }
};


int main(){
//    RealDocument realDocument("12345Ui","reals_doc.txt");
    SecureDocumentProxy doc(RealDocument("12345Ui","reals_doc.txt"));
    doc.display();
    doc.setPassword("Wrong password");
    doc.display();
    doc.setPassword("12345Ui");
    doc.display();
}
