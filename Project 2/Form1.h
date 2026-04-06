#pragma once
#include "aCandlestick.h"
#include "aCandlestickLoader.h"
#using <System.Windows.Forms.DataVisualization.dll>

namespace CppCLRWinFormsProject {
    using namespace System;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;
    using namespace System::Windows::Forms::DataVisualization::Charting;

    /// <summary>
    /// Main window for the Candlestick application.
    /// Acts as the main chart viewer that defaults to ABBV_daily.csv and can launch more.
    /// </summary>
    public ref class Form1 : public System::Windows::Forms::Form
    {
    public:
        // Default constructor (used for the very first window that opens)
        Form1(void)
        {
            InitializeComponent();
            
            // Set up initial constraints for Easy Start requirement
            dateTimePickerStartDate->Value = DateTime(2021, 1, 28);
            dateTimePickerEndDate->Value = DateTime(2021, 2, 28);

            // Project 2 Requirement: Initially display ABBV_daily.csv right on startup
            try {
                String^ defaultFile = L"ABBV_daily.csv"; 
                if (System::IO::File::Exists(defaultFile)) {
                    fullCandleList = aCandlestickLoader::LoadFromCSV(defaultFile);
                    this->Text = System::IO::Path::GetFileNameWithoutExtension(defaultFile);
                    ApplyFilter();
                }
            }
            catch (...) { /* File might not be in the current directory during startup */ }
        }

        // NEW: Overloaded constructor for opening additional windows dynamically
        Form1(String^ filePath, DateTime startDate, DateTime endDate)
        {
            InitializeComponent();
            
            dateTimePickerStartDate->Value = startDate;
            dateTimePickerEndDate->Value = endDate;

            // Load the specified file
            fullCandleList = aCandlestickLoader::LoadFromCSV(filePath);
            this->Text = System::IO::Path::GetFileNameWithoutExtension(filePath);
            ApplyFilter();
        }

    protected:
        ~Form1() { if (components) delete components; }

    private:
        System::Windows::Forms::DateTimePicker^ dateTimePickerStartDate;
        System::Windows::Forms::DateTimePicker^ dateTimePickerEndDate;
        System::Windows::Forms::Button^ buttonLoadStock;
        System::Windows::Forms::Button^ buttonUpdate;
        System::Windows::Forms::OpenFileDialog^ openFileDialog;
        System::Windows::Forms::Label^ labelStartDate;
        System::Windows::Forms::Label^ labelEndDate;
        System::Windows::Forms::Panel^ panelTop;
        System::Windows::Forms::DataVisualization::Charting::Chart^ chartStock;
        System::ComponentModel::Container^ components;

        List<aCandlestick^>^ fullCandleList;

        void InitializeComponent(void)
        {
            System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
            System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
            System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
            System::Windows::Forms::DataVisualization::Charting::Series^ series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
            this->dateTimePickerStartDate = (gcnew System::Windows::Forms::DateTimePicker());
            this->dateTimePickerEndDate = (gcnew System::Windows::Forms::DateTimePicker());
            this->buttonLoadStock = (gcnew System::Windows::Forms::Button());
            this->buttonUpdate = (gcnew System::Windows::Forms::Button());
            this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
            this->labelStartDate = (gcnew System::Windows::Forms::Label());
            this->labelEndDate = (gcnew System::Windows::Forms::Label());
            this->panelTop = (gcnew System::Windows::Forms::Panel());
            this->chartStock = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
            this->panelTop->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chartStock))->BeginInit();
            this->SuspendLayout();
            // 
            // dateTimePickerStartDate
            // 
            this->dateTimePickerStartDate->Format = System::Windows::Forms::DateTimePickerFormat::Short;
            this->dateTimePickerStartDate->Location = System::Drawing::Point(3, 21);
            this->dateTimePickerStartDate->Name = L"dateTimePickerStartDate";
            this->dateTimePickerStartDate->Size = System::Drawing::Size(200, 26);
            this->dateTimePickerStartDate->TabIndex = 2; // Fixed tab indexing
            // 
            // dateTimePickerEndDate
            // 
            this->dateTimePickerEndDate->Format = System::Windows::Forms::DateTimePickerFormat::Short;
            this->dateTimePickerEndDate->Location = System::Drawing::Point(209, 21);
            this->dateTimePickerEndDate->Name = L"dateTimePickerEndDate";
            this->dateTimePickerEndDate->Size = System::Drawing::Size(200, 26);
            this->dateTimePickerEndDate->TabIndex = 3;
            // 
            // buttonLoadStock
            // 
            this->buttonLoadStock->BackColor = System::Drawing::SystemColors::ActiveCaption;
            this->buttonLoadStock->Location = System::Drawing::Point(572, 3);
            this->buttonLoadStock->Name = L"buttonLoadStock";
            this->buttonLoadStock->Size = System::Drawing::Size(128, 41);
            this->buttonLoadStock->TabIndex = 0; // LOAD BUTTON MUST BE 0
            this->buttonLoadStock->Text = L"Load Stock(s)";
            this->buttonLoadStock->UseVisualStyleBackColor = false;
            this->buttonLoadStock->Click += gcnew System::EventHandler(this, &Form1::buttonLoadStock_Click);
            // 
            // buttonUpdate
            // 
            this->buttonUpdate->BackColor = System::Drawing::SystemColors::ActiveCaption;
            this->buttonUpdate->Location = System::Drawing::Point(415, 3);
            this->buttonUpdate->Name = L"buttonUpdate";
            this->buttonUpdate->Size = System::Drawing::Size(75, 41);
            this->buttonUpdate->TabIndex = 1;
            this->buttonUpdate->Text = L"Update";
            this->buttonUpdate->UseVisualStyleBackColor = false;
            this->buttonUpdate->Click += gcnew System::EventHandler(this, &Form1::buttonUpdate_Click);
            // 
            // openFileDialog
            // 
            this->openFileDialog->DefaultExt = L"csv";
            this->openFileDialog->FileName = L"ABBV_daily.csv"; 
            this->openFileDialog->Filter = L"All Stocks|*.csv|Monthly|*_monthly.csv|Weekly|*_weekly.csv|Daily|*_daily.csv";
            this->openFileDialog->Multiselect = true;
            // 
            // labelStartDate
            // 
            this->labelStartDate->AutoSize = true;
            this->labelStartDate->Location = System::Drawing::Point(3, 0);
            this->labelStartDate->Name = L"labelStartDate";
            this->labelStartDate->Size = System::Drawing::Size(87, 20);
            this->labelStartDate->TabIndex = 4;
            this->labelStartDate->Text = L"Start Date:";
            // 
            // labelEndDate
            // 
            this->labelEndDate->AutoSize = true;
            this->labelEndDate->Location = System::Drawing::Point(209, 0);
            this->labelEndDate->Name = L"labelEndDate";
            this->labelEndDate->Size = System::Drawing::Size(81, 20);
            this->labelEndDate->TabIndex = 5;
            this->labelEndDate->Text = L"End Date:";
            this->labelEndDate->Click += gcnew System::EventHandler(this, &Form1::labelEndDate_Click);
            // 
            // panelTop
            // 
            this->panelTop->Controls->Add(this->buttonLoadStock);
            this->panelTop->Controls->Add(this->buttonUpdate);
            this->panelTop->Controls->Add(this->dateTimePickerEndDate);
            this->panelTop->Controls->Add(this->labelEndDate);
            this->panelTop->Controls->Add(this->dateTimePickerStartDate);
            this->panelTop->Controls->Add(this->labelStartDate);
            this->panelTop->Dock = System::Windows::Forms::DockStyle::Top;
            this->panelTop->Location = System::Drawing::Point(0, 0);
            this->panelTop->Name = L"panelTop";
            this->panelTop->Size = System::Drawing::Size(800, 50);
            this->panelTop->TabIndex = 1;
            // 
            // chartStock
            // 
            chartArea1->AxisX->LabelStyle->Format = L"MM/dd/yyyy";
            chartArea1->AxisY->IsStartedFromZero = false; // Project constraint
            chartArea1->AxisY->LabelStyle->Format = L"F2";
            chartArea1->Name = L"PriceArea";
            chartArea1->Position->Auto = false;
            chartArea1->Position->Height = 75;
            chartArea1->Position->Width = 100;
            chartArea2->AlignWithChartArea = L"PriceArea";
            chartArea2->AxisY->LabelStyle->Format = L"N0";
            chartArea2->Name = L"VolumeArea";
            chartArea2->Position->Auto = false;
            chartArea2->Position->Height = 25;
            chartArea2->Position->Width = 100;
            chartArea2->Position->Y = 75;
            this->chartStock->ChartAreas->Add(chartArea1);
            this->chartStock->ChartAreas->Add(chartArea2);
            this->chartStock->Dock = System::Windows::Forms::DockStyle::Fill;
            this->chartStock->Location = System::Drawing::Point(0, 50);
            this->chartStock->Name = L"chartStock";
            
            // Note: DataSource mapping must match properties of the aCandlestick object
            series1->ChartArea = L"PriceArea";
            series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Candlestick;
            series1->CustomProperties = L"PriceDownColor=Red, PriceUpColor=Green";
            series1->IsXValueIndexed = true;
            series1->Name = L"Price";
            series1->XValueMember = L"Date";
            series1->YValueMembers = L"High,Low,Open,Close"; // Candlestick specific members 
            series1->YValuesPerPoint = 4;
            
            series2->ChartArea = L"VolumeArea";
            series2->IsXValueIndexed = true;
            series2->Name = L"Volume";
            series2->XValueMember = L"Date";
            series2->YValueMembers = L"Volume";
            
            this->chartStock->Series->Add(series1);
            this->chartStock->Series->Add(series2);
            this->chartStock->Size = System::Drawing::Size(800, 550);
            this->chartStock->TabIndex = 4;
            // 
            // Form1
            // 
            this->ClientSize = System::Drawing::Size(800, 600);
            this->Controls->Add(this->chartStock);
            this->Controls->Add(this->panelTop);
            this->Name = L"Form1";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Stock Launcher - Main Window";
            this->panelTop->ResumeLayout(false);
            this->panelTop->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chartStock))->EndInit();
            this->ResumeLayout(false);
        }

        System::Void buttonLoadStock_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
            {
                DateTime start = dateTimePickerStartDate->Value;
                DateTime end = dateTimePickerEndDate->Value;
                
                if (end < start) { DateTime temp = start; start = end; end = temp; }

                array<String^>^ fileNames = openFileDialog->FileNames;

                for (int i = 0; i < fileNames->Length; i++)
                {
                    if (i == 0) // Load first stock into the current window
                    {
                        fullCandleList = aCandlestickLoader::LoadFromCSV(fileNames[i]);
                        this->Text = L"Main Stock - " + System::IO::Path::GetFileNameWithoutExtension(fileNames[i]);
                        ApplyFilter();
                    }
                    else // Load subsequent selected stocks into NEW Form1 windows
                    {
                        Form1^ newWindow = gcnew Form1(fileNames[i], start, end);
                        newWindow->Show();
                    }
                }
            }
        }

        System::Void buttonUpdate_Click(System::Object^ sender, System::EventArgs^ e) 
        {
            ApplyFilter();
        }

        /// <summary>
        /// Applies the date filter. Strict compliance mapping to the graph specifically via DataBind.
        /// </summary>
        void ApplyFilter()
        {
            if (fullCandleList == nullptr || fullCandleList->Count == 0) return;

            DateTime start = dateTimePickerStartDate->Value.Date;
            DateTime end = dateTimePickerEndDate->Value.Date;
            if (end < start) { DateTime tmp = start; start = end; end = tmp; }

            List<aCandlestick^>^ filtered = gcnew List<aCandlestick^>();

            for each(aCandlestick^ c in fullCandleList) {
                if (c->Date >= start && c->Date <= end) {
                    filtered->Add(c);
                }
            }
            
            // Requirement Strict Implementation (Points Add disallowed)
            this->chartStock->DataSource = filtered;
            this->chartStock->DataBind();
        }

    private: 
        System::Void labelEndDate_Click(System::Object^ sender, System::EventArgs^ e) {
        }
    };
}
