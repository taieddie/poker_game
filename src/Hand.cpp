#define __USE_MINGW_ANSI_STDIO 0

#include "Hand.h"
#include <iostream>
#include <algorithm>

using namespace std;

Hand::Hand(vector<Card> cards)
{
    cards_ = cards;
    sort(cards_.begin(), cards_.end(), Card::less_than_value());
}

Hand::Hand()
{

}

Hand::~Hand()
{
    //dtor
}

// Determines if card count array is a straight.
// Input : Array of card counts, highest straight output, maxIndex into array
// Output : Returns true if we have a straight and false if not.
bool Hand::findStraight (int cardCount[], int& outHighestStraight, int maxIndex)
{
    int highestStraight = -1;
    int consecutiveCount = 0;
    int previousCount = 0;

    if (maxIndex > (NUMBER_OF_CARD_VALUES - 1))
    {
        cout << "Invalid index (" << maxIndex << ") given to findStraight()" << endl;
        return false;
    }

    int consecutiveCardCount = 0;
    int previousCardValue = 0;
    int highestStraight = 0;

    for (int cardIndex = 0; cardIndex < cards_.size(); cardIndex++)
    {
        if (cards_[cardIndex].getValue() == (previousCardValue - 1) )
        {
            consecutiveCardCount++;
        }
        else if (cards_[cardIndex].getValue() != previousCardValue)
        {
            consecutiveCardCount = 1;
            highestStraight = cards_[cardIndex].getValue();
        }

        if (consecutiveCardCount == 5)
        {
            outHighestStraight = highestStraight;
            return true;
        }

        previousCardValue = cards_[cardIndex].getValue();
    }

    return false;

}

// Determines if current hand is a straight.
// Input : Output to highest straight.
// Output :  Returns true if we have a straight and false if not.
bool Hand::containsStraight(int& highestStraightOut)
{
    if (cards_.size() < 5)
        return false;

    int previousValue = cards_[0].getValue();
    int currentValue = 0;
    int consecutiveCount = 1;
    // The cards are sorted, so we just
    // need to find the sequential ones
    for (int cardIndex = 1;cardIndex < cards_.size(); cardIndex++)
    {
        currentValue = cards_[cardIndex].getValue();
        if ( currentValue == (previousValue - 1))
        {
            consecutiveCount++;
        }
        else
        {
            consecutiveCount = 0;
        }

        //Found a straight
        if (consecutiveCount == 5)
        {
            highestStraightOut = currentValue;
            return true;
        }

        previousValue = currentValue;
    }

    return false;
}

// Determines if current hand is a flush.
// Input :
// Output :  Returns true if we have a flush and false if not.
bool Hand::containsFlush()
{
    if (cards_.size() < 5)
        return false;

    Card::Suit previousSuit = cards_[0].getSuit();
    Card::Suit currentSuit = Card::None;
    bool foundFlush = true;

    // Compares each suit to see if it has changed
    for (int cardIndex = 1;cardIndex < cards_.size(); cardIndex++)
    {
        currentSuit = cards_[cardIndex].getSuit();
        if (previousSuit != currentSuit)
        {
            foundFlush = false;
            break;
        }
    }

    return foundFlush;
}


// Determines if current hand contains a four of a kind.
// Input : output to values of kickers.
// Output :  Returns true if hand contains a four of a kind.
bool Hand::containsFourOfAKind(vector<int>& kickers)
{
    if (cards_.size() < 4)
        return false;

    vector<int> foundKickers;
    int containsFour = false;
    int fourValue = 0;
    int currentCardVal = 0;
    int allCounts[NUMBER_OF_CARD_VALUES] = {0};

    // Increments card values using an array.
    for (int cardIndex = 0;cardIndex < cards_.size(); cardIndex++)
    {
        currentCardVal = cards_[cardIndex].getValue();
        allCounts[currentCardVal - 2]++;
        if (allCounts[currentCardVal - 2] == 4)
        {
            fourValue = currentCardVal;
            containsFour = true;
            break;
        }
    }

    // If there is a four of a kind, add the kickers
    if (containsFour)
    {
        for (int cardIndex = 0;cardIndex < NUMBER_OF_CARD_VALUES; cardIndex++)
        {
            currentCardVal = cards_[cardIndex].getValue();
            if (currentCardVal != fourValue)
            {
                foundKickers.push_back(currentCardVal);
                kickers = foundKickers;
                break;
            }
        }
    }

    return containsFour;

}

// Determines if current hand contains a full house.
// Input :
// Output :  Returns true if hand does contain a full house and false if not.
bool Hand::containsFullHouse()
{
    if (cards_.size() < 5)
        return false;

    bool containsThreePair = false;
    bool containsTwoPair = false;
    int currentCardVal = 0;

    int allCounts[NUMBER_OF_CARD_VALUES] = {0};
    // Increments card values using an array
    for (int cardIndex = 0;cardIndex < cards_.size(); cardIndex++)
    {
        currentCardVal = cards_[cardIndex].getValue();
        allCounts[currentCardVal - 2]++;
    }

    // Checks to see if we a have three of a kind and a two pair
    for (int cardIndex = 0;cardIndex < NUMBER_OF_CARD_VALUES; cardIndex++)
    {
            // Three of a kind
            if (allCounts[cardIndex] == 3)
            {
                containsThreePair = true;
            }

            // Two Pair
            if (allCounts[cardIndex] == 2)
            {
                containsTwoPair = true;
            }
    }

    return containsThreePair && containsTwoPair;

}

// Determines if current hand contains a three of a kind.
// Input : output to values of kickers.
// Output :  Returns true if hand contains a three of a kind and false if not.
bool Hand::containsThreeOfAKind(vector<int>& kickers)
{
    if (cards_.size() < 3)
        return false;

    vector<int> foundKickers;
    int containsThree = false;
    int threeValue = 0;
    int currentCardVal = 0;
    int allCounts[NUMBER_OF_CARD_VALUES] = {0};

    // Increments card values using an array
    for (int cardIndex = 0;cardIndex < cards_.size(); cardIndex++)
    {
        currentCardVal = cards_[cardIndex].getValue();
        allCounts[currentCardVal - 2]++;
        if (allCounts[currentCardVal - 2] == 3)
        {
            threeValue = currentCardVal;
            containsThree = true;
            break;
        }
    }

     // If there is a three of a kind
    if (containsThree)
    {
        for (int cardIndex = 0;cardIndex < NUMBER_OF_CARD_VALUES; cardIndex++)
        {
            currentCardVal = cards_[cardIndex].getValue();
            // Push kickers that are not the valid of the three of a kind
            if (currentCardVal != threeValue)
            {
                foundKickers.push_back(currentCardVal);
            }
        }
        kickers = foundKickers;
    }

    return containsThree;

}

// Determines if current hand contains a two pair.
// Input : output to values of kickers.
// Output :  Returns true if hand contains a two pair and false if not.
bool Hand::containsTwoPairs(vector<int>& kickers)
{
    if (cards_.size() < 4)
        return false;

    vector<int> foundKickers;
    vector<int> allPairs;
    int pairCount = 0;
    int currentCardVal = 0;
    int allCounts[NUMBER_OF_CARD_VALUES] = {0};

    // Increments card values in an array
    for (int cardIndex = 0;cardIndex < cards_.size(); cardIndex++)
    {
        currentCardVal = cards_[cardIndex].getValue();
        allCounts[currentCardVal - 2]++;
        if (allCounts[currentCardVal - 2] == 2)
        {
            pairCount++;
            allPairs.push_back(currentCardVal);
        }
    }

    // If there are pairs
    if (pairCount >= 2)
    {
        for (int cardIndex = 0;cardIndex < NUMBER_OF_CARD_VALUES; cardIndex++)
        {
            currentCardVal = cards_[cardIndex].getValue();
            // If the current value is not equal to any of the pairs
            if (currentCardVal != allPairs[0] &&
                currentCardVal != allPairs[1])
            {
                foundKickers.push_back(currentCardVal);
                break;
            }
        }
        kickers = foundKickers;
    }

    return pairCount >= 2;
}

// Determines if current hand contains a pair.
// Input : output to values of kickers.
// Output :  Returns true if hand contains a pair and false if not.
bool Hand::containsAPairs(vector<int>& kickers)
{
    if (cards_.size() < 2)
        return false;

    vector<int> foundKickers;
    int pairValue = 0;;
    int currentCardVal = 0;
    int allCounts[NUMBER_OF_CARD_VALUES] = {0};

    // Increments card values using an array
    for (int cardIndex = 0;cardIndex < cards_.size(); cardIndex++)
    {
        currentCardVal = cards_[cardIndex].getValue();
        allCounts[currentCardVal - 2]++;
        if (allCounts[currentCardVal - 2] == 2)
        {
            pairValue = currentCardVal;
            break;
        }
    }

    // We have a pair
    if (pairValue != 0)
    {
        for (int cardIndex = 0;cardIndex < NUMBER_OF_CARD_VALUES; cardIndex++)
        {
            currentCardVal = cards_[cardIndex].getValue();

            // Add values that do not equal the pair
            if (currentCardVal != pairValue)
            {
                foundKickers.push_back(currentCardVal);
            }
        }
        kickers = foundKickers;
    }


    return pairValue != 0;
}

// Determines if the category of the current hand
// Input :
// Output :  Returns the rank of the hand and its kickers
Hand::RankAndKickers Hand::getBestFiveHandCategory()
{
    RankAndKickers temp;
    temp.bestRank = NO_RANK;

    if (cards_.size() != 5)
    {
        cout << "Error in getBestFiveHandCategory(), received only " << cards_.size() << " cards" << endl;
        return temp;
    }

    int highestStraight = -1;
    int numKickers = 0;
    bool foundStraight = containsStraight(highestStraight);
    bool foundFlush = containsFlush();
    vector <int> kickers;

    RankAndKickers retRankAndKickers;

    // Check the return value
    if ( foundFlush && (highestStraight == 14) )
    {
        retRankAndKickers.bestRank = ROYAL_FLUSH;
    }
    else if ( foundFlush && (foundStraight))
    {
        retRankAndKickers.bestRank = STRAIGHT_FLUSH;
    }
    else if (containsFourOfAKind(kickers))
    {
        retRankAndKickers.bestRank = FOUR_OF_A_KIND;
        retRankAndKickers.kickers = kickers;
    }
    else if (containsFullHouse())
    {
        retRankAndKickers.bestRank = FULL_HOUSE;
    }
    else if (foundFlush)
    {
        retRankAndKickers.bestRank = FLUSH;
    }
    else if (foundStraight)
    {
        retRankAndKickers.bestRank = STRAIGHT;
    }
    else if (containsThreeOfAKind(kickers))
    {
        retRankAndKickers.bestRank = THREE_OF_A_KIND;
        retRankAndKickers.kickers = kickers;
    }
    else if (containsTwoPairs(kickers))
    {
        retRankAndKickers.bestRank = TWO_PAIR;
        retRankAndKickers.kickers = kickers;
    }
    else if (containsAPairs(kickers))
    {
        retRankAndKickers.bestRank = ONE_PAIR;
        retRankAndKickers.kickers = kickers;
    }
    else
    {
        retRankAndKickers.bestRank = HIGH_CARD;
        // Add all kickers
        for (int cardIndex = 0;cardIndex < cards_.size();cardIndex++)
        {
            retRankAndKickers.kickers.push_back(cards_[cardIndex].getValue());
        }
    }

    return retRankAndKickers;

}

// Determines if there is a straight
// Input : List of cards
// Output :  Returns the highest straight value
int Hand::findStraight(const vector<Card>& cards)
{

    if (cards.size() < 5)
        return -1;

    int previousValue = cards[0].getValue();
    int highestVal = cards[0].getValue();
    int currentValue = 0;
    int consecutiveCount = 1;
    // The cards are sorted, so we just
    // need to find the sequential ones
    for (int cardIndex = 1;cardIndex < cards.size(); cardIndex++)
    {
        currentValue = cards[cardIndex].getValue();

        if ( currentValue == (previousValue - 1))
        {
            consecutiveCount++;
        }
        else
        {
            highestVal = currentValue;
            consecutiveCount = 1;
        }


        // Found straight, return highest value
        if (consecutiveCount == 5)
        {
            return highestVal;
        }

        previousValue = currentValue;
    }

    return -1;


}

// Determines if hand contains a straight flush
// Input : vector of clubs,spades,hearts,diamonds. output of highest straight value and best suit
// For the retSuit value, 1 means the best is clubs, 2 means spades, 3 means hearts, and 4 means diamonds
// Output :  Returns true if hand contains a straight flush
bool Hand::containsStraightFlush(vector<Card>& clubs,
                                 vector<Card>& spades,
                                 vector<Card>& hearts,
                                 vector<Card>& diamonds,
                                 int& highestStraightValueOutput,
                                 int& retSuit)
{
    bool foundFlush = clubs.size() >= 5 || spades.size() >=5 || hearts.size() >= 5 || diamonds.size() >= 5;
    if (!foundFlush)
        return false;

    int highestStraightVal = 0;
    int eachSuitStraight = 0;
    int whichSuit = 0;

    // Gets the highest straight for all Suits
    eachSuitStraight = findStraight(clubs);
    if (eachSuitStraight > highestStraightVal)
	{
		highestStraightVal = eachSuitStraight;
        whichSuit = 1;
	}

    eachSuitStraight = findStraight(spades);
    if (eachSuitStraight > highestStraightVal)
	{
		highestStraightVal = eachSuitStraight;
		whichSuit = 2;
	}

    eachSuitStraight = findStraight(hearts);
    if (eachSuitStraight > highestStraightVal)
	{
		highestStraightVal = eachSuitStraight;
		whichSuit = 3;
	}

    eachSuitStraight = findStraight(diamonds);
    if (eachSuitStraight > highestStraightVal)
	{
		highestStraightVal = eachSuitStraight;
		whichSuit = 4;
	}

	highestStraightValueOutput = highestStraightVal;
    retSuit = whichSuit;

	return (highestStraightVal != -1);

}

// Determines the value of the hand
// Input : vector of cards and the max index
// Output :  Returns the value of the hand
int Hand::getHandValue(vector<Card> cards, int maxIndex)
{
    int totalValue = 0;

    for (int cardIndex = 0;cardIndex < 5; cardIndex++)
    {
        // Add the nth bit
        totalValue |= (1 << cards[cardIndex].getValue());
    }

    return totalValue;
}

// Determines the best 5 card hand, given a five or more card hand
// Input :
// Output :  Returns the best 5 card hand.
vector<Card> Hand::getBestHand()
{
    vector<Card> cardCount[NUMBER_OF_CARD_VALUES];
    vector<Card> clubs;
    vector<Card> spades;
    vector<Card> hearts;
    vector<Card> diamonds;

    Card currentCard;
    for (unsigned cardIndex = 0; cardIndex < cards_.size(); cardIndex++)
    {
        currentCard = cards_[cardIndex];

        if ( (currentCard.getValue() == -1) ||
             (currentCard.getSuit() < Card::Club &&
              currentCard.getSuit() > Card::Diamond) )
        {
            //cout << allCards[cardIndex] << endl;/
            cout << "Error, received an invalid card" << endl;
            continue;
        }

        // Smallest value is 2,
        // align it to the start of the array
        cardCount[currentCard.getValue() - 2].push_back(currentCard);

        if (currentCard.getSuit() == Card::Club)
            clubs.push_back(currentCard);
        else if (currentCard.getSuit() == Card::Spade)
            spades.push_back(currentCard);
        else if (currentCard.getSuit() == Card::Heart)
            hearts.push_back(currentCard);
        else if (currentCard.getSuit() == Card::Diamond)
            diamonds.push_back(currentCard);
        else
        {
            cout << "Error, got invalid suit" << endl;
        }

    }

    sort(clubs.begin(), clubs.end(), Card::less_than_value());
    sort(spades.begin(), spades.end(), Card::less_than_value());
    sort(hearts.begin(), hearts.end(), Card::less_than_value());
    sort(diamonds.begin(), diamonds.end(), Card::less_than_value());

    vector <int> allPairs;
    int threeOfAKindValue = -1;
    int fourOfAKindValue = -1;
    int cardValue = 0;
    int maxValue = currentCard.getValue();
    for (int valueIndex = 0; valueIndex < NUMBER_OF_CARD_VALUES;valueIndex++)
    {
        cardValue = valueIndex + 2;
        if (cardCount[valueIndex].size() == 2)
        {
            allPairs.push_back(cardValue);
        }

        if (cardCount[valueIndex].size() == 3)
        {
            threeOfAKindValue = cardValue;
        }

        if (cardCount[valueIndex].size() == 4)
        {
            fourOfAKindValue = cardValue;
        }

        if (cardValue > maxValue)
            maxValue = cardValue;
    }

    bool foundFlush = clubs.size() >= 5 || spades.size() >=5 || hearts.size() >= 5 || diamonds.size() >= 5;

    int bestStraightFlush = 0;
    int highestStraightVal = -1;
    int bestSuit = 0;

    bool foundStraightFlush = containsStraightFlush(clubs, spades, hearts, diamonds, highestStraightVal, bestSuit);

    // A royal flush is essentially a straight flush....
    vector<Card> bestHand;
    // Royal flush
    if (foundStraightFlush)
    {
        vector<Card> bestSuitVect;
        // The suits are sorted already
        if (bestSuit == 1)
        {
            bestSuitVect = clubs;
        }
        else if (bestSuit == 2)
        {
            bestSuitVect = spades;
        }
        else if (bestSuit == 3)
        {
            bestSuitVect = hearts;
        }
        else if (bestSuit == 4)
        {
            bestSuitVect = diamonds;
        }
        else
        {
            cout << "Error" << endl;
        }

         // Making sure we don't go out of bounds
            for (int index = 0;index < bestSuitVect.size();index++)
            {
                bestHand.push_back(bestSuitVect[index]);
                if(index == 4)
                    break;
            }
    }

    // Four of a kind
    else if (fourOfAKindValue != -1)
    {

    }
    // Full house
    else if ( (threeOfAKindValue != -1) && (allPairs.size() >= 1) )
    {

    }
    // Flush
    else if ( foundFlush )
    {
        // We need to find the BEST flush by
        // basically summing the bits of the numbers
        int bestVal = 0;
        int eachVal = 0;

        eachVal = getHandValue(clubs, 5);
        if (eachVal > bestVal)
        {
            bestVal = eachVal;
            bestSuit = 1;
        }

        eachVal = getHandValue(spades, 5);
        if (eachVal > bestVal)
        {
            bestVal = eachVal;
            bestSuit = 2;
        }

        eachVal = getHandValue(hearts, 5);
        if (eachVal > bestVal)
        {
            bestVal = eachVal;
            bestSuit = 3;
        }

        eachVal = getHandValue(diamonds, 5);
        if (eachVal > bestVal)
        {
            bestVal = eachVal;
            bestVal = eachVal;
            bestSuit = 4;
        }

        vector<Card> bestSuitVect;
        // The suits are sorted already
        if (bestSuit == 1)
        {
            bestSuitVect = clubs;
        }
        else if (bestSuit == 2)
        {
            bestSuitVect = spades;
        }
        else if (bestSuit == 3)
        {
            bestSuitVect = hearts;
        }
        else if (bestSuit == 4)
        {
            bestSuitVect = diamonds;
        }
        else
        {
            cout << "Error" << endl;
        }

         // Making sure we don't go out of bounds
            for (int index = 0;index < bestSuitVect.size();index++)
            {
                bestHand.push_back(bestSuitVect[index]);
                if(index == 4)
                    break;
            }
    }
    // For straight, loop through allCount and see if there is a sequential

    // For three of a kind, we have the threeOfAKindValue and we just need the two kickers by looping cardCount to find kicker.

    // For two pair, we have that stored in allPairs. Get the highest pairs. Loop cardCount to find kicker.

    // For one pair, we have that stored in allPairs. Get the highest pair.  Loop cardCount to find kicker.

    // High card loop cardCount and get top 5 cards.

    return bestHand;

}

// Determines the string of the value (10 = J)
// Input : The card value
// Output :  Returns the string representation of the card value
string Hand::cardValueToString (int cardValue)
{
          switch (cardValue)
            {
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
                return to_string(cardValue);
                break;
            case 11:
                return "J";
                break;
            case 12:
                return "Q";
                break;
            case 13:
                return "K";
                break;
            case 14:
                return "A";
                break;
            default:
                return "Invalid";
                break;
            }
}

// Prints the category of the 5 card hand
// Input :
// Output :  None, just prints
void Hand::printFiveHandCategory()
{
    //vector<Card> allCards = getVectOfCards(fiveCardHand);

    for (unsigned int index = 0;index < cards_.size();index++)
    {
        //cout << "card = (" << allCards[index] << ")" << endl;
        cout << "Card value = " << cards_[index].getValue() << ", type = " << cards_[index].getSuit() << endl;
    }

    RankAndKickers best = getBestFiveHandCategory();
    vector<int> kickers = best.kickers;
    Rank bestRank = best.bestRank;

    if (bestRank == ROYAL_FLUSH)
    {
        cout << "Found royal flush!" << endl;
    }
    else if (bestRank == STRAIGHT_FLUSH)
    {
        cout << "Found straight flush!" << endl;
    }
    else if (bestRank == FOUR_OF_A_KIND)
    {
        cout << "Found four of a kind with kicker " << kickers.front() << endl;
    }
    else if (bestRank == FULL_HOUSE)
    {
        cout << "Found full house!" << endl;
    }
    else if (bestRank == FLUSH)
    {
        cout << "Found flush!" << endl;
    }
    else if (bestRank == STRAIGHT)
    {
        cout << "Found straight!" << endl;
    }
    else if (bestRank == THREE_OF_A_KIND)
    {
        cout << "Found three of a kind with kickers " << kickers[0] << " and " << kickers[1] << endl;
    }
    else if (bestRank == TWO_PAIR)
    {
        cout << "Found two pair with kicker " << kickers[0] << endl;
    }
    else if (bestRank == ONE_PAIR)
    {
        cout << "Found one pair with kickers " << cardValueToString(kickers[0]) <<
        ", " << cardValueToString(kickers[1]) << ", " << cardValueToString(kickers[2]) << endl;
    }
    else if (bestRank == HIGH_CARD)
    {
        cout << "High card with values " << cardValueToString(kickers[0]) <<
        ", " << cardValueToString(kickers[1]) << ", " <<
                cardValueToString(kickers[2]) << ", " <<
                cardValueToString(kickers[3]) << ", " <<
                cardValueToString(kickers[4]) << endl;
    }
    else if (bestRank == NO_RANK)
    {
        cout << "Error - Looks like the rank was not set!" << endl;
    }
    else
    {
        cout << "Error - Found unknown rank" << endl;
    }

}

// Determines the value of the hand
// Input :
// Output :  Returns the hand value of the current hand
int Hand::getHandValue()
{
    RankAndKickers best = getBestFiveHandCategory();
    vector<int> kickers = best.kickers;
    Rank bestRank = best.bestRank;
    int cardSumValue = 0;
    int kickersBitsSum = 0;

    // The logic below is to add
    // the rank to an integer and then
    // add the bits set by each kicker
    if (bestRank == ROYAL_FLUSH)
    {
        cardSumValue += 11*RANK_MULTIPLIER;
        cout << "Found royal flush!" << endl;
    }
    else if (bestRank == STRAIGHT_FLUSH)
    {
        cardSumValue += 10*RANK_MULTIPLIER;
        cout << "Found straight flush!" << endl;
    }
    else if (bestRank == FOUR_OF_A_KIND)
    {
        cardSumValue += 9*RANK_MULTIPLIER;
        cout << "Found four of a kind with kicker " << kickers.front() << endl;
    }
    else if (bestRank == FULL_HOUSE)
    {
        cardSumValue += 8*RANK_MULTIPLIER;
        cout << "Found full house!" << endl;
    }
    else if (bestRank == FLUSH)
    {
        cardSumValue += 7*RANK_MULTIPLIER;
        cout << "Found flush!" << endl;
    }
    else if (bestRank == STRAIGHT)
    {
        cardSumValue += 6*RANK_MULTIPLIER;
        cout << "Found straight!" << endl;
    }
    else if (bestRank == THREE_OF_A_KIND)
    {
        cardSumValue += 5*RANK_MULTIPLIER;
        if (kickers.size() != 2)
        {
             cout << "Error got three of a kind with kicker size = " << kickers.size() << endl;
        }
        else
        {
        cout << "Found three of a kind with kickers " << kickers[0] << " and " << kickers[1] << endl;
        }
    }
    else if (bestRank == TWO_PAIR)
    {
        cardSumValue += 4*RANK_MULTIPLIER;
        if (kickers.size() != 1)
        {
             cout << "Error got two pair with kicker size = " << kickers.size() << endl;
        }
        else
        {
            cout << "Found two pair with kicker " << kickers[0] << endl;
        }
    }
    else if (bestRank == ONE_PAIR)
    {
        cardSumValue += 3*RANK_MULTIPLIER;
        if (kickers.size() != 3)
        {
             cout << "Error got one pair with kicker size = " << kickers.size() << endl;
        }
        else
        {

            cout << "Found one pair with kickers " << cardValueToString(kickers[0]) <<
            ", " << cardValueToString(kickers[1]) << ", " << cardValueToString(kickers[2]) << endl;
            }
    }
    else if (bestRank == HIGH_CARD)
    {
        if (kickers.size() != 5)
        {
             cout << "Error got high card with kicker size = " << kickers.size() << endl;
        }
        else
        {
            cout << "High card with values " << cardValueToString(kickers[0]) <<
            ", " << cardValueToString(kickers[1]) << ", " <<
                    cardValueToString(kickers[2]) << ", " <<
                    cardValueToString(kickers[3]) << ", " <<
                    cardValueToString(kickers[4]) << endl;
        }
    }
    else if (bestRank == NO_RANK)
    {
        cout << "Error - Looks like the rank was not set!" << endl;
        return 0;
    }
    else
    {
        cout << "Error in getHandValue() - Found unknown rank" << endl;
        return 0;
    }

    for (int kickerIndex = 0; kickerIndex < kickers.size();kickerIndex++)
    {
        kickersBitsSum |= (1 << kickers[kickerIndex]);
    }

    cardSumValue += kickersBitsSum;

    return cardSumValue;

}

// Prints the values and suits of the current hand
// Input :
// Output :
void Hand::printHand()
{
    for (int cardIndex = 0; cardIndex < cards_.size();cardIndex++)
    {
        cout << "Card at index = " << cardIndex << " = " << cards_[cardIndex].getString() << endl;
    }


}



// Prototype for performance below **************************************************
// Instead of having a multiple functions to check for certain categories,
// we could have processed all cards in one-go and figure out which rank it is.

/*
Hand::RankAndKickers Hand::getBestFiveHandCategory()
{
    RankAndKickers temp;
    temp.bestRank = NO_RANK;
    if (cards_.size() != 5)
    {
        cout << "Error in getBestFiveHandCategory(), received only " << cards_.size() << " cards" << endl;
        return temp;
    }

    int cardCount[NUMBER_OF_CARD_VALUES] = {0};
    Card currentCard = cards_[0];
    cardCount[currentCard.getValue() - 2]++;

    bool flushFound = cards_.size() >= 5 ? true: false;

    Card::Suit lastType = currentCard.getSuit();
    int maxValue = currentCard.getValue();
    int highestPair = -1;

    int threeOfAKindValue = -1;
    int fourOfAKindValue = -1;

    vector <int> allPairs;

    for (unsigned cardIndex = 1; cardIndex < cards_.size(); cardIndex++)
    {
        currentCard = cards_[cardIndex];

        if ( (currentCard.getValue() == -1) ||
             (currentCard.getSuit() < Card::Club &&
              currentCard.getSuit() > Card::Diamond) )
        {
            //cout << allCards[cardIndex] << endl;/
            cout << "Error, received an invalid card" << endl;
            continue;
        }

        // Smallest value is 2,
        // align it to the start of the array
        cardCount[currentCard.getValue() - 2]++;


    }

    int cardValue = 0;
    for (int valueIndex = 0; valueIndex < NUMBER_OF_CARD_VALUES;valueIndex++)
    {
        cardValue = valueIndex + 2;
        if (cardCount[valueIndex] == 2)
        {
            allPairs.push_back(cardValue);
        }

        if (cardCount[valueIndex] == 3)
        {
            threeOfAKindValue = cardValue;
        }

        if (cardCount[valueIndex] == 4)
        {
            fourOfAKindValue = cardValue;
        }

        if (cardValue > maxValue)
            maxValue = cardValue;

    }

    int highestStraight = -1;
    int maxIndex = maxValue - 2;
    bool straightFound = findStraight(cardCount, highestStraight, maxIndex);
    int kickers = 0;

    RankAndKickers retRankAndKickers;
    retRankAndKickers.bestRank = NO_RANK;

    if ( flushFound && straightFound && (highestStraight == 14) )
    {
        retRankAndKickers.bestRank = ROYAL_FLUSH;
    }
    else if ( flushFound && straightFound )
    {
        retRankAndKickers.bestRank = STRAIGHT_FLUSH;
    }
    else if (fourOfAKindValue != -1)
    {
        retRankAndKickers.bestRank = FOUR_OF_A_KIND;
    }
    else if ((threeOfAKindValue != -1) &&
             (allPairs.size() > 1) )
    {
        retRankAndKickers.bestRank = FULL_HOUSE;
    }
    else if (flushFound)
    {
        retRankAndKickers.bestRank = FLUSH;
    }
    else if (straightFound)
    {
        retRankAndKickers.bestRank = STRAIGHT;
    }
    else if (threeOfAKindValue != -1)
    {
        retRankAndKickers.bestRank = THREE_OF_A_KIND;

        kickers = 2;

        while ( (kickers > 0) && (maxIndex >=0) )
        {
            if ( ((maxIndex + 2) != threeOfAKindValue) &&
                  (cardCount[maxIndex] > 0) )
            {

                cout << "kicker = " << (maxIndex + 2) << " ";
                retRankAndKickers.kickers.push_back((maxIndex + 2));
                kickers--;
            }
            maxIndex--;
        }

    }
    else if (allPairs.size() == 2)
    {
        retRankAndKickers.bestRank = TWO_PAIR;
        cout << "Found two pairs" << endl;

        kickers = 1;


       while ( (kickers > 0) && (maxIndex >=0) )
        {
            if ( ((maxIndex + 2) != allPairs[0]) &&
                 ((maxIndex + 2) != allPairs[1]) &&
                  (cardCount[maxIndex] > 0) )
            {

                cout << "kicker = " << (maxIndex + 2) << " ";
                retRankAndKickers.kickers.push_back((maxIndex + 2));
                kickers--;
            }
            maxIndex--;
        }

    }
    else if (allPairs.size() == 1)
    {
        retRankAndKickers.bestRank = ONE_PAIR;
        cout << "Found a pair with value = " << allPairs.front() << endl;

        kickers = 3;

        while ( (kickers > 0) && (maxIndex >=0) )
        {
            if ( ((maxIndex + 2) != allPairs[0]) &&
                  (cardCount[maxIndex] > 0) )
            {

                cout << "kicker = " << (maxIndex + 2) << " ";
                retRankAndKickers.kickers.push_back((maxIndex + 2));
                kickers--;
            }
            maxIndex--;
        }
    }
    else
    {
        retRankAndKickers.bestRank = HIGH_CARD;
        cout << "Found no categories" << endl;
        kickers = 5;



        while ( (kickers > 0) && (maxIndex >=0) )
        {
            if ( (cardCount[maxIndex] > 0) )
            {

                cout << "kicker = " << (maxIndex + 2) << " ";
                retRankAndKickers.kickers.push_back((maxIndex + 2));
                kickers--;
            }
            maxIndex--;
        }

    }



        cout << endl;


        return retRankAndKickers;

}

*/
