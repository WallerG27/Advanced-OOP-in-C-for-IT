#include "pch.h"
#include "aCandlestickLoader.h"

using namespace System;
using namespace System::Collections::Generic;

List<CppCLRWinFormsProject::aCandlestick^>^ CppCLRWinFormsProject::aCandlestickLoader::LoadFromCSV(String^ filePath)
{
	List<CppCLRWinFormsProject::aCandlestick^>^ candlestickList = gcnew List<CppCLRWinFormsProject::aCandlestick^>();
	
	array<wchar_t>^ separator = gcnew array<wchar_t>{ ',', '\"' };

	try
	{
		// Read all lines from the CSV file
		array<String^>^ lines = System::IO::File::ReadAllLines(filePath);
		// Skip the header line and parse each subsequent line into an aCandlestick object
		for (int i = 1; i < lines->Length; i++)
		{
			String^ line = lines[i];
			array<String^>^ values = line->Split(separator, StringSplitOptions::RemoveEmptyEntries);
			if (values->Length >= 6)
			{
				DateTime date = DateTime::Parse(values[0]);
				double open = Double::Parse(values[1]);
				double high = Double::Parse(values[2]);
				double low = Double::Parse(values[3]);
				double close = Double::Parse(values[4]);
				unsigned long volume = static_cast<unsigned long>(Double::Parse(values[5]));
				
				CppCLRWinFormsProject::aCandlestick^ candlestick = gcnew CppCLRWinFormsProject::aCandlestick(date, open, high, low, close, volume);
				candlestickList->Add(candlestick);
			}
		}
	}
	catch (Exception^ ex)
	{
		// Handle exceptions (e.g., file not found, parsing errors) as needed
		Console::WriteLine("Error loading CSV file: " + ex->Message);
	}
	return candlestickList;
}