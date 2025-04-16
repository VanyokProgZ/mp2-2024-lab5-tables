#include "gtest.h"
#include "DoubleHash.h"

TEST(double_hash, can_create) {
	ASSERT_NO_THROW(HASH_TABLE_STRING<int>());
}
TEST(double_hash, hash_izvrat_can) {
	HASH_TABLE_STRING<int> h(3);
	ASSERT_NO_THROW(h.Hash_IzVrat("abababab"));
}
TEST(double_hash, hash_izvrat_range) {
	HASH_TABLE_STRING<int> h(3);
	std::string s = "abcdefghijklmnopqrstuvwxyz";
	for (int i = 0; i < s.size(); i++) {
		ASSERT_GE(3, h.Hash_IzVrat("" + s[i]));
	}
}
TEST(double_hash, polinomial_can) {
	HASH_TABLE_STRING<int> h(3);
	ASSERT_NO_THROW(h.Polinomial_hash("abababab"));
}
TEST(double_hash, polinomial_range) {
	HASH_TABLE_STRING<int> h(3);
	std::string s = "abcdefghijklmnopqrstuvwxyz";
	for (int i = 0; i < s.size(); i++) {
		ASSERT_GE(3, h.Polinomial_hash("" + s[i]));
		ASSERT_LE(1, h.Polinomial_hash("" + s[i]));
	}
}
TEST(double_hash, can_insert_) {
	HASH_TABLE_STRING<int> h(3);
	Data<std::string, int> d("a", 8);
	ASSERT_NO_THROW(h.insert(d));
}
TEST(double_hash, cant_insert_same) {
	HASH_TABLE_STRING<int> h(3);
	Data<std::string, int> d("a", 8);
	h.insert(d);
	ASSERT_ANY_THROW(h.insert(d));
}
TEST(double_hash, can_find) {
	HASH_TABLE_STRING<int> h(3);
	Data<std::string, int> d("a", 8);
	h.insert(d);
	ASSERT_NO_THROW(h.find("a"));
}
TEST(double_hash, can_find_correct_bool) {
	HASH_TABLE_STRING<int> h(3);
	Data<std::string, int> d("a", 8);
	h.insert(d);
	auto r = h.find("a");
	ASSERT_EQ(r.first, 1);
}
TEST(double_hash, can_find_correct_data) {
	HASH_TABLE_STRING<int> h(3);
	Data<std::string, int> d("a", 8);
	h.insert(d);
	auto r = h.find("a");
	ASSERT_EQ(r.second, d);
}
TEST(double_hash, can_find_FALL) {
	HASH_TABLE_STRING<int> h(3);
	Data<std::string, int> d("a", 8);
	h.insert(d);
	ASSERT_NO_THROW(h.find("e"));
}
TEST(double_hash, can_find_correct_bool_fall) {
	HASH_TABLE_STRING<int> h(3);
	Data<std::string, int> d("a", 8);
	h.insert(d);
	auto r = h.find("e");
	ASSERT_EQ(r.first, 0);
}
TEST(double_hash, can_delete) {
	HASH_TABLE_STRING<int> h(3);
	Data<std::string, int> d("a", 8);
	h.insert(d);
	ASSERT_NO_THROW(h.Delete(d.getKey()));
}
TEST(double_hash, can_delete_correct) {
	HASH_TABLE_STRING<int> h(3);
	h.insert({"a",4});
	h.insert({ "b",6 });
	h.Delete("a");
	ASSERT_EQ(h.find("a").first, 0);
	ASSERT_EQ(h.find("b").first, 1);
}
TEST(double_hash, cant_delete_fall) {
	HASH_TABLE_STRING<int> h(3);
	Data<std::string, int> d("a", 8);
	h.insert(d);
	ASSERT_ANY_THROW(h.Delete("lol"));
}
TEST(double_hash, d_h_coeff) {
	HASH_TABLE_STRING<int> h(3);
	auto a = h.Hash_IzVrat("abacaba");
	auto b = h.Polinomial_hash("abacaba");
	auto r = h.Double_hash_coeff("abacaba");
	ASSERT_EQ(a, r.first);
	ASSERT_EQ(b, r.second);
	
}
TEST(double_hash, collision_many_insert) {
	HASH_TABLE_STRING<int> h(3);
	ASSERT_ANY_THROW(for (int i = 0; i < 100; i++)h.insert({ "" + i,4 }));
}
TEST(double_hash, dublicate_data_insert) {
	HASH_TABLE_STRING<int> h(3);
	h.insert({"a",5});
	ASSERT_ANY_THROW(h.insert({ "a",6 }));
}