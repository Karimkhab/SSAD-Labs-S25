#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class FormatType {
public:
    string font;
    int size;
    string color;

    FormatType(const string& f, int s, const string& col)
            : font(f), size(s), color(col) {}

    void print() const {
        cout << "Font: " << font << ", Size: " << size << ", Color: " << color;
    }
};

class FormatFactory {
private:
    unordered_map<string, FormatType*> formats;

public:
    FormatType* getFormat(const string& font, int size, const string& color) {
        string key = font + to_string(size) + color;
        if (formats.find(key) == formats.end()) {
            formats[key] = new FormatType(font, size, color);
        }
        return formats[key];
    }

    ~FormatFactory() {
        for (auto& pair : formats) {
            delete pair.second;
        }
    }
};

class FormattedCharacter {
private:
    char character;
    FormatType* format;

public:
    FormattedCharacter(char c, FormatType* fmt)
            : character(c), format(fmt) {}

    void print() const {
        cout << "Character: " << character << " with properties: ";
        format->print();
        cout << endl;
    }
};

int main() {
    FormatFactory factory;

    vector<FormattedCharacter> document;

    FormatType* redArial12 = factory.getFormat("Arial", 12, "Red");
    FormatType* blackTimes12 = factory.getFormat("Times New Roman", 12, "Black");
    FormatType* blueArial14 = factory.getFormat("Arial", 14, "Blue");
    FormatType* greenArial16 = factory.getFormat("Arial", 16, "Green");

    document.emplace_back('H', redArial12);
    document.emplace_back('e', redArial12);
    document.emplace_back('l', redArial12);
    document.emplace_back('l', redArial12);
    document.emplace_back('o', redArial12);

    document.emplace_back(' ', blackTimes12);

    document.emplace_back('W', blueArial14);
    document.emplace_back('o', blueArial14);
    document.emplace_back('r', blueArial14);
    document.emplace_back('l', blueArial14);
    document.emplace_back('d', blueArial14);

    document.emplace_back('!', greenArial16);

    cout << "Document content:\n";
    for (const auto& fc : document) {
        fc.print();
    }

    cout << "\nMemory Usage Analysis:\n";
    cout << "Total characters: " << document.size() << endl;
    cout << "Each character stores its own properties (font, size, color)\n";
    cout << "This is inefficient when many characters share the same formatting!\n";


    return 0;
}
