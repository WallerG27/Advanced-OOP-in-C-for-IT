#include "pch.h"
#include "aCandlestick.h"

CppCLRWinFormsProject::aCandlestick::aCandlestick(System::DateTime d, double o, double h, double l, double c, unsigned long v)
{
	Date = d;
	Open = o;
	High = h;
	Low = l;
	Close = c;
	Volume = v;
}