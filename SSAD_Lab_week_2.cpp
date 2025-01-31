// Karim Khabibrakhmanov DSAI - 05
#include <iostream>
 using namespace std;

class Box{
private:
    unsigned int length;
    unsigned int width;
    unsigned int height;
public:
    Box(){
        this->length = 0;
        this->width = 0;
        this->height = 0;
    }
    Box(const Box& other){
        this->length = other.length;
        this->width = other.width;
        this->height = other.height;
    }
    Box(unsigned length,unsigned width,unsigned height){
        this->length = length;
        this->width = width;
        this->height = height;
    }

    Box& operator=(const Box& b) {
        if (this != &b) {
            this->length = b.length;
            this->width = b.width;
            this->height = b.height;
        }
        return *this;
    }

    unsigned int getVolume() const {
        return length*width*height;
    }
    void scale(unsigned scaleValue){
        this->length = this->length*scaleValue;
        this->width = this->width*scaleValue;
        this->height = this->height*scaleValue;
    }
    bool isBigger(const Box& other){
        return getVolume() > other.getVolume();
    }
    bool isSmaller(const Box& other){
        return getVolume() < other.getVolume();
    }
    Box operator*(unsigned int scaleValue) const {
        return Box(length * scaleValue,width * scaleValue,height * scaleValue);
    }
    bool operator==(const Box& other) const {
        return getVolume()==other.getVolume();
    }
};

class Cube{
private:
    unsigned int sideSize;
public:
    Cube(){
        this->sideSize=0;
    }
    Cube(unsigned int sideSize){
        this->sideSize=sideSize;
    }
    Cube(const Cube& other){
        this->sideSize = other.sideSize;
    }
    unsigned int getVolume() const {
        return sideSize*sideSize*sideSize;
    }

    operator Box() const {
        return Box(sideSize, sideSize, sideSize);
    }
};

int main(){
    Box A(3,4,5);
    Box B(1,2,3);
    Cube C(3);
    int scale = 2;
    cout << "Volume of A before * by "<< scale <<": "<<A.getVolume()<<" || ";
    A = A *scale;
    cout << "Volume of A after * by "<< scale <<": "<<A.getVolume()<<"\n";
    cout << "A equals to B?: "<< boolalpha << (A==B) <<endl;
    Box Temp = C;
    cout << "Box Temp become cube C: "<< Temp.getVolume();
}
