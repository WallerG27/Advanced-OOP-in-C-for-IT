#pragma once
#include <string>
using namespace System;

namespace CppCLRWinFormsProject
{
    public ref class aCandlestick
    {
    public:
        // IMPORTANT: These MUST be marked as 'property' for Windows Forms DataBinding to recognize them!
        
        property System::DateTime Date;
        property double Open;
        property double High;
        property double Low;
        property double Close;
        property unsigned long Volume;

        /// <summary>
        /// Constructs an aCandlestick object representing an 
        /// OHLCV candlestick for a specific date/time.
        /// </summary>
        aCandlestick(DateTime d, double o, double h, double l, double c, unsigned long v);
    };
}