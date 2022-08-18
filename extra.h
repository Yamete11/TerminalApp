#ifndef PROJECT_EXTRA_H
#define PROJECT_EXTRA_H

void check_the_order(const std::vector<std::string>& arguments);
std::vector<std::string> change_alias(const std::vector<std::string>& vec_of_arg);
bool check_for_i(const std::vector<std::string>& vec_of_arg);
std::vector<std::string> rearrange_after_i(const std::vector<std::string>& vec_of_arg);

std::string find_o(const std::vector<std::string>& arguments_to_check);
bool is_a_flag(const std::string& value);
bool rest_of_the_arg(int index, const std::vector<std::string>& vector);
void print_info();
void check_f_flag(const std::string& first_value, const std::string& second_value);
void check_with_i_order(const std::vector<std::string>& arguments);


#endif
