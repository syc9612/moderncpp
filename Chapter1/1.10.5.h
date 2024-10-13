#include <cmath>
#include <iostream>

class nested_interval{
    private:
    double a,b;
    double c = (a+b)/2;
    
    double result;

    public:
    double function(double x);
    bool isValid(double a,double b);

    double solution();
};

double nested_interval::function(double x){
    return sin(x) + cos(5 * x);
}

bool nested_interval::isValid(double a, double b){
    double check = nested_interval::function(a) * nested_interval::function(b);
    return std::signbit(check);
}

double nested_interval::solution(){
    double a = 0.5;
    double b = 1.0;
    double c;

    nested_interval ni;

    if(ni.function(a) * ni.function(b) >=0 ){
        std::cerr << "re setting the range";
    }

    while(c>pow(c,-12)){
        c= (a+b)/2;

        if(ni.function(c) == 0.0){ //함수값이 0 이면 멈추고
            break;
        }

        if(std::signbit(ni.function(c)) == std::signbit(ni.function(a))){ //부호가 같으면 a = c로 초기화
            a = c;
        }
        else{
            b = c;
        }
    }

    return c;
}