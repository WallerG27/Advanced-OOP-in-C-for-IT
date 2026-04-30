#pragma once
#include "aSmartCandlestick.h"

using namespace System;
using namespace System::Collections::Generic;

namespace CppCLRWinFormsProject
{
    public ref class aRecognizer abstract
    {
    public:
        // Name of the pattern to populate the ComboBox
        property String^ PatternName;

        // Number of candlesticks required for this pattern
        property int PatternSize;

        aRecognizer(String^ name, int size)
        {
            PatternName = name;
            PatternSize = size;
        }

        // Virtual match function to be overridden by derived classes
        virtual bool match(int currentIndex, List<aSmartCandlestick^>^ lsc) abstract;

        // Scans the list and returns indices of the last candlestick in the matched patterns
        List<int>^ recognize(List<aSmartCandlestick^>^ lsc)
        {
            List<int>^ matchedIndices = gcnew List<int>();
            
            // Cannot recognize a pattern if there are fewer candlesticks than the pattern size
            if (lsc == nullptr || lsc->Count < PatternSize)
                return matchedIndices;

            // Start checking from the index where a complete pattern can be formed
            for (int i = PatternSize - 1; i < lsc->Count; i++)
            {
                if (match(i, lsc))
                {
                    matchedIndices->Add(i);
                }
            }

            return matchedIndices;
        }
    };
}