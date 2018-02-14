#include "PokerPlayer.h"
#include <iostream>
#include <dirent.h>
#include <stdio.h>
#include <regex>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm>

using namespace std;

// Contains regular expression about a card
const regex real_card("([1-9]|10|J|Q|K|A){1}(H|C|D|S){1}");
smatch matches;

// Gets the card value
// Input : String of the cardValue
// Output : Integer representing the card value
int PokerPlayer::getCardValue (string cardValue)
{
    // The string given is "0","1"...."9"
    if (cardValue.length() == 1)
    {
        if ( (cardValue[0] >= 0) &&
             (cardValue[0] <= 57) )
        {
            return (cardValue[0] - '0');
        }
        else if (cardValue[0] == 74)
        {
            return 11;
        }
        else if (cardValue[0] == 81)
        {
            return 12;
        }
        else if (cardValue[0] == 75)
        {
            return 13;
        }
        else if (cardValue[0] == 65)
        {
            return 14;
        }
        else
        {
            cout << "Invalid card value (" << cardValue[0] << ") passed into getCardValue()" << endl;
        }
    }
    // The string given is "10"
    else if (cardValue.length() == 2)
    {
        if ( (cardValue[0] == 49) &&
             (cardValue[1] == 48) )
        {
            return 10;
        }
        else
        {
            cout << "Invalid card value (" << cardValue[0] << cardValue[1] << ") passed into getCardValue()" << endl;
        }
    }
    else
    {
         cout << "Invalid card value (" << cardValue << ") passed into getCardValue()" << endl;
    }

    return -1;
}

// Validates card type
// Input : Char of the cardType
// Output : Char of the cardType if it is valid
Card::Suit PokerPlayer::getCardType (char cardType)
{
    if (cardType == 'H')
    {
          return Card::Heart;
    }
    else if (cardType == 'C')
    {
        return Card::Club;
    }
    else if (cardType == 'D')
    {
        return Card::Diamond;
    }
    else if (cardType == 'S')
    {
        return Card::Spade;
    }
    else
    {
        cout << "Invalid card type (" << cardType << ") passed into getCardType()" << endl;
        return Card::None;
    }
}

// Determines if the string is a valid card
// Input : string of the card
// Output : true if it is valid and false if its not
bool PokerPlayer::isValidCard (string card)
{
    return regex_search(card, matches, real_card) ;
}

// Gets a card, given a card string
// Input : string of the card
// Output : Card object
Card PokerPlayer::getCard (string cardString)
{
    Card retCard;
    retCard.setValue(-1);
    retCard.setSuit(Card::None);

    if (!isValidCard(cardString))
    {
        cout << "Invalid card string(" << cardString << ") passed into getCard() caught by regex" << endl;
        return retCard;
    }

    if (cardString.length() == 2)
    {
        retCard.setValue(getCardValue(cardString.substr(0,1)));
        retCard.setSuit(getCardType(cardString[1]));
    }
    else if (cardString.length() == 3)
    {
        retCard.setValue(getCardValue(cardString.substr(0,2)));
        retCard.setSuit(getCardType(cardString[2]));
    }
    else
    {
        retCard.setValue(-1);
        retCard.setSuit(Card::None);
        cout << "Invalid card string (" << cardString << ") passed into getCard()" << endl;
    }


    return retCard;
}

// Gets a card, given a card string
// Input : string of all cards
// Output : Card object
vector<Card> PokerPlayer::getVectOfCards(string cards)
{
    vector<Card> results;
    stringstream ss(cards);
    string token;
    Card currentCard;
    while(getline(ss,token,','))
    {
        //cout << "Before token = " << token << endl;
        token.erase(std::remove (token.begin(), token.end(), '['), token.end());
        token.erase(std::remove (token.begin(), token.end(), '"'), token.end());
        token.erase(std::remove (token.begin(), token.end(), ']'), token.end());
        token.erase(std::remove (token.begin(), token.end(), ' '), token.end());

        //cout << "After token = " << token << endl;

        currentCard = getCard(token);
        if( (currentCard.getValue() == -1) || (currentCard.getSuit() < Card::Club &&
                                               currentCard.getSuit() > Card::Diamond) )
        {
            cout << "Error in getVectOfCards, received an invalid card " << endl;
        }
        else
        {
            results.push_back(getCard(token));
        }
    }

    return results;
}

// Gets a card, given a card string
// Input : string of all cards
// Output : Card object
Hand determineBestHand (vector<Hand> allHands)
{
    Hand temp;
    if (allHands.size () <= 0)
    {
        cout << "Error got invalid hand size of " << allHands.size() << endl;
        return temp;
    }

    int bestHandIndex = 0;
    int bestHandValue = allHands.front().getHandValue();

    for (int handIndex = 1; handIndex < allHands.size(); handIndex++)
    {
        if (allHands[handIndex].getHandValue() > bestHandValue)
        {
            bestHandIndex = handIndex;
            bestHandValue = allHands[handIndex].getHandValue();
        }
    }

    return allHands[bestHandIndex];


}

int main()
{
    //cout << "Hello world!" << endl;

    //string hand =  "[\"JH\", \"5C\", \"4S\", \"JC\", \"9H\"]";

    cout << "Problem 1 - " << endl;
    string handOne =  "4C, 8C, 3C, 7C, 6C";

    PokerPlayer player;

    cout << "Input hand = " << handOne << endl;
    vector<Card> allFiveCards = player.getVectOfCards(handOne);
    Hand MyFiveCardHand(allFiveCards);
    MyFiveCardHand.printFiveHandCategory();

    cout << endl << endl;

    cout << "Problem 2 - " << endl;

    string handOneString = "JH, 4C, 4S, JC, 10S";
    string handTwoString = "4H, 2C, 3S, 6C, 5S";
    cout << "Compare hand one " << handOneString << " with " << handTwoString << endl;

    vector<Card> handOneCompare = player.getVectOfCards(handOneString);
    vector<Card> handTwoCompare  = player.getVectOfCards(handTwoString);

    vector<Hand> allHands;

    allHands.push_back(handOneCompare);
    allHands.push_back(handTwoCompare);


    Hand bestHand = determineBestHand(allHands);

    cout << "Best Hand - " << endl;
    bestHand.printHand();

    cout << endl << endl;

    cout << "Problem 3 - " << endl;

    string moreThanFive =  "9C, QC, KC, 10C, JC, AS, QS, KS, 10S, JS";
    cout << "Input hand = " << moreThanFive << endl;
    vector<Card> allCards = player.getVectOfCards(moreThanFive);
    Hand MyNHand(allCards);
    Hand bestFiveCardHand = MyNHand.getBestHand();
    cout << "Best Hand - " << endl;
    bestFiveCardHand.printHand();








    /*
    vector<Hand> allHands;

    allHands.push_back(handOne);
    allHands.push_back(handTwo);

    Hand bestHand = determineBestHand(allHands);

    cout << "Best Hand - " << endl;
    bestHand.printHand();


    string myHand[] = {"JH", "4C", "4S", "JC", "9H"};
    string hand = "10D, JD, QD, KD, AD";
    string hand =  "[\"JH\", \"5C\", \"4S\", \"JC\", \"9H\"]";
    //string hand = "3H, 7S, 3S, QD, AH, 3D, 4S";
    //string hand = "JH, 4C, 4S, JC, 9A";
    //string hand = "4H, 2C, 3S, 6C, 5S";
    //string hand = "JH, 8C, 7S, 9C, 10S";
    //findAndPrintBestCategory("JH, 4C, 4S, JC, 9H");
    pokerHelper myHelper = pokerHelper();
    myHelper.printBestCategory(hand);
    //vector<Card> bestHand = myHelper.printBestCategory(hand);

*/

    return 0;
}


