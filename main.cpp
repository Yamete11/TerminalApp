#include <iostream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include "functions.h"
#include "extra.h"


int main(int args_count, const char* args[]) {
    const auto arguments = std::vector<std::string>(args + 1, args + args_count);

    if(arguments.empty()){
        print_info();
    }

    std::vector<std::string> clean_list = change_alias(arguments);

    try{

        if(check_for_i(clean_list)){
            check_with_i_order(clean_list);
            clean_list = rearrange_after_i(clean_list);
        }

        check_the_order(clean_list);


        std::string write_to_a_file = find_o(clean_list);



        for (int i = 0; i < clean_list.size(); i++) {
            if (clean_list[i] == "-d") {
                flags::count_digits(clean_list[1], write_to_a_file);
            } else if (clean_list[i] == "-f") {
                flags::check_file(clean_list[1]);
            } else if (clean_list[i] == "-dd") {
                flags::count_digit_words(clean_list[1], write_to_a_file);
            } else if (clean_list[i] == "-c") {
                flags::count_character(clean_list[1], write_to_a_file);
            } else if (clean_list[i] == "-w") {
                flags::count_words(clean_list[1], write_to_a_file);
            } else if (clean_list[i] == "-s") {
                flags::print_alphabetically(clean_list[1], false, write_to_a_file);
            } else if (clean_list[i] == "-rs") {
                flags::print_reversive(clean_list[1], false, write_to_a_file);
            } else if (clean_list[i] == "-l") {
                if (clean_list[i + 1] == "-s") {
                    flags::print_alphabetically(clean_list[1], true, write_to_a_file);
                } else if (clean_list[i + 1] == "-rs") {
                    flags::print_reversive(clean_list[1], true, write_to_a_file);
                }
                i++;
            } else if (clean_list[i] == "-p"){
                std::vector<std::string> words_to_use (clean_list.begin() + i, clean_list.end());
                flags::check_palindrom(clean_list[1], words_to_use, write_to_a_file);
            } else if (clean_list[i] == "-a"){
                std::vector<std::string> words_to_use (clean_list.begin() + i, clean_list.end());
                flags::check_anagram(clean_list[1], words_to_use, write_to_a_file);
            } else if (clean_list[i] == "-n"){
                flags::count_lines(clean_list[1], write_to_a_file);
            } else if (clean_list[i] == "-fl"){
                std::string main_char = clean_list[i + 1];
                flags::first_letter(clean_list[1], main_char, write_to_a_file);
            }
        }
    } catch (const std::runtime_error& ex){
        std::cout << ex.what();
    }


}
