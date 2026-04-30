#pragma once
#include "aCandlestick.h"
#include <cmath>
#include <algorithm> // Required for std::max and std::min

using namespace System;
using namespace System::Collections::Generic;

namespace CppCLRWinFormsProject
{
    public ref class aSmartCandlestick : public aCandlestick
    {
    public:
        // Properties for the smart candlestick
        property double range;
        property double bodyRange;
        property double upperRange;
        property double lowerRange;
        property double bodyHigh;
        property double bodyLow;
        property bool isBullish; // Bullush is green candlesticks, market goes up
        property bool isBearish; // Bearish is red candlesticks, market goes down 

        /// <summary>
        /// Default constructor
        /// Passes dummy/zero values to the base aCandlestick constructor since it doesn't have an empty one.
        /// </summary>
        aSmartCandlestick() 
            : aCandlestick(System::DateTime::MinValue, 0.0, 0.0, 0.0, 0.0, 0)
        {
            calculateRange();
        }

        /// <summary>
        /// Copy constructor from base class
        /// </summary>
        aSmartCandlestick(aCandlestick^ sourceCandlestick) 
            : aCandlestick(
                sourceCandlestick->Date, 
                sourceCandlestick->Open, 
                sourceCandlestick->High, 
                sourceCandlestick->Low, 
                sourceCandlestick->Close, 
                sourceCandlestick->Volume)
        {
            calculateRange();
        }

        /// <summary>
        /// Standard constructor passing individual values
        /// </summary>
        aSmartCandlestick(System::DateTime d, double o, double h, double l, double c, unsigned long v)
            : aCandlestick(d, o, h, l, c, v) // Pass all required arguments up to the base class
        {
            calculateRange();
        }

        /// <summary>
        /// Copy constructor from another aSmartCandlestick
        /// </summary>
        aSmartCandlestick(aSmartCandlestick^ sourceSmartCandlestick)
            : aCandlestick(
                sourceSmartCandlestick->Date,
                sourceSmartCandlestick->Open,
                sourceSmartCandlestick->High,
                sourceSmartCandlestick->Low,
                sourceSmartCandlestick->Close,
                sourceSmartCandlestick->Volume)
        {
            // Note: We used the correctly capitalized base class properties (Date, Open, High, etc.)
            calculateRange();
        }

        void calculateRange()
        {
            // Use the properties inherited from aCandlestick (must be properly capitalized)
            range = High - Low;
            bodyRange = std::abs(Close - Open);
            bodyHigh = std::max(Open, Close);
            bodyLow = std::min(Open, Close);
            upperRange = High - bodyHigh;
            lowerRange = bodyLow - Low;
            isBullish = Close > Open;
            isBearish = Open > Close;
        }

        List<aSmartCandlestick^>^ convertToSmartCandlestick(List<aCandlestick^>^ candlesticks)
        {
            List<aSmartCandlestick^>^ smartCandlesticks = gcnew List<aSmartCandlestick^>();
            for each (aCandlestick^ c in candlesticks)
            {
                smartCandlesticks->Add(gcnew aSmartCandlestick(c));
            }
            return smartCandlesticks;
        }
    };
}

