#pragma once
#include "aRecognizer.h"

namespace CppCLRWinFormsProject
{
    /// <summary>
    /// Base recognizer for Harami patterns
    /// </summary>
    public ref class recognizer_Harami : public aRecognizer
    {
    public:
        // Harami is a 2 candlestick pattern
        recognizer_Harami() : aRecognizer("Harami Pattern", 2) {}

    protected:
        recognizer_Harami(String^ name, int size) : aRecognizer(name, size) {}

    public:
        virtual bool match(int currentIndex, List<aSmartCandlestick^>^ lsc) override
        {
            // Safety check
            if (currentIndex < 1) return false;

            aSmartCandlestick^ current = lsc[currentIndex];
            aSmartCandlestick^ previous = lsc[currentIndex - 1];

            // The body of the previous candlestick must be larger and completely contain the current body.
            bool containedAtTop = current->bodyHigh < previous->bodyHigh && current->bodyLow >= previous->bodyLow;
            bool containedAtBottom = current->bodyHigh <= previous->bodyHigh && current->bodyLow > previous->bodyLow;

            return containedAtTop || containedAtBottom;
        }
    };

    /// <summary>
    /// Recognizer for Bullish Harami
    /// </summary>
    public ref class recognizer_BullishHarami : public recognizer_Harami
    {
    public:
        recognizer_BullishHarami() : recognizer_Harami("Bullish Harami", 2) {}

        virtual bool match(int currentIndex, List<aSmartCandlestick^>^ lsc) override
        {
            if (!recognizer_Harami::match(currentIndex, lsc))
                return false;

            aSmartCandlestick^ current = lsc[currentIndex];
            aSmartCandlestick^ previous = lsc[currentIndex - 1];

            // Bullish Harami: previous is bearish, current is bullish
            return previous->isBearish && current->isBullish;
        }
    };

    /// <summary>
    /// Recognizer for Bearish Harami
    /// </summary>
    public ref class recognizer_BearishHarami : public recognizer_Harami
    {
    public:
        recognizer_BearishHarami() : recognizer_Harami("Bearish Harami", 2) {}

        virtual bool match(int currentIndex, List<aSmartCandlestick^>^ lsc) override
        {
            if (!recognizer_Harami::match(currentIndex, lsc))
                return false;

            aSmartCandlestick^ current = lsc[currentIndex];
            aSmartCandlestick^ previous = lsc[currentIndex - 1];

            // Bearish Harami: previous is bullish, current is bearish
            return previous->isBullish && current->isBearish;
        }
    };
}



