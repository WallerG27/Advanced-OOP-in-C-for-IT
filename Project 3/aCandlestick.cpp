#include "pch.h"
#include "aCandlestick.h"

namespace CppCLRWinFormsProject
{
    // Make sure you do NOT use the colon ( : ) initializer list here anymore.
    // Properties must be assigned inside the brackets.
    aCandlestick::aCandlestick(DateTime d, double o, double h, double l, double c, unsigned long v)
    {
        this->Date = d;
        this->Open = o;
        this->High = h;
        this->Low = l;
        this->Close = c;
        this->Volume = v;
    }
}