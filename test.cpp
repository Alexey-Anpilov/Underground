#include<iostream>
#include<cassert>
#include"station.h"
#include"line.h"
#include"change_station.h"

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
/*
        --Borovitskaya
       |      | 2       
     1 |  Polyanka      
       |      | 4       
        --Chehovskaya 
*/

    Station st1(1, 12, "Borovitskaya");
    Line line(&st1);
    assert(line.GetSt(1) == st1);  //добавление первой станции конструктором

    Station st2(2, 15, "Polyanka");
    line.AddStation(&st2, 2);    
    assert(line.GetSt(2) == st2);  //добавление станции к начальной
   
    Station st3(3, 10, "Chehovskaya");
    line.AddStation(&st3, 4);
    assert(line.FindLeftNeighbor(3).first == st2 && line.FindLeftNeighbor(3).second == 4);    //добавление станции в корректное место и работа Line::FindLeftNeighbor
    assert(line.FindRightNeighbor(2).first == st3 && line.FindRightNeighbor(2).second == 4);  //работа Line::FindRightNeighbor

    assert(line.MinTime(1, 3) == 6);                       
    assert(line.MinTime(1, 3) == line.MinTime(3, 1));

    line.MakeCircle(1);
    assert(line.FindLeftNeighbor(1).first == st3 && line.FindRightNeighbor(3).first == st1);    //проверка создания круговой линии
    assert(line.MinTime(2, 3) == 3);    //корректность работы минимального времени на кольцевой линии
    assert(line.MinTime(1, 2) == 2);

/*
        -----Borovitskaya
     3 |          | 2       
   Prazhskaya  Polyanka      
     1 |          | 4       
        -----Chehovskaya
*/
    
    Station st4(4, 20, "Prazhskaya");
    line.AddStation(&st4, 1, 3);
    assert(line.FindLeftNeighbor(1).first == st4);
    assert(line.MinTime(1, 4) == 3);
    assert(line.MinTime(2, 4) == 5);


    Station st5(2, 10, "Tulskaya");         //добавление станции в произвольное место
    line.AddStation(&st5, 1, 2);
    st2.SetStNum(3);
    assert(line.FindRightNeighbor(2).first == st2 && line.FindLeftNeighbor(2).first == st1);

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
