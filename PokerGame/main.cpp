//
//  main.cpp
//  PokerGame
//
//  Created by user on 2020/10/27.
//

#include <iostream>
#include <map>
#include "PokerGame.h"
std::map<int, int> winrate;
void InitWinrRate(){
    winrate.insert(std::pair<int, int>(0, 0));
    winrate.insert(std::pair<int, int>(1, 0));
    winrate.insert(std::pair<int, int>(2, 0));
    winrate.insert(std::pair<int, int>(3, 0));
    winrate.insert(std::pair<int, int>(5, 0));
    winrate.insert(std::pair<int, int>(7, 0));
    winrate.insert(std::pair<int, int>(10, 0));
    winrate.insert(std::pair<int, int>(40, 0));
    winrate.insert(std::pair<int, int>(100, 0));
    winrate.insert(std::pair<int, int>(500, 0));
}
void GetWinRate(){
    InitWinrRate();
    int count = 100000;
    int i = 0;
    PokerGame pokerGame;
    while(i++ < count){
        pokerGame.ResetCards();
        if(pokerGame.DrawCards(5) == false){
            break;
        }
        std::cout << i << ": ";
        winrate[pokerGame.GetMoney()]++;
    }
    std::cout << "List win rates:\n";
    std::cout << "同花大順: " << (double)winrate[500]*100/count << "%" <<std::endl;
    std::cout << "同花順: " << (double)winrate[100]*100/count << "%" << std::endl;
    std::cout << "鐵支: " << (double)winrate[40]*100/count << "%" << std::endl;
    std::cout << "葫蘆: " << (double)winrate[10]*100/count << "%" << std::endl;
    std::cout << "同花: " << (double)winrate[7]*100/count << "%" << std::endl;
    std::cout << "順子: " << (double)winrate[5]*100/count << "%" << std::endl;
    std::cout << "三條: " << (double)winrate[3]*100/count << "%" << std::endl;
    std::cout << "兩對: " << (double)winrate[2]*100/count << "%" << std::endl;
    std::cout << "一對(JQKA): " << (double)winrate[1]*100/count << "%" << std::endl;
    std::cout << "無: " << (double)winrate[0]*100/count << "%" << std::endl;
}
int main(int argc, const char * argv[]) {
//    GetWinRate();
    int count = 0;
    int totalMoney = 0;
    while (1) {
        PokerGame pokerGame;
        std::cout << pokerGame.AllCardsToString() << std::endl;
        int drawTimes = 10;
        int money = 0;

        while (drawTimes > 0) {
            if(pokerGame.DrawCards(5) == false){
                break;
            }
//            std::vector<Card> c(5);
//            c[0] = Card('D',13);
//            c[1] = Card('D',12);
//            c[2] = Card('D',1);
//            c[3] = Card('D',11);
//            c[4] = Card('D',2);
//            pokerGame.SetHandCards(c);
            std::cout << "Draw: " << pokerGame.HandCardsToString() << std::endl;
            money += pokerGame.GetMoney();
            --drawTimes;
        }
        std::cout << "Remains: " << pokerGame.AllCardsToString() << std::endl;
        std::cout << "Win: " << money << std::endl;
        std::cout << "------------------------" << std::endl;
        totalMoney += money;
        count++;
        if (count == 10000) {
            break;
        }
    }
    std::cout << "Totally play " << count << " times." << std::endl;
    std::cout << "Average win: " << (double)totalMoney/count << std::endl;
    return 0;
}
