#pragma once
#include <type_traits>

template < typename _Enum, _Enum beginVal, _Enum endVal>
class EnumIterator {
private:
    typedef typename std::underlying_type<_Enum>::type val_t;
    int val;

public:
    EnumIterator(const _Enum& e) : val(static_cast<val_t>(e)) {}
    EnumIterator() : val(static_cast<val_t>(beginVal)) {}

    bool  operator!=(const EnumIterator& i) { return val != i.val; }
    _Enum operator*() { return static_cast<_Enum>(val); }

    EnumIterator begin() { return *this; } //default ctor is good
    EnumIterator end() {
        static const EnumIterator endIter = ++EnumIterator(endVal); // cache it
        return endIter;
    }
    EnumIterator operator++() { ++val; return *this; }
};