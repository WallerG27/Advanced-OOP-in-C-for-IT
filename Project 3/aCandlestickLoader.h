#pragma once

#include "aCandlestick.h"

using namespace System;
using namespace System::Collections::Generic;

namespace CppCLRWinFormsProject
{
    public ref class aCandlestickLoader abstract sealed
    {
    public:
        static List<aCandlestick^>^ LoadFromCSV(String^ filePath);
    };
}