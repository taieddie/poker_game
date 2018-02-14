#include <vector>
#include <string>
#include "Hand.h"

using namespace std;

class PokerPlayer
{
    friend class UnitTester;
    public:
        vector<Card> getVectOfCards(string cards);
    private:
        int getCardValue (string cardValue);
        Card::Suit getCardType (char cardType);
        bool isValidCard (string card);
        Card getCard (string cardString);
        Hand determineBestHand (vector<Hand> allHands);
};






