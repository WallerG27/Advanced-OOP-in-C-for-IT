#pragma once
#include "aRecognizer.h"

namespace CppCLRWinFormsProject
{
    /// <summary>
    /// Recognizer for the Three White Soldiers pattern
    /// </summary>
    public ref class recognizer_White_Soldier : public aRecognizer
    {
    public:
        // Three White Soldiers is a 3 candlestick pattern
        recognizer_White_Soldier() : aRecognizer("Three White Soldiers", 3) {}

        virtual bool match(int currentIndex, List<aSmartCandlestick^>^ lsc) override
        {
            // Safety check for 3 candlesticks
            if (currentIndex < 2) return false;

            aSmartCandlestick^ c1 = lsc[currentIndex - 2];
            aSmartCandlestick^ c2 = lsc[currentIndex - 1];
            aSmartCandlestick^ c3 = lsc[currentIndex];

            // 1. All the candlesticks must be Bullish.
            if (!c1->isBullish || !c2->isBullish || !c3->isBullish)
                return false;

            // 2. The low of each candlestick (except the first one) must be within the body of the previous candlestick.
            if (!(c2->Low <= c1->bodyHigh && c2->Low >= c1->bodyLow)) return false;
            if (!(c3->Low <= c2->bodyHigh && c3->Low >= c2->bodyLow)) return false;

            // 3. The open of each candlestick (except the first one) must be within the body of the previous candlestick.
            if (!(c2->Open <= c1->bodyHigh && c2->Open >= c1->bodyLow)) return false;
            if (!(c3->Open <= c2->bodyHigh && c3->Open >= c2->bodyLow)) return false;

            // 4. The close of each candlestick (except the first one) must be above the high of the previous candlestick.
            if (!(c2->Close > c1->High)) return false;
            if (!(c3->Close > c2->High)) return false;

            return true;
        }
    };
}

