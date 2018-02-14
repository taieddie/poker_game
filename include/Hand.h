#include "Card.h"
#include <vector>
#include <string>

using namespace std;

class Hand
{
        friend class UnitTester;
        enum Rank
        {
        ROYAL_FLUSH,
        STRAIGHT_FLUSH,
        FOUR_OF_A_KIND,
        FULL_HOUSE,
        FLUSH,
        STRAIGHT,
        THREE_OF_A_KIND,
        TWO_PAIR,
        ONE_PAIR,
        HIGH_CARD,
        NO_RANK
        };

        typedef struct RankAndKickers
        {
            Rank bestRank;
            vector<int> kickers;
        } RankAndKickers;


        const int NUMBER_OF_CARD_VALUES = 13;
        const int RANK_MULTIPLIER = 10000000;

    public:
        Hand(vector<Card> cards);
        Hand();
        void printHand();
        int getHandValue();
        vector<Card> getBestHand();
        RankAndKickers getBestFiveHandCategory();
        void printFiveHandCategory();
        string cardValueToString (int cardValue);
        virtual ~Hand();

    protected:

    private:
        vector<Card> cards_;
        int findStraight(const vector<Card>& cards);
        bool findStraight (int cardCount[], int& outHighestStraight, int maxIndex);
        bool containsStraight(int& highestStraightOut);
        bool containsFlush();
        bool containsFourOfAKind(vector<int>& kickers);
        bool containsFullHouse();
        bool containsThreeOfAKind(vector<int>& kickers);
        bool containsTwoPairs(vector<int>& kickers);
        bool containsAPairs(vector<int>& kickers);
        bool containsStraightFlush(vector<Card>& clubs,
                                   vector<Card>& spades,
                                   vector<Card>& hearts,
                                   vector<Card>& diamonds,
                                   int& highestStraightValueOutput,
                                   int& retSuit);
        int getHandValue(vector<Card> cards, int maxIndex);
};


