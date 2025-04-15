#include "gtest.h"
#include "data.h"

TEST(data, can_default_cnstr) {
	ASSERT_NO_THROW((Data<int, int>()));
}
TEST(data, can_cnstr) {
	ASSERT_NO_THROW((Data<int, int>(23,432)));
}
TEST(data, cnstr_key) {
	auto d = Data<int, int>(23, 432);
	ASSERT_EQ(d.getKey(), 23);
}
TEST(data, cnstr_data) {
	auto d = Data<int, int>(23, 432);
	ASSERT_EQ(d.getData(), 432);
}
TEST(data, can_data_cnstr) {
	auto d = Data<int, int>(23, 432);
	d.getData() = 54;
	ASSERT_EQ(d.getData(), 54);
}
TEST(data, op_as) {
	auto d = Data<int, int>(23, 432);
	ASSERT_NO_THROW(auto r = d);
}
TEST(data, op_as_key) {
	auto d = Data<int, int>(23, 432);
	auto r = d;
	ASSERT_EQ(23, r.getKey());
}
TEST(data, op_as_data) {
	auto d = Data<int, int>(23, 432);
	auto r = d;
	ASSERT_EQ(432, r.getData());
}
TEST(data, setkey) {
	auto d = Data<int, int>(23, 432);
	d.setKey(2332);
	ASSERT_EQ(2332, d.getKey());
}
TEST(data, can_swap) {
	auto d = Data<int, int>(23, 432);
	auto t = Data<int, int>(243, 1231);
	ASSERT_NO_THROW(t = d.swap(t));
}
TEST(data, swap_key) {
	auto d = Data<int, int>(23, 432);
	auto t = Data<int, int>(243, 1231);
	t = d.swap(t);
	ASSERT_EQ(d.getKey(), 243);
	ASSERT_EQ(t.getKey(), 23);
}
TEST(data, swap_data) {
	auto d = Data<int, int>(23, 432);
	auto t = Data<int, int>(243, 1231);
	t = d.swap(t);
	ASSERT_EQ(d.getData(), 1231);
	ASSERT_EQ(t.getData(), 432);
}
