#include "StrFormater.h"

std::string& StrFormater::get_str() {
	std::string* ret_string = new std::string(*this->formating_str);
	for (int i = 0; i < this->conformity_arr->size(); i++) {
		std::string replacing_pattern = "{" + std::to_string(i) + "}";
		int replacing_pattern_len = replacing_pattern.length();
		int replacing_pattern_entrance = ret_string->find(replacing_pattern);
		if (replacing_pattern_entrance == std::string::npos) {
			continue;
		}
		ret_string->replace(replacing_pattern_entrance, replacing_pattern_len, (*this->conformity_arr)[i]);
	}
	return *ret_string;
}

StrFormater::StrFormater(std::string str) {
	formating_str = new std::string(str);
	conformity_arr = new std::vector<std::string>();
}

void StrFormater::del_args() {
	conformity_arr->clear();
}

int StrFormater::get_pattern_num(std::string::iterator& begin_pattern, std::string::iterator& end_pattern) {
	std::string::iterator num_iter = begin_pattern + 1;
	if (num_iter == end_pattern) {
		const char* err_str = "Invalid pattern in string, no number between { }";
		throw new std::exception(err_str);
	}

	int str_len = end_pattern - num_iter;
	char* num_str = new char[str_len + 1];
	num_str[str_len] = '\0';
	for (int i = 0; i < str_len; i++) {
		num_str[i] = *num_iter;
		num_iter++;
	}

	return atoi(num_str);
}

std::string::iterator StrFormater::get_pattern_end(const std::string::iterator& begin_pattern, const std::string::iterator& end_str) {
	std::string::iterator end_pattern = begin_pattern;
	while (end_pattern != end_str && *end_pattern != '}') {
		end_pattern++;
	}
	if (end_pattern == end_str) {
		const char* err_str = "Invalid pattern in string, no \'}\' was found";
		throw new std::exception(err_str);
	}
	return end_pattern;
}

void StrFormater::inner_set_args(std::initializer_list<std::string> arg_list) {
	for (auto argument : arg_list) {
		conformity_arr->push_back(*new std::string(argument));
	}
}