#pragma once
#include <string>
using namespace System;

namespace CppCLRWinFormsProject
{
    public ref class aCandlestick
    {
    public:
        /// <summary>
        /// Declares a DateTime variable named Date that stores a date and time value.
        /// </summary>
        System::DateTime Date;
        double Open;
        double High;
        double Low;
        double Close;
        unsigned long Volume;

        /// <summary>
        /// Constructs an aCandlestick object representing an 
        /// OHLCV candlestick for a specific date/time.
        /// </summary>
        /// <param name="d">The date and time of the candlestick (timestamp).</param>
        /// <param name="o">The opening price/value for the period.</param>
        /// <param name="h">The highest price/value for the period.</param>
        /// <param name="l">The lowest price/value for the period.</param>
        /// <param name="c">The closing price/value for the period.</param>
        /// <param name="v">The volume (or trade count) for the period.</param>
        aCandlestick(DateTime d, double o, double h, double l, double c, unsigned long v);
    };
}