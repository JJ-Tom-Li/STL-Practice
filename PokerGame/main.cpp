//
//  main.cpp
//  PokerGame
//
//  Created by user on 2020/10/27.
//

#include <iostream>
#include <map>
#include "PokerGame.h"
int main(int argc, const char * argv[]) {
    int playCount = 0;
    int totalWinMoney = 0;
    PokerGame pokerGame;
    std::string input = "0";
    
    std::cout << "輸入任意字元開始遊戲:" << std::endl;
    while (std::cin >> input){
        if (input == "0") {
            break;
        }
        playCount++;
        std::cout << "開始第" << playCount << "次遊戲:" << std::endl;
        pokerGame.ResetGame();
        
        int winMoney = 0;
        int drawCount = 10;
        for (int i = 1; i <= drawCount; i++) {
            if(pokerGame.DrawCards(5) == false){
                break;
            }
            std::cout << "第" << i << "輪抽牌: " << pokerGame.HandCardsToString() << std::endl;
            winMoney += pokerGame.GetMoney();
        }
        
        std::cout << "剩下的牌: " << pokerGame.AllCardsToString() << "\n"
                << drawCount << "輪抽牌共贏得: " << winMoney << " 元\n"
                << "------------------------" << std::endl;
        
        totalWinMoney += winMoney;
        
        std::cout << "輸入任意文字繼續遊玩，輸入0結束:";
    }
    
    std::cout << "總遊玩次數: " << playCount << " 次.\n"
            << "共贏得 " << totalWinMoney << " 元，平均贏得: " << (double)totalWinMoney/playCount << " 元" <<std::endl;
    return 0;
}
