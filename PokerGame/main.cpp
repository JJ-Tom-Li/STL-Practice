//
//  main.cpp
//  PokerGame
//
//  Created by user on 2020/10/27.
//

#include <iostream>
#include "PokerGame.h"
int main(int argc, const char * argv[]) {
    int count = 1;
    while (1) {
        PokerGame pokerGame;
        int drawTimes = 10;
        int totalMoney = 0;
    //    std::vector<std::string> cards(5);
    //    cards[0] = "C3";
    //    cards[1] = "C13";
    //    cards[2] = "C4";
    //    cards[3] = "C2";
    //    cards[4] = "C1";
    //    totalMoney += pokerGame.GetMoney(cards);
        while (drawTimes > 0) {

            totalMoney += pokerGame.GetMoney(pokerGame.DrawCards(5));
            --drawTimes;
        }
        std::cout << "Totally win: " << totalMoney << std::endl;
        count++;
        if (totalMoney >= 30) {
            break;
        }
    }
    std::cout << "Totally play " << count << " times." << std::endl;
    return 0;
}
