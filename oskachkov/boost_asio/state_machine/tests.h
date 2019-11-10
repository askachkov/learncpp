1)
#include <iostream>
#include <string>

struct s_t
{
    uint8_t x;
    uint32_t y;
};

int main()
{
    std::cout << sizeof(s_t)<< "\n";
}

2)
int8_t x;
…
void intr(){
    x=0;
}
void main(){
    x=1;
    while(x);
}

3)
#include <iostream>
#include <thread>

int32_t x=0;
void increment()
{
    auto i=1000;
    while(i--){
        x++;
    }
}

void decrement()
{
    auto i=1000;
    while(i--){
        x--;
    }
}

int main() {
    auto t0=std::thread(increment);
    auto t1=std::thread(decrement);
     //Join the thread with the main thread
    t0.join();
    t1.join();
    std::cout << x<< "\n";

    return 0;
}

4)
#include <iostream>

void revert_str(char *str){
}

int main() {
    char *str="12345";
    std::cout << str<<std::endl;
    revert_str(str);
    std::cout << str<<std::endl;

    return 0;
}

5)
#include <iostream>
// bit settet to 1 in byte
int8_t bit_calculate(uint8_t x){

}

int main()
{
    std::cout << bit_calculate(10)<<std::endl;
    return 0;
}


6)?
uint16_t *sqr(uint16_t d)
{
    uint16_t nm= d*d;
    return &nm;
}

int main()
{
    uint16_t *x=sqr(3);
    uint16_t y=*sqr(5);
    std::cout <<" x= " << *x  <<" y= " << y<< "\n";
}

-----------------
7) linked list add
8) linked list sort

9)// sort array

void sort(const char* arr){

}

int main()
{
    char aa[]={1,4,56,7,8};
    sort(aa);
    return 0;
}

10)
//copy 0-3 bit from change to 5-7 inout

void combine(uint8_t *inout, uint8_t change){

}

int main(){
    uint8_t aa;
    combine(&aa,12);
    return 0;
}

11)
//Reverse string

char * string = "Hello";

void reverseStr(char * inOut)
{

}
