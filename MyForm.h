#pragma once
#include"Include.h"
#include"MyOpencv.h"
#include <msclr\marshal_cppstd.h>
namespace RP {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
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
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	protected:
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(177, 306);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(175, 57);
			this->button1->TabIndex = 0;
			this->button1->Text = L"COMPARE IMAGES";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// label1
			// 
			this->label1->Location = System::Drawing::Point(12, 49);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(151, 30);
			this->label1->TabIndex = 1;
			this->label1->Text = L"SELECT FIRST IMAGE";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label2
			// 
			this->label2->Location = System::Drawing::Point(12, 167);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(151, 30);
			this->label2->TabIndex = 2;
			this->label2->Text = L"SELECT SECOND IMAGE";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// textBox1
			// 
			this->textBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox1->Location = System::Drawing::Point(12, 82);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(371, 20);
			this->textBox1->TabIndex = 3;
			this->textBox1->Click += gcnew System::EventHandler(this, &MyForm::textBox1_Click);
			// 
			// textBox2
			// 
			this->textBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox2->Location = System::Drawing::Point(12, 200);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(371, 20);
			this->textBox2->TabIndex = 4;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(389, 79);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(98, 25);
			this->button2->TabIndex = 5;
			this->button2->Text = L"Select Image";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(389, 197);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(98, 25);
			this->button3->TabIndex = 6;
			this->button3->Text = L"Select Image";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(521, 410);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"App";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void textBox1_Click(System::Object^ sender, System::EventArgs^ e) {
		
	}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	OpenFileDialog openFD;
	openFD.Filter = "All files (*.*)|*.*|PNG files (*.png)|*.png|JPEG files (*.jpeg)|*.jpeg";
	if (openFD.ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		textBox1->Text = openFD.FileName;
	}
}
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	OpenFileDialog openFD;
	openFD.Filter = "All files (*.*)|*.*|PNG files (*.png)|*.png|JPEG files (*.jpeg)|*.jpeg";
	if (openFD.ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		textBox2->Text = openFD.FileName;
	}
}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	std::string img1S = msclr::interop::marshal_as<std::string>(textBox1->Text);
	std::string img2S = msclr::interop::marshal_as<std::string>(textBox2->Text);


	if (!img1S.empty() && !img2S.empty()) {
		if (img1S == img2S) {
			MessageBox::Show("Both selected images are the same!", "Warning",
				MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}

		cv::Mat img1 = cv::imread(img1S);
		cv::Mat img2 = cv::imread(img2S);
		ShowManyImages("Comparison Window", img1, img2);
	}
	else if(img1S.empty() && img2S.empty()) {
		MessageBox::Show("You've selected no images.\n\nPlease select two images to compare.", "Warning",
			MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
	else {
		MessageBox::Show("You've selected only one image.\n\nPlease select two images to compare.", "Warning",
			MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}
};
}
