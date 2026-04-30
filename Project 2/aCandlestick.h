#pragma once
#include <string>
using namespace System;

namespace CppCLRWinFormsProject
{
    public ref_class aCandlestick
    {
    public:
        // Properties MUST be capitalized (Date, Open, High...)
        property System::DateTime date;
        property double open;
        property double high;
        property double low;
        property double close;
        property unsigned long volume;
        // Constructors
        aCandlestick();
        aCandlestick(DateTime d, double o, double h, double l, double c, unsigned long v);
        aCandlestick(aCandlestick^ sourceCandlestick);
        aCandlestick(String^ fileLine);
       
        // Methods
        void data(String^ fileLine);
    };
}