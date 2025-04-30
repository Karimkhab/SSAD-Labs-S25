#include <iostream>

using namespace std;

class RecipeTemplate{
protected:
    vector<string> ingredients;
public:
    RecipeTemplate(vector<string> ingredients): ingredients(ingredients){}
    virtual void listIngredients(){
        cout<<"List of Ingredients:\n";
        int id = 1;
        for (string ingr: ingredients){
            cout<<"  "<<id++<<") "<<ingr<<"\n";
        }
    }

    virtual void prepareRecipe() = 0;

    virtual void serve(){
        cout<<"Serve the dish!\n";
    }

    virtual void makeRecipe() final{
        prepareRecipe();
        listIngredients();
        serve();
        cout<<"\n";
    }
};

class CakeRecipe: public RecipeTemplate{
public:
    CakeRecipe(vector<string> ingredients): RecipeTemplate(ingredients){}

    void prepareRecipe() override{
        cout<<"Cake recipe is ready!\n";
    }
};

class SaladRecipe: public RecipeTemplate{
public:
    SaladRecipe(vector<string> ingredients): RecipeTemplate(ingredients){}

    void prepareRecipe() override{
        cout<<"Salad recipe is ready!\n";
    }
};



int main(){
    CakeRecipe cake({"Apple", "Flour", "Sugar", "Milk", "Strawberry"});
    SaladRecipe salad({"Cabbage", "Cucumber", "Carrot", "Salt"});

    cake.makeRecipe();
    salad.makeRecipe();
    return 0;
}
