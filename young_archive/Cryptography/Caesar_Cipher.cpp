#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;
char charcaesar(char c, int k)//’c’ holds the letter to beencrypted or decrypted and ‘k’ holds the key
{
	if (isalpha(c) && c != toupper(c))
	{
		c = toupper(c);//use upper to keep from havingto use two separate for A..Z a..z
			c = (((c - 65) + k) % 26) + 65; //Encryption, (add kwith c) mod 26
	}
	else
	{
		c = ((((c - 65) - k) + 26) % 26) + 65; //Decryption(subtract k from c) mod 26
			c = tolower(c);//use lower to keep from havingto use two separate for A..Z a..z
	}
	return c;
}

int main()
{
	string input, output;
	int choice = 0;
	while (choice != 2) {
		cout << endl << "Press 1: Encryption / Decryption; Press 2:quit: ";
		try {
			cin >> choice;
			if (choice != 1 && choice != 2) throw "IncorrectChoice";
		}
		catch (const char* chc) {
			cerr << "INCORRECT CHOICE !!!!" << endl;
			return 1;
		}
		if (choice == 1) {
			int key;
			try {
				cout << endl << "Choose key value(choose a number between 1 to 26) : ";
				cin >> key;
				cin.ignore();
				if (key < 1 || key > 26) throw "Incorrect key";
			}
			catch (const char* k) {
				cerr << "INCORRECT KEY VALUE CHOSEN !!!" << endl;
				return 1;
			}
			try {
				cout << endl << "NOTE: Put LOWER CASE letters for encryption and" << endl;
				cout << "UPPER CASE letters for decryption" << endl;
				cout << endl << "Enter cipertext(only alphabets) and press enter to continue: ";
				getline(cin, input);
				for (int i = 0; i < input.size(); i++) {
					if ((!(input[i] >= 'a' && input[i] <= 'z')) &&
						(!(input[i] >= 'A' && input[i] <= 'Z'))) throw
						"Incorrect string";
				}
			}
			catch (const char* str) {
				cerr << "YOUR STRING MAY HAVE DIGITS OR SPECIAL SYMBOLS!!!" << endl;
				cerr << "PLEASE PUT ONLY ALPHABETS !!!" << endl;
				return 1;
			}
			for (unsigned int x = 0; x < input.length(); x++) {
				output += charcaesar(input[x], key); //calling the Caesar function, where the actual encryption and decryption takes place
			}
			cout << output << endl;
			output.clear();
		}
	}
}