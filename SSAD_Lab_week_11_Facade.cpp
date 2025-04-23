#include<iostream>

using namespace std;

class Lights{
private:
    bool turnOn;
public:
    Lights(): turnOn(false) {}
    Lights(bool t): turnOn(t) {}

    void on(){
        if (turnOn){
            cout<<"Lights turned on already.\n";
            return;
        }
        turnOn = true;
        cout<<"Lights turn on...\n";
    }

    void off(){
        if (!turnOn){
            cout<<"Lights turned off already.\n";
            return;
        }
        turnOn = false;
        cout<<"Lights turn off...\n";
    }
};
class Thermostat{
private:
    int temperature;
public:
    Thermostat(): temperature(10) {}
    Thermostat(int t): temperature(t) {}

    void setTemperature(int temperature){
        this->temperature = temperature;
        cout<<"Temperature of thermostat: "<<this->temperature <<" degrees\n";
    }
};
class SecurityCameras{
private:
    bool activated;
public:
    SecurityCameras(): activated(false){}
    SecurityCameras(bool a): activated(a){}

    void activate() {
        if (this->activated){
            cout<<"Security is already activate.\n";
            return;
        }
        this->activated = true;
        cout<<"Security is activate.\n";
    }
    void deactivate(){
        if (!this->activated){
            cout<<"Security is already deactivate.\n";
            return;
        }
        this->activated = true;
        cout<<"Security is deactivate...\n";
    }
};

class AliceSmartHome{
private:
    string userName;
    Lights lights;
    Thermostat thermostat;
    SecurityCameras cameras;
public:
    AliceSmartHome(string name):userName(name){}

    void leavingFromHome(){
        cout<<"Hello "<<userName<<"!\n";
        lights.on();
        thermostat.setTemperature(23);
        cameras.deactivate();
    }
    void arrivingFromHome(){
        cout<<"Good lack in your travel "<<userName<<"!\n";
        lights.off();
        thermostat.setTemperature(20);
        cameras.activate();
    }
};

int main(){
    AliceSmartHome aliceForKarim("Karim");
    aliceForKarim.arrivingFromHome();
    aliceForKarim.leavingFromHome();
}
