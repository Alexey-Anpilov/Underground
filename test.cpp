#include<iostream>
#include<cassert>
#include"station.h"
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
    line1.AddStation(&st1);
    Station st2(2, 15, "Polyanka");
    line1.AddStation(&st2, 2);
    Station st3(3, 10, "Chehovskaya");
    line1.AddStation(&st3, 5);
    line1.MakeCircle(1);
    Station st4(4, 15, "Nagornaya");
    line1.AddStation(&st4, 3, 1);
    std::cout << line1.MinTime(3,1) << std::endl  
              << line1.MinTime(1,2) << std::endl
              << line1.MinTime(3,2) << std::endl
              << line1.MinTime(1,3) << std::endl;
}


int main() {
    TestStation();
    TestLine();
}








/*
TEST(TestStation, BasicAbilities){
    {
        //создание станции
        Station st(1, 12, "Novodachnaya");
        EXPECT_EQ(st.GetNum(), 1) << "Station number is incorrect. Wrong performance of Station::GetNum or constructor";
        EXPECT_EQ(st.GetStream(), 12) << "Station stream is incorrect. Wrong performance of Station::GetStream or constructor";
        EXPECT_EQ(st.GetName(), "Novodachnaya") << "Station name is incorrect. Wrong performance of Station::GetName or constructor";

        //изменение пассажиропотока
        st.ChangePassStream(20);
        EXPECT_EQ(st.GetStream(), 20) <<"Wrong work of Station::ChangePassStream";
    }
    {
        //сравнение станции операторами < и ==
        Station st1(1, 12, "c"), st2(2, 1, "a");    //рядовой случай
        EXPECT_TRUE(st1 < st2);
        EXPECT_FALSE(st1 == st2);

        Station st3(2, 2, "b");    // а вдруг сравнивает не по номеру     
        EXPECT_FALSE(st2 < st3); 
        EXPECT_EQ(st2, st3);
    }
}
*/
