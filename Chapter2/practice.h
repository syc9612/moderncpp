#include <iostream>
#include <vector>
#include <string>

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

//이동생성자 구현
class MoveConstructor{
    private:
    std::string* data;

    public:
    // 기본 생성자
    MoveConstructor(const std::string& value){
        data = new std::string(value);
        std::cout << "call normal constructor \n";
    }

    // 이동 생성자 (noexcept 추가)
    MoveConstructor(MoveConstructor&& other) noexcept {
        data = other.data;
        other.data = nullptr;
        std::cout << "call move Constructor (noexcept) \n";
    }

    // 복사 생성자와 복사 대입 연산자를 삭제하여 이동만 가능하게 함.
    MoveConstructor(const MoveConstructor&) = delete;
    MoveConstructor& operator=(cost MoveConstructor&) = delete;

    //이동 대입 연산자 (noexcpet 추가)
    MoveConstructor& operator=(MoveConstructor&& other) noexcept{
        if(this != &other){
            delete data;
            data = ohter.data;
            other.data= nullptr;
            std::cout << "call the move into constuctor(noexcept)\n";
        }
        return *this;
    }
    ~MoveConstructor(){
        delete data;
    }
    void print() const{
        if (data){
            std::cout << "Data: " << *data << "\n";
        }
        else{
            std::cout << "No data in here\n";
        }
    }
};

/*
int main() {
    MyClass obj1("Hello");
    MyClass obj2(std::move(obj1)); // 이동 생성자 호출

    obj1.print(); // obj1의 데이터가 이동되어 nullptr이 됨
    obj2.print(); // obj2는 이동된 데이터 소유

    MyClass obj3("World");
    obj3 = std::move(obj2);        // 이동 대입 연산자 호출

    obj2.print(); // obj2의 데이터가 이동되어 nullptr이 됨
    obj3.print(); // obj3은 이동된 데이터 소유

    return 0;
}
*/

/*
2.3.5.3  복사 제거
이동 생성자자와 이동 배정 연산자에 로그를 기록하는 문장을 추가한다면, 이동 생성자가 생각만큼 자주 호출되지 않음을 알 수 있다.
-> 이는 컴파일러가 최적화 해주고 있다. =복복사제거.
복사 제거의 중요한 용도는 반환값 최적화이다.
*/
inline vector ones(int n){
    vector v(n);
    for (unsigned i=0; i<n; i++){
        v[i] = 1.0;
    }
    return v;
}
voctor w(ones(7));