#include <iostream>
#include <vector>

class solver{
    private:
    matrix_type A;

    public:
    solver(int nrows, int ncols){ // 오류1: 존재하지 않는 기본 생성자를 호출함
        A(nrows. ncols); // 오류2: 생성자 호출이 아님. 왜냐하면 생성자 호출이 아닌 함수 로출이 된다. 이를 컴파일러가 A.operator(){nrows, ncols} 로 해석함.
    }

    /*
    정상 표현.
    solver(int nrows, int ncols) : A{nrwos, ncols} {}
    */
};

class vector{
    private:
    vector(const vector& v): my_size{v.my_size}, data{new double[my_size]}{
        for( unsigned i = 0; i< my_size; ++i){
            data[i] = v.data[i]; 
        }
    }
    ~vector() { delete[] data; }
    
    public:
    unsigned my_size;
    
    double *data; //unique_ptr<double[]> data;
    /*
    유니크 포인터를 사용하게 되면 ~vector 소멸자 사용안해도 되며, data[new double[my_size]] 또한 선언할필요가 없어질것으로 보인다.
    
    */
};