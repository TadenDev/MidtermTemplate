#pragma once
#include <cmath>
#include <random>
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <vector> 
#include <cstdlib> //this is where the shuffle feature is.
using namespace std;

class Password {
private:
	char characters[15];
	int length;
	//  put shuffle in pvt class 
	void shuffle() {
		for (int i = length - 1; i > 0; --i) {
			// this grabs the index randomly from 0 to 1
			int j = rand() % (i + 1);
			swap(characters[i], characters[j]);
		}
	}
public:
	// initalizing characters for the password obj. and random seed. 

	Password(): length(0) {
		srand(static_cast<unsigned int>(time(0)));
	}
	//I decided it was easier to have a switch case instead of seperate get functions. this will iderate the
	// characters as upper, lower, special, and numbers instead of adding all the results of the fucntions together. 

	void addRandomCharacters() {
		int type = rand() % 4; 
		// length ++ will add the new character to the array. 
		switch (type) {
		case 0:
			characters[length++] = 'A' + (rand() % 26);
			break;

		case 1:
			characters[length++] = 'a' + (rand() % 26);
			break;
		case 2:
			characters[length++] = "!@*$^%+=&)(?/_-~`'."[rand() % 18];
			break;
		case 3:
			characters[length++] = "1234567890"[rand() % 10];
			break;
		} 

	}
	// this will generate a password by using the switch statement above. It will iderate through each one
	// until the length is greater than 14. 
	void generatePassword() {
		length = 0;
		while (length < 14) {
			addRandomCharacters(); 

		}
		//this is to terminate the character array
		characters[length] = '\0';
		shuffle();
	}
	const char* getPassword() const {
		return characters; 
	}

	void clear() {
		length = 0;

	}
};



