#include "pch.h"
#include "aCandlestick.h"

namespace CppCLRWinFormsProject
{
    // Default constructor
    aCandlestick::aCandlestick()
    {
        date = DateTime::MinValue;
        open = 0.0;
        high = 0.0;
        low = 0.0;
        close = 0.0;
        volume = 0;
    }

    // Parameterized constructor
    aCandlestick::aCandlestick(DateTime d, double o, double h, double l, double c, unsigned long v)
    {
        Date = d;
        Open = o;
        High = h;
        Low = l;
        Close = c;
        Volume = v;
    }

    // Copy constructor
    aCandlestick::aCandlestick(aCandlestick^ sourceCandlestick)
    {
        Date = sourceCandlestick->Date;
        Open = sourceCandlestick->Open;
        High = sourceCandlestick->High;
        Low = sourceCandlestick->Low;
        Close = sourceCandlestick->Close;
        Volume = sourceCandlestick->Volume;
    }

    // String parsing constructor
    aCandlestick::aCandlestick(String^ fileLine)
    {
        data(fileLine);
    }

    // Data parsing implementation
    void aCandlestick::data(String^ fileLine)
    {
        // Expected format: Date,Open,High,Low,Close,Volume
        array<String^>^ parts = fileLine->Split(',');
        if (parts->Length == 6)
        {
            Date = DateTime::Parse(parts[0]);
            Open = Double::Parse(parts[1]);
            High = Double::Parse(parts[2]);
            Low = Double::Parse(parts[3]);
            Close = Double::Parse(parts[4]);
            
            // Cast to UInt32 to prevent potential data loss warning
            Volume = UInt32::Parse(parts[5]); 
        }
    }
}