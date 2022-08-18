#ifndef PROJECT_FUNCTIONS_H
#define PROJECT_FUNCTIONS_H


namespace help{
    std::string check_marks(std::string& word);

    bool check_a_digit(std::string word);

    bool anagram(std::string first_str, std::string second_str);
}



namespace flags{
    bool check_file(const std::string& path_file);

    void count_lines(const std::string& source_file, const std::string& write_to_a_file);

    void count_digits(const std::string& source_file, const std::string& write_to_a_file);

    void count_digit_words(const std::string& source_file, const std::string& write_to_a_file);

    void count_character(const std::string& source_file, const std::string& write_to_a_file);

    void count_words(const std::string& source_file, const std::string& write_to_a_file);

    void print_alphabetically(const std::string& source_file, bool by_length, const std::string& write_to_a_file);

    void print_reversive(const std::string& source_file, bool by_length, const std::string& write_to_a_file);

    void check_palindrom(const std::string& source_file, std::vector<std::string>& vec_of_words, const std::string& write_to_a_file);

    void check_anagram(const std::string& source_file, const std::vector<std::string>& vec_of_words, const std::string& write_to_a_file);

    void first_letter(const std::string& source_file, const std::string& vec_of_words, const std::string& write_to_a_file);

}

#endif
