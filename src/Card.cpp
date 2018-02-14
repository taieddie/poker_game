#include "Card.h"

Card::Card()
{
    value_ = -1;
    suit_ = None;
}

Card::Card(int value, Suit suit):value_(value),suit_(suit){}

Card::~Card()
{
    //dtor
}

// Getter for the card value
// Input :
// Output :  Returns card value
int Card::getValue() const
{
    return value_;
}

// Getter for the card suit
// Input :
// Output :  Returns card suit
Card::Suit Card::getSuit() const
{
    return suit_;
}

// Setter for the card value
// Input : A card value
// Output :
void Card::setValue(int value)
{
    value_ = value;
}

// Setter for the card suit
// Input : A card suit
// Output :
void Card::setSuit(Suit suit)
{
    suit_ = suit;
}

// Converts card value to string
// Input :
// Output : String representation of the card value
string Card::cardValueToString ()
{
          switch (value_)
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
                return to_string(value_);
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

// Returns the string representation of the card suit
// Input :
// Output : String representation of card suit
string Card::cardSuitToString()
{
    if (suit_ == Club)
    {
        return "C";
    }
    else if (suit_ == Spade)
    {
        return "S";
    }
    else if (suit_ == Heart)
    {
        return "H";
    }
    else if (suit_ == Diamond)
    {
        return "D";
    }
    return "Invalid Suit";
}

// Returns the string representation of the card
// Input :
// Output : String representation of the card
string Card::getString()
{
    return cardValueToString() + cardSuitToString();
}

