#define __USE_MINGW_ANSI_STDIO 0

#include <string>

using namespace std;


class Card
{
    friend class UnitTester;
    public:
        enum Suit
        {
        Club,
        Spade,
        Heart,
        Diamond,
        None
        };

        Card();
        Card(int value, Suit suit);
        virtual ~Card();
        int getValue() const;
        Card::Suit getSuit() const;
        void setValue(int value);
        void setSuit(Card::Suit suit);
        string getString();

        struct less_than_value
        {
            inline bool operator() (const Card& left, const Card& right)
            {
                return left.getValue() > right.getValue();
            }
        };

    private:
        int value_;
        Suit suit_;
        string cardValueToString ();
        string cardSuitToString();
};
