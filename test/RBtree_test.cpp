#include "gtest.h"
#include "vector.h"
#include "RBTREE.h"
#include <random>

template<class T>
void random_shuffle(vector<T>& v)
{
	T t;
	for (size_t i = v.size() - 1; i > 0; --i)
	{	
		auto r = std::rand();
		t = v[i];
		v[i] = v[r % (i + 1)];
		v[r % (i + 1)] = t;
	}
}

TEST(rbtree, can_create_default) {
	ASSERT_NO_THROW(RBTree<int>);
}
TEST(rbtree, can_create_default_cnt) {
	RBTree<int> tree;
	ASSERT_EQ(0ull, tree.TESTER_VERTEX_CNT());
}
TEST(rbtree, can_create_default_LOG) {
	RBTree<int> tree;
	ASSERT_EQ(tree.Log(), 0);
}
TEST(rbtree, can_insert) {
	RBTree<int> tree;
	ASSERT_NO_THROW(tree.insert("skgfdb",34));
}
TEST(rbtree, can_insert_data) {
	RBTree<int> tree;
	Data<std::string, int> d("sgfsefw", 243);
	ASSERT_NO_THROW(d);
}
TEST(rbtree, insert_Black) {
	RBTree<int> tree;
	tree.insert("skgfdb", 34);
	ASSERT_NO_THROW(tree.NO_RED_RED());
}
TEST(rbtree, insert_data_Black) {
	RBTree<int> tree;
	Data<std::string, int> d("sgfsefw", 243);
	tree.insert(d);
	ASSERT_NO_THROW(tree.NO_RED_RED());
}
TEST(rbtree, insert_cnt) {
	RBTree<int> tree;
	tree.insert("skgfdb", 34);
	ASSERT_EQ(1, tree.TESTER_VERTEX_CNT());
}
TEST(rbtree, insert_data_cnt) {
	RBTree<int> tree;
	Data<std::string, int> d("sgfsefw", 243);
	tree.insert(d);
	ASSERT_EQ(1, tree.TESTER_VERTEX_CNT());
}
TEST(rbtree, insert_three_cnt) {
	RBTree<int> tree;
	tree.insert("b", 34);
	tree.insert("a", 34);
	tree.insert("c", 34);
	ASSERT_EQ(3, tree.TESTER_VERTEX_CNT());
}
TEST(rbtree, insert_three_no_r_r) {
	RBTree<int> tree;
	tree.insert("b", 34);
	tree.insert("a", 34);
	tree.insert("c", 34);
	ASSERT_NO_THROW(tree.NO_RED_RED());
}
TEST(rbtree, insert_three_black_depth) {
	RBTree<int> tree;
	tree.insert("b", 34);
	tree.insert("a", 34);
	tree.insert("c", 34);
	ASSERT_NO_THROW(tree.TESTER_DEPTH_B());
}
TEST(rbtree, can_del) {
	RBTree<int> tree;
	tree.insert("b", 34);
	tree.insert("a", 34);
	tree.insert("c", 34);
	ASSERT_NO_THROW(tree.Delete("b"));
}
TEST(rbtree, cant_del_no_ex) {
	RBTree<int> tree;
	tree.insert("b", 34);
	tree.insert("a", 34);
	tree.insert("c", 34);
	ASSERT_ANY_THROW(tree.Delete("d"));
}
TEST(rbtree, del_right_cnt) {
	RBTree<int> tree;
	tree.insert("b", 34);
	tree.insert("a", 34);
	tree.insert("c", 34);
	tree.Delete("b");
	ASSERT_EQ(2, tree.TESTER_VERTEX_CNT());
}
TEST(rbtree, del_no_r_r) {
	RBTree<int> tree;
	tree.insert("b", 34);
	tree.insert("a", 34);
	tree.insert("c", 34);
	tree.Delete("a");
	ASSERT_NO_THROW(tree.NO_RED_RED());
}
TEST(rbtree, del_all) {
	RBTree<int> tree;
	tree.insert("b", 34);
	tree.insert("a", 34);
	tree.insert("c", 34);
	tree.Delete("b");
	tree.Delete("a");
	tree.Delete("c");
	ASSERT_EQ(0, tree.TESTER_VERTEX_CNT());
}
TEST(rbtree, stress_insert) {
	RBTree<int,int> tree;
	size_t sz = 10000;
	vector<int> v(sz);
	for (int i = 0; i < sz; i++) {
		v[i] = i - sz / 2;
	}
	srand(time(0));
	random_shuffle(v);

	for (int i = 0; i < sz; i++) {
		tree.insert(v[i],v[i]);
		ASSERT_NO_THROW(tree.NO_RED_RED());
		ASSERT_NO_THROW(tree.TESTER_DEPTH_B());
		ASSERT_EQ(i + 1, tree.TESTER_VERTEX_CNT());
	}
}
TEST(rbtree, stress_delete) {
	RBTree<int, int> tree;
	size_t sz = 10000;
	vector<int> v(sz);
	for (int i = 0; i < sz; i++) {
		v[i] = i - sz / 2;
	}
	srand(time(0));
	random_shuffle(v);

	for (int i = 0; i < sz; i++) {
		tree.insert(v[i], v[i]);
	}
	for (int i = 0; i < sz; i++) {
		tree.Delete(v[i]);
		ASSERT_NO_THROW(tree.NO_RED_RED());
		ASSERT_NO_THROW(tree.TESTER_DEPTH_B());
		ASSERT_EQ(sz-i-1, tree.TESTER_VERTEX_CNT());
	}
}
