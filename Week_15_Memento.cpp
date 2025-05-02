#include <iostream>
#include <string>
#include <stack>

using namespace std;

// Memento: holds editor state
class Memento {
private:
    string state;
public:
    Memento(const string& state): state(state){}
    string getState() const{
        return state;
    }
};

// Originator: the text editor
class TextEditor{
private:
    string text;
public:
    TextEditor(): text(""){}
    TextEditor(const string& text): text(text){}

    void appendText(const string& newText){
        save();
        text+=newText;
    }
    string getText() const{
        return text;
    }

    // TODO: capture current state
    Memento save() const{
        return Memento(text);
    }

    // TODO: restore to a previous state
    void restore(const Memento& memento){
        text = memento.getState();
    }
};

// Caretaker: manages undo/redo stacks
class UndoRedoManager {
private:
    stack<Memento> undoStack;
    stack<Memento> redoStack;
public:
    UndoRedoManager(){}

    // TODO: push current editor state onto undo stack and clear redo
    void saveState(TextEditor& editor){
        undoStack.push(editor.save());
        while(!redoStack.empty()) {
            redoStack.pop();
        }
    }

    // TODO: pop from undo, push to redo, restore previous
    void undo(TextEditor& editor){
        if(undoStack.empty()) return;

        redoStack.push(editor.save());
        editor.restore(undoStack.top());
        undoStack.pop();
    }

    // TODO: pop from redo, push to undo, restore
    void redo(TextEditor& editor){
        if(redoStack.empty()) return;

        undoStack.push(editor.save());
        editor.restore(redoStack.top());
        redoStack.pop();
    }
};

int main() {
    TextEditor editor;
    UndoRedoManager undoRedoManager;

    // Initial text
    cout << "Initial text: " << editor.getText() << endl;

    // Append some text and save state
    editor.appendText("Hello");
    undoRedoManager.saveState(editor);
    cout << "After appending 'Hello': " << editor.getText() << endl;

    // Append more text and save state
    editor.appendText(" World");
    undoRedoManager.saveState(editor);
    cout << "After appending ' World': " << editor.getText() << endl;

    // Undo and show state
    undoRedoManager.undo(editor);
    cout << "After undoing: " << editor.getText() << endl;

    // Redo and show state
    undoRedoManager.redo(editor);
    cout << "After redoing: " << editor.getText() << endl;

    return 0;
}
