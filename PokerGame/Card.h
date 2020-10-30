//
//  Card.cpp
//  PokerGame
//
//  Created by user on 2020/10/27.
//
#ifndef CARD_H
#define CARD_H
#include <string>
#include <vector>
#include <iostream>
#define NUMBER_OF_CARD_SUITS 4
#define MAX_CARD_NUMBER 13
#define NUMBER_OF_POKER_CARDS 52
static const std::string suits[NUMBER_OF_CARD_SUITS] = {"黑桃", "紅心", "方塊", "梅花"};
class Card {
public:
    Card();
    Card(std::string, int);
    static std::vector<Card> GeneratePokerCards();
    
    bool Equals(Card);
    bool SuitEquals(Card);
    bool SuitEquals(std::string);
    bool NumberEquals(Card);
    bool NumberEquals(int);
    int Sub(Card);
    int Sub(int);
    std::string ToString();
    
    static std::vector<Card> Sort(std::vector<Card>);
private:
    
    std::string suit;
    int number;
    static bool CardCompare(Card, Card);
};

Card::Card(){
    this->suit = " ";
    this->number = 0;
}

Card::Card(std::string suit, int number){
    this->suit = suit;
    this->number = number;
}

bool Card::Equals(Card card){
    return ( this->SuitEquals(card) && this->NumberEquals(card) );
}

bool Card::SuitEquals(Card card){
    return (this->suit == card.suit);
}

bool Card::SuitEquals(std::string suit){
    return (this->suit == suit);
}

bool Card::NumberEquals(Card card){
    return (this->number == card.number);
}

bool Card::NumberEquals(int number){
    return (this->number == number);
}

int Card::Sub(Card card){
    return (this->number - card.number);
}

int Card::Sub(int number){
    return (this->number - number);
}

std::vector<Card> Card::GeneratePokerCards(){
    std::vector<Card> cards;
    cards.assign(NUMBER_OF_POKER_CARDS, Card());
    for (int i = 0; i < NUMBER_OF_CARD_SUITS; i++) {
        for (int j = 0; j < MAX_CARD_NUMBER; j++) {
            cards[i * MAX_CARD_NUMBER + j] = Card(suits[i], j + 1);
        }
    }
    
    return cards;
}

std::string Card::ToString(){
    std::string suitString;
    std::string numberString;
    std::string cardToString;
    suitString = this->suit;
    
    switch (this->number) {
        case 1:
            numberString = "A";
            break;
        case 11:
            numberString = "J";
            break;
        case 12:
            numberString = "Q";
            break;
        case 13:
            numberString = "K";
            break;
        default:
            numberString = std::to_string(this->number);
            break;
    }
    cardToString = suitString + numberString;
    return cardToString;
}

std::vector<Card> Card::Sort(std::vector<Card> cards){
    std::vector<Card> sortedCards = cards;
    std::sort(sortedCards.begin(), sortedCards.end(), Card::CardCompare);
    return sortedCards;
}

bool Card::CardCompare(Card card1, Card card2){
    return card1.number < card2.number;
}
#endif
