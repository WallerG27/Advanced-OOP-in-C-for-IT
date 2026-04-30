#pragma once
#include "aCandlestick.h"
#include "aSmartCandlestick.h"
#include "aCandlestickLoader.h"
#include "aRecognizer.h"
#include "recognizer_Marubozu.h"
#include "recognizer_Engulfing.h"
#include "recognizer_Harami.h" 
#include "recognizer_Black_Crow.h"     
#include "recognizer_White_Soldier.h"  
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
            SetupRecognizersRuntime();

            // Set up initial constraints for Easy Start requirement
            dateTimePickerStartDate->Value = DateTime(2021, 1, 28);
            dateTimePickerEndDate->Value = DateTime(2021, 2, 28);

            // Project 3 Requirement: Initially display ABBV_daily.csv right on startup
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

        // Overloaded constructor for opening additional windows dynamically
        Form1(String^ filePath, DateTime startDate, DateTime endDate)
        {
            InitializeComponent();
            SetupRecognizersRuntime();

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
        System::Windows::Forms::ComboBox^ comboBoxPatterns; // NEW: Pattern Selector
        System::Windows::Forms::CheckBox^ checkBoxKeepAnnotations; // NEW: Keep Annotations Checkbox
        System::Windows::Forms::OpenFileDialog^ openFileDialog;
        System::Windows::Forms::Label^ labelStartDate;
        System::Windows::Forms::Label^ labelEndDate;
        System::Windows::Forms::Panel^ panelTop;
        System::Windows::Forms::DataVisualization::Charting::Chart^ chartStock;
        System::ComponentModel::Container^ components;

        List<aCandlestick^>^ fullCandleList;
        List<aSmartCandlestick^>^ boundSmartCandleList; // NEW: Track exactly what's currently graphed

        // Dictionary to tie the string name in the ComboBox back to the actual Recognizer class
        Dictionary<String^, aRecognizer^>^ recognizerDictionary;

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
            this->comboBoxPatterns = (gcnew System::Windows::Forms::ComboBox());
            this->checkBoxKeepAnnotations = (gcnew System::Windows::Forms::CheckBox());
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
            this->dateTimePickerStartDate->Size = System::Drawing::Size(150, 26);
            this->dateTimePickerStartDate->TabIndex = 2; // Fixed tab indexing
            // 
            // dateTimePickerEndDate
            // 
            this->dateTimePickerEndDate->Format = System::Windows::Forms::DateTimePickerFormat::Short;
            this->dateTimePickerEndDate->Location = System::Drawing::Point(159, 21);
            this->dateTimePickerEndDate->Name = L"dateTimePickerEndDate";
            this->dateTimePickerEndDate->Size = System::Drawing::Size(150, 26);
            this->dateTimePickerEndDate->TabIndex = 3;
            // 
            // buttonUpdate
            // 
            this->buttonUpdate->BackColor = System::Drawing::SystemColors::ActiveCaption;
            this->buttonUpdate->Location = System::Drawing::Point(315, 17);
            this->buttonUpdate->Name = L"buttonUpdate";
            this->buttonUpdate->Size = System::Drawing::Size(75, 34);
            this->buttonUpdate->TabIndex = 1;
            this->buttonUpdate->Text = L"Update";
            this->buttonUpdate->UseVisualStyleBackColor = false;
            this->buttonUpdate->Click += gcnew System::EventHandler(this, &Form1::buttonUpdate_Click);
            // 
            // comboBoxPatterns
            // 
            this->comboBoxPatterns->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->comboBoxPatterns->FormattingEnabled = true;
            this->comboBoxPatterns->Location = System::Drawing::Point(396, 21);
            this->comboBoxPatterns->Name = L"comboBoxPatterns";
            this->comboBoxPatterns->Size = System::Drawing::Size(160, 28);
            this->comboBoxPatterns->TabIndex = 4;
            this->comboBoxPatterns->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::comboBoxPatterns_SelectedIndexChanged);
            // 
            // checkBoxKeepAnnotations
            // 
            this->checkBoxKeepAnnotations->AutoSize = true;
            this->checkBoxKeepAnnotations->Location = System::Drawing::Point(565, 23);
            this->checkBoxKeepAnnotations->Name = L"checkBoxKeepAnnotations";
            this->checkBoxKeepAnnotations->Size = System::Drawing::Size(160, 24);
            this->checkBoxKeepAnnotations->TabIndex = 5;
            this->checkBoxKeepAnnotations->Text = L"Keep Annotations";
            this->checkBoxKeepAnnotations->UseVisualStyleBackColor = true;
            // 
            // buttonLoadStock
            // 
            this->buttonLoadStock->BackColor = System::Drawing::SystemColors::ActiveCaption;
            this->buttonLoadStock->Location = System::Drawing::Point(725, 17);
            this->buttonLoadStock->Name = L"buttonLoadStock";
            this->buttonLoadStock->Size = System::Drawing::Size(120, 34);
            this->buttonLoadStock->TabIndex = 0; // LOAD BUTTON MUST BE 0
            this->buttonLoadStock->Text = L"Load Stock(s)";
            this->buttonLoadStock->UseVisualStyleBackColor = false;
            this->buttonLoadStock->Click += gcnew System::EventHandler(this, &Form1::buttonLoadStock_Click);
            // 
            // labelStartDate
            // 
            this->labelStartDate->AutoSize = true;
            this->labelStartDate->Location = System::Drawing::Point(3, 0);
            this->labelStartDate->Name = L"labelStartDate";
            this->labelStartDate->Size = System::Drawing::Size(87, 20);
            // 
            // labelEndDate
            // 
            this->labelEndDate->AutoSize = true;
            this->labelEndDate->Location = System::Drawing::Point(155, 0);
            this->labelEndDate->Name = L"labelEndDate";
            this->labelEndDate->Size = System::Drawing::Size(81, 20);
            // 
            // panelTop
            // 
            this->panelTop->Controls->Add(this->buttonLoadStock);
            this->panelTop->Controls->Add(this->checkBoxKeepAnnotations);
            this->panelTop->Controls->Add(this->comboBoxPatterns);
            this->panelTop->Controls->Add(this->buttonUpdate);
            this->panelTop->Controls->Add(this->dateTimePickerEndDate);
            this->panelTop->Controls->Add(this->labelEndDate);
            this->panelTop->Controls->Add(this->dateTimePickerStartDate);
            this->panelTop->Controls->Add(this->labelStartDate);
            this->panelTop->Dock = System::Windows::Forms::DockStyle::Top;
            this->panelTop->Location = System::Drawing::Point(0, 0);
            this->panelTop->Name = L"panelTop";
            this->panelTop->Size = System::Drawing::Size(860, 60);
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
            this->chartStock->Location = System::Drawing::Point(0, 60);
            this->chartStock->Name = L"chartStock";

            series1->ChartArea = L"PriceArea";
            series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Candlestick;
            series1->CustomProperties = L"PriceDownColor=Red, PriceUpColor=Green";
            series1->IsXValueIndexed = true;
            series1->Name = L"Price";
            series1->XValueMember = L"Date";
            series1->YValueMembers = L"High,Low,Open,Close"; 
            series1->YValuesPerPoint = 4;

            series2->ChartArea = L"VolumeArea";
            series2->IsXValueIndexed = true;
            series2->Name = L"Volume";
            series2->XValueMember = L"Date";
            series2->YValueMembers = L"Volume";

            this->chartStock->Series->Add(series1);
            this->chartStock->Series->Add(series2);
            this->chartStock->Size = System::Drawing::Size(860, 540);
            this->chartStock->TabIndex = 4;
            // 
            // Form1
            // 
            this->ClientSize = System::Drawing::Size(860, 600);
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

        /// <summary>
        /// REQUIREMENT: Load ComboBox at RUNTIME, not design time.
        /// </summary>
        void SetupRecognizersRuntime()
        {
            recognizerDictionary = gcnew Dictionary<String^, aRecognizer^>();

            // Create recognizers
            array<aRecognizer^>^ recognizers = {
                gcnew recognizer_Marubozu(),
                gcnew recognizer_BullishMarubozu(),
                gcnew recognizer_BearishMarubozu(),
                gcnew recognizer_Engulfing(),
                gcnew recognizer_BullishEngulfing(),
                gcnew recognizer_BearishEngulfing(),
                
                // Base Harami catches both Bullish & Bearish versions per quiz instructions
                gcnew recognizer_Harami(),          
                
                // Add the new 3-Candle Array Recognizers
                gcnew recognizer_Black_Crow(),      
                gcnew recognizer_White_Soldier()    
            };

            for each (aRecognizer^ r in recognizers)
            {
                recognizerDictionary->Add(r->PatternName, r);
                comboBoxPatterns->Items->Add(r->PatternName);
            }
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

            // To support Project 3, we extract basic List<aCandlestick^> to List<aSmartCandlestick^>
            List<aCandlestick^>^ filtered = gcnew List<aCandlestick^>();

            for each (aCandlestick^ c in fullCandleList) {
                if (c->Date >= start && c->Date <= end) {
                    filtered->Add(c);
                }
            }

            // Create a smart candlestick helper to invoke convertToSmartCandlestick
            aSmartCandlestick^ converterHelper = gcnew aSmartCandlestick();
            boundSmartCandleList = converterHelper->convertToSmartCandlestick(filtered);

            // Clear any active annotations since the graph timeline is changing
            chartStock->Annotations->Clear();

            // Note setting chartStock properties via Binding and Object lists
            this->chartStock->DataSource = boundSmartCandleList;
            this->chartStock->DataBind();
        }

        /// <summary>
        /// Displays visual annotations matching the newly selected pattern.
        /// </summary>
        System::Void comboBoxPatterns_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
        {
            if (comboBoxPatterns->SelectedItem == nullptr || boundSmartCandleList == nullptr || boundSmartCandleList->Count == 0)
                return;

            String^ selectedPattern = comboBoxPatterns->SelectedItem->ToString();

            // Clear annotations if the "Keep Annotations" checkbox is NOT checked
            if (!checkBoxKeepAnnotations->Checked)
            {
                chartStock->Annotations->Clear();
            }

            // Find matching pattern Recognizer
            if (recognizerDictionary->ContainsKey(selectedPattern))
            {
                aRecognizer^ currentRecognizer = recognizerDictionary[selectedPattern];

                // Get list of matching target indices where the pattern occurs
                List<int>^ matches = currentRecognizer->recognize(boundSmartCandleList);

                // Add configured annotations for all matches found
                for each (int matchIndex in matches)
                {
                    DrawPatternAnnotation(currentRecognizer, matchIndex);
                }

                // Force a specific redraw requirement for Chart objects
                this->chartStock->Update();
            }
        }

        /// <summary>
        /// Helper Method: Calculate positioning and draws the required visual annotation
        /// on the chart matching the detected candlestick pattern criteria.
        /// </summary>
        void DrawPatternAnnotation(aRecognizer^ currentRecognizer, int matchIndex)
        {
            // Default to the current candlestick's High/Low
            double maxHigh = chartStock->Series["Price"]->Points[matchIndex]->YValues[0];
            double minLow = chartStock->Series["Price"]->Points[matchIndex]->YValues[1];

            // Expand bounds if it's a multi-candlestick pattern
            if (currentRecognizer->PatternSize > 1) 
            {
                for (int p = 0; p < currentRecognizer->PatternSize; p++)
                {
                    int checkIndex = matchIndex - p;
                    if (checkIndex >= 0)
                    {
                        double checkHigh = chartStock->Series["Price"]->Points[checkIndex]->YValues[0];
                        double checkLow = chartStock->Series["Price"]->Points[checkIndex]->YValues[1];
                        if (checkHigh > maxHigh) maxHigh = checkHigh;
                        if (checkLow < minLow) minLow = checkLow;
                    }
                }
            }

            // Set color appropriately
            System::Drawing::Color patternColor;
            if (currentRecognizer->PatternName->Contains("Bullish")) {
                patternColor = System::Drawing::Color::Green;
            } 
            else if (currentRecognizer->PatternName->Contains("Bearish")) {
                patternColor = System::Drawing::Color::Red;
            } 
            else {
                patternColor = System::Drawing::Color::Blue; // Neutral patterns
            }

            // 1. Create the exact highlight box outlining the candlestick
            RectangleAnnotation^ highlightBox = gcnew RectangleAnnotation();
            highlightBox->Name = currentRecognizer->PatternName + "_Box_" + matchIndex; 
            highlightBox->AxisX = chartStock->ChartAreas["PriceArea"]->AxisX;
            highlightBox->AxisY = chartStock->ChartAreas["PriceArea"]->AxisY;
            highlightBox->IsSizeAlwaysRelative = false;
            highlightBox->AnchorDataPoint = chartStock->Series["Price"]->Points[matchIndex];
            
            highlightBox->LineColor = patternColor;
            highlightBox->BackColor = System::Drawing::Color::FromArgb(40, (int)patternColor.R, (int)patternColor.G, (int)patternColor.B);
            highlightBox->LineWidth = 2;

            highlightBox->AnchorY = (maxHigh + minLow) / 2.0;
            highlightBox->Height = maxHigh - minLow;
            highlightBox->Width = 0.8 * currentRecognizer->PatternSize;  
            highlightBox->AnchorAlignment = System::Drawing::ContentAlignment::MiddleCenter;
            
            if (currentRecognizer->PatternSize > 1) {
                    highlightBox->AnchorOffsetX = (currentRecognizer->PatternSize - 1) * -0.5;
            }

            // 2. Create the Text above the Box 
            TextAnnotation^ textLabel = gcnew TextAnnotation();
            textLabel->Name = currentRecognizer->PatternName + "_Text_" + matchIndex;
            textLabel->Text = currentRecognizer->PatternName;
            textLabel->ForeColor = patternColor;
            textLabel->Font = gcnew System::Drawing::Font("Times New Roman", 10, System::Drawing::FontStyle::Bold);
            
            textLabel->AxisX = chartStock->ChartAreas["PriceArea"]->AxisX;
            textLabel->AxisY = chartStock->ChartAreas["PriceArea"]->AxisY;
            textLabel->IsSizeAlwaysRelative = false;
            textLabel->AnchorDataPoint = chartStock->Series["Price"]->Points[matchIndex];
            textLabel->AnchorY = maxHigh;
            textLabel->AnchorAlignment = System::Drawing::ContentAlignment::BottomCenter;
            
            if (currentRecognizer->PatternSize > 1) {
                    textLabel->AnchorOffsetX = (currentRecognizer->PatternSize - 1) * -0.5;
            }

            // 3. Add to Chart
            this->chartStock->Annotations->Add(highlightBox);
            this->chartStock->Annotations->Add(textLabel);
        }
    };
}
