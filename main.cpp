#include <iostream>
#include <vector>

int main() {
    // 1
    std::vector<int> vec = {4, 7, 2};
    try { std::cout << vec.at(5); }
    catch(std::out_of_range& exc) { std::cout << exc.what() << std::endl; }

    try { vec.reserve(vec.max_size() + 10); }
    catch (std::length_error& exc) { std::cout << exc.what() << std::endl; }

    try { std::stoi("abc123"); }
    catch (std::invalid_argument& exc) { std::cout << exc.what() << std::endl; }

    struct A {
        virtual void foo() = 0;
    };

    struct B : A {
        void foo() override {};
    };

    struct C : A {
        void foo() override {};
    };

    B b;
    A& a = b;
    try {  C& c = dynamic_cast<C&>(a); }
    catch (std::bad_cast &exc) {  std::cout << exc.what() << std::endl; }

    try { int* arr = new int[100000000000000000]; }
    catch(std::bad_alloc& exc){ std::cout << exc.what() << std::endl; }


    // 2
    class MyException : public std::invalid_argument {
    public:
        MyException(const char* msg) : std::invalid_argument(msg) {}
    };

    class Car {
        int _speed;
    public:
        Car(int s) : _speed(s) {
            if(s < 0 || s > 400) { //Если скорость меньше нуля или больше 400, выбрасывается исключение
                throw MyException("wrong speed");
            }
        };
    };

    try { Car c(450); }
    catch (MyException& exc) { std::cout << exc.what() << std::endl; }

    // 3
    // Код с утечкой памяти:
    {
        class Data {
            int* _data;
        public:
            Data(int n) { _data = new int[n]; }
        };

        {
            Data d(5);
        } // Здесь происходит утечка памяти при выходе объекта d из области видимости
    }

    // Эквивалентный код без утечек памяти
    {
        class Data {
            int* _data;
        public:
            Data(int n) { _data = new int[n]; }
            ~Data() { delete[] _data; }
        };

        {
            Data d(5);
        } // Здесь вызывается деструктор, который очищает динамичесски выделенную память и утечки не происходит
    }
}