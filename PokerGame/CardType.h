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
bool IsStraight(std::vector<Card>);
bool IsRestart(std::vector<Card>);
bool IsFlush(std::vector<Card>);
bool Is10JQKA(std::vector<Card>);
std::pair<int, int> GetMaxSameNumber(std::vector<Card>);

class CardType{
public:
    std::string typeName;
    CardType(std::string name){
        typeName = name;
    }
    virtual bool IsThisType(std::vector<Card>) = 0;
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
            cards.erase(cards.begin() + start);
            cards.erase(cards.begin() + start);
            cards.erase(cards.begin() + start);
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
            cards.erase(cards.begin() + start);
            cards.erase(cards.begin() + start);
            cards.erase(cards.begin() + start);
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
        //std::cout << start << "," << maxSameNumber << std::endl;
        if (maxSameNumber == 2) {
            cards.erase(cards.begin() + start);
            cards.erase(cards.begin() + start);
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
        //std::cout << start << "," << maxSameNumber << std::endl;
        if (maxSameNumber == 2
            && ( cards[start].NumberEquals(11) || cards[start].NumberEquals(12) || cards[start].NumberEquals(13) || cards[start].NumberEquals(1))) {
                cards.erase(cards.begin() + start);
                cards.erase(cards.begin() + start);
                result = (!cards[0].NumberEquals(cards[1]) && !cards[1].NumberEquals(cards[2]) && !cards[0].NumberEquals(cards[2]));
        }
        return result;
    }
};

bool IsStraight(std::vector<Card> cards){
    // Straight:順子
    if (Is10JQKA(cards)) {
        return true;
    }
    else{
        for (int i = 1; i < cards.size(); i++) {
            if (cards[i].Sub(cards[i-1]) != 1) {
                return false;
            }
        }
        return true;
    }
}

bool IsRestart(std::vector<Card> cards){
    // 從MAX_CARD_NUMBER繞回A的牌型，在經過排序後，第一張一定會是A，最後一張一定是MAX_CARD_NUMBER．
    return (cards[0].NumberEquals(1)) &&( cards[cards.size()-1].NumberEquals(MAX_CARD_NUMBER));
}

bool IsFlush(std::vector<Card> cards){
    // Flush:同花
    int length = (int)cards.size();
    for (int i = 1; i < length; i++) {
        if (!cards[i].SuitEquals(cards[i-1])) {
            return false;
        }
    }
    return true;
}

bool Is10JQKA(std::vector<Card> cards){
    return (cards[0].NumberEquals(1)
            && cards[1].NumberEquals(10)
            && cards[2].NumberEquals(11)
            && cards[3].NumberEquals(12)
            && cards[4].NumberEquals(13));
}

std::pair<int, int> GetMaxSameNumber(std::vector<Card> cards){
    int maxSameNumber = 1;
    int sameNumber = 1;
    int start = 0;
    int maxStart = 0;
    for (int i = 0; i < cards.size() - 1; i++) {
        if (cards[i].NumberEquals(cards[i+1])) {
            sameNumber++;
        }
        else{
            if (maxSameNumber < sameNumber) {
                maxSameNumber = sameNumber;
                maxStart = start;
            }
            sameNumber = 1;
            start = i+1;
        }
    }
    if (maxSameNumber < sameNumber) {
        maxSameNumber = sameNumber;
        maxStart = start;
    }
    std::pair<int, int> startAndMaxNumber(maxStart, maxSameNumber);
    return startAndMaxNumber;
}
#endif /* CardType_h */
