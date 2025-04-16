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

TEST(unsorted_arr, insert_correct_sz) {
	unsorted_array<int> a;
	vector<Data<std::string, int>> v0;
	a.insert({"a",4});
	v0.push_back({ "a",4 });
	a.insert({ "b",3 });
	v0.push_back({ "b",3 });
	a.insert({ "c",2 });
	v0.push_back({ "c",2 });
	a.insert({ "d",1 });
	v0.push_back({ "d",1 });
	auto v = a.GET_VECTOR();
	ASSERT_EQ(v.size(), v0.size());
}

TEST(unsorted_arr, insert_correct_el) {
	unsorted_array<int> a;
	vector<Data<std::string, int>> v0;
	a.insert({ "a",4 });
	v0.push_back({ "a",4 });
	a.insert({ "b",3 });
	v0.push_back({ "b",3 });
	a.insert({ "c",2 });
	v0.push_back({ "c",2 });
	a.insert({ "d",1 });
	v0.push_back({ "d",1 });
	auto v = a.GET_VECTOR();
	for (size_t i = 0; i < v.size(); i++) {
		ASSERT_EQ(v[i], v0[i]);
	}
}
TEST(unsorted_arr, delete_sz) {
	unsorted_array<int> a;
	vector<Data<std::string, int>> v0;
	a.insert({ "a",4 });
	v0.push_back({ "a",4 });
	a.insert({ "b",3 });
	v0.push_back({ "b",3 });
	a.insert({ "c",2 });
	v0.push_back({ "c",2 });
	a.insert({ "d",1 });
	a.Delete_by_name("d");
	auto v = a.GET_VECTOR();
	ASSERT_EQ(v.size(), v0.size());
}
TEST(unsorted_arr, delete_correct_el) {
	unsorted_array<int> a;
	vector<Data<std::string, int>> v0;
	a.insert({ "a",4 });
	v0.push_back({ "a",4 });
	a.insert({ "b",3 });
	v0.push_back({ "b",3 });
	a.insert({ "c",2 });
	v0.push_back({ "c",2 });
	a.insert({ "d",1 });
	a.Delete_by_name("d");
	auto v = a.GET_VECTOR();
	for (size_t i = 0; i < v.size(); i++) {
		ASSERT_EQ(v[i], v0[i]);
	}
}
TEST(unsorted_arr, cant_delete_notexists) {
	unsorted_array<int> a;
	a.insert({ "a",4 });
	a.insert({ "b",3 });
	a.insert({ "c",2 });
	a.insert({ "d",1 });
	ASSERT_ANY_THROW(a.Delete_by_name("r"));
}
TEST(unsorted_arr, can_find) {
	unsorted_array<int> a;
	a.insert({ "a",4 });
	a.insert({ "b",3 });
	a.insert({ "c",2 });
	a.insert({ "d",1 });
	ASSERT_NO_THROW(a.find_by_name("c"));
}
TEST(unsorted_arr, can_find_correct) {
	unsorted_array<int> a;
	a.insert({ "a",4 });
	a.insert({ "b",3 });
	a.insert({ "c",2 });
	a.insert({ "d",1 });
	auto p = a.find_by_name("c");
	ASSERT_EQ(p.first, 1);
	ASSERT_EQ(p.second, (Data<std::string, int>("c", 2)));
}
TEST(unsorted_arr, cant_find_correct) {
	unsorted_array<int> a;
	a.insert({ "a",4 });
	a.insert({ "b",3 });
	a.insert({ "c",2 });
	a.insert({ "d",1 });
	auto p = a.find_by_name("r");
	ASSERT_EQ(p.first, 0);
	ASSERT_EQ(p.second, (Data<std::string, int>()));
}












TEST(sorted_arr, can_create) {
	ASSERT_NO_THROW(sorted_array<int>());
}
TEST(sorted_arr, create_sz) {
	sorted_array<int> a;
	ASSERT_EQ(0, a.size());
}
TEST(sorted_arr, can_insert) {
	sorted_array<int> a;
	Data<std::string, int> d("a", 5);
	ASSERT_NO_THROW(a.insert(d));
}
TEST(sorted_arr, can_get_vector) {
	sorted_array<int> a;
	Data<std::string, int> d("a", 5);
	a.insert(d);
	ASSERT_NO_THROW(a.GET_VECTOR());
}
TEST(sorted_arr, get_vector) {
	sorted_array<int> a;
	Data<std::string, int> d("a", 5);
	a.insert(d);
	auto y = a.GET_VECTOR();
	ASSERT_EQ(d, y[0]);
}
TEST(sorted_arr, cant_insert_same) {
	sorted_array<int> a;
	Data<std::string, int> d("a", 5);
	a.insert(d);
	ASSERT_ANY_THROW(a.insert(d));
}

TEST(sorted_arr, insert_correct_sz) {
	sorted_array<int> a;
	vector<Data<std::string, int>> v0;
	a.insert({ "a",4 });
	v0.push_back({ "a",4 });
	a.insert({ "b",3 });
	v0.push_back({ "b",3 });
	a.insert({ "c",2 });
	v0.push_back({ "c",2 });
	a.insert({ "d",1 });
	v0.push_back({ "d",1 });
	auto v = a.GET_VECTOR();
	ASSERT_EQ(v.size(), v0.size());
}

TEST(sorted_arr, insert_correct_el) {
	sorted_array<int> a;
	vector<Data<std::string, int>> v0;
	a.insert({ "c",4 });
	v0.push_back({ "a",3 });
	a.insert({ "a",3 });
	v0.push_back({ "b",2 });
	a.insert({ "b",2 });
	v0.push_back({ "c",4 });
	a.insert({ "d",1 });
	v0.push_back({ "d",1 });
	auto v = a.GET_VECTOR();
	for (size_t i = 0; i < v.size(); i++) {
		ASSERT_EQ(v[i], v0[i]);
	}
}
TEST(sorted_arr, delete_sz) {
	sorted_array<int> a;
	vector<Data<std::string, int>> v0 = { {"a",4}, {"b",1}, {"c",2}};
	a.insert({ "a",4 });
	a.insert({ "d",3 });
	a.insert({ "c",2 });
	a.insert({ "b",1 });
	a.Delete("a");
	auto v = a.GET_VECTOR();
	ASSERT_EQ(v.size(), v0.size());
}
TEST(sorted_arr, delete_correct_el) {
	sorted_array<int> a;
	vector<Data<std::string, int>> v0 = { {"a",4}, {"b",1}, {"c",2} };
	a.insert({ "a",4 });
	a.insert({ "d",3 });
	a.insert({ "c",2 });
	a.insert({ "b",1 });
	a.Delete("d");
	auto v = a.GET_VECTOR();
	for (size_t i = 0; i < v.size(); i++) {
		ASSERT_EQ(v[i], v0[i]);
	}
}
TEST(sorted_arr, cant_delete_notexists) {
	sorted_array<int> a;
	a.insert({ "a",4 });
	a.insert({ "b",3 });
	a.insert({ "c",2 });
	a.insert({ "d",1 });
	ASSERT_ANY_THROW(a.Delete("r"));
}
TEST(sorted_arr, can_find) {
	sorted_array<int> a;
	a.insert({ "a",4 });
	a.insert({ "b",3 });
	a.insert({ "c",2 });
	a.insert({ "d",1 });
	ASSERT_NO_THROW(a.find_by_name("c"));
}
TEST(sorted_arr, can_find_correct) {
	sorted_array<int> a;
	a.insert({ "a",4 });
	a.insert({ "c",2 });
	a.insert({ "b",3 });
	a.insert({ "d",1 });
	auto p = a.find_by_name("c");
	ASSERT_EQ(p.first, 2);
	ASSERT_EQ(p.second, (Data<std::string, int>("c", 2)));
}
TEST(sorted_arr, cant_find_correct) {
	sorted_array<int> a;
	a.insert({ "a",4 });
	a.insert({ "b",3 });
	a.insert({ "c",2 });
	a.insert({ "d",1 });
	auto p = a.find_by_name("r");
	ASSERT_EQ(p.first, -1);
	ASSERT_EQ(p.second, (Data<std::string, int>()));
}
