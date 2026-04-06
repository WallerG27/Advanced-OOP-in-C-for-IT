#pragma once
#include "aCandlestick.h"
#include "aCandlestickLoader.h"
//#include "Form_display.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Collections::Generic;

namespace CppCLRWinFormsProject {
	/// <summary>
	/// Main window for the Candlestick application.
	/// Hosts the DataGridView for candlestick rows and controls to load files and filter by date range.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::OpenFileDialog^ OpenFileDialog_LoadStock;
	private: System::Windows::Forms::Button^ Button_LoadStock;
	private: System::Windows::Forms::DateTimePicker^ DateTimePicker_StartDate;
	private: System::Windows::Forms::DataGridView^ DataGridView_StockData;
	private: System::Windows::Forms::Panel^ BottomPanel;
	private: System::Windows::Forms::DateTimePicker^ DateTimePicker_EndDate;
	private: System::Windows::Forms::Button^ Button_Update;
	private: System::Windows::Forms::Label^ Label_StartDate;
	private: System::Windows::Forms::Label^ Label_EndDate;


	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// Initializes UI controls and layout for the form.
		/// </summary>
		void InitializeComponent(void)
		{
			this->OpenFileDialog_LoadStock = (gcnew System::Windows::Forms::OpenFileDialog());
			this->Button_LoadStock = (gcnew System::Windows::Forms::Button());
			this->DateTimePicker_StartDate = (gcnew System::Windows::Forms::DateTimePicker());
			this->DataGridView_StockData = (gcnew System::Windows::Forms::DataGridView());
			this->DateTimePicker_EndDate = (gcnew System::Windows::Forms::DateTimePicker());
			this->Button_Update = (gcnew System::Windows::Forms::Button());
			this->Label_StartDate = (gcnew System::Windows::Forms::Label());
			this->Label_EndDate = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DataGridView_StockData))->BeginInit();
			this->SuspendLayout();
			// 
			// OpenFileDialog_LoadStock
			// 
			this->OpenFileDialog_LoadStock->DefaultExt = L"csv";
			this->OpenFileDialog_LoadStock->FileName = L"ABBV_daily";
			this->OpenFileDialog_LoadStock->Filter = L"All Stocks|*.csv|Monthly|*_monthly.csv|Weekly|*_weekly.csv|Daily|*_daily.csv";
			this->OpenFileDialog_LoadStock->InitialDirectory = L"C:\\Users\\Gavin\\Downloads\\All My Coding Classes\\Advanced OOP in C++ for IT (C++ 20"
				L"26)\\Stock Data";
			// 
			// Button_LoadStock
			// 
			this->Button_LoadStock->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->Button_LoadStock->Location = System::Drawing::Point(293, 328);
			this->Button_LoadStock->Name = L"Button_LoadStock";
			this->Button_LoadStock->Size = System::Drawing::Size(140, 43);
			this->Button_LoadStock->TabIndex = 0;
			this->Button_LoadStock->Text = L"Load Stock";
			this->Button_LoadStock->UseVisualStyleBackColor = false;
			this->Button_LoadStock->Click += gcnew System::EventHandler(this, &Form1::Button_LoadStock_Click);
			// 
			// DateTimePicker_StartDate
			// 
			this->DateTimePicker_StartDate->Location = System::Drawing::Point(12, 334);
			this->DateTimePicker_StartDate->Name = L"DateTimePicker_StartDate";
			this->DateTimePicker_StartDate->Size = System::Drawing::Size(275, 26);
			this->DateTimePicker_StartDate->TabIndex = 1;
			this->DateTimePicker_StartDate->Value = System::DateTime(2021, 1, 28, 0, 0, 0, 0);
			this->DateTimePicker_StartDate->ValueChanged += gcnew System::EventHandler(this, &Form1::DateTimePicker_StartDate_ValueChanged);
			// 
			// DataGridView_StockData
			// 
			this->DataGridView_StockData->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->DataGridView_StockData->Location = System::Drawing::Point(64, 12);
			this->DataGridView_StockData->Name = L"DataGridView_StockData";
			this->DataGridView_StockData->RowHeadersWidth = 62;
			this->DataGridView_StockData->RowTemplate->Height = 28;
			this->DataGridView_StockData->Size = System::Drawing::Size(741, 294);
			this->DataGridView_StockData->TabIndex = 2;
			this->DataGridView_StockData->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Form1::DataGridView_StockData_CellContentClick);
			// 
			// DateTimePicker_EndDate
			// 
			this->DateTimePicker_EndDate->Location = System::Drawing::Point(585, 334);
			this->DateTimePicker_EndDate->Name = L"DateTimePicker_EndDate";
			this->DateTimePicker_EndDate->Size = System::Drawing::Size(275, 26);
			this->DateTimePicker_EndDate->TabIndex = 3;
			this->DateTimePicker_EndDate->Value = System::DateTime(2021, 2, 28, 0, 0, 0, 0);
			// 
			// Button_Update
			// 
			this->Button_Update->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->Button_Update->Location = System::Drawing::Point(439, 328);
			this->Button_Update->Name = L"Button_Update";
			this->Button_Update->Size = System::Drawing::Size(140, 43);
			this->Button_Update->TabIndex = 4;
			this->Button_Update->Text = L"Update";
			this->Button_Update->UseVisualStyleBackColor = false;
			this->Button_Update->Click += gcnew System::EventHandler(this, &Form1::Button_Update_Click);
			// 
			// Label_StartDate
			// 
			this->Label_StartDate->AutoSize = true;
			this->Label_StartDate->Location = System::Drawing::Point(12, 309);
			this->Label_StartDate->Name = L"Label_StartDate";
			this->Label_StartDate->Size = System::Drawing::Size(83, 20);
			this->Label_StartDate->TabIndex = 5;
			this->Label_StartDate->Text = L"Start Date";
			// 
			// Label_EndDate
			// 
			this->Label_EndDate->AutoSize = true;
			this->Label_EndDate->Location = System::Drawing::Point(581, 309);
			this->Label_EndDate->Name = L"Label_EndDate";
			this->Label_EndDate->Size = System::Drawing::Size(77, 20);
			this->Label_EndDate->TabIndex = 6;
			this->Label_EndDate->Text = L"End Date";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(874, 383);
			this->Controls->Add(this->Label_EndDate);
			this->Controls->Add(this->Label_StartDate);
			this->Controls->Add(this->Button_Update);
			this->Controls->Add(this->DateTimePicker_EndDate);
			this->Controls->Add(this->DataGridView_StockData);
			this->Controls->Add(this->DateTimePicker_StartDate);
			this->Controls->Add(this->Button_LoadStock);
			this->Name = L"Form1";
			this->Text = L"Candlestick";
			this->AcceptButton = this->Button_LoadStock;
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DataGridView_StockData))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		/// <summary>
		/// A C++/CLI field that holds a managed list of aCandlestick objects.
		/// </summary>
	private: List<aCandlestick^>^ ListCandles;

		   /// <summary>
		   /// A managed array of System::String^ references, typically used to store lines of text.
		   /// </summary>
	private: array<String^>^ lines;

		   /// <summary>
		   /// Handles the Load Stock button click: shows an open-file dialog, reads the selected CSV file, 
		   /// loads candlestick data, configures the Start/End date pickers based on the loaded data, and 
		   /// applies a date filter. On error it clears loaded data and the grid.
		   /// </summary>
	private: System::Void Button_LoadStock_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (OpenFileDialog_LoadStock->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			String^ filePath = OpenFileDialog_LoadStock->FileName;

			// Read all lines from the CSV file
			lines = System::IO::File::ReadAllLines(filePath);

			// Load parsed candlesticks and populate grid
			try
			{
				ListCandles = aCandlestickLoader::LoadFromCSV(filePath);

				// If we have candles, set the Start/End date controls allowed range but do NOT force
				// the visible selected values to the file earliest/latest. Keep the user's current
				// choice (initial defaults) unless they are outside the new allowed range.
				if (ListCandles != nullptr && ListCandles->Count > 0)
				{
					// Compute min/max dates
					DateTime minDate = ListCandles[0]->Date;
					DateTime maxDate = minDate;
					// Iterate through the loaded candles to find the minimum and maximum dates. 
					// This will allow us to set the allowed range for the date pickers.
					for each (aCandlestick ^ c in ListCandles)
					{
						if (c->Date < minDate) minDate = c->Date;
						if (c->Date > maxDate) maxDate = c->Date;
					}

					// Preserve current selected values so they stay at the prechosen defaults until user changes them
					DateTime prevStart = DateTimePicker_StartDate->Value;
					DateTime prevEnd = DateTimePicker_EndDate->Value;

					// Configure allowed ranges
					DateTimePicker_StartDate->MinDate = minDate;
					DateTimePicker_StartDate->MaxDate = maxDate;
					DateTimePicker_EndDate->MinDate = minDate;
					DateTimePicker_EndDate->MaxDate = maxDate;

					// Restore or clamp previous selections:
					// If the previous value is still within the file's range, restore it so it doesn't jump.
					// If outside, clamp to nearest allowed date so the control remains valid.
					if (prevStart < minDate) DateTimePicker_StartDate->Value = minDate;
					else if (prevStart > maxDate) DateTimePicker_StartDate->Value = maxDate;
					else DateTimePicker_StartDate->Value = prevStart;

					if (prevEnd < minDate) DateTimePicker_EndDate->Value = minDate;
					else if (prevEnd > maxDate) DateTimePicker_EndDate->Value = maxDate;
					else DateTimePicker_EndDate->Value = prevEnd;
				}
				// Apply the date filter to show the loaded data in the grid based on the current 
				// Start/End date selections.
				ApplyDateFilter();
			}
			catch (Exception^)
			{
				// leave lines available as fallback
				ListCandles = nullptr;
				DataGridView_StockData->DataSource = nullptr;
			}
		}
	}

		   /// <summary>
		   /// Click event handler that updates the display by applying the current date filter.
		   /// </summary>
	private: System::Void Button_Update_Click(System::Object^ sender, System::EventArgs^ e) {
		ApplyDateFilter();
	}

		   /// <summary>
		   /// Event handler invoked when the StartDate value changes. Intended to apply a date filter 
		   /// (call is currently commented out).
		   /// </summary>
	private: System::Void DateTimePicker_StartDate_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		//ApplyDateFilter();
	}

		   /// <summary>
		   /// Event handler called when the EndDate control's value changes. The handler currently does nothing (ApplyDateFilter call is commented out).
		   /// </summary>
	private: System::Void DateTimePicker_EndDate_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		//ApplyDateFilter();
	}

		   /// <summary>
		   /// Event handler invoked when the content of a DataGridView cell is clicked.
		   /// </summary>
	private: System::Void DataGridView_StockData_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
	}

		   /// <summary>
		   /// Creates a System::Data::DataTable from a list of aCandlestick objects, mapping each candlestick 
		   /// to a row. Returns nullptr if the input list is nullptr.
		   /// </summary>
	private: System::Data::DataTable^ CreateDataTableFromCandles(System::Collections::Generic::List<aCandlestick^>^ list)
	{
		// If the input list is null, we cannot create a DataTable, so return null to indicate failure.
		if (list == nullptr)
			return nullptr;
		// Create a new DataTable to hold the candlestick data
		System::Data::DataTable^ table = gcnew System::Data::DataTable();

		// Define columns (use appropriate CLR types)
		table->Columns->Add("Date", System::DateTime::typeid);
		table->Columns->Add("Open", System::Double::typeid);
		table->Columns->Add("High", System::Double::typeid);
		table->Columns->Add("Low", System::Double::typeid);
		table->Columns->Add("Close", System::Double::typeid);
		table->Columns->Add("Volume", System::Double::typeid);

		// Fill rows
		for each (aCandlestick ^ c in list)
		{
			// Create a new DataRow and populate it with the candlestick data
			System::Data::DataRow^ r = table->NewRow();
			r["Date"] = c->Date;
			r["Open"] = c->Open;
			r["High"] = c->High;
			r["Low"] = c->Low;
			r["Close"] = c->Close;
			r["Volume"] = (System::Double)c->Volume;
			table->Rows->Add(r);
		}
		// Return the populated DataTable
		return table;
	}

		   /// <summary>
		   /// Filters the in-memory candle list by the StartDate/EndDate range, binds the filtered data to 
		   /// DataGridView_StockData, formats numeric columns, and refreshes the grid.
		   /// </summary>
	private: void ApplyDateFilter()
	{
		// If we don't have any candles loaded, clear the grid and return
		if (ListCandles == nullptr || ListCandles->Count == 0)
		{
			DataGridView_StockData->DataSource = nullptr;
			return;
		}
		// Get selected date range from the controls
		DateTime start = DateTimePicker_StartDate->Value.Date;
		DateTime end = DateTimePicker_EndDate->Value.Date;

		// Ensure start <= end by swapping if necessary. This allows the user to select dates in either order without breaking the filter.
		if (end < start)
		{
			DateTime tmp = start;
			start = end;
			end = tmp;
		}

		// Filter the candles in-memory by the selected date range. We can do this efficiently because ListCandles is sorted by date.
		List<aCandlestick^>^ filtered = gcnew List<aCandlestick^>();
		for each (aCandlestick ^ candle in ListCandles)
		{
			if (candle->Date.Date >= start && candle->Date.Date <= end)
			{
				filtered->Add(candle);
			}
			if (candle->Date.Date > end)
			{
				break; // Our ListCandles is sorted by date, we can stop once we pass the end date
			}
		}

		// Bind a DataTable so the DataGridView shows column headers and types reliably
		System::Data::DataTable^ table = CreateDataTableFromCandles(filtered);

		DataGridView_StockData->DataSource = nullptr;
		DataGridView_StockData->DataSource = table;

		// Format numeric columns to show two decimal places
		if (DataGridView_StockData->Columns->Contains("Open"))  DataGridView_StockData->Columns["Open"]->DefaultCellStyle->Format = "N2";
		if (DataGridView_StockData->Columns->Contains("High"))  DataGridView_StockData->Columns["High"]->DefaultCellStyle->Format = "N2";
		if (DataGridView_StockData->Columns->Contains("Low"))   DataGridView_StockData->Columns["Low"]->DefaultCellStyle->Format = "N2";
		if (DataGridView_StockData->Columns->Contains("Close")) DataGridView_StockData->Columns["Close"]->DefaultCellStyle->Format = "N2";
		if (DataGridView_StockData->Columns->Contains("Volume")) DataGridView_StockData->Columns["Volume"]->DefaultCellStyle->Format = "N0";

		DataGridView_StockData->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::AllCells;
		DataGridView_StockData->Refresh();
	}

	};
}