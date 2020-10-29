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
    
public:
    PokerGame();
    
    void ResetCards();
    void ShuffleCards(int);
    std::string CardsToString(std::vector<Card>);
    std::string HandCardsToString();
    std::string AllCardsToString();
    int GetMoney();
    bool DrawCards(int);
    void SetHandCards(std::vector<Card>);
private:
    std::vector<Card> cards;
    std::vector<Card> handCards;
    CardTypeChecker cardTypeChecker;
    std::random_device seed;
    std::mt19937_64 randomNumberGenerator;
    std::uniform_int_distribution<int> distribution;
    
    Card DrawCard();
    bool RemoveCard();
};

PokerGame::PokerGame(){
    randomNumberGenerator = std::mt19937_64(seed());
    ResetCards();
}

void PokerGame::ResetCards(){
    cards = Card::GeneratePokerCards();
    ShuffleCards(10);
}

void PokerGame::ShuffleCards(int shuffleTimes = 1){
    int randomInt;
    Card tempCard;
    int length = (int)cards.size();
    distribution = std::uniform_int_distribution<int>(0, length - 1);
    
    while (shuffleTimes > 0) {
        for (int i = 0; i < length; i++) {
            randomInt = distribution(randomNumberGenerator);
            
            tempCard = cards[i];
            cards[i] = cards[randomInt];
            cards[randomInt] = tempCard;
        }
        --shuffleTimes;
    }
}

std::string PokerGame::CardsToString(std::vector<Card> cards){
    int length = (int)cards.size();
    std::string returnString;
    
    for (int i = 0; i < length; i++) {
        returnString += cards[i].ToString() + ", ";
    }
    return returnString;
}

std::string PokerGame::HandCardsToString(){
    return CardsToString(this->handCards);
}

std::string PokerGame::AllCardsToString(){
    return CardsToString(this->cards);
}

int PokerGame::GetMoney(){
    if (handCards.size() == 0) {
        return 0;
    }
    
    std::string cardType = cardTypeChecker.GetCardType(handCards);
    int money = cardTypeChecker.GetMoneyByCardType(cardType);
    
    std::vector<Card> sortedCards = Card::Sort(handCards);
    std::cout << CardsToString(sortedCards) << cardType << ", wins " << money << "\n" << std::endl;
   return money;
}

bool PokerGame::DrawCards(int numberOfCards){
    if (numberOfCards > cards.size()) {
        std::cout << cards.size() << " cards remains. No enough cards to draw." << std::endl;
        return false;
    }
    else{
        handCards = std::vector<Card>(numberOfCards, Card());
        for (int i = 0; i < numberOfCards; i++) {
            handCards[i] = DrawCard();
        }
    }
    return true;
}

Card PokerGame::DrawCard(){
    Card drawCard = Card();
    int length = (int)cards.size();
    int randomInt = 0;
    distribution = std::uniform_int_distribution<int>(0, length - 1);
    randomInt = distribution(randomNumberGenerator);
    
    drawCard = cards[randomInt];
    cards.erase(cards.begin() + randomInt);
    return drawCard;
}
void PokerGame::SetHandCards(std::vector<Card> cards){
    handCards = cards;
}
#endif
