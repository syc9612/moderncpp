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

   vector(vector&& c) noexcept:my_size{v.my_size}, data{v.data}{
        v.data = nullptr;
        v.my_size = 0;
   }
   /*
클래스에서 이동 생성자와 이동 배정 연산자를 미리 정의한다면 오른값이 불필요하게 복사되는 일을 방지할 수 있다.

의미 이동론 - 얕은 복사. 이동 생성자는 원본 객체로부터 데이터를 "훔쳐온다" 의 개념이다.
원본 객체는 빈 상태가 된다. 새 메모리 블록이 할당되지 않으므로, bad_alloc 발생하지 않는다.
따라서 모든 생성자를 noexcept로 선언 가능.

오른값으로 함수에 전달된 객체는 함수가 반환되면 expire 상태. -> 이는 무결성이 보장되지 않음.  -> 따라서 객체의 파괴가 절대 실패해선 안됨.

원시포인터가 엉뚱한곳을 가르키는 일이 발생해선 안된다. 해제 실패나거나 엉뚱한 데이터를 해제해버린다.`
따라서, v.data를 nullptr로 반드시 선언. -> v가 범위를 벗어나서 소멸자 호출될때 해당 메모리가 다시 해제되는 현상 발생.
*/

};
