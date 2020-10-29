//
//  CardTypeChecker.h
//  PokerGame
//
//  Created by user on 2020/10/28.
//

#ifndef CardTypeChecker_h
#define CardTypeChecker_h
#include <string>
#include <map>
#include <vector>
#include "Card.h"
#include "CardType.h"

class CardTypeChecker{
public:
    CardTypeChecker();
    std::string GetCardType(std::vector<Card>);
    int GetMoneyByCardType(std::string);
    
private:
    std::vector<CardType*> cardTypes;
    std::map<std::string, int> cardTypesMoney;
    
    void InitCardTypes();
};

CardTypeChecker::CardTypeChecker(){
    InitCardTypes();
}

void CardTypeChecker::InitCardTypes(){
    cardTypes.push_back(new RoyalFlush("同花大順"));
    cardTypes.push_back(new StraightFlush("同花順"));
    cardTypes.push_back(new FourOfAKind("鐵支"));
    cardTypes.push_back(new FullHouse("葫蘆"));
    cardTypes.push_back(new Flush("同花"));
    cardTypes.push_back(new Straight("順子"));
    cardTypes.push_back(new ThreeOfAKind("三條"));
    cardTypes.push_back(new TwoPairs("兩對"));
    cardTypes.push_back(new OnePair("一對(JQKA)"));
    
    cardTypesMoney.insert(std::pair<std::string, int>("同花大順", 500));
    cardTypesMoney.insert(std::pair<std::string, int>("同花順", 100));
    cardTypesMoney.insert(std::pair<std::string, int>("鐵支", 40));
    cardTypesMoney.insert(std::pair<std::string, int>("葫蘆", 10));
    cardTypesMoney.insert(std::pair<std::string, int>("同花", 7));
    cardTypesMoney.insert(std::pair<std::string, int>("順子", 5));
    cardTypesMoney.insert(std::pair<std::string, int>("三條", 3));
    cardTypesMoney.insert(std::pair<std::string, int>("兩對", 2));
    cardTypesMoney.insert(std::pair<std::string, int>("一對(JQKA)", 1));
}

std::string CardTypeChecker::GetCardType(std::vector<Card> cards){
    std::string cardType = "無";
    // 注意！！ 必須先排序過才能比對牌型
    std::vector<Card> sortedCards = Card::Sort(cards);
    
    for (int i = 0; i < cardTypes.size(); i++) {
        if (cardTypes[i]->IsThisType(sortedCards)) {
            cardType = cardTypes[i]->typeName;
            break;
        }
    }
    return cardType;
}

int CardTypeChecker::GetMoneyByCardType(std::string cardType){
    int money = 0;
    if (cardTypesMoney.find(cardType) != cardTypesMoney.end()) {
        money = cardTypesMoney[cardType];
    }
    return money;
}
#endif /* CardTypeChecker_h */
