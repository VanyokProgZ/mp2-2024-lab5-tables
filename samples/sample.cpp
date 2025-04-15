#include <iostream>
#include "RBTREE.h"
#include <random>
#include "vector.h"
#include "DoubleHash.h"
#include "polinome.h"
#if defined(_WIN32)
const char* OS_CLEAR = "cls";
#elif defined(__linux__)
const char* OS_CLEAR = "clear";
#elif defined(__unix__)
const char* OS_CLEAR = "clear";
#endif
#define CLS system(OS_CLEAR)

int main()
{
	try {
		std::cout << "Type size of hash_table: ";
		size_t inpsz;
		std::cin >> inpsz;
		HASH_TABLE_STRING<Polinome<double>> hash_table(inpsz);
		RBTree<Polinome<double>, std::string> redBlackTree;
		while (1) {
			std::string q;
			std::cout << "The polynomials are entered in the following format: 'CXaYbZc + CYbXaZc - ZcYa + C' ->\nC - const, \nX - 'X or x', Y - 'Y or y', Z-'Z or z';\na,b,c - degrees of X Y Z\n\n ";
			std::cout << "\nEXAMPLE OF POLINOM: 23x4y6z7 - xyz + 5z - 65yz8\n\n";
			std::cout << "what to do?\n1 -> arithmetics\n2 -> insert new polinome\n3 -> delete polinome\n4 -> find\nexit -> exit()\nYour choice: ";
			std::cin >> q;
			if (q == "1") {
				CLS;
				std::cout << "what to do?\n1 -> polinome + polinome\n2 -> polinome - polinome\n3 -> polinome * polinome\n4 -> polinome * double\nback -> back()\nYour choice: ";
				std::cin >> q;
				if (q == "1") {
					std::string s1, s2;
					std::pair<bool, Data<std::string, Polinome<double>>> r1;
					Polinome<double> a, b;
					while (1)
					{
						std::cout << "Enter the name of first polinome: ";
						std::cin >> s1;
						r1 = hash_table.find(s1);
						if (r1.first) {
							break;
						}
						std::cout << "Cant find this Polinome, type name again? (1/0): ";
						std::cin >> q;
						if (q == "0") {
							break;
						}
					}
					if (!r1.first) continue;
					a = r1.second.getData();
					while (1)
					{
						std::cout << "Enter the name of second polinome: ";
						std::cin >> s1;
						r1 = hash_table.find(s1);
						if (r1.first) {
							break;
						}
						std::cout << "Cant find this Polinome, type name again? (1/0): ";
						std::cin >> q;
						if (q == "0") {
							break;
						}
					}
					if (!r1.first) continue;
					b = r1.second.getData();
					Polinome<double> res = (a + b);
					std::cout << "HASH_TABLE Result first + second: " << res << std::endl;
					std::cout << "Save result into tables? (1/0): ";
					std::cin >> q;
					if(q=="1"){
						std::cout << "What name of result polinome?: ";
						std::cin >> q;
						Data<std::string, Polinome<double>> ins_d(q, res);
						hash_table.insert(ins_d);
						redBlackTree.insert(ins_d);
					}
					std::cout << "\nType something to continue\n";
					std::cin >> q;
					CLS;
				}
				else if (q == "2") {
					std::string s1, s2;
					std::pair<bool, Data<std::string, Polinome<double>>> r1;
					Polinome<double> a, b;
					while (1)
					{
						std::cout << "Enter the name of first polinome: ";
						std::cin >> s1;
						r1 = hash_table.find(s1);
						if (r1.first) {
							break;
						}
						std::cout << "Cant find this Polinome, type name again? (1/0): ";
						std::cin >> q;
						if (q == "0") {
							break;
						}
					}
					if (!r1.first) continue;
					a = r1.second.getData();
					while (1)
					{
						std::cout << "Enter the name of second polinome: ";
						std::cin >> s1;
						r1 = hash_table.find(s1);
						if (r1.first) {
							break;
						}
						std::cout << "Cant find this Polinome, type name again? (1/0): ";
						std::cin >> q;
						if (q == "0") {
							break;
						}
					}
					if (!r1.first) continue;
					b = r1.second.getData();
					Polinome<double> res = (a - b);
					std::cout << "HASH_TABLE Result first - second: " << res << std::endl;
					std::cout << "Save result into tables? (1/0): ";
					std::cin >> q;
					if (q == "1") {
						std::cout << "What name of result polinome?: ";
						std::cin >> q;
						Data<std::string, Polinome<double>> ins_d(q, res);
						hash_table.insert(ins_d);
						redBlackTree.insert(ins_d);
					}
					std::cout << "\nType something to continue\n";
					std::cin >> q;
					CLS;
				}
				else if (q == "3") {
					std::string s1, s2;
					std::pair<bool, Data<std::string, Polinome<double>>> r1;
					Polinome<double> a, b;
					while (1)
					{
						std::cout << "Enter the name of first polinome: ";
						std::cin >> s1;
						r1 = hash_table.find(s1);
						if (r1.first) {
							break;
						}
						std::cout << "Cant find this Polinome, type name again? (1/0): ";
						std::cin >> q;
						if (q == "0") {
							break;
						}
					}
					if (!r1.first) continue;
					a = r1.second.getData();
					while (1)
					{
						std::cout << "Enter the name of second polinome: ";
						std::cin >> s1;
						r1 = hash_table.find(s1);
						if (r1.first) {
							break;
						}
						std::cout << "Cant find this Polinome, type name again? (1/0): ";
						std::cin >> q;
						if (q == "0") {
							break;
						}
					}
					if (!r1.first) continue;
					b = r1.second.getData();
					Polinome<double> res = (a * b);
					std::cout << "HASH_TABLE Result first * second: " << res << std::endl;
					std::cout << "Save result into tables? (1/0): ";
					std::cin >> q;
					if (q == "1") {
						std::cout << "What name of result polinome?: ";
						std::cin >> q;
						Data<std::string, Polinome<double>> ins_d(q, res);
						hash_table.insert(ins_d);
						redBlackTree.insert(ins_d);
					}
					std::cout << "\nType something to continue\n";
					std::cin >> q;
					CLS;
				}
				else if (q == "4") {
					std::string s1, s2;
					std::pair<bool, Data<std::string, Polinome<double>>> r1;
					Polinome<double> a;
					double b;
					while (1)
					{
						std::cout << "Enter the name of first polinome: ";
						std::cin >> s1;
						r1 = hash_table.find(s1);
						if (r1.first) {
							break;
						}
						std::cout << "Cant find this Polinome, type name again? (1/0): ";
						std::cin >> q;
						if (q == "0") {
							break;
						}
					}
					std::cout << "Enter the constant: ";
					std::cin >> q;
					b = parser_My(q);
					if (!r1.first) continue;
					a = r1.second.getData();
					Polinome<double> res = (a * b);
					std::cout << "HASH_TABLE Result first * const: " << res << std::endl;
					std::cout << "Save result into tables? (1/0): ";
					std::cin >> q;
					if (q == "1") {
						std::cout << "What name of result polinome?: ";
						std::cin >> q;
						Data<std::string, Polinome<double>> ins_d(q, res);
						hash_table.insert(ins_d);
						redBlackTree.insert(ins_d);
					}
					std::cout << "\nType something to continue\n";
					std::cin >> q;
					CLS;
				}
				else if (q == "back") {
					continue;
				}
				else {
					std::cout << "Type something to continue\n";
					std::cin >> q;
					CLS;
				}
			}
			else if (q == "2") {
				std::cout << "Enter the number of Monoms in first polinome: ";
				size_t sz1;
				std::cin >> sz1;
				Polinome<double> a(sz1);
				std::cout << "Type polinom: ";
				std::cin >> a;
				std::cout << "Enter the name of polinom: ";
				std::cin >> q;
				Data<std::string, Polinome<double>> ins_d(q, a);
				hash_table.insert(ins_d);
				redBlackTree.insert(ins_d);
			}
		}
	}
    catch (const std::exception& e) {
        std::cout << e.what() << '\n';
    }
}