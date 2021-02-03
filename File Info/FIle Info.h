#pragma once
#include <fstream>
#include <iostream>
#include <string>

class File_Info {

public:

	using sz = std::string::size_type;

	File_Info() = delete;
	File_Info(std::string file_path) : f_path(file_path), info_read(false) {}

	void read_info() {

		std::ifstream file(f_path);
		char c = ' ';

		while (file.get(c)) {
			s_file += c;
		}
		file.close();

		info_read = true;

	}

	sz n_lines() {

		if (info_read) {

			sz num_lines = 0;
			sz index = s_file.find_first_of("\n\r");;
			
			while (index != 0) {
				index = s_file.find_first_of("\n\r", index);
				++index;
				++num_lines;
			}
			
			return num_lines;

		}

		std::cerr << "Must read file first." << std::endl;

	}
	sz n_words() {

		if (info_read) {

			sz num_words = 0;
			sz index = s_file.find_first_not_of(" \n\r");
			while (index != std::string::npos) {
				index = s_file.find_first_of(" \n\r", index);
				index = s_file.find_first_not_of(" \n\r", index);
				++num_words;
			}

			return num_words;

		}	

		std::cerr << "Must read file first." << std::endl;

	}
	int n_bytes() {

		std::ifstream file(f_path);
		file.seekg(0, file.end);
		return file.tellg();

	}

	std::string f_path;
	std::string s_file;

private:

	bool info_read;

};
