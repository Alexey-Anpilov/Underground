#include<iostream>
#include<cassert>
#include"station.h"
#include"line.h"
#include"change_station.h"
#include"skip_list.h"
#include"underground.h"


void TestStation(){
    // создание станции
    {
        Station st(1, 12, "Novodachnaya");   
        assert(st.getNum() == 1);
        assert(st.getStream() == 12);
        assert(st.getName() == "Novodachnaya");
    }

    // изменение пассажиропотока
    {
        Station st(1, 12, "Novodachnaya");
        st.changePassStream(20);
        assert(st.getStream() == 20);
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

/*void TestChange(){              //тесты для пересадки(надо дополнить)
    Change ch(10, 20);
    assert(ch.getTime() == 10 && ch.getStream() == 20);
}*/
/*void TestChangeStation(){      //тесты для пересадочной станции
    Change ch(1, 2);
    ChangeStation st(2, 10, "Arbatskaya");
    st.addChange(ch);          //добавление пересадки
    assert(!st.getChanges().empty());

    Station st1(1, 6, "Ohotnii ryad");
    Line line;
    line.addStation(1, 6, "Ohotnii ryad");    
    line.addChangeStation(2, 10, "Arbatskaya");                       
    line.addChange("Arbatskaya", ch);
    assert(!line.find_p(2)->getChanges().empty());
}*/


void TestSkipList(){
    skip_list<int, int> nums;
    nums.add(1, 2);
    nums.add(2, 4);
    nums.add(4, 6);
    nums.add(3, 10);
    auto it = nums.begin();
    assert(*it == 2);   //проверка метода begin
    it = nums.end();    
    assert(*it == 6);   //проверка метода end
    assert(nums.size() == 4);   //проверка метода size
    
    auto b = nums.begin();
    assert(b != it);    //проверка перегрузки !=
    assert(*(++b) == 4 && *(--b) == 2); //проверка перегрузки ++ и --(префикс)
    assert(*(b++) == 2 && *(b--) == 4 && *b == 2);  //проверка ++ и -- (постфикс)
    b += 3;
    assert(*it == *b);  //проверка перегрузки +=
    b -= 3;
    assert(*b == *nums.begin()); //проверка перегрузки -=
    b = it;
    assert(*b == *it);  //проверка перегрузки =
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
    Line line;
    line.addStation(1,12, "Borovitskaya");
    assert(line.find_t(1).getName() == "Borovitskaya");  //добавление первой станции 

    Station st2(2, 15, "Polyanka");
    line.addStation(2, 15, "Polyanka", 2);    
    assert(line.find_t(2) == st2);
    
    Station st3(3, 10, "Chehovskaya");
    line.addStation(3, 10, "Chehovskaya", 4);
    assert(line.findLeftNeighbor(3) == st2);    //добавление станции в корректное место и работа Line::FindLeftNeighbor
    assert(line.findRightNeighbor(2) == st3);  //работа Line::FindRightNeighbor
    assert(line.minTime(1, 3) == 6);                      //проверка работы метода Line::MinTime;
    assert(line.minTime(1, 3) == line.minTime(3, 1));     //в обе стороны должно быть одинаковое время

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
    line.addStation(2, 20, "Prazhskaya", 1, 2);
    assert(line.findLeftNeighbor(2).getName() == "Borovitskaya" && line.findRightNeighbor(2).getName() == "Polyanka");    //корректное добавление в произвольное место
    assert(line.minTime(3, 1) == 3);

    Station st5(1, 5, "Chertanovskaya");                                //добавляем в начало
    line.addStation(1, 5, "Chertanovskaya", 0, 3);
    assert(line.findRightNeighbor(1).getName() == st1.getName());
    assert(line.minTime(3, 1) == 4 && line.minTime(3, 5) == 6);

    Station st6(6, 7, "Tulskaya");                                      //проверяем, что ничего не сломалось после добавления в начало
    line.addStation(6, 7, "Tulskaya", 2);
    assert(line.findLeftNeighbor(6).getName() == "Chehovskaya" && line.minTime(1, 6) == 12);


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

    line.makeCircle(1);
    assert(line.findLeftNeighbor(1).getName() == "Tulskaya");    //проверка создания круговой линии
    assert(line.findRightNeighbor(6).getName() == "Chertanovskaya");
    assert(line.minTime(4, 1) == 6 && line.minTime(1, 4) == line.minTime(1,4));    //корректность работы минимального времени на кольцевой линии
    assert(line.minTime(1, 6) == 1);
    assert(line.minTime(5, 1) == 3);



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
    line.addStation(7, 20, "Uzhnaya", 1, 3);
    assert(line.findLeftNeighbor(1).getName() == "Uzhnaya");
    assert(line.minTime(6, 1) == 4);
    assert(line.minTime(1, 7) == 3);


    Station st8(6, 10, "Serpuhovskaya");         //добавление станции в произвольное место
    line.addStation(6, 10, "Serpuhovskaya", 1, 3);
    assert(line.findRightNeighbor(6).getName() == "Tulskaya" && line.findLeftNeighbor(6).getName() == "Chehovskaya");

//Тут надо добавить схему

    Station st9(1, 6, "Timiryazevskaya");       //добавление станции в начало для кольцевой линии
    line.addStation(1, 6, "Timiryazevskaya",2 ,2);
    assert(line.findRightNeighbor(1).getName() == "Chertanovskaya" && line.findLeftNeighbor(1).getName() == "Uzhnaya");
    assert(line.minTime(1,9) == 2 && line.minTime(1,4) == 6);  

    Station st10(10, 8, "Tsetnoi bulvar");      //небольшая проверка, что ничего не сломалось после добавления в начало
    line.addStation(10, 8, "Tsetnoi bulvar", 1, 2);
    assert(line.findRightNeighbor(10).getName() == "Timiryazevskaya" && line.findLeftNeighbor(10).getName() == "Uzhnaya");  

}
void TestUnderground(){
    Line line;
    line.addStation(1, 12, "Borovitskaya");
    line.addStation(2, 15, "Polyanka", 2);
    line.addStation(3, 10, "Chehovskaya", 4);
    line.addChangeStation(4, 10, "ChangeHere");
    Line line1;
    line1.addStation(1, 12, "bbrrr");
    line1.addChangeStation(2, 2, "chst", 4);
    Station* st1 = line1.find_p(2);
    Station* st2 = line.find_p(4);
    line.addChange("ChangeHere", Change(1,2,st2, st1));
    line1.addChange("chst", Change(1, 2, st1, st2));
    Underground underground;
    underground.addLine(line);
    underground.addLine(line1);
    std::pair<uint, std::vector<std::string>> path = underground.timeMinPath("Borovitskaya", "bbrrr");
    std::cout << path.first << std::endl;
    for(const auto& st:path.second){
        std::cout << st << std::endl;
    }
}

int main() {
    TestSkipList();
    TestStation();
/*TestLine();*/
    TestUnderground();
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
