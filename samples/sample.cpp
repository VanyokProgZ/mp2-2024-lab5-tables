#include <iostream>
#include "RBTREE.h"
#include <random>
#include "vector.h"
#include "DoubleHash.h"
#include "polinome.h"
#include "arrays.h"

#if defined(_WIN32)
const char* OS_CLEAR = "cls";
#elif defined(__linux__)
const char* OS_CLEAR = "clear";
#elif defined(__unix__)
const char* OS_CLEAR = "clear";
#endif
#define CLS system(OS_CLEAR)

template<class T>
void Log_Table(const std::string& name,HASH_TABLE_STRING<T>&h, RBTree<T, std::string>& tree, unsorted_array<T>& ua, sorted_array<T>& sa,bool make_null) {
	std::cout << "-----------------------------------------\n";
	std::cout << "operation name: \t" << name<<'\n';
	std::cout << "Hash table: \t" << h.Log() << '\n';
	std::cout << "Red Black Tree: \t" << tree.Log() << '\n';
	std::cout << "Unsorted array: \t" << ua.Log() << '\n';
	std::cout << "Sorted array: \t" << sa.Log() << '\n';
	std::cout << "-----------------------------------------\n";
	if (make_null) {
		h.resetLog();
		tree.resetLog();
		ua.resetLog();
		sa.resetLog();
	}
}

int main()
{
	try {
		std::cout << "Type size of hash_table (programm set the first prime >= your number): ";
		size_t inpsz;
		std::cin >> inpsz;
		if (inpsz < 1000) {
			std::cout << "No, it's small size; now size = 1013\n";
			inpsz = 1013;
		}
		HASH_TABLE_STRING<Polinome<double>> hash_table(inpsz);
		RBTree<Polinome<double>, std::string> redBlackTree;
		unsorted_array<Polinome<double>> uns_arr;
		sorted_array<Polinome<double>> s_arr;

		while (1) {
			std::string q;
			std::cout << "The polynomials are entered in the following format: 'CXaYbZc + CYbXaZc - ZcYa + C' ->\nC - const, \nX - 'X or x', Y - 'Y or y', Z-'Z or z';\na,b,c - degrees of X Y Z\n\n ";
			std::cout << "\nEXAMPLE OF POLINOM: 23x4y6z7 - xyz + 5z - 65yz8\n\n";
			std::cout << "what to do?\n1 -> arithmetics\n2 -> insert new polinome\n3 -> delete polinome\n4 -> find\nexit -> exit()\nYour choice: ";
			std::cin >> q;
			if (q == "1") {
				CLS;
				std::cout << "LOG ONLY TABLE OPERATIONS! - without real +-*.., only insert,find,delete\n";
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
						redBlackTree.find_vertex_by_key(s1);
						uns_arr.find_by_name(s1);
						s_arr.find_by_name(s1);
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
						redBlackTree.find_vertex_by_key(s1);
						uns_arr.find_by_name(s1);
						s_arr.find_by_name(s1);
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
					std::cout << "Result first + second: " << res << std::endl;
					Log_Table("Polinum plus Polinome (with all finding! (and not successful too!))", hash_table, redBlackTree, uns_arr, s_arr, 1);
					std::cout << "Save result into tables? (1/0): ";
					std::cin >> q;
					if(q=="1"){
						std::cout << "What name of result polinome?: ";
						std::cin >> q;
						auto r_ = redBlackTree.HaveAKey(q);
						while (r_) {
							std::cout << "That key already exists!\ntype name again? (1/0): ";
							std::cin >> q;
							if (q == "1") {
								std::cout << "What name of result polinome?: ";
								std::cin >> q;
								r_ = redBlackTree.HaveAKey(q);
							}
							else {
								break;
							}
						}
						hash_table.resetLog();
						redBlackTree.resetLog();
						uns_arr.resetLog();
						s_arr.resetLog();
						if (!r_) {
							Data<std::string, Polinome<double>> ins_d(q, res);
							hash_table.insert(ins_d);
							redBlackTree.insert(ins_d);
							s_arr.insert(ins_d);
							uns_arr.insert(ins_d);
							Log_Table("insert", hash_table, redBlackTree, uns_arr, s_arr, 1);
						}
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
						redBlackTree.find_vertex_by_key(s1);
						uns_arr.find_by_name(s1);
						s_arr.find_by_name(s1);
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
						redBlackTree.find_vertex_by_key(s1);
						uns_arr.find_by_name(s1);
						s_arr.find_by_name(s1);
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
					Log_Table("Polinum minus Polinome (with all finding! (and not successful too!))", hash_table, redBlackTree, uns_arr, s_arr, 1);
					std::cout << "Save result into tables? (1/0): ";
					std::cin >> q;
					if (q == "1") {
						std::cout << "What name of result polinome?: ";
						std::cin >> q;
						auto r_ = redBlackTree.HaveAKey(q);
						while (r_) {
							std::cout << "That key already exists!\ntype name again? (1/0): ";
							std::cin >> q;
							if (q == "1") {
								std::cout << "What name of result polinome?: ";
								std::cin >> q;
								r_ = redBlackTree.HaveAKey(q);
							}
							else {
								break;
							}
						}
						hash_table.resetLog();
						redBlackTree.resetLog();
						uns_arr.resetLog();
						s_arr.resetLog();
						if (!r_) {
							Data<std::string, Polinome<double>> ins_d(q, res);
							hash_table.insert(ins_d);
							redBlackTree.insert(ins_d);
							s_arr.insert(ins_d);
							uns_arr.insert(ins_d);
							Log_Table("insert", hash_table, redBlackTree, uns_arr, s_arr, 1);
						}
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
						redBlackTree.find_vertex_by_key(s1);
						uns_arr.find_by_name(s1);
						s_arr.find_by_name(s1);
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
						redBlackTree.find_vertex_by_key(s1);
						uns_arr.find_by_name(s1);
						s_arr.find_by_name(s1);
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
					Log_Table("Polinum multiply Polinome (with all finding! (and not successful too!))", hash_table, redBlackTree, uns_arr, s_arr, 1);
					std::cout << "Save result into tables? (1/0): ";
					std::cin >> q;
					if (q == "1") {
						std::cout << "What name of result polinome?: ";
						std::cin >> q;
						auto r_ = redBlackTree.HaveAKey(q);
						while (r_) {
							std::cout << "That key already exists!\ntype name again? (1/0): ";
							std::cin >> q;
							if (q == "1") {
								std::cout << "What name of result polinome?: ";
								std::cin >> q;
								r_ = redBlackTree.HaveAKey(q);
							}
							else {
								break;
							}
						}
						hash_table.resetLog();
						redBlackTree.resetLog();
						uns_arr.resetLog();
						s_arr.resetLog();
						if (!r_) {
							Data<std::string, Polinome<double>> ins_d(q, res);
							hash_table.insert(ins_d);
							redBlackTree.insert(ins_d);
							s_arr.insert(ins_d);
							uns_arr.insert(ins_d);
							Log_Table("insert", hash_table, redBlackTree, uns_arr, s_arr, 1);
						}
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
						redBlackTree.find_vertex_by_key(s1);
						uns_arr.find_by_name(s1);
						s_arr.find_by_name(s1);
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
					std::cout << "Enter the constant: ";
					std::cin >> q;
					b = parser_My(q);
					a = r1.second.getData();
					Polinome<double> res = (a * b);
					std::cout << "HASH_TABLE Result first * const: " << res << std::endl;
					Log_Table("Polinum multiply const (with all finding! (and not successful too!))", hash_table, redBlackTree, uns_arr, s_arr, 1);
					std::cout << "Save result into tables? (1/0): ";
					std::cin >> q;
					if (q == "1") {
						std::cout << "What name of result polinome?: ";
						std::cin >> q;
						auto r_ = redBlackTree.HaveAKey(q);
						while (r_) {
							std::cout << "That key already exists!\ntype name again? (1/0): ";
							std::cin >> q;
							if (q == "1") {
								std::cout << "What name of result polinome?: ";
								std::cin >> q;
								r_ = redBlackTree.HaveAKey(q);
							}
							else {
								break;
							}
						}
						hash_table.resetLog();
						redBlackTree.resetLog();
						uns_arr.resetLog();
						s_arr.resetLog();
						if (!r_) {
							Data<std::string, Polinome<double>> ins_d(q, res);
							hash_table.insert(ins_d);
							redBlackTree.insert(ins_d);
							s_arr.insert(ins_d);
							uns_arr.insert(ins_d);
							Log_Table("insert", hash_table, redBlackTree, uns_arr, s_arr, 1);
						}
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
				std::cout << "Enter the number of Monoms in polinome: ";
				size_t sz1;
				std::cin >> sz1;
				Polinome<double> a(sz1);
				std::cout << "Type polinome: ";
				std::cin >> a;
				std::cout << "Enter the name of polinom: ";
				std::cin >> q;
				auto r_ = redBlackTree.HaveAKey(q);
				while (r_) {
					std::cout << "That key already exists!\ntype name again? (1/0): ";
					std::cin >> q;
					if (q == "1") {
						std::cout << "Enter the name of polinome: ";
						std::cin >> q;
						r_ = redBlackTree.HaveAKey(q);
					}
					else {
						break;
					}
				}
				hash_table.resetLog();
				redBlackTree.resetLog();
				uns_arr.resetLog();
				s_arr.resetLog();
				if (!r_) {
					Data<std::string, Polinome<double>> ins_d(q, a);
					hash_table.insert(ins_d);
					redBlackTree.insert(ins_d);
					s_arr.insert(ins_d);
					uns_arr.insert(ins_d);
					Log_Table("insert", hash_table, redBlackTree, uns_arr, s_arr, 1);
					std::cout << "\nType something to continue\n";
					std::cin >> q;
				}
				CLS;
			}
			else if (q == "3") {
				std::cout << "Type polinom's name: ";
				std::cin >> q;
				auto r_ = redBlackTree.HaveAKey(q);
				while (!r_) {
					std::cout << "That key dont exists!\ntype name again? (1/0): ";
					std::cin >> q;
					if (q == "1") {
						std::cout << "Enter the name of polinome: ";
						std::cin >> q;
						r_ = redBlackTree.HaveAKey(q);
					}
					else {
						break;
					}
				}
				hash_table.resetLog();
				redBlackTree.resetLog();
				uns_arr.resetLog();
				s_arr.resetLog();
				if (r_) {
					
					hash_table.Delete(q);
					redBlackTree.Delete(q);
					s_arr.Delete(q);
					uns_arr.Delete_by_name(q);
					Log_Table("delete", hash_table, redBlackTree, uns_arr, s_arr, 1);
					std::cout << "\nType something to continue\n";
					std::cin >> q;
				}
				CLS;
			}
			else if (q == "4") {
				std::cout << "Type polinom's name: ";
				std::cin >> q;
				auto hash_res = hash_table.find(q);
				auto rbtree_res = redBlackTree.find_vertex_by_key(q);
				auto sa_res = s_arr.find_by_name(q);
				auto unsa_res = uns_arr.find_by_name(q);
				if (rbtree_res != nullptr) {
					std::cout << "Found: ";
					std::cout << rbtree_res->data.getData() << std::endl;
				}
				else {
					std::cout << "didn't find anything!" << std::endl;
				}
				Log_Table("searching", hash_table, redBlackTree, uns_arr, s_arr, 1);
				std::cout << "\nType something to continue\n";
				std::cin >> q;
				CLS;
			}
			else if (q == "exit") {
				CLS;
				std::cout << "Goodbye!;)" << std::endl;
				return 0;
			}
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what() << '\n';
	}
};