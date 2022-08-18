#include <iostream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include "functions.h"

/**
 * checks if the given file exists
 * @param source_file name of the source file
 * @return true if the given file exists
 */
bool flags::check_file(const std::string& source_file){
     return std::filesystem::exists(source_file);
}

/**
 * counts and prints number of lines in a text file
 * @param source_file - name of the source file
 * @param write_to_a_file - name of the file where data should be written if the flag -o is present
 */
void flags::count_lines(const std::string& source_file, const std::string& write_to_a_file){
    std::string lines;
    int num_of_lines = 0;

    std::ifstream read_line(source_file);
    while(getline(read_line, lines)){
        num_of_lines++;
    }

    if(write_to_a_file != " "){
        auto write_file = std::ofstream(write_to_a_file, std::ios_base::app);
        write_file << "Number of lines : " << num_of_lines << '\n';
    } else {
        std::cout << "Number of lines : " << num_of_lines << '\n';
        std::cout << "=========================" << '\n';
    }
}

/**
 * counts and prints number of digits in a text file
 * @param source_file - name of the source file
 * @param write_to_a_file - name of the file where data should be written if the flag -o is present
 */
void flags::count_digits(const std::string& source_file, const std::string& write_to_a_file){
    int num_of_digits = 0;
    char word;

    std::ifstream read_file(source_file);
    while(read_file >> word){
        if(isdigit(word)){
            num_of_digits++;
        }
    }
    if(write_to_a_file != " "){
        auto write_file = std::ofstream(write_to_a_file, std::ios_base::app);
        write_file << "Number of digits : " << num_of_digits << '\n';
    } else {
        std::cout << "Number of digits : " << num_of_digits << '\n';
        std::cout << "=========================" << '\n';
    }


}

/**
 * removes punctuation marks and checks if the given word consists only of digits
 * @param word - word to check
 * @return true if the word consists only of digits
 */
bool help::check_a_digit(std::string word){

    check_marks(word);

    for(const auto& ch : word){
        if(!isdigit(ch)){
            return false;
        }
    }
    return true;
}

/**
 * counts and prints words which consists only of digits
 * @param source_file - name of the source file
 * @param write_to_a_file - name of the file where data should be written if the flag -o is present
 */
void flags::count_digit_words(const std::string& source_file, const std::string& write_to_a_file){
    int num_of_digits = 0;
    std::string word;

    std::ifstream read_file(source_file);
    while(read_file >> word){
        if(help::check_a_digit(word)){
            num_of_digits++;
        }
    }
    if(write_to_a_file != " "){
        auto write_file = std::ofstream(write_to_a_file, std::ios_base::app);
        write_file << "Number of digits : " << num_of_digits << '\n';
    } else {
        std::cout << "Number of digits words : " << num_of_digits << '\n';
        std::cout << "=========================" << '\n';
    }

}


/**
 * counts and prints number of characters in a text file
 * @param source_file - name of the source file
 * @param write_to_a_file - name of the file where data should be written if the flag -o is presente
 */
void flags::count_character(const std::string& source_file, const std::string& write_to_a_file){
    int num_of_char = 0;
    char line;

    std::ifstream read_file(source_file);
    while(read_file >> line){
        if(line != ' '){
            num_of_char++;
        }
    }

    if(write_to_a_file != " "){
        auto write_file = std::ofstream(write_to_a_file, std::ios_base::app);
        write_file << "Number of characters :" << num_of_char << '\n';
    } else {
        std::cout << "Number of chars : " << num_of_char << '\n';
        std::cout << "=========================" << '\n';
    }

}

/**
 * counts and prints number of words in a text file
 * @param source_file - name of the source file
 * @param write_to_a_file - name of the file where data should be written if the flag -o is present
 */
void flags::count_words(const std::string& source_file, const std::string& write_to_a_file){
    int num_of_words = 0;
    std::string word;

    std::ifstream read_file(source_file);
    while(read_file >> word){
        num_of_words++;
    }

    if(write_to_a_file != " "){
        auto write_file = std::ofstream(write_to_a_file, std::ios_base::app);
        write_file << "Number of words : " << num_of_words << '\n';
    } else {
        std::cout << "Number of words : " << num_of_words << '\n';
        std::cout << "=========================" << '\n';
    }

}

/**
 * prints alphabetically text from a text file
 * @param source_file - name of the source file
 * @param by_length - if true sorts the text by length
 * @param write_to_a_file - name of the file where data should be written if the flag -o is present
 */
void flags::print_alphabetically(const std::string& source_file, bool by_length, const std::string& write_to_a_file){
    std::string word;
    std::vector<std::string> vec_of_words;
    std::string the_way_sorted;

    std::ifstream read_file(source_file);
    while(read_file >> word){
        vec_of_words.push_back(word);
    }
    if(by_length){
        the_way_sorted = "Printed alphabetically by length : ";
        std::sort(vec_of_words.begin(), vec_of_words.end(), [](const std::string& a, const std::string& b){
            return a.size() > b.size();
        });
    } else {
        the_way_sorted = "Printed alphabetically : ";
        std::sort(vec_of_words.begin(), vec_of_words.end());
    }

    if(write_to_a_file != " "){
        auto write_file = std::ofstream(write_to_a_file, std::ios_base::app);
        write_file << the_way_sorted;
        for(const auto& da : vec_of_words){
            write_file << da << ' ';
        }
        write_file << '\n';
    } else {
        std::cout << the_way_sorted;
        for(const auto& str : vec_of_words){
            std::cout << str << ' ';
        }
        std::cout << '\n' << "=========================" << '\n';
    }
}

/**
 * prints reversively text from a text file
 * @param source_file - name of the source file
 * @param by_length - if true sorts the text by length
 * @param write_to_a_file - name of the file where data should be written if the flag -o is present
 */
void flags::print_reversive(const std::string& source_file, bool by_length, const std::string& write_to_a_file){
    std::string word;
    std::vector<std::string> vec_of_words;
    std::string the_way_sorted;

    std::ifstream read_file(source_file);
    while(read_file >> word){
        vec_of_words.push_back(word);
    }

    if(by_length){
        the_way_sorted = "Printed reversive by length : ";
        std::sort(vec_of_words.begin(), vec_of_words.end(), [](const std::string& a, const std::string& b){
            return a.size() < b.size();
        });
    } else {
        the_way_sorted = "Printed reversive : ";
        std::sort(vec_of_words.begin(), vec_of_words.end());
        std::reverse(vec_of_words.begin(), vec_of_words.end());
    }
    if(write_to_a_file != " "){
        auto write_file = std::ofstream(write_to_a_file, std::ios_base::app);
        write_file << the_way_sorted;
        for(const auto& da : vec_of_words){
            write_file << da << ' ';
        }
        write_file << '\n';
    } else {
        std::cout << the_way_sorted;
        for(const auto& str : vec_of_words){
            std::cout << str << ' ';
        }
        std::cout << '\n' << "=========================" << '\n';
    }

}

/**
 * checks and removes if the given word has any punctuation marks at the end
 * @param word - word to check
 * @return word
 */
std::string help::check_marks(std::string& word){
    std::vector<char> vec_of_char {',', '.', ';', ':'};
    for(auto ch : vec_of_char){
        if(ch == word[word.size() - 1]){
            word.pop_back();
        }
    }
    return word;
}

/**
 * checks if the given words are palindromes, and prints those that are also present in the file
 * @param source_file - name of the source file
 * @param vec_of_words - vector of words to check if they are palindroms
 * @param write_to_a_file - name of the file where data should be written if the flag -o is present
 */
void flags::check_palindrom(const std::string& source_file, std::vector<std::string>& vec_of_words, const std::string& write_to_a_file){
    std::vector<std::string> palindroms;
    std::string word;

    vec_of_words.erase(std::remove_if(vec_of_words.begin(), vec_of_words.end(), [](const std::string& word){
        for(int i = 0, j = word.size() - 1; i < j; i++, j--){
            if(word[i] != word[j]){
                return true;
            }
        }
        return false;
    }), vec_of_words.end());

    std::ifstream read_file(source_file);
    while(read_file >> word){
        help::check_marks(word);
        if(std::find(vec_of_words.begin(), vec_of_words.end(), word) != vec_of_words.end()){
            palindroms.push_back(word);
        }
    }
    palindroms.erase(unique(palindroms.begin(), palindroms.end()),palindroms.end());

    if(write_to_a_file != " "){
        auto write_file = std::ofstream(write_to_a_file, std::ios_base::app);
        write_file << "Palindromes in the file : ";
        for(const auto& da : palindroms){
            write_file << da << ' ';
        }
        write_file << '\n';
    } else {
        std::cout << "Palindromes in the file : ";
        for(const auto& s : palindroms){
            std::cout << s << ' ';
        }
        std::cout << '\n' << "=========================" << '\n';
    }
}

/**
 * checks if 2 words are anagrams to each other
 * @param first_str - first word to check
 * @param second_str - second word to check
 * @return true if the given words are anagrams to each other
 */
bool help::anagram(std::string first_str, std::string second_str){
    std::sort(first_str.begin(), first_str.end());
    std::sort(second_str.begin(), second_str.end());
    if(first_str == second_str){
        return true;
    }
    return false;
}

/**
 * checks if the given words are anagrams, and prints those that are also present in the file
 * @param source_file - name of the source file
 * @param vec_of_words - vector of words to check if they are anagrams
 * @param write_to_a_file - name of the file where data should be written if the flag -o is present
 */
void flags::check_anagram(const std::string& source_file, const std::vector<std::string>& vec_of_words, const std::string& write_to_a_file){
    std::vector<std::string> anagrams;
    std::string word;

    std::ifstream read_file(source_file);
    while(read_file >> word){
        help::check_marks(word);
        for(const auto& w : vec_of_words){
            if(w.size() == word.size()){
                auto check = help::anagram(w, word);
                if(check){
                    anagrams.push_back(word);
                }
            }
        }
    }

    anagrams.erase(unique(anagrams.begin(), anagrams.end()),anagrams.end());

    if(write_to_a_file != " "){
        auto write_file = std::ofstream(write_to_a_file, std::ios_base::app);
        write_file << "Anagrams in the file : ";
        for(const auto& da : anagrams){
            write_file << da << ' ';
        }
        write_file << '\n';
    } else {
        std::cout << "Anagrams in the file : ";
        for(const auto& a : anagrams){
            std::cout << a << ' ';
        }
        std::cout << '\n' << "=========================" << '\n';
    }
}

/**
 * finds and prints all the words which starts with the given char
 * @param source_file - name of the source file
 * @param main_char - char with which words must begin
 * @param write_to_a_file - name of the file where data should be written if the flag -o is present
 */
void flags::first_letter(const std::string& source_file, const std::string& main_char, const std::string& write_to_a_file){
    char key_char = main_char[0];
    char second_char;
    if(key_char > 90){
        second_char = toupper(key_char);
    } else {
        second_char = tolower(key_char);
    }

    std::vector<std::string> right_words;
    std::ifstream read_file(source_file);
    std::string word;
    while(read_file >> word){
        if(word[0] == key_char || word[0] == second_char){
            help::check_marks(word);
            right_words.push_back(word);
        }
    }

    if(write_to_a_file != " "){
        auto write_file = std::ofstream(write_to_a_file, std::ios_base::app);
        write_file << "Words starting with letter " << main_char << " : ";
        for(const auto& da : right_words){
            write_file << da << ' ';
        }
        write_file << '\n';
    } else {
        std::cout << "Print words with the first letter " << main_char << " : ";
        for(const auto& a : right_words){
            std::cout << a << ' ';
        }
        std::cout << '\n' << "=========================" << '\n';
    }
}


