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

class CardTypeChecker{
public:
    CardTypeChecker();
    std::string GetCardType(std::vector<Card>);
    int GetMoneyByCardType(std::string);
private:
    std::map<std::string, int> cardTypes;
    bool IsStraight(std::vector<Card>);
    std::string CheckStraightTypes(std::vector<Card>);
    std::string CheckNonStraightTypes(std::vector<Card>);
    bool IsFlush(std::vector<Card>);
    bool IsFourOfAKind(std::vector<Card> cards);
    void InitCardTypes();
    bool IsRestart(std::vector<Card>);
    bool Is10JQKA(std::vector<Card>);
    std::pair<int, int> GetMaxSameNumber(std::vector<Card> cards);
};

CardTypeChecker::CardTypeChecker(){
    InitCardTypes();
}

void CardTypeChecker::InitCardTypes(){
    cardTypes.insert(std::pair<std::string, int>("同花大順", 500));
    cardTypes.insert(std::pair<std::string, int>("同花順", 100));
    cardTypes.insert(std::pair<std::string, int>("鐵支", 40));
    cardTypes.insert(std::pair<std::string, int>("葫蘆", 10));
    cardTypes.insert(std::pair<std::string, int>("同花", 7));
    cardTypes.insert(std::pair<std::string, int>("順子", 5));
    cardTypes.insert(std::pair<std::string, int>("三條", 3));
    cardTypes.insert(std::pair<std::string, int>("兩對", 2));
    cardTypes.insert(std::pair<std::string, int>("一對(JQKA)", 1));
}

std::string CardTypeChecker::GetCardType(std::vector<Card> cards){
    std::string cardType = ""; //"同花大順";
    std::vector<Card> sortedCards = Card::Sort(cards);
    
    //TODO
    if (IsStraight(sortedCards)) {
        cardType = CheckStraightTypes(sortedCards);
    }
    else if (IsFlush(sortedCards)){
        cardType = "同花";
    }
    else{
        cardType = CheckNonStraightTypes(sortedCards);
    }
    return cardType;
}


bool CardTypeChecker::IsStraight(std::vector<Card> cards){
    // Straight:順子
    if (IsRestart(cards)) {
        // 判斷K繞回A的順子類型(ex. 10 J Q K A)
        int left = 0;
        int right = (int)cards.size() - 1;
        while(cards[left].Sub(cards[left+1]) == -1) left++;
        while(cards[right].Sub(cards[right-1]) == 1) right--;
        
        // 若是K繞回A的順子類型，left必定=right - 1.
        return (right - left == 1);
    }
    else{
        for (int i = 1; i < cards.size(); i++) {
            if (cards[i].Sub(cards[i-1]) != 1) {
                return false;
            }
        }
        return true;
    }
    return true;
}

bool CardTypeChecker::IsRestart(std::vector<Card> cards){
    // 從MAX_CARD_NUMBER繞回A的牌型，在經過排序後，第一張一定會是A，最後一張一定是MAX_CARD_NUMBER．
    return (cards[0].NumberEquals(1)) &&( cards[cards.size()-1].NumberEquals(MAX_CARD_NUMBER));
}

std::string CardTypeChecker::CheckStraightTypes(std::vector<Card> cards){
    if (IsFlush(cards)) {
        if (Is10JQKA(cards)) {
            return "同花大順";
        }
        else{
            return "同花順";
        }
    }
    else{
        return "順子";
    }
}

bool CardTypeChecker::IsFlush(std::vector<Card> cards){
    // Flush:同花
    int length = (int)cards.size();
    for (int i = 1; i < length; i++) {
        if (!cards[i].SuitEquals(cards[i-1])) {
            return false;
        }
    }
    return true;
}

bool CardTypeChecker::Is10JQKA(std::vector<Card> cards){
    return (cards[0].NumberEquals(1)
            && cards[1].NumberEquals(10)
            && cards[2].NumberEquals(11)
            && cards[3].NumberEquals(12)
            && cards[4].NumberEquals(13));
}

std::string CardTypeChecker::CheckNonStraightTypes(std::vector<Card> cards){
    if (IsFourOfAKind(cards)) {
        return "鐵支";
    }
    else{
        return "ff";
    }
}

bool CardTypeChecker::IsFourOfAKind(std::vector<Card> cards){
    // Four of a kind : 鐵支
    int sameNumber = GetMaxSameNumber(cards).second;
    return ( sameNumber == 4);
}

std::pair<int, int> CardTypeChecker::GetMaxSameNumber(std::vector<Card> cards){
    int maxSameNumber = 1;
    int sameNumber = 1;
    int start = 0;
    for (int i = 0; i < cards.size() - 1; i++) {
        if (cards[i].NumberEquals(cards[i+1])) {
            sameNumber++;
        }
        else{
            if (maxSameNumber < sameNumber) {
                maxSameNumber = sameNumber;
                start = i;
            }
        }
    }
    std::pair<int, int> startAndMaxNumber(start, maxSameNumber);
    return startAndMaxNumber;
}

int CardTypeChecker::GetMoneyByCardType(std::string cardType){
    int money = 0;
    if (cardTypes.find(cardType) != cardTypes.end()) {
        money = cardTypes[cardType];
    }
    return money;
}
#endif /* CardTypeChecker_h */
