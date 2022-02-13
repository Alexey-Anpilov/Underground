#include <iostream>
#include "RegularStation.h"

int main(){
    RegularStation st1(12, 1, "borovitskaya");
    RegularStation st2(13, 2, "Cherta");
    std::cout << st1.GetNum() << std::endl << st2.GetNum() << std::endl;

    if (st1 < st2){
        std::cout << "YES YES YES" << std::endl;
    }else{
        std::cout << "NO NO NO" << std::endl;
    }
}