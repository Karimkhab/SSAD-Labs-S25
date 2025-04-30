#include <string>
#include <vector>
#include <iostream>

using namespace std;

// Forward declaration
class SmartHouseMediator;

class Device {
public:
    virtual void sendMessage(const string& message) = 0;
    virtual void receiveMessage(const string& message) = 0;
    // Associate this device with a mediator
    virtual void setMediator(SmartHouseMediator* mediator) = 0;
    virtual ~Device() = default;
};

class SmartHouseMediator {
private:
    vector<Device*> devices;
public:

    void addDevice(Device* device) {
        devices.push_back(device);
    }

    void mediate(Device* sender, const string& message) {
        for (Device* device: devices){
            if (device!=sender){
                device->receiveMessage(message);
            }
        }
    }

};

class MotionSensor : public Device {
private:
    SmartHouseMediator* mediator = nullptr;
public:
    void sendMessage(const string& message) override {
        cout << "Notification - Motion Sensor: " << message << "\n";
        if (mediator) {
            mediator->mediate(this, message);
        }
    }

    void receiveMessage(const string& message) override {
        cout << "MotionSensor received a " << message
             << ", the owner will be notified that they expect a visitor\n";
    }

    void setMediator(SmartHouseMediator* med) override {
        this->mediator = med;
        cout<<"Smart house mediator set for Motion Sensor!\n";
    }
};

class TemperatureSensor : public Device {
private:
    SmartHouseMediator* mediator = nullptr;
public:

    void sendMessage(const string& message) override {
        cout << "Notification - Temperature Sensor: " << message << "\n";
        if (mediator) {
            mediator->mediate(this, message);
        }
    }

    void receiveMessage(const string& message) override {
        cout << "TemperatureSensor received a " << message
             << ", the room temperature will be adjusted\n";
    }

    void setMediator(SmartHouseMediator* med) override {
        this->mediator = med;
        cout<<"Smart house mediator set for Temperature Sensor!\n";
    }
};


int main() {
    SmartHouseMediator* mediator = new SmartHouseMediator();
    MotionSensor* motion = new MotionSensor();
    TemperatureSensor* temp = new TemperatureSensor();

    motion->setMediator(mediator);

    temp->setMediator(mediator);

    cout<<"\n";

    // register devices with the mediator
    // TODO: mediator.addDevice(&motion);
    // TODO: mediator.addDevice(&temp);
    mediator->addDevice(motion);
    mediator->addDevice(temp);

    mediator->mediate(motion, "Motion device start working!\n");
    cout<<"\n";
    mediator->mediate(temp, "Temperature device start working!\n");
    cout<<"\n";

    // simulate an event
    motion->sendMessage("Motion detected");

    return 0;
}
