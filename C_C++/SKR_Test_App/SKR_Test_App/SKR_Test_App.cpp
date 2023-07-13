// SKR_Test_App.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include "Test_Func.h"

#define APP_VERSION 0x00000001

#define major	 	(((APP_VERSION >> 24) & 0xFF))
#define sub_major	(((APP_VERSION >> 16) & 0xFF))
#define minor		(((APP_VERSION >> 0) & 0xFFFF))

using namespace std;

int main()
{
	unsigned int choice = 99;
	unsigned int option = 0;
	while (1)
	{
		cout << endl << "==================================================================" << endl;
		cout << "                      SKR TEST APP : v" << major << "." << sub_major << "." << minor << endl;
		cout << "==================================================================" << endl << endl;
		cout << "1. Generate Random Number File        2. Generate Txt to Bin File (AVAG) " << endl ;
		cout << "3. Generate hex file (PCIe SW)        4. Generate cfg file (PCIe SW)     " << endl ;
		cout << "5. Generate Incr Number File          6. ---------------------------     " << endl;
		cout << "7. Generate PLL RAM XML File          8. Generate PLL ROM XML File     " << endl;
		cout << "99. Exit" << endl << endl;
		cout << "==================================================================" << endl << endl;
		cout << "Enter your choice! : " << endl << endl;
		cin >> std::dec >> choice;
		switch (choice)
		{
		case 1:
			cout << "Enter file size (KBs) : " << endl;
			cin >> std::dec >> option;
			Gen_Random_num_file(option *1024,"Random_num.bin");
			break;
		case 2:
			cout << "1. container_info    2. packet_info    3. raw_data" << endl;
			cout << "Choose your option : " << endl;
			cin >> std::dec >> option;
			Gen_txt_to_bin_file(option);
			break;
		case 3:
			cout << "make sure file name is PCIe_SW.bin" << endl;
			cout << "Press Enter to Proceed" << endl;
			cin.get();
			cin.get();
			Gen_bin_to_hex_file();
			break;
		case 4:
			cout << "make sure file name is PCIe_SW.bin" << endl;
			cout << "Press Enter to Proceed" << endl;
			cin.get();
			cin.get();
			Gen_bin_to_cfg_file();
			break;
		case 5:
			cout << "Enter file size (KBs) : " << endl;
			cin >> std::dec >> option;
			Gen_Incr_num_file(option * 1024, "Incr_num.bin");
			break;
		case 7:
			cout << "Enter PLL Number : " << endl;
			cin >> std::dec >> option;
			Gen_RAM_XML_file(option);
			break;
		case 8:
			cout << "Enter PLL Number : " << endl;
			cin >> std::dec >> option;
			Gen_ROM_XML_file(option);
			break;
		case 99:
			exit(0);
			break;
		default:
			cout << "Invalid choice!" << endl;
		}

	}
	_getch();

    return 0;
}

