#pragma once
#include <string>
#include <vector>
#include <exception>
#include <regex>

class StrFormater {
public:
	template <typename... str_args>
	StrFormater(std::string str, str_args... args);
	StrFormater(std::string str);
	std::string& get_str();
	template <typename... str_args>
	void set_args(str_args... args);
	void del_args();
private:
	std::vector<std::string>* conformity_arr;
	std::string* formating_str;

	void inner_set_args(std::initializer_list<std::string> arg_list);
	int get_pattern_num(std::string::iterator& begin_pattern, std::string::iterator& end_str);
	std::string::iterator get_pattern_end(const std::string::iterator& begin_pattern, const std::string::iterator& end_str);
};

template <typename... str_args>
StrFormater::StrFormater(std::string str, str_args... args) : StrFormater(str) {
	std::initializer_list<std::string> arg_list = { args... };
	this->inner_set_args(arg_list);
}

template <typename... str_args>
void StrFormater::set_args(str_args... args) {
	std::initializer_list<std::string> arg_list = { args... };
	this->inner_set_args(arg_list);
}