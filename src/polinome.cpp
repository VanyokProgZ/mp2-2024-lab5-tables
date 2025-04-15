#include "polinome.h"

bool check_allow_main_symb(const std::string& s) {	//check all nums or vars in string
	for (const auto& el : s) {
		if (!_dig(el) && !vars(el)) return 0;
	}
	return 1;
}

bool all_Nums(const std::string& s) {	//check all nums in string
	for (const auto& el : s) {
		if (!_dig(el)) return 0;
	}
	return 1;
}