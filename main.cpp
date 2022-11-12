#include "FormatDate.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include "XorStreamCipher.hpp"

std::string transXor(std::string data, std::string pass) {
	return nk125::xorCrypt::ucvToStr(nk125::xorCrypt::transform(nk125::xorCrypt::strToUcv(data), nk125::xorCrypt::strToUcv(pass)));
}

void writeNote() {
	std::string pass, note, fname, defname = nk125::dateFormatter::getDate();

	std::cout << "\nEnter the title of your note (put \".\" to autoinsert: \"" << defname << "\"): ";
	std::getline(std::cin, fname);

	if (fname == ".") fname = defname;

	std::cout << "\nEnter your password for your note: ";
	std::getline(std::cin, pass);

	std::cout << "\nStart to type your secret note!, press CTRL+Z twice to finish it:\n\n";

	std::ofstream file(fname, std::ios::binary);

	while (!std::cin.eof()) {
		std::string buf;
		std::getline(std::cin, buf);

		note += buf + "\n";
	}

	if (file.is_open()) {
		note = transXor(note, pass);

		file.write(note.c_str(), note.size());
		file.close();

		std::cout << "Note written succesfully\n";
	}
	else {
		std::cout << "Note wasn't written, displaying the encrypted note in stderr...\n";
		std::cerr << note;
	}

	std::exit(0);
}

void readNote() {
	std::string fname, pass;

	std::cout << "\nType the note name here: ";
	std::getline(std::cin, fname);

	std::cout << "\nNow enter your password: ";
	std::getline(std::cin, pass);

	std::cout << "\nDecrypting and showing up: (If the password is wrong the note will only contain weird characters and not the note!!)\n\n";
	
	std::ifstream file(fname, std::ios::binary);

	if (file.is_open()) {
		file.seekg(0, std::ios_base::end);

		std::streamoff sz = file.tellg();
		fname.resize(static_cast<size_t>(sz));

		file.seekg(0, std::ios_base::beg);
		file.read(&fname[0], sz);
		file.close();

		std::cout << transXor(fname, pass);
	}
	else {
		std::cout << "There was an error reading the note\n";
	}

	std::exit(0);
}

int main() {
	while (true) {
		int choice = 0;

		std::cout << "== SecretNote ==\n\n"
			<< "1.- Write a note\n2.- Read a note\n\n";

		std::cin >> choice;
		std::cin.ignore();

		switch (choice) {
		case 1:
			writeNote();
			break;
		case 2:
			readNote();
			break;
		default:
			std::cout << "Invalid choice\n.";
			break;
		}
	}
}
