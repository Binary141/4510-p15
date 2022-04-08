#include <iostream>
#include <string>
#include <bitset>
#include <bits/stdc++.h>
#include <list>

int main(){
	std::string text;
	std::string key;
	std::string binary_str;
	std::string binary_key;
	int padding = 0;
	std::string temp_string;
	std::vector<std::string> string_list;
	std::string binary_key_12_bits;
	std::string final_str;
	long int number;
	long int temp_number;
	const int length = 12;

	std::cout << "Key? ";
       	std::cin >> key;
	std::cout << std::endl;
	
	// Convert key to binary	
	for (std::size_t i = 0; i < key.size(); i++){
		binary_key.append(std::bitset<8>(key[i]).to_string());
	}

	std::cout << "text? ";
       	std::cin >> text;
	std::cout << std::endl;
	// Convert text to binary	
	for (std::size_t i = 0; i < text.size(); i++){
		binary_str.append(std::bitset<8>(text[i]).to_string());
	}

	while ((binary_str.size() % length) != 0 ){
		binary_str.append("1");
		padding += 1;
		binary_str.append("0");
		padding += 1;
	}

	binary_str.append(std::bitset<length>(padding).to_string());
	for (int i=0; i < binary_str.size(); i++){
		temp_string += binary_str[i];
		if(temp_string.size() == length){
			string_list.push_back(temp_string);
			temp_string = "";
		}
	}

	std::cout <<  "After the block is added that tells us how much padding was added (12-bit block): " << std::endl;
	for (int i=0; i < string_list.size(); i++){
		std::cout << string_list[i];
	}
	std::cout << std::endl << std::endl;

	binary_key_12_bits = binary_key.substr(0,length);
	for (int i=0; i < string_list.size(); i++){
		if( i == 0 ){
			// first run through with no previous xor
			reverse(string_list[0].begin(), string_list[0].end());
			number = std::bitset<length>(binary_key_12_bits).to_ulong() ^ std::bitset<length>(string_list[0]).to_ulong();
			temp_number = std::bitset<length>(binary_key_12_bits).to_ulong() ^ std::bitset<length>(string_list[0]).to_ulong();
			std::cout << "Key in binary (first 12 bits): " << binary_key_12_bits << std::endl;
			std::cout << "First 12 bit block (reversed): " << string_list[0] << std::endl;
			std::cout << "Xor:          " << std::bitset<length>(number) << std::endl;

			final_str.append(std::bitset<length>(number).to_string());
		}
		else{
			// take previous xor, xor it with next block, then revverse the output and xor that with the key
			std::cout << "2nd 12 bit block		" << std::bitset<length>(string_list[i]) << std::endl;
			std::cout << "Output of last Xor	" << std::bitset<length>(number) << std::endl;
			temp_number = std::bitset<length>(number).to_ulong() ^ std::bitset<length>(string_list[i]).to_ulong();
			number = std::bitset<length>(temp_number).to_ulong();
			std::cout << "Xor			" << std::bitset<length>(number) << std::endl << std::endl;

			std::cout << "Key in binary (first 12 bits): " << binary_key_12_bits << std::endl;
			// reverses the xor output
			auto x = std::bitset<length>(number);
			auto str = x.to_string();
			std::reverse(str.begin(), str.end());
			auto y = std::bitset<length>(str);
			std::cout << "Xor'ed output (reversed)	   : " << y << std::endl;
			temp_number = std::bitset<length>(y).to_ulong() ^ std::bitset<length>(binary_key_12_bits).to_ulong();
			number = std::bitset<length>(temp_number).to_ulong();
			std::cout << "Xor			" << std::bitset<length>(number) << std::endl << std::endl;

			final_str.append(std::bitset<length>(number).to_string());
		}
		std::cout << std::endl;
		
	}
	std::cout << "FINAL_STR: " << final_str << std::endl;

	return 0;
}
