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

void TestChange(){              //тесты для пересадки(надо дополнить)
    Change ch(10, 20);
    assert(ch.GetTime() == 10 && ch.GetStream() == 20);
}

void TestChangeStation(){      //тесты для пересадочной станции
    Change ch(1, 2);
    ChangeStation st(2, 10, "Arbatskaya");
    st.AddChange(ch);          //добавление пересадки
    assert(!st.GetChanges().empty());

    Station st1(1, 6, "Ohotnii ryad");
    Line line(st1);
    line.AddStation(&st, 2);                            //добавление станции пересадки на линию
    assert(line.FindLeftNeighbor(2).first == st1 && line.FindRightNeighbor(1).first == st);
    assert(!line.GetSt(2).GetChanges().empty());
}

void TestLine(){
/*  Сначала идут тесты на прямое добавление и некольцевой линии
    Схема такая:

          Borovitskaya
             | 2       
          Polyanka      
             | 4       
          Chehovskaya 
*/

    Station st1(1, 12, "Borovitskaya");
    Line line(st1);
    assert(line.GetSt(1) == st1);  //добавление первой станции конструктором

    Station st2(2, 15, "Polyanka");
    line.AddStation(&st2, 2);    
    assert(line.GetSt(2) == st2);  //добавление станции к начальной
   

    Station st3(3, 10, "Chehovskaya");
    line.AddStation(&st3, 4);
    assert(line.FindLeftNeighbor(3).first == st2 && line.FindLeftNeighbor(3).second == 4);    //добавление станции в корректное место и работа Line::FindLeftNeighbor
    assert(line.FindRightNeighbor(2).first == st3 && line.FindRightNeighbor(2).second == 4);  //работа Line::FindRightNeighbor

    assert(line.MinTime(1, 3) == 6);                      //проверка работы метода Line::MinTime;
    assert(line.MinTime(1, 3) == line.MinTime(3, 1));     //в обе стороны должно быть одинаковое время


/*  Далее станции добавляются в произвольное место или в начало
    Схема такая:
         Chertanovskaya
             | 3
         Borovitskaya
             | 1
         Prazhskaya
             | 2       
         Polyanka      
             | 4       
         Chehovskaya 
             | 2
          Tulskaya
*/


    Station st4(2, 20, "Prazhskaya");
    line.AddStation(&st4,1, 2);
    st2.SetStNum(3);
    st3.SetStNum(4);
    assert(line.FindLeftNeighbor(2).first == st1 && line.FindRightNeighbor(2).first == st2);    //корректное добавление в произвольное место
    assert(line.MinTime(3, 1) == 3);

    Station st5(1, 5, "Chertanovskaya");                                //добавляем в начало
    line.AddStation(&st5, 0, 3);
    assert(line.FindRightNeighbor(1).first.GetName() == st1.GetName());
    assert(line.MinTime(3, 1) == 4 && line.MinTime(3, 5) == 6);

    Station st6(6, 7, "Tulskaya");                                      //проверяем, что ничего не сломалось после добавления в начало
    line.AddStation(&st6, 2);
    assert(line.FindLeftNeighbor(6).first.GetName() == "Chehovskaya" && line.MinTime(1, 6) == 12);


/*  Далее станции идет проверка cсоздания кольцевой линии
    Схема такая:
      ---Chertanovskaya
     |        | 3
     |    Borovitskaya
     |        | 1
     |    Prazhskaya
   1 |        | 2       
     |    Polyanka      
     |        | 4       
     |    Chehovskaya 
     |        | 2
     -----Tulskaya
*/

    line.MakeCircle(1);
    assert(line.FindLeftNeighbor(1).first.GetName() == "Tulskaya");    //проверка создания круговой линии
    assert(line.FindRightNeighbor(6).first.GetName() == "Chertanovskaya");
    assert(line.MinTime(4, 1) == 6 && line.MinTime(1, 4) == line.MinTime(1,4));    //корректность работы минимального времени на кольцевой линии
    assert(line.MinTime(1, 6) == 1);
    assert(line.MinTime(5, 1) == 3);



/*  Проверка добавления в разные места для кольцевой линии
    Схема такая:
       ---Chertanovskaya
     |        | 3
     |    Borovitskaya
     |        | 1
     |    Prazhskaya
   3 |        | 2       
     |    Polyanka      
     |        | 4       
     |    Chehovskaya 
     |        | 1    
     |    Serpuhovskaya
     |        | 3
     |    Tulskaya
     |        | 1
     -----Uzhnaya
     
*/

    Station st7(7, 20, "Uzhnaya"); //добавление станции в конец
    line.AddStation(&st7, 1, 3);
    assert(line.FindLeftNeighbor(1).first == st7);
    assert(line.MinTime(6, 1) == 4);
    assert(line.MinTime(1, 7) == 3);


    Station st8(6, 10, "Serpuhovskaya");         //добавление станции в произвольное место
    line.AddStation(&st8, 1, 3);
    assert(line.FindRightNeighbor(6).first.GetName() == "Tulskaya" && line.FindLeftNeighbor(6).first.GetName() == "Chehovskaya");

    Station st9(1, 6, "Timiryazevskaya");
    line.AddStation(&st9,2 ,2);
    line.PrintLine();
    
}

uint Line::st_count = 0;

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
