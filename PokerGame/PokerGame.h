//
//  PokerGame.cpp
//  PokerGame
//
//  Created by user on 2020/10/27.
//
#ifndef POKERGAME_H
#define POKERGAME_H

#include <vector>
#include <map>
#include <string>
#include <random>
#include <iostream>
#include "Card.h"
#include "CardTypeChecker.h"

class PokerGame {
    std::vector<Card> cards;
    
public:
    PokerGame();
    
    void ResetCards();
    void ShuffleCards(int);
    void ShowCards();
    int GetMoney(std::vector<std::string>);
    std::vector<std::string> DrawCards(int);
    
private:
    CardTypeChecker cardTypeChecker;
    std::random_device seed;
    std::mt19937_64 randomNumberGenerator;
    std::uniform_int_distribution<int> distribution;
    
    Card DrawCard();
    bool RemoveCard();
};

PokerGame::PokerGame(){
    randomNumberGenerator = std::mt19937_64(seed());
    cards = Card::GeneratePokerCards();
    ShuffleCards(10);
}


void PokerGame::ShuffleCards(int shuffleTimes = 1){
    int randomInt;
    Card tempCard;
    int length = (int)cards.size();
    distribution = std::uniform_int_distribution<int>(0, length - 1);
    
    //std::cout << "Shuffle " << shuffleTimes << " times" << std::endl;
    while (shuffleTimes > 0) {
        for (int i = 0; i < length; i++) {
            randomInt = distribution(randomNumberGenerator);
            //std::cout << i << " to " << randomInt << std::endl;
            // 隨機交換
            tempCard = cards[i];
            cards[i] = cards[randomInt];
            cards[randomInt] = tempCard;
        }
        --shuffleTimes;
    }
}

void PokerGame::ShowCards(){
    int length = (int)cards.size();
    for (int i = 0; i < length; i++) {
        std::cout << cards[i].ToString() << ",";
    }
    std::cout << std::endl;
}

int PokerGame::GetMoney(std::vector<std::string> handCards){
    if (handCards.size() == 0) {
        return 0;
    }
    
    std::vector<Card> handCards_(handCards.size());
    for (int i = 0; i < handCards.size(); i++) {
        handCards_[i] = Card::StringToCard(handCards[i]);
    }
    
    std::string cardType = cardTypeChecker.GetCardType(handCards_);
    int money = cardTypeChecker.GetMoneyByCardType(cardType);
    
    std::vector<Card> sortedCards = Card::Sort(handCards_);
    for (int i = 0; i < handCards.size(); i++) {
        std::cout << sortedCards[i].ToString() << ", ";
    }
    std::cout << cardType << ", wins " << money << "\n" << std::endl;
    return money;
}

std::vector<std::string> PokerGame::DrawCards(int numberOfCards){
    std::vector<std::string> drawCards;
    if (numberOfCards > cards.size()) {
        std::cout << cards.size() << " cards remains. No enough cards to draw." << std::endl;
    }
    else{
        drawCards = std::vector<std::string>(numberOfCards, "");
        std::cout << "Draw ";
        for (int i = 0; i < numberOfCards; i++) {
            drawCards[i] = DrawCard().ToString();
            std::cout << drawCards[i] << ", ";
        }
        std::cout << " from cards" << std::endl;
    }
    return drawCards;
}

Card PokerGame::DrawCard(){
    Card drawCard = Card();
    int length = (int)cards.size();
    distribution = std::uniform_int_distribution<int>(0, length - 1);
    int randomInt = distribution(randomNumberGenerator);
    
    //std::cout << "Draw " << cards[randomInt].ToString() << " from cards" << std::endl;
    drawCard = cards[randomInt];
    //ShowCards();
    cards.erase(cards.begin() + randomInt);
    //ShowCards();
    return drawCard;
}
#endif
