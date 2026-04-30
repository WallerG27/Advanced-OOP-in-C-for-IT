#pragma once
#include "aRecognizer.h"

namespace CppCLRWinFormsProject
{
    /// <summary>
    /// Base recognizer for Engulfing patterns
    /// </summary>
    public ref class recognizer_Engulfing : public aRecognizer
    {
    public:
        // Engulfing is a 2 candlestick pattern
        recognizer_Engulfing() : aRecognizer("Engulfing Pattern", 2) {}

    protected:
        recognizer_Engulfing(String^ name, int size) : aRecognizer(name, size) {}

    public:
        virtual bool match(int currentIndex, List<aSmartCandlestick^>^ lsc) override
        {
            // Safety check
            if (currentIndex < 1) return false;

            aSmartCandlestick^ current = lsc[currentIndex];
            aSmartCandlestick^ previous = lsc[currentIndex - 1];

            // The body of the current candlestick must be larger and completely engulf the previous body.
            // Using slightly loose equals on one side, but it must be strictly larger on the other.
            bool engulfsAtTop = current->bodyHigh > previous->bodyHigh && current->bodyLow <= previous->bodyLow;
            bool engulfsAtBottom = current->bodyHigh >= previous->bodyHigh && current->bodyLow < previous->bodyLow;

            return engulfsAtTop || engulfsAtBottom;
        }
    };

    /// <summary>
    /// Recognizer for Bullish Engulfing
    /// </summary>
    public ref class recognizer_BullishEngulfing : public recognizer_Engulfing
    {
    public:
        recognizer_BullishEngulfing() : recognizer_Engulfing("Bullish Engulfing", 2) {}

        virtual bool match(int currentIndex, List<aSmartCandlestick^>^ lsc) override
        {
            if (!recognizer_Engulfing::match(currentIndex, lsc))
                return false;

            aSmartCandlestick^ current = lsc[currentIndex];
            aSmartCandlestick^ previous = lsc[currentIndex - 1];

            // Bullish Engulfing: previous is bearish, current is bullish
            return previous->isBearish && current->isBullish;
        }
    };

    /// <summary>
    /// Recognizer for Bearish Engulfing
    /// </summary>
    public ref class recognizer_BearishEngulfing : public recognizer_Engulfing
    {
    public:
        recognizer_BearishEngulfing() : recognizer_Engulfing("Bearish Engulfing", 2) {}

        virtual bool match(int currentIndex, List<aSmartCandlestick^>^ lsc) override
        {
            if (!recognizer_Engulfing::match(currentIndex, lsc))
                return false;

            aSmartCandlestick^ current = lsc[currentIndex];
            aSmartCandlestick^ previous = lsc[currentIndex - 1];

            // Bearish Engulfing: previous is bullish, current is bearish
            return previous->isBullish && current->isBearish;
        }
    };
}

