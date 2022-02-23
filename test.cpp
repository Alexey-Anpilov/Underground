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
    Line line1;
    Station st1(1, 12, "Borovitskaya");
    line1.AddStation(&st1, 5);
    Station st2(2, 15, "Polyanka");
    line1.AddStation(&st2, 2);
    Station st3(3, 10, "Chehovskaya");
    line1.AddStation(&st3, 3);
    line1.PrintLine();
    std::cout << line1.FindRightNeighbor(2).first.GetName() << std::endl << line1.FindRightNeighbor(2).second << std::endl;
}


int main() {
    TestStation();
    TestLine();
}