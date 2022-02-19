#include<iostream>
#include"station.h"
#include<cassert>
#include"line.h"

void TestStation(){
    // создание станции
    {
        Station st(1, 12, "Novodachnaya");   
        assert(st.GetNum() == 1);
        assert(st.GetStream() == 12);
        assert(st.GetName() == "Novodachnaya");
    }

    // изменение пассажиропотока
    {
        Station st(1, 12, "Novodachnaya");
        st.ChangePassStream(20);
        assert(st.GetStream() == 20);

    }

    // сравнение станций операторами < и ==
    {
        Station st1(1, 12, "c"), st2(2, 1, "a");     //рядовой случай
        assert(st1 < st2);
        assert(!(st1 == st2));

        Station st3(2, 2, "b");    // а вдруг сравнивает не по номеру     
        assert(!(st2 < st3)); 
        assert(st2 == st3);
        
    }
}

void TestLine(){
    Station st1(1,10,"Bor");
    Station st2(2, 20, "Cher");
    Travel t(st1, st2, 3);
    std::vector<Travel> l1 = {t};
    Station st3(3, 15, "D");
    Station st4(4, 40, "R");
    Line line(l1);
    line.AddStation(st3, 5);
    line.AddStation(st4, 6);
    std::cout << line.FindMinTime("Bor", "R") << std::endl; 
    std::cout << line.FindMinTime("R", "Bor") << std::endl; 
    std::cout << line.FindMinTime("Cher", "D") << std::endl; 
    std::cout << line.FindMinTime("D", "Cher") << std::endl; 
    std::cout << line.FindMinTime("Cher", "R") << std::endl; 
    std::cout << line.FindMinTime("R", "Cher") << std::endl;
}
int main() {
    TestStation();
    TestLine();
}