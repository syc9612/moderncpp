#include <iostream>
#include <cmath>

class platonic_solid{
    private:
    int line;

    public:
    double volume(int line);
    double surface_area(int line);
};

double platonic_solid::volume(int line){
    if(line == 4){
        return (sqrt(3) * pow(line,3)) / 12 ;
    }
    return 0;
}
double platonic_solid::surface_area(int line){
    return 0;
}