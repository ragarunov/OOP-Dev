// Workshop 10 - Multi-Threading
// SecureData.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <functional>
#include "SecureData.h"

using namespace std;

namespace w10 {

	void converter(char* t, char key, int n, const Cryptor& c) {
		for (int i = 0; i < n; i++)
			t[i] = c(t[i], key);
	}

	SecureData::SecureData(const char* file, char key) {
		// open text file
		std::fstream input(file, std::ios::in);
		if (!input)
			throw std::string("\n***Failed to open file ") +
			std::string(file) + std::string(" ***\n");

		// copy from file into memory
		nbytes = 0;
		input >> std::noskipws;
		while (input.good()) {
			char c;
			input >> c;
			nbytes++;
		}
		nbytes--;
		input.clear();
		input.seekg(0, std::ios::beg);
		text = new char[nbytes + 1];

		int i = 0;
		while (input.good())
			input >> text[i++];
		text[--i] = '\0';
		std::cout << "\n" << nbytes << " bytes copied from text "
			<< file << " into memory (null byte added)\n";
		encoded = false;

		// encode using key
		code(key);
		std::cout << "Data encrypted in memory\n";
	}

	SecureData::~SecureData() {
		delete[] text;
	}

	void SecureData::display(std::ostream& os) const {
		if (text && !encoded)
			os << text << std::endl;
		else if (encoded)
			throw std::string("\n***Data is encoded***\n");
		else
			throw std::string("\n***No data stored***\n");
	}

	void SecureData::code(char key) {
//		converter(text, key, nbytes, Cryptor());
//		encoded = !encoded;

		const int numT = 4;
		int size = nbytes / numT;
		thread t[numT];
		Cryptor c[numT];

		for (int i = 0; i < numT; i++)
			t[i] = thread(bind(converter, text + i*size, key, i + 1 < numT ? size : (nbytes - i*size), c[i]));

		for (int j = 0; j < numT; j++) t[j].join();
		encoded = !encoded;
	}

	void SecureData::backup(const char* file) {
		if (!text)
			throw std::string("\n***No data stored***\n");
		else if (!encoded)
			throw std::string("\n***Data is not encoded***\n");
		else {
			// open binary file
			fstream f(file, ios::out);

			// write binary file here
			for (int i = 0; i < nbytes; ++i) f << text[i];

		}
	}

	void SecureData::restore(const char* file, char key) {
		// open binary file
		fstream f(file, ios::in);

		// allocate memory here
		char temp;
		nbytes = 0;
//		f >> std::noskipws;
		while (!f.eof()) {

			f >> temp;
			nbytes++;

		}

		text = new char[nbytes];

		// read binary file here
		f.clear(); //go to beginning
		f.seekg(0, ios::beg);
		nbytes = -1;

		while (!f.eof()) {

			nbytes++;
			f >> text[nbytes];

		}

		text[nbytes] = '\0';

		std::cout << "\n" << nbytes + 1 << " bytes copied from binary file "
			<< file << " into memory (null byte included)\n";
		encoded = true;

		// decode using key
		code(key);
		std::cout << "Data decrypted in memory\n\n";
	}

	std::ostream& operator<<(std::ostream& os, const SecureData& sd) {
		sd.display(os);
		return os;
	}

}