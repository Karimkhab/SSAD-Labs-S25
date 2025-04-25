#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>

using namespace std;

class File {
public:
    string path;
    File(const string& filePath) : path(filePath) {}
};

class EventListener {
public:
    virtual ~EventListener() = default;
    virtual void update(const string& eventType, const File& file) = 0;
};

class EventManager {
private:
    map<string, vector<shared_ptr<EventListener>>> listeners;

public:
    EventManager(const vector<string>& operations) {
        for (size_t i = 0; i < operations.size(); ++i) {
            const string& operation = operations[i];
            listeners[operation] = vector<shared_ptr<EventListener>>();
        }
    }

    void subscribe(const string& eventType, shared_ptr<EventListener> listener) {
        map<string, vector<shared_ptr<EventListener>>>::iterator it = listeners.find(eventType);
        if (it != listeners.end()) {
            it->second.push_back(listener);
        }
    }

    void unsubscribe(const string& eventType, shared_ptr<EventListener> listener) {
        map<string, vector<shared_ptr<EventListener>>>::iterator it = listeners.find(eventType);
        if (it != listeners.end()) {
            vector<shared_ptr<EventListener>>& listenersVector = it->second;
            listenersVector.erase(
                    remove(listenersVector.begin(), listenersVector.end(), listener),
                    listenersVector.end()
            );
        }
    }

    void notify(const string& eventType, const File& file) {
        map<string, vector<shared_ptr<EventListener>>>::iterator it = listeners.find(eventType);
        if (it != listeners.end()) {
            for (size_t i = 0; i < it->second.size(); ++i) {
                shared_ptr<EventListener> listener = it->second[i];
                listener->update(eventType, file);
            }
        }
    }
};

class Editor {
public:
    unique_ptr<EventManager> events;
    unique_ptr<File> file;

    Editor() {
        vector<string> operations;
        operations.push_back("open");
        operations.push_back("save");
        events.reset(new EventManager(operations));
    }

    void openFile(const string& filePath) {
        file.reset(new File(filePath));
        events->notify("open", *file);
    }

    void saveFile() {
        if (!file) {
            cerr << "No file is open!" << "\n";
            return;
        }
        cout << "Saving file: " << file->path << "\n";
        events->notify("save", *file);
    }
};

class LoggingListener : public EventListener {
private:
    string name;
public:
    LoggingListener(const string& listenerName) : name(listenerName) {}
    void update(const string& eventType, const File& file) override {
        cout << "Logging Notification for: " << name << ";\n"
             << "Event type: " << eventType << ";\n"
             << "File path: " << file.path << ";\n" << "\n";
    }
};

class EmailNotificationListener : public EventListener {
private:
    string name;
public:
    EmailNotificationListener(const string& listenerName) : name(listenerName) {}
    void update(const string& eventType, const File& file) override {
        if (eventType == "save") {
            cout << "Email Notification for: " << name << ";\n"
                 << "Event type: " << eventType << ";\n"
                 << "File path: " << file.path << ";\n" << "\n";
        }
    }
};

int main() {
    Editor editor;

    shared_ptr<EventListener> logger(new LoggingListener("System Logger"));
    shared_ptr<EventListener> emailAlerts(new EmailNotificationListener("Admin Email"));

    editor.events->subscribe("open", logger);
    editor.events->subscribe("save", logger);
    editor.events->subscribe("save", emailAlerts);

    cout << "Opening file test.txt...\n";
    editor.openFile("test.txt");

    cout << "Saving file test.txt...\n";
    editor.saveFile();

    editor.events->unsubscribe("save", logger);

    cout << "Saving again after unsubscribing logger from save events...\n";
    editor.saveFile();

    return 0;
}
