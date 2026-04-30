#pragma once
#include "aRecognizer.h"

namespace CppCLRWinFormsProject
{
    /// <summary>
    /// Recognizer for the Three Black Crows pattern
    /// </summary>
    public ref class recognizer_Black_Crow : public aRecognizer
    {
    public:
        // Three Black Crows is a 3 candlestick pattern
        recognizer_Black_Crow() : aRecognizer("Three Black Crows", 3) {}

        virtual bool match(int currentIndex, List<aSmartCandlestick^>^ lsc) override
        {
            // Safety check for 3 candlesticks
            if (currentIndex < 2) return false;

            aSmartCandlestick^ c1 = lsc[currentIndex - 2];
            aSmartCandlestick^ c2 = lsc[currentIndex - 1];
            aSmartCandlestick^ c3 = lsc[currentIndex];

            // 1. All the candlesticks must be Bearish.
            if (!c1->isBearish || !c2->isBearish || !c3->isBearish)
                return false;

            // 2. The high of each candlestick (except the first one) must be within the body of the previous candlestick.
            if (!(c2->High <= c1->bodyHigh && c2->High >= c1->bodyLow)) return false;
            if (!(c3->High <= c2->bodyHigh && c3->High >= c2->bodyLow)) return false;

            // 3. The open of each candlestick (except the first one) must be within the body of the previous candlestick.
            if (!(c2->Open <= c1->bodyHigh && c2->Open >= c1->bodyLow)) return false;
            if (!(c3->Open <= c2->bodyHigh && c3->Open >= c2->bodyLow)) return false;

            // 4. The close of each candlestick (except the first one) must be below the low of the previous candlestick.
            if (!(c2->Close < c1->Low)) return false;
            if (!(c3->Close < c2->Low)) return false;

            return true;
        }
    };
}

