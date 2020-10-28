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
class Card {
public:
    
    Card();
    Card(char, int);
    static std::vector<Card> GeneratePokerCards();
    
    bool Equals(Card);
    bool SuitEquals(Card);
    bool SuitEquals(char);
    bool NumberEquals(Card);
    bool NumberEquals(int);
    int Sub(Card);
    
    std::string ToString();
    static Card StringToCard(std::string);
    static std::vector<Card> Sort(std::vector<Card>);
    constexpr static const char suits[NUMBER_OF_CARD_SUITS] = {'S', 'H', 'D', 'C'};
private:
    char suit;
    int number;
    static bool CardCompare(Card, Card);
};

Card::Card(){
    this->suit = '0';
    this->number = 0;
}

Card::Card(char suit, int number){
    this->suit = suit;
    this->number = number;
}

bool Card::Equals(Card card){
    return ( this->SuitEquals(card) && this->NumberEquals(card) );
}

bool Card::SuitEquals(Card card){
    return (this->suit == card.suit);
}

bool Card::SuitEquals(char suit){
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

std::vector<Card> Card::GeneratePokerCards(){
    std::vector<Card> cards;
    cards.assign(NUMBER_OF_POKER_CARDS, Card());
    for (int i = 0; i < NUMBER_OF_CARD_SUITS; i++) {
        for (int j = 0; j < MAX_CARD_NUMBER; j++) {
            cards[i * MAX_CARD_NUMBER + j] = Card(Card::suits[i], j + 1);
        }
    }
    
    return cards;
}

std::string Card::ToString(){
    std::string cardToString;
    cardToString = this->suit + std::to_string(this->number);
    return cardToString;
}

Card Card::StringToCard(std::string cardString){
    Card card;
    card.suit = cardString[0];
    card.number = std::stoi(cardString.substr(1));
    //std::cout << card.suit << "," << card.number << std::endl;
    return card;
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
