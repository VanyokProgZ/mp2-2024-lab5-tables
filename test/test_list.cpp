#include <gtest.h>
#include "list.h"

TEST(List, can_create_default) {
	ASSERT_NO_THROW(List<int>());
}
TEST(List, can_create_from_initializer_list)
{
	ASSERT_NO_THROW(List<int>({1,2,3,4,5}));
}
TEST(List, can_create_from_empty_initializer_list)
{
	ASSERT_NO_THROW(List<int>({ }));
}
TEST(List, correct_create_from_initializer_list)
{
	List<int> a={ 1,2,3,4,5 };
	int i = 1;
	for (auto it = a.begin();; ++it, i++) {
		ASSERT_EQ(*it, i);
		if (it == a.last())break;
	}
}
TEST(List, can_create_copy_constructor) {
	List<int> a = { 1,2,3,4,5 };
	ASSERT_NO_THROW(List<int> b(a));
}
TEST(List, can_create_empty_copy_constructor) {
	List<int> a = { };
	ASSERT_NO_THROW(List<int> b(a));
}
TEST(List, copy_constructor_right_values) {
	List<int> a = { 1,2,3,4,5 };
	List<int> b(a);
	for (auto it1 = a.begin(), it2 = b.begin();; ++it1, ++it2) {
		ASSERT_EQ(*it1, *it2);
		if (it1 == a.last())break;
	}
}
TEST(List, correct_copy) {
	List<int> a = { 1,2,3,4,5 };
	List<int> b = {5};
	b = a;
	ASSERT_EQ(b, a);
}
TEST(List, correct_copy_own_mem) {
	List<int> a = { 1,2,3,4,5 };
	List<int> b = { 5 };
	b = a;
	b[0] = 23;
	ASSERT_NE(b, a);
}
TEST(List, correct_selfcopy) {
	List<int> a = { 1,2,3,4,5 };
	List<int> b = { 1,2,3,4,5 };
	a = a;
	ASSERT_EQ(a, a);
	ASSERT_EQ(a, b);
}
TEST(List, copy_constructor_own_memory) {
	List<int> a = { 1,2,3,4,5 };
	List<int> b(a);
	for (auto it1 = a.begin(), it2 = b.begin();; ++it1, ++it2) {
		*it1 = (*it1) + 1;
		ASSERT_NE(*it1, *it2);
		if (it1 == a.last())break;
	}
}
TEST(List, can_size) {
	List<int> a = { 1,2,3,4,5,6,7,8,9,10,22968 };
	ASSERT_NO_THROW(a.size());
}
TEST(List, can_size_empty) {
	List<int> a = {  };
	ASSERT_NO_THROW(a.size());
}
TEST(List, size) {
	List<int> a = { 1,2,3,4,5,6,7,8,9,10,22968 };
	ASSERT_EQ(a.size(), 11);
}
TEST(List, size_empty) {
	List<int> a = {  };
	ASSERT_EQ(a.size(), 0);
}
TEST(List, can_create_construct_value) {
	List<int> a = { 22869 };
	ASSERT_NO_THROW(List<int> b(22869));
}
TEST(List, create_construct_value_correct_value) {
	List<int> a = { 22869 };
	List<int> b(22869);
	ASSERT_EQ(*a.begin(), *b.begin());
}
TEST(List, create_construct_value_correct_size) {
	List<int> a = { 22869 };
	List<int> b(22869);
	ASSERT_EQ(b.size(),1);
}
TEST(List, can_create_many_same_value_construct) {
	ASSERT_NO_THROW(List<int> a(23, 43));
}
TEST(List, correct_create_many_same_value_construct) {
	List<int> a(23, 43);
	for (auto it = a.begin();; ++it) {
		ASSERT_EQ(*it, 43);
		if (it == a.last())break;
	}
}
TEST(List, correct_create_many_same_value_construct_size) {
	List<int> a(23, 43);
	ASSERT_EQ(a.size(), 23);
}
TEST(List, can_push_back_val) {
	List<int> a = { 1,2 };
	ASSERT_NO_THROW(a.push_back(243));
}
TEST(List, size_push_back_val) {
	List<int> a = { 1,2 };
	a.push_back(234);
	ASSERT_EQ(a.size(), 3);
}
TEST(List, can_push_back_val_to_empty) {
	List<int> a = {};
	ASSERT_NO_THROW(a.push_back(243));
}
TEST(List, size_push_back_val_to_empty) {
	List<int> a = { };
	a.push_back(234);
	ASSERT_EQ(a.size(), 1);
}
TEST(List, push_back_correct) {
	List<int> a = { 1 };
	a.push_back(2);
	auto it = a.begin();
	++it;
	ASSERT_EQ(*it, 2);
}
TEST(List, push_back_to_empty_correct) {
	List<int> a = {};
	a.push_back(2);
	auto it = a.begin();
	ASSERT_EQ(*it, 2);
}
TEST(List, can_push_front) {
	List<int> a = { 23 };
	ASSERT_NO_THROW(a.push_front(6));
}
TEST(List, can_push_front_to_empty) {
	List<int> a = {};
	ASSERT_NO_THROW(a.push_front(2006));
}
TEST(List, size_push_front) {
	List<int> a = { 1,2,3 };
	a.push_front(12343);
	ASSERT_EQ(a.size(), 4);
}
TEST(List, size_push_front_to_empty) {
	List<int> a = { };
	a.push_front(12343);
	ASSERT_EQ(a.size(), 1);
}
TEST(List, push_front_correct) {
	List<int> a = { 1 };
	a.push_front(2);
	auto it = a.begin();
	ASSERT_EQ(*it, 2);
}
TEST(List, push_front_to_empty_correct) {
	List<int> a = {};
	a.push_front(2);
	auto it = a.begin();
	ASSERT_EQ(*it, 2);
}
TEST(List, can_insert) {
	List<int> a = { 1,2 };
	ASSERT_NO_THROW(a.insert(1, 23));
}
TEST(List, can_insert_in_back) {
	List<int> a = { 1 };
	ASSERT_NO_THROW(a.insert(1, 23));
}
TEST(List, can_insert_in_beginning) {
	List<int> a = { 1 };
	ASSERT_NO_THROW(a.insert(0, 23));
}
TEST(List, can_insert_in_empty) {
	List<int> a = {};
	ASSERT_NO_THROW(a.insert(0, 23));
}
TEST(List, throw_insert_bad_index) {
	List<int> a = { 1 };
	ASSERT_ANY_THROW(a.insert(2, 23));
}
TEST(List, throw_insert_bad_index_in_empty) {
	List<int> a = { };
	ASSERT_ANY_THROW(a.insert(1, 23));
}
TEST(List, can_insert_correct) {
	List<int> a = { 1,2 };
	a.insert(1, 228);
	auto it = a.begin();
	ASSERT_EQ(*it, 1);
	++it;
	ASSERT_EQ(*it, 228);
	++it;
	ASSERT_EQ(*it, 2);
}
TEST(List, can_insert_correct_in_empty) {
	List<int> a = { };
	a.insert(0, 228);
	auto it = a.begin();
	ASSERT_EQ(*it,228);
}
TEST(List, operator_breckets_correct_get) {
	List<int> a = { 1,2,3,4,5,6 };
	ASSERT_EQ(a[3], 4);
}
TEST(List, can_move_cstrct) {
	List<int> a = { 1,2,3,4,5 };
	List<int> b = { 6,7,8,9,10 };
	ASSERT_NO_THROW(List<int> d = std::move(a + b));
}
TEST(List, move_cstrct) {
	List<int> a = { 1,2,3,4,5 };
	List<int> b = { 6,7,8,9,10 };
	List<int> c = { 1,2,3,4,5,6,7,8,9,10 };
	List<int> d = std::move(a + b);
	ASSERT_EQ(d, c);
}
TEST(List, can_move_op) {
	List<int> a = { 1,2,3,4,5 };
	List<int> b = { 6,7,8,9,10 };
	List<int> c;
	ASSERT_NO_THROW(c = std::move(a + b));
}
TEST(List, move_op) {
	List<int> a = { 1,2,3,4,5 };
	List<int> b = { 6,7,8,9,10 };
	List<int> c;
	ASSERT_EQ(c = std::move(a + b), List<int>({1,2,3,4,5,6,7,8,9,10}));
}
TEST(List, operator_breckets_correct_set) {
	List<int> a = { 1,2,3,4,5,6 };
	a[3] = 2008;
	ASSERT_EQ(a[3], 2008);
}
TEST(List, can_at) {
	List<int> a = { 1,2,3,4,5,6 };
	ASSERT_NO_THROW(a.at(0));
	ASSERT_NO_THROW(a.at(5));
	ASSERT_NO_THROW(a.at(3));
}
TEST(List, throw_at_big_ind) {
	List<int> a = { 1,2,3,4,5,6 };
	ASSERT_ANY_THROW(a.at(27));
}
TEST(List, correct_get_at) {
	List<int> a = { 1,2,3,4,5,6 };
	ASSERT_EQ(a.at(3), 4);
}
TEST(List, at_correct_set) {
	List<int> a = { 1,2,3,4,5,6 };
	a.at(3) = 2008;
	ASSERT_EQ(a.at(3), 2008);
}
TEST(List, operator_ravno_ravno) {
	List<int> a = { 1,2,3,4,5 };
	List<int> b = {1,2,3,4,5 };
	ASSERT_EQ(a==b,true);
}
TEST(List, operator_ravno_neravno) {
	List<int> a = { 1,2,3,4,5 };
	List<int> b = { 0,2,3,4,5 };
	ASSERT_NE(a==b,true);
}
TEST(List, operator_neravno_ravno) {
	List<int> a = { 1,2,3,4,5 };
	List<int> b = { 1,2,3,4,5 };
	ASSERT_NE(a!=b,true);
}
TEST(List, operator_neravno_neravno) {
	List<int> a = { 1,2,3,4,5 };
	List<int> b = { 0,2,3,4,5 };
	ASSERT_EQ(a!=b,true);
}
TEST(List, can_operator_plus) {
	List<int> a = { 1,2,3,4,5 };
	List<int> b = { 6,7,8,9,10 };
	ASSERT_NO_THROW(a + b);
}
TEST(List, can_operator_plus_with_one_empty_r) {
	List<int> a = { 1,2,3,4,5 };
	List<int> b = {};
	ASSERT_NO_THROW(a + b);
}
TEST(List, can_operator_plus_with_one_empty_l) {
	List<int> a = { 1,2,3,4,5 };
	List<int> b = {};
	ASSERT_NO_THROW(b+a);
}
TEST(List, can_operator_plus_with_two_empty) {
	List<int> a = {};
	List<int> b = {};
	ASSERT_NO_THROW(a + b);
}
TEST(List, correct_operator_plus) {
	List<int> a = { 1,2,3,4,5 };
	List<int> b = { 6,7,8,9,10 };
	List<int> c = { 1,2,3,4,5,6,7,8,9,10 };
	ASSERT_EQ(c, a + b);
}
TEST(List, correct_operator_plus_with_empty) {
	List<int> a = { 1,2,3,4,5 };
	List<int> b = { };
	ASSERT_EQ(a, a + b);
	ASSERT_EQ(b+a, a );
}
TEST(List, correct_operator_plus_with_two_empty) {
	List<int> a = { };
	List<int> b = { };
	ASSERT_EQ(a, a + b);
	ASSERT_EQ(b + a, a);
}
TEST(List, can_pop_front) {
	List<int> a = { 19,17 };
	ASSERT_NO_THROW(a.pop_front());
}
TEST(List, cant_pop_front_from_empty) {
	List<int> a = { };
	ASSERT_ANY_THROW(a.pop_front());
}
TEST(List, can_pop_back) {
	List<int> a = { 19,17 };
	ASSERT_NO_THROW(a.pop_back());
}
TEST(List, cant_pop_back_from_empty) {
	List<int> a = { };
	ASSERT_ANY_THROW(a.pop_back());
}
TEST(List, pop_front_change_size) {
	List<int> a = { 1,2,3,4,5 };
	a.pop_front();
	ASSERT_EQ(4, a.size());
}
TEST(List, pop_back_change_size) {
	List<int> a = { 1,2,3,4,5 };
	a.pop_back();
	ASSERT_EQ(4, a.size());
}
TEST(List, pop_back_correct) {
	List<int> a = { 1,2,3,4,5 };
	List<int> b = { 1,2,3,4 };
	a.pop_back();
	ASSERT_EQ(a,b);
}
TEST(List, pop_front_correct) {
	List<int> a = { 1,2,3,4,5 };
	List<int> b = { 2,3,4,5 };
	a.pop_front();
	ASSERT_EQ(a, b);
}
TEST(List, can_del_at) {
	List<int> a = { 1,2,3,4,5 };
	ASSERT_NO_THROW(a.del_at(2));
}
TEST(List, can_del_at_beginning) {
	List<int> a = { 1,2,3,4,5 };
	ASSERT_NO_THROW(a.del_at(0));
}
TEST(List, can_del_at_end) {
	List<int> a = { 1,2,3,4,5 };
	ASSERT_NO_THROW(a.del_at(4));
}
TEST(List, cant_del_at_in_empty) {
	List<int> a = { };
	ASSERT_ANY_THROW(a.del_at(0));
}
TEST(List, cant_del_at_big_index) {
	List<int> a = {2,2,3,4 };
	ASSERT_ANY_THROW(a.del_at(7));
}
TEST(List, correct_del_at) {
	List<int> a = { 1,2,3,4,6,9 };
	List<int> b = { 1,2,3,6,9 };
	a.del_at(3);
	ASSERT_EQ(a, b);
}
TEST(List, correct_del_at_beginning) {
	List<int> a = { 1,2,3,4,6,9 };
	List<int> b = { 2,3,4,6,9 };
	a.del_at(0);
	ASSERT_EQ(a, b);
}
TEST(List, correct_del_at_end) {
	List<int> a = { 1,2,3,4,6,9 };
	List<int> b = { 1,2,3,4,6};
	a.del_at(5);
	ASSERT_EQ(a, b);
}
TEST(List, can_sorted_merge) {
	List<int> a = { 1,2,3,4,6,9 };
	List<int> b = { 1,2,3,4,6 };
	ASSERT_NO_THROW(a.sorted_merge(a, b));
}
TEST(List, can_sorted_merge_empty_r) {
	List<int> a = { 1,2,3,4,6,9 };
	List<int> b = { };
	ASSERT_NO_THROW(a.sorted_merge(a, b));
}
TEST(List, can_sorted_merge_empty_l) {
	List<int> a = { 1,2,3,4,6,9 };
	List<int> b = { };
	ASSERT_NO_THROW(a.sorted_merge(b, a));
}
TEST(List, can_sorted_merge_empty_all) {
	List<int> a = { };
	List<int> b = { };
	ASSERT_NO_THROW(a.sorted_merge(b, a));
}
TEST(List, correct_sorted_merge) {
	List<int> a = { 1,2,3,4,6,9 };
	List<int> b = { 1,2,3,5,6 };
	List<int> c = { 1,1,2,2,3,3,4,5,6,6,9 };
	ASSERT_EQ(a.sorted_merge(a, b), c);
}
TEST(List, correct_sorted_merge_empty_r) {
	List<int> a = { 1,2,3,4,6,9 };
	List<int> b = { };
	List<int> c = { 1,2,3,4,6,9 };
	ASSERT_EQ(a.sorted_merge(a, b), c);
}
TEST(List, correct_sorted_merge_empty_l) {
	List<int> a = { 1,2,3,4,6,9 };
	List<int> b = { };
	List<int> c = { 1,2,3,4,6,9 };
	ASSERT_EQ(a.sorted_merge(b,a), c);
}
TEST(List, correct_sorted_merge_empty_all) {
	List<int> a = { };
	ASSERT_EQ(a.sorted_merge(a, a), a);
}
TEST(List, can_clear) {
	List<int> a = { 1,2,3,4,5 };
	ASSERT_NO_THROW(a.clear());
}
TEST(List, can_clear_empty) {
	List<int> a = { };
	ASSERT_NO_THROW(a.clear());
}
TEST(List, correct_clear) {
	List<int> a = { 1,2,3,4,5 };
	a.clear();
	ASSERT_EQ(a, List<int>());
}
TEST(List, correct_clear_empty) {
	List<int> a = { };
	a.clear();
	ASSERT_EQ(a, List<int>());
}
TEST(List, can_check_sorted) {
	List<int> a = { 1,2,3,4 };
	ASSERT_NO_THROW(a.check_sorted());
}
TEST(List, can_check_sorted_empty) {
	List<int> a = { };
	ASSERT_NO_THROW(a.check_sorted());
}
TEST(List, correct_check_sorted_sort) {
	List<int> a = { 1,2,3,4 };
	ASSERT_EQ(a.check_sorted(), true);
}
TEST(List, correct_check_sorted_ne_sort) {
	List<int> a = { 1,2,4,3 };
	ASSERT_NE(a.check_sorted(), true);
}
TEST(List, correct_check_sorted_empty) {
	List<int> a = {};
	ASSERT_EQ(a.check_sorted(), true);
}
TEST(List, can_merge_sort) {
	List<int> a = { 4,6,2,7,2,7,8,9,3 };
	ASSERT_NO_THROW(a.merge_sort());
}
TEST(List, can_merge_sort_empty) {
	List<int> a = { };
	ASSERT_NO_THROW(a.merge_sort());
}
TEST(List, correct_merge_sort) {
	List<int> a = { 4,6,2,7,2,7,8,9,3 };
	List<int> b = { 2,2,3,4,6,7,7,8,9 };
	a.merge_sort();
	ASSERT_EQ(a,b);
}
TEST(List, correct_merge_sort_empty) {
	List<int> a = {  };
	List<int> b = { };
	a.merge_sort();
	ASSERT_EQ(a, b);
}
TEST(List_iterator, correct_razimenovanie) {
	List<int> a = { 1,2 };
	ASSERT_EQ(*(a.begin()), 1);
	ASSERT_EQ(*(a.last()), 2);
}
TEST(List_iterator, correct_plus_plus) {
	List<int> a = { 1,2,3,4 };
	auto it = a.begin();
	int i = 1;
	for (;; ++it) {
		ASSERT_EQ(*it, i++);
		if (it == a.last())break;
	}
}
TEST(List_iterator, correct_minus_minus) {
	List<int> a = { 1,2,3,4 };
	auto it = a.last();
	int i = 4;
	for (;; --it) {
		ASSERT_EQ(*it, i--);
		if (it == a.begin())break;
	}
}
