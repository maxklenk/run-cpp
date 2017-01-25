
#include "ISBN.h"


//
// Begin legacy template solution - re-engineer this using constexpr
//

template <bool Condition, unsigned int, unsigned int>
struct selection;

template <unsigned int TrueValue, unsigned int FalseValue>
struct selection<true, TrueValue, FalseValue> {
    static const unsigned int value = TrueValue;
};

template <unsigned int TrueValue, unsigned int FalseValue>
struct selection<false, TrueValue, FalseValue> {
    static const unsigned int value = FalseValue;
};

template <unsigned int Number, char NextDigit>
struct appendDigit
{
    static const unsigned int value = Number * 10 + (NextDigit - '0');
};

template <char Digit>
struct isDigit
{
    static const bool value = (Digit >= '0' && Digit <= '9');
};

template<unsigned int prefix, unsigned int group, unsigned int registrant, unsigned int publication, unsigned int checksum>
struct ISBNResult
{
    enum {
        Prefix = prefix,
        Group = group,
        Registrant = registrant,
        Publication = publication,
        Checksum = checksum
    };
};

template<unsigned int prefix, unsigned int group, unsigned int registrant, unsigned int publication, unsigned int checksum, unsigned int state, char... Chars>
struct ISBNParser;

template<unsigned int prefix, unsigned int group, unsigned int registrant, unsigned int publication, unsigned int checksum>
struct ISBNParser<prefix, group, registrant, publication, checksum, 4> : public ISBNResult<prefix, group, registrant, publication, checksum> {};
    
template<unsigned int prefix, unsigned int group, unsigned int registrant, unsigned int publication, unsigned int checksum>
struct ISBNParser<prefix, group, registrant, publication, checksum, 3> : public ISBNResult<0, prefix, group, registrant, publication> {};

template<unsigned int prefix, unsigned int group, unsigned int registrant, unsigned int publication, unsigned int checksum, unsigned int state, char Current, char... Chars>
struct ISBNParser<prefix, group, registrant, publication, checksum, state, Current, Chars...> : public ISBNParser<
    selection<state == 0 && isDigit<Current>::value, appendDigit<prefix, Current>::value, prefix>::value,
    selection<state == 1 && isDigit<Current>::value, appendDigit<group, Current>::value, group>::value,
    selection<state == 2 && isDigit<Current>::value, appendDigit<registrant, Current>::value, registrant>::value,
    selection<state == 3 && isDigit<Current>::value, appendDigit<publication, Current>::value, publication>::value,
    selection<state == 4 && isDigit<Current>::value, appendDigit<checksum, Current>::value, checksum>::value,
    selection<Current == '\'', state+1, state>::value,
    Chars...
> {};
    
template<unsigned int prefix, unsigned int group, unsigned int registrant, unsigned int publication, unsigned int checksum>
struct ISBNInstantiator
{
    constexpr static ISBN create()
    {
        return ISBN(prefix, group, registrant, publication, checksum);
    }
};

template<unsigned int group, unsigned int registrant, unsigned int publication, unsigned int checksum>
struct ISBNInstantiator<0, group, registrant, publication, checksum>
{
    constexpr static ISBN create()
    {
        return ISBN(group, registrant, publication, checksum);
    }
};

template <char... Chars>
constexpr ISBN operator "" _isbn()
{
    using Result = ISBNParser<0, 0, 0, 0, 0, 0, Chars...>;
    return ISBNInstantiator<Result::Prefix, Result::Group, Result::Registrant, Result::Publication, Result::Checksum>::create();
}


//
// End legacy template solution
//




//
// Test case
// 

int main(int argc, char * argv[])
{
    // using template solution, comment this out...
    constexpr auto isbn13 = 978'4873'113'68'5_isbn;
    constexpr auto isbn10 = 4873'113'68'5_isbn;

    // ... and replace with this
    //constexpr auto isbn13 = "978'4873'113'68'5"_isbn;
    //constexpr auto isbn10 = "4873'113'68'5"_isbn;
    
    isbn13.print();
    isbn10.print();
    
    return 0;
}
