#include <iostream>
#include <vector>

using namespace std;

class Animal {
protected:
    string name;
    int age;
public:
    Animal(string name, int age) : name(name), age(age) {}

    virtual void makeSound() = 0;

    void setName(const string &name) {
        this->name = name;
    }

    void setAge(int age) {
        this->age = age;
    }

    const string &getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    virtual ~Animal() {}
};

class LandAnimal : virtual public Animal {
public:
    LandAnimal(string name, int age) : Animal(name, age) {}

    void makeSound() override {
        cout << "I am a land animal!" << endl;
    }

    void walk() {
        cout << getName() << " walks!" << endl;
    }
};

class WaterAnimal : virtual public Animal {
public:
    WaterAnimal(string name, int age) : Animal(name, age) {}

    void makeSound() override {
        cout << "I am a water animal!" << endl;
    }

    void swim() {
        cout << getName() << " swims!" << endl;
    }
};

class Lion : public LandAnimal {
public:
    Lion(string name, int age) : Animal(name, age), LandAnimal(name, age) {}

    void makeSound() override {
        cout << "I am " << getName() << " and I am a land animal!\n"
             << "Arhhhh!" << endl;
    }

    void walk() {
        cout << "My name is " << getName() << " and I am a lion, which can walk!" << endl;
    }
};

class Dolphin : public WaterAnimal {
public:
    Dolphin(string name, int age) : Animal(name, age), WaterAnimal(name, age) {}

    void makeSound() override {
        cout << "I am " << getName() << " and I am a water animal!\n"
             << "Buuulp!" << endl;
    }

    void swim() {
        cout << "My name is " << getName() << " and I am a dolphin, which can swim!" << endl;
    }
};

class Frog : public LandAnimal, public WaterAnimal {
public:
    Frog(string name, int age) : Animal(name, age), LandAnimal(name, age), WaterAnimal(name, age) {}

    void makeSound() override {
        cout << "I am " << getName() << " and I am an amphibian!\n"
             << "Qwaaa!" << endl;
    }

    void walk() {
        cout << "My name is " << getName() << " and I am a frog, which can walk!" << endl;
    }

    void swim() {
        cout << "My name is " << getName() << " and I am a frog, which can swim!" << endl;
    }
};

int main() {
    vector<Animal *> zoo;
    zoo.push_back(new Lion("Leo", 5));
    zoo.push_back(new Dolphin("Dove", 10));
    zoo.push_back(new Frog("Frank", 2));

    cout << "First animal:\n";
    int check = 1;
    for (Animal *animal : zoo) {
        if (check !=1){
            cout<< "\nNext animal:\n";
        }
        check = 0;
        animal->makeSound();
        if (LandAnimal *landAnimal = dynamic_cast<LandAnimal *>(animal)) {
            landAnimal->walk();
        }
        if (WaterAnimal *waterAnimal = dynamic_cast<WaterAnimal *>(animal)) {
            waterAnimal->swim();
        }
    }

    for (Animal *animal : zoo) {
        delete animal;
    }

    return 0;
}
