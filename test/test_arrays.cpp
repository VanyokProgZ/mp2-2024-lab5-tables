#include "gtest.h";
#include "arrays.h"

TEST(unsorted_arr, can_create) {
	ASSERT_NO_THROW(unsorted_array<int>());
}
TEST(unsorted_arr, create_sz) {
	unsorted_array<int> a;
	ASSERT_EQ(0, a.size());
}
TEST(unsorted_arr, can_insert) {
	unsorted_array<int> a;
	Data<std::string, int> d("a", 5);
	ASSERT_NO_THROW(a.insert(d));
}
TEST(unsorted_arr, can_get_vector) {
	unsorted_array<int> a;
	Data<std::string, int> d("a", 5);
	a.insert(d);
	ASSERT_NO_THROW(a.GET_VECTOR());
}
TEST(unsorted_arr, get_vector) {
	unsorted_array<int> a;
	Data<std::string, int> d("a", 5);
	a.insert(d);
	auto y = a.GET_VECTOR();
	ASSERT_EQ(d, y[0]);
}
TEST(unsorted_arr, cant_insert_same) {
	unsorted_array<int> a;
	Data<std::string, int> d("a", 5);
	a.insert(d);
	ASSERT_ANY_THROW(a.insert(d));
}


















TEST(sorted_arr, can_create) {
	ASSERT_NO_THROW(sorted_array<int>());
}
TEST(sorted_arr, create_sz) {
	sorted_array<int> a;
	ASSERT_EQ(0, a.size());
}