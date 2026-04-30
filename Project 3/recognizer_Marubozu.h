#pragma once

#include "aRecognizer.h"

namespace CppCLRWinFormsProject
{
    /// <summary>
    /// Base recognizer for Marubozu patterns
    /// </summary>
    public ref class recognizer_Marubozu : public aRecognizer
    {
    public:
        // Default constructor sets the name and size
        recognizer_Marubozu() : aRecognizer("Marubozu", 1) {}

        // Protected constructor for derived classes to set their own names
    protected:
        recognizer_Marubozu(String^ name, int size) : aRecognizer(name, size) {}

    public:
        virtual bool match(int currentIndex, List<aSmartCandlestick^>^ lsc) override
        {
            aSmartCandlestick^ sc = lsc[currentIndex];

            // Prevent divide by zero if range is incredibly small or flat
            if (sc->range <= 0.0) 
            {
                return false;
            }

            // Marubozu has little to no wicks, meaning bodyRange is almost equal to total range.
            // Using a tolerance where the body makes up at least 96% of the entire range.
            return (sc->bodyRange / sc->range) > 0.96;
        }
    };

    /// <summary>
    /// Recognizer for Bullish Marubozu
    /// </summary>
    public ref class recognizer_BullishMarubozu : public recognizer_Marubozu
    {
    public:
        recognizer_BullishMarubozu() : recognizer_Marubozu("Bullish Marubozu", 1) {}

        virtual bool match(int currentIndex, List<aSmartCandlestick^>^ lsc) override
        {
            // It must be a valid Marubozu AND it must be Bullish
            return recognizer_Marubozu::match(currentIndex, lsc) && lsc[currentIndex]->isBullish;
        }
    };

    /// <summary>
    /// Recognizer for Bearish Marubozu
    /// </summary>
    public ref class recognizer_BearishMarubozu : public recognizer_Marubozu
    {
    public:
        recognizer_BearishMarubozu() : recognizer_Marubozu("Bearish Marubozu", 1) {}

        virtual bool match(int currentIndex, List<aSmartCandlestick^>^ lsc) override
        {
            // It must be a valid Marubozu AND it must be Bearish
            return recognizer_Marubozu::match(currentIndex, lsc) && lsc[currentIndex]->isBearish;
        }
    };
}

