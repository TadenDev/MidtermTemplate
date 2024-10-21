// PM&G.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Header1.h"
#include <fstream>
#include <string>
#include <vector> 

using namespace std;

bool writeRecordToFile(const string& file_name,const string& field_one, const string& field_two);

bool writeRecordToFile(const string& file_name,const string& field_one, const string& field_two) {
	ofstream file;
	file.open(file_name, ios_base::app);
	file << field_one << "," << field_two << endl;
	file.close();

	return true;

}
// Had to overload getline in order to be able to read the char

bool Getline(ifstream& file, string& field_one, string& field_two, char delimiter) {
	string line;
	if (getline(file, line)) { // Read the entire line
		size_t commaPos = line.find(delimiter);
		if (commaPos != string::npos) {
			field_one = line.substr(0, commaPos); // Extract field_one
			field_two = line.substr(commaPos + 1); // Extract field_two
			return true;
		}
	}
	return false; 
}

vector<string> readRecordFromFile(const string& file_name,const string& search_term);
vector<string> readRecordFromFile(const string& file_name, const string& search_term) {
	vector<string> record;
	ifstream file;
	file.open(file_name);
	bool found_record = false;

	//checks to make sure the file is opening
	string field_one, field_two; 

	string line;
	while (Getline(file, field_one, field_two, ',')) { //using the overloaded GetLine 
		if (field_one == search_term) {
			record.push_back(field_one);
			record.push_back(field_two);
			break; // Stop after finding the first match
		}
	}

	file.close(); 
	return record;
}


int main()
{
	
	Password password;
	string  website;
	string  search_term; 
	string choice;
	cout << "Welcome to your password manager. \n" << endl;
	//basic welcome message
	//while loop to keep user inside of program unless specifically typed Q

	while (true) {
		cout << "Would you like to search S, or create C, a website and password? or Q for quit:  " << endl;
		cin >> choice;
		//choice will dictate the function, search or create password. 

		if (choice == "S") {
			std::cout << "Please type in website you want to search a password for: ";
			cin >> search_term;
			vector<string> data = readRecordFromFile("Passwords.txt", search_term);


			if (!data.empty()) {

				cout << "Found: " << data[0] << " " << data[1] << endl;
			}
			else {

				cout << "Couldn't find: " << search_term << " do you want to generate and add new Y/N ?" << endl;
				string newChoice;
				cin >> newChoice;
				if (newChoice == "Y") {
					cout << "Please type in the website you want to create a password for: ";
					cin >> website;
					password.generatePassword();
					cout << "Generated Password: " << ("Passwords.txt", website, password.getPassword());
					bool writeToFile = writeRecordToFile("Passwords.txt", website, password.getPassword());
				}
			}
		}
		else if (choice == "C") {

			cout << "Please type in a website you want to create a password for:  \n";
			cin >> website;
			password.generatePassword();
			cout << "Generated Password: " << password.getPassword() << endl;
			bool writeToFile = writeRecordToFile("Passwords.txt", website, password.getPassword());

		}
		else if (choice == "Q") {
			cout << "Closing program now." << endl;
			break;
		}
		else {
			std::cout << "Invalid option. please type S, C, or Q";
		}
	} 



		return 0; 
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
