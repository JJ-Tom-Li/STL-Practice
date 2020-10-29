//
//  CardType.h
//  PokerGame
//
//  Created by user on 2020/10/29.
//

#ifndef CardType_h
#define CardType_h
#include <iostream>
#include <string>
#include <vector>

class CardType{
public:
    std::string typeName;
    
    CardType(std::string name){
        typeName = name;
    }
    virtual bool IsThisType(std::vector<Card>) = 0;
    
protected:
    bool IsStraight(std::vector<Card>);
    bool IsFlush(std::vector<Card>);
    bool Is10JQKA(std::vector<Card>);
    std::pair<int, int> GetMaxSameNumber(std::vector<Card>);
    std::vector<Card> RemoveCards(std::vector<Card>, int, int);
};

class RoyalFlush : public CardType{
public:
    RoyalFlush(std::string name) : CardType(name){}
    
    bool IsThisType(std::vector<Card> cards){
        return (IsStraight(cards) && IsFlush(cards) && Is10JQKA(cards));
    }
};

class StraightFlush : public CardType{
public:
    StraightFlush(std::string name) : CardType(name){}
    
    bool IsThisType(std::vector<Card> cards){
        return (IsStraight(cards) && IsFlush(cards));
    }
};

class FourOfAKind : public CardType{
public:
    FourOfAKind(std::string name) : CardType(name){}
    
    bool IsThisType(std::vector<Card> cards){
        int maxSameNumber = GetMaxSameNumber(cards).second;
        return (maxSameNumber == 4);
    }
};

class FullHouse : public CardType{
public:
    FullHouse(std::string name) : CardType(name){}
    
    bool IsThisType(std::vector<Card> cards){
        std::pair<int, int> pair = GetMaxSameNumber(cards);
        int start = pair.first;
        int maxSameNumber = pair.second;
        bool result = false;
        
        if (maxSameNumber == 3) {
            cards = RemoveCards(cards, start, 3);
            result = cards[0].NumberEquals(cards[1]);
        }
        return result;
    }
};

class Flush : public CardType{
public:
    Flush(std::string name) : CardType(name){}
    
    bool IsThisType(std::vector<Card> cards){
        return IsFlush(cards);
    }
};

class Straight : public CardType{
public:
    Straight(std::string name) : CardType(name){}
    
    bool IsThisType(std::vector<Card> cards){
        return IsStraight(cards);
    }
};

class ThreeOfAKind : public CardType{
public:
    ThreeOfAKind(std::string name) : CardType(name){}
    
    bool IsThisType(std::vector<Card> cards){
        std::pair<int, int> pair = GetMaxSameNumber(cards);
        int start = pair.first;
        int maxSameNumber = pair.second;
        bool result = false;
        
        if (maxSameNumber == 3) {
            cards = RemoveCards(cards, start, 3);
            result = !cards[0].NumberEquals(cards[1]);
        }
        return result;
    }
};

class TwoPairs : public CardType{
public:
    TwoPairs(std::string name) : CardType(name){}
    bool IsThisType(std::vector<Card> cards){
        std::pair<int, int> pair = GetMaxSameNumber(cards);
        int start = pair.first;
        int maxSameNumber = pair.second;
        bool result = false;
        
        if (maxSameNumber == 2) {
            cards = RemoveCards(cards, start, 2);
            maxSameNumber = GetMaxSameNumber(cards).second;
            result = (maxSameNumber == 2);
        }
        return result;
    }
};

class OnePair : public CardType{
public:
    OnePair(std::string name) : CardType(name){}
    bool IsThisType(std::vector<Card> cards){
        std::pair<int, int> pair = GetMaxSameNumber(cards);
        int start = pair.first;
        int maxSameNumber = pair.second;
        bool result = false;
        
        if (maxSameNumber == 2
            /*&& ( cards[start].NumberEquals(11) || cards[start].NumberEquals(12) || cards[start].NumberEquals(13) || cards[start].NumberEquals(1))*/) {
            cards = RemoveCards(cards, start, 2);
                result = (!cards[0].NumberEquals(cards[1]) && !cards[1].NumberEquals(cards[2]) && !cards[0].NumberEquals(cards[2]));
        }
        return result;
    }
};

bool CardType::IsStraight(std::vector<Card> cards){
    // Straight:順子
    if (Is10JQKA(cards)) {
        return true;
    }
    
    for (int i = 1; i < cards.size(); i++) {
        if (cards[i].Sub(cards[i-1]) != 1) {
            return false;
        }
    }
    return true;
}

bool CardType::IsFlush(std::vector<Card> cards){
    // Flush:同花
    int length = (int)cards.size();
    for (int i = 1; i < length; i++) {
        if (!cards[i].SuitEquals(cards[i-1])) {
            return false;
        }
    }
    return true;
}

bool CardType::Is10JQKA(std::vector<Card> cards){
    return (cards[0].NumberEquals(1)
            && cards[1].NumberEquals(10)
            && cards[2].NumberEquals(11)
            && cards[3].NumberEquals(12)
            && cards[4].NumberEquals(13));
}

std::pair<int, int> CardType::GetMaxSameNumber(std::vector<Card> cards){
    int maxSameNumber = 1;
    int sameNumber = 1;
    int start = 0;
    int maxStart = 0;
    for (int i = 1; i < cards.size(); i++) {
        if (cards[i].NumberEquals(cards[i-1])) {
            sameNumber++;
        }
        else{
            sameNumber = 1;
            start = i;
        }
        if (maxSameNumber < sameNumber) {
            maxSameNumber = sameNumber;
            maxStart = start;
        }
    }
    std::pair<int, int> startAndMaxNumber(maxStart, maxSameNumber);
    return startAndMaxNumber;
}

std::vector<Card> CardType::RemoveCards(std::vector<Card> cards, int start, int number){
    std::vector<Card> removedCards = cards;
    for (int i = 0; i < number; i++) {
        removedCards.erase(removedCards.begin() + start);
    }
    return removedCards;
}
#endif /* CardType_h */
