#include "Hand.h"
#include <vector>
#include <iostream>
#include <string>


// This class is responsible for unit testing the different classes
// involved in the poker game. This will unit test each function,
// making sure all paths are covered. Subsystem testing will also
// be done, making sure the entire paths are covered.

class UnitTester
{
    public:
        bool testCaseOne();

    protected:

    private:
};

bool UnitTester::testCaseOne()
{
    vector<Card> myCards;

    Card cardOne(4,Card::Spade);
    Card cardTwo(4, Card::Spade);
    Card cardThree(4,Card::Spade);
    Card cardFour(4, Card::Spade);
    Card cardFive(4, Card::Spade);

    myCards.push_back(cardOne);
    myCards.push_back(cardTwo);
    myCards.push_back(cardThree);
    myCards.push_back(cardFour);
    myCards.push_back(cardFive);

    Hand myHand(myCards);

    return myHand.containsFlush();
}
/*
int main()
{
    bool allTestsPassed = true;

    UnitTester myTester;

    allTestsPassed &= myTester.testCaseOne();

    string output = allTestsPassed? "All Tests Passed!" : "Some tests has failed!!!!" ;
    cout << output << endl;
}

*/
