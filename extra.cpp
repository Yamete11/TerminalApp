#include <iostream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include "extra.h"


/**
 * changes aliases to flags
 * @param vec_of_arg - vector of arguments to change
 * @return vector of changes flags
 */
std::vector<std::string> change_alias(const std::vector<std::string>& vec_of_arg){
    std::vector<std::string> vec = vec_of_arg;
    std::map<std::string, std::string> alias {
            {"-f", "--file"},
            {"-n", "--newlines"},
            {"-d", "--digits"},
            {"-dd", "--numbers"},
            {"-c", "--chars"},
            {"-w", "--words"},
            {"-s", "--sorted"},
            {"-rs", "--reverse-sorted"},
            {"-l", "--by-length"},
            {"-a", "--anagrams"},
            {"-o", "--palindromes"},
            {"-i", "--input"},
            {"-fl", "--first-letter"}
    };

    for(auto& arg : vec){
        for(const auto& alia : alias){
            if(arg == alia.second){
                arg = alia.first;
            }
        }
    }
    return vec;
}

/**
 * checks if the given value if a flag
 * @param value - to check if it's a flag
 * @return true if the given value is a flag
 */
bool is_a_flag(const std::string& value){
    std::vector<std::string> vec_of_flags {"-f", "-n", "-d", "-dd", "-c", "-w", "-s", "-rs", "-l", "-a", "-o", "-i", "-p", "-fl"};
    for(const auto& flag : vec_of_flags){
        if(value == flag){
            return true;
        }
    }
    return false;
};

/**
 * checks if there is a flag in a vector of arguments
 * @param index - index to start from
 * @param arguments - vector of arguments to check
 * @return true if there is a flag in the vector
 */
bool rest_of_the_arg(int index, const std::vector<std::string>& arguments){
    for(int i = index; i < arguments.size(); i++){
        if(is_a_flag(arguments[i])){
            return true;
        }
    }
    return false;
};


/**
 * check if there is a right order of given arguments
 * @param arguments vector of arguments to check
 */
void check_the_order(const std::vector<std::string>& arguments) {
    if (std::count(arguments.begin(), arguments.end(), "-f") > 1) {
        throw std::runtime_error("Flag '-f' can be used only once, at the beginning of the command.");
    }
    for(int i = 0; i < arguments.size(); i++) {
        if(arguments[0] != "-f"){
            throw std::runtime_error("Flag '-f' must be at the beginning of the command.");
        } else if(arguments[i] == "-f" && !std::filesystem::exists(arguments[i + 1])){
            throw std::runtime_error("After the flag '-f' must be given a source file.");
        } else if(arguments[i] == "-l" && !(arguments[i + 1] == "-s" || arguments[i + 1] == "-rs")){
            throw std::runtime_error("After the flag '-l' must be given the flag '-s' or '-rs'.");
        } else if(arguments[i] == "-o" && is_a_flag(arguments[i + 1])){
            throw std::runtime_error("After the flag '-o' must be given a file path.");
        } else if(arguments[i] == "-a" && rest_of_the_arg(i + 1, arguments)){
            throw std::runtime_error("The flag '-a' must be the last used flag in the command.");
        } else if(arguments[i] == "-p" && rest_of_the_arg(i + 1, arguments)){
            throw std::runtime_error("The flag '-p' must be the last used flag in the command.");
        } else if(arguments[i] == "-fl" && is_a_flag(arguments[i + 1])){
            throw std::runtime_error("After the flag '-fl' must be given a character.");
        } else if(arguments[i] == "-fl" && arguments[i + 1].size() > 1){
            throw std::runtime_error("After the flag '-fl' must be given a single character.");
        };
};
}

/**
 * check if there is a right order of given arguments
 * @param arguments - vector of arguments to check
 */
void check_with_i_order(const std::vector<std::string>& arguments){
    if(arguments.size() > 3){
        throw std::runtime_error("Too many arguments in the command. Number of arguments should be equal 3.");
    } else if(arguments.size() < 3){
        throw std::runtime_error("Too little arguments in the command. Number of arguments should be equal 3.");
    } else if(arguments[0] != "-i"){
        throw std::runtime_error("The flag '-i' must be the first used flag.");
    } else if(arguments[0] == "-i" && rest_of_the_arg(1, arguments)){
        throw std::runtime_error("The flag '-i' must be the only used flag.");
    }
}

/**
 * looks for flag '-o' in the given vector
 * @param arguments_to_check - vector of arguments to check
 * @return true if there is the '-o' flag in the given vector
 */
std::string find_o(const std::vector<std::string>& arguments_to_check) {
    auto it = std::find(arguments_to_check.begin(), arguments_to_check.end(), "-o");
    auto index = std::distance(arguments_to_check.begin(), it) + 1;

    std::string extra_file_name;

    if(index > arguments_to_check.size()){
        extra_file_name = " ";
    } else {
        extra_file_name = arguments_to_check[index];
    }
    return extra_file_name;
}

/**
 * rearrange vector in the correct way, if the flag '-i' has been found
 * @param vec_of_arg - vector of arguments to rearrange
 * @return vector of rearranged arguments
 */
std::vector<std::string> rearrange_after_i(const std::vector<std::string>& vec_of_arg){
    std::vector<std::string> vec_for_i;
    std::string word;

    std::ifstream read_file(vec_of_arg[1]);
    read_file >> word;
    vec_for_i.push_back(word);
    vec_for_i.push_back(vec_of_arg[2]);
    while(read_file >> word){
        vec_for_i.push_back(word);

    }
    return vec_for_i;
};

/**
 * checks if there is the flag '-i' in the given vector
 * @param vec_of_arg - vector of arguments to check
 * @return true if there is the flag '-i' in the vector
 */
bool check_for_i(const std::vector<std::string>& vec_of_arg){
    for(const auto& i : vec_of_arg){
        if(i == "-i"){
            return true;
        }
    }
    return false;
};


/**
 * prints name of the program, what it is created for and possible flags to use in the program
 */
void print_info(){
    std::cout << "========================== " << "PJAText2" << " ==========================" << '\n' << '\n'
              << "The program is designed to display information about a text file." << '\n'
              << "By using different flags, you can display the relevant information." << '\n' << '\n'
              << "List of possible flags : " << '\n' << '\n'
              << "'-f' or '--file' - checks if the given file exists. The flag can be used only" << '\n'
              << "once and must be placed at the beginning of the command. " << '\n'
              << "Correct order : '-f' 'source file' ..." << '\n' << '\n'
              << "'-n' or '--newlines' - displays the number of lines in a source file. Can only" << '\n'
              << "be used if the -f flag is present at the beginning of the command. " << '\n'
              << "Correct order : '-f' 'source file' '-n' ..." << '\n' << '\n'
              << "'-d' or '--digits' - displays the number of digits in a source file. Can only" << '\n'
              << "be used if the -f flag is present at the beginning of the command. " << '\n'
              << "Correct order : '-f' 'source file' '-d' ..." << '\n' << '\n'
              << "'-dd' or '--numbers' - displays the number of digits separated by whitespaces in a source" << '\n'
              << "file. Can only be used if the -f flag is present at the beginning of the command. " << '\n'
              << "Correct order : '-f' 'source file' '-dd' ..." << '\n' << '\n'
              << "'-c' or '--chars' - displays the number of characters in a source file. Can only" << '\n'
              << "be used if the -f flag is present at the beginning of the command. " << '\n'
              << "Correct order : '-f' 'source file' '-c' ..." << '\n' << '\n'
              << "'-w' or '--words' - displays the number of words in a source file. Can only" << '\n'
              << "be used if the -f flag is present at the beginning of the command. " << '\n'
              << "Correct order : '-f' 'source file' '-w' ..." << '\n' << '\n'
              << "'-s' or '--sorted' - displays all words from the source file in alphabetical order. Can only" << '\n'
              << "be used if the -f flag is present at the beginning of the command. " << '\n'
              << "Correct order : '-f' 'source file' '-s' ..." << '\n' << '\n'
              << "'-rs' or '--reverse-sorted' - display all words in the source file in reverse alphabetical order." << '\n'
              << "Can only be used if the -f flag is present at the beginning of the command. " << '\n'
              << "Correct order : '-f' 'source file' '-rs' ..." << '\n' << '\n'
              << "'-l' or '--by-length' - modify the behavior of the -s or -rs flag that follows so that instead " << '\n'
              << "of taking the alphabetical order into account, the flags respect the order specified by the" << '\n'
              << "length of the individual words." << '\n'
              << "Can only be used if the -f flag is present at the beginning of the command. " << '\n'
              << "Correct order : '-f' 'source file' '-l' *'-s' or '-rs'* ..." << '\n' << '\n'
              << "'-a' or '--anagrams' - displays all words from the source file that are anagrams" << '\n'
              << "of words just after the flag. The '-a' flag should be the last specified flag" << '\n'
              << "followed by an indefinite number of words (can be 0)" << '\n'
              << "Can only be used if the -f flag is present at the beginning of the command. " << '\n'
              << "Correct order : '-f' 'source file' '-a' 'argument [1]' 'argument [2]' ..." << '\n' << '\n'
              << "'-p' or '--palindromes' - display all words that follow -p that are palindromes and" << '\n'
              << "appear in the source file. The '-p' flag should be the last specified flag" << '\n'
              << "followed by an indefinite number of words (can be 0)" << '\n'
              << "Can only be used if the -f flag is present at the beginning of the command. " << '\n'
              << "Correct order : '-f' 'source file' '-p' 'argument [1]' 'argument [2]' ..." << '\n' << '\n'
              << "'-o' or '--output' - modifies the program operation in such a way that instead of" << '\n'
              << "displaying information on the console in which the application is launched, the" << '\n'
              << "effect of the program operation in the form of text has been saved to a output file with" << '\n'
              << "a specified (output file) path" << '\n'
              << "Can only be used if the -f flag is present at the beginning of the command. " << '\n'
              << "Correct order : '-f' 'source file' '-o' 'output file' ..." << '\n' << '\n'
              << "'-i' or '--input - after which the path to the input file is expected, modifies the" << '\n'
              << "operation of the program in such a way that instead of specifying the" << '\n'
              << "rest of the flags as arguments, the application should retrieve the" << '\n'
              << "flags and their data from the input file. This flag should be the only" << '\n'
              << "one specified when starting the application (the rest of the flag is included in the input file)." << '\n'
              << "Correct order : '-i' 'input file' 'source file'" << '\n' << '\n';


}

