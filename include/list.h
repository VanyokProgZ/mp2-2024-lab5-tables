#pragma once
#include <iostream>
#include "vector.h"

template<class val_>
class List;
template<typename _val>
class Iterator_L : public std::iterator<std::input_iterator_tag, _val>
{
	friend class List<_val>;

	List<_val>* main_structure;
	typename List<_val>::node* this_ptr;	//protected struct node (in class List)
public:

	Iterator_L(const List<_val>& list_, typename List<_val>::node& node_) : main_structure(const_cast<List<_val>*>(&list_)), this_ptr(&node_) {}
	Iterator_L(const Iterator_L& iter) : this_ptr(iter.this_ptr), main_structure(iter.main_structure) {};

	bool operator!=(const Iterator_L& it2) const { return this_ptr != it2.this_ptr; };
	bool operator==(const Iterator_L& it2) const { return this_ptr == it2.this_ptr; };
	typename Iterator_L<_val>::reference operator*() const { return this_ptr->data; };

	Iterator_L& operator++() {
		if (this_ptr != main_structure->pLast) {
			this_ptr = this_ptr->next;
			return *this;
		}
		else {
			throw std::out_of_range("List out of range");
		}
	}
	Iterator_L& operator--() {	//ineffective because nodes have only 'next' pointer
		if (this_ptr != main_structure->pFirst) {
			typename List<_val>::node* temp = this_ptr;
			this_ptr = main_structure->pFirst;
			while (this_ptr->next != temp) {
				this_ptr = this_ptr->next;
			}
			return *this;
		}
		else {
			throw std::out_of_range("List out of range");
		}
	}

};
//	List structure:
// 
//		[head]	[pFirst] [] [] [] [] [] [] [pLast]
//

template <typename val_>
class List {
	friend class Iterator_L<val_>;
protected:
	struct node {
		node* next;
		val_ data;
		node() : next(nullptr) {}
		node(const val_& v) : next(nullptr), data(v) {}
		node& operator=(const val_& _val) {
			data = _val;
			return *this;
		}
	};
private:
	node *pFirst, *pLast, *this_node, *head;

	void stepUp() noexcept { //exception situation on the conscience of the developer
		this_node = this_node->next;
	}

public:

	Iterator_L<val_> begin() const {	//on first element (head->next, no head)
		if (pFirst == nullptr) {
			throw std::out_of_range("ITERATOR OUT OF RANGE");
		}
		return Iterator_L<val_>(*this, *pFirst);
	}
	Iterator_L<val_> last() const {	//on last element (not like end())
		if (pLast == nullptr) {
			throw std::out_of_range("ITERATOR OUT OF RANGE");
		}
		return Iterator_L<val_>(*this, *pLast);
	}
	
//constructors--------------------------

	List(std::initializer_list<val_> list_) {
		head = new node();
		pFirst = nullptr;
		pLast = nullptr;
		for (auto& el : list_) {
			this->push_back(el);
		}
	}

	List() {
		pFirst =	nullptr;	//first node after head
		pLast =		nullptr;	//last element in List
		this_node = nullptr;	//assistive node

		head =		new node();	//fictitious node
	}
	List(const List& _right) {
		
		pFirst =	nullptr;
		pLast =		nullptr;
		this_node = nullptr;

		if (_right.pFirst != nullptr) {
			head = new node();
			this_node = head;
			for (Iterator_L<val_> it = _right.begin();; ++it) {	// ++val or val.operator++() (not val++) (from Iterator_L class)
				this_node->next = new node(*it);
				stepUp();
				if (it == _right.last()) break;
			}
			pLast = this_node;
			pFirst = head->next;
		}
		else {
			head = new node();
		}
	}
	List(List&& right_): head(right_.head), pFirst(right_.pFirst),pLast(right_.pLast) {
		right_.head = nullptr;
		right_.pFirst = nullptr;
		right_.pLast = nullptr;
	}
	List(const val_& right_) {
		head = new node();
		pFirst = nullptr;
		pLast = nullptr;
		this->push_back(right_);
	}
	List(const size_t& sz, const val_& right_) {
		head = new node();
		pFirst = nullptr;
		pLast = nullptr;
		size_t r = sz;
		while(r--)
		this->push_back(right_);
	}
	~List() {
		if (head != nullptr) {
			this_node = head->next;
			while (head != nullptr) {
				delete head;
				head = this_node;
				if (head != nullptr)
					this_node = head->next;
			}
		}
	}
//---------------------------------------

	void push_back(const val_& _val) {
		if (pFirst == nullptr) {
			head->next = new node(_val);
			pFirst = head->next;
			pLast = pFirst;
		}
		else {
			this_node = pFirst;
			while (this_node->next != nullptr) {
				stepUp();
			}
			this_node->next = new node(_val);
			stepUp();
			pLast = this_node;
		}
	}
	void push_back(const node& _n) {
		if (pFirst == nullptr) {
			head->next = new node(_n.get());
			pFirst = head->next;
			pLast = pFirst;
		}
		else {
			this_node = pFirst;
			while (this_node->next != nullptr) {
				stepUp();
			}
			this_node->next = new node(_n.get());
			stepUp();
			pLast = this_node;
		}
	}

	void insert(size_t pos, const val_& _val) {
		node* tmp = new node(_val);
		this_node = head;
 		for (size_t i = 0; i < pos; i++) {
			if (this_node->next == nullptr && i <= pos - 1) {
				throw std::out_of_range("List out of range");
			}
			stepUp();
		}
		tmp->next = this_node->next;
		this_node->next = tmp;
		pFirst = head->next;
		while (this_node->next != nullptr) stepUp();
		pLast = this_node;
	}

	void push_front(const val_& _val) noexcept {
		insert(0, _val);
	}

	size_t size() const {
		size_t sz = 0;
		node* this_node;
		this_node = head;
		while (this_node->next != nullptr) {
			++sz;
			this_node = this_node->next;
		}
		return sz;
	}
	size_t size() {
		size_t sz = 0;
		this_node = head;
		while (this_node->next != nullptr) {
			++sz;
			stepUp();
		}
		return sz;
	}

	val_& operator[](size_t pos_) {	//exception situation on the conscience of the developer
		this_node = head;
		size_t tmp = 0;
		while (tmp++ < pos_) {
			stepUp();
		}
		return this_node->next->data;
	}
	val_& at(size_t pos_) {
		if(pos_ >= size()) throw std::out_of_range("List out of range");
		this_node = head;
		size_t tmp = 0;
		while (tmp++ < pos_) {
			stepUp();
		}
		return this_node->next->data;
	}
	List<val_> operator+(const List& right_) const {
		if (right_.pFirst==nullptr && pFirst==nullptr) { return List<val_>({}); }
		else if (right_.pFirst==nullptr) { return List<val_>(*this); }
		else if (pFirst==nullptr) { return List<val_>(right_); }
		List<val_> res(*this);
		for (auto it = right_.begin();; ++it) {
			res.push_back(*it);
			if (it == right_.last()) break;
		}
		return res;
	}
	List<val_> operator-(const List& right_) = delete;
	List& operator=(List&& right_) noexcept {
		if (this != &right_) {
			clear();
			head = right_.head;
			pFirst = right_.pFirst;
			pLast = right_.pLast;
			right_.head = nullptr;
			right_.pFirst = nullptr;
			right_.pLast = nullptr;
		}
		return *this;
	}
	List& operator=(const List& right_) {
		if (this == &right_) {
			return *this;
		}
		size_t sz_l = size(), sz_r = right_.size();
		while (sz_l < sz_r) {
			sz_l++;
			push_back(0);
		}
		while (sz_r < sz_l) {
			sz_l--;
			pop_back();
		}
		this_node = head->next;
		node* rtmp = right_.head->next;
		while (true) {
			this_node->data = rtmp->data;
			if (this_node == pLast) break;
			stepUp();
			rtmp = rtmp->next;
		}
		return *this;
	}
	bool operator==(const List& right_) const{
		if (size() == 0 && right_.size() == 0) return true;
		if (size() != right_.size()) {
			return false;
		}
		auto it1 = begin(), it2 = right_.begin();
		for (;; ++it1, ++it2) {
			if (*it1 != *it2)return false;
			if (it1 == last())break;
		}
		return true;
	}
	bool operator!=(const List& right_) const {
		return !((*this).operator==(right_));
	}
#define out_del_range_exc(a) if (head->next == nullptr) {throw std::out_of_range(("cant delete "+std::string(a)+" element from empty object"));}	//!a must be string! and exception situation on the conscience of the developer
	void pop_front() {
		out_del_range_exc("first")
		this_node = head;
		head = pFirst;
		delete this_node;
		if (pFirst == pLast) {
			head->next = pFirst = pLast = nullptr;
		}
		else {
			pFirst = head->next;
		}
	}
	void pop_back() {
		out_del_range_exc("last")
		this_node = head;
		while (this_node->next != pLast) {
			stepUp();
		}
		delete pLast;
		if (pFirst == this_node->next) {
			head->next=pFirst = pLast = nullptr;
		}
		else {
			this_node->next = nullptr;
			pLast = this_node;
		}
	}

	void del_at(size_t pos_) {
		out_del_range_exc("")
		if (pos_ == 0) {
			pop_front();
		}
		else {
			size_t sz = size();
			if (pos_ >= sz) {
				throw std::out_of_range("delete position out of range");
			}
			else if(sz-1 == pos_){
				pop_back();
			}
			else {
				size_t cur_ = 0;
				this_node = head;
				while (cur_ != pos_) {
					stepUp();
					++cur_;
				}
				node* tmp = this_node->next->next;
				delete[] this_node->next;
				this_node->next = tmp;
			}
		}
	}
	List sorted_merge(const List& left_, const List& right_) {
		
		if (right_.pFirst == nullptr && left_.pFirst == nullptr) { return List(); }
		else if (left_.pFirst == nullptr) { return List(right_); }
		else if (right_.pFirst == nullptr) { return List(left_); }
		List<val_> res;
		auto p1 = left_.begin(), p2 = right_.begin(), e1 = left_.last(), e2 = right_.last();
		bool f1 = true, f2 = true;
		while (true) {
			if (*p1 <= *p2) {
				res.push_back(*p1);
				if (p1 == e1) {
					f1 = false;
					break;
				}
				p1.operator++();
			}
			else {
				res.push_back(*p2);
				if (p2 == e2) {
					f2 = false;
					break;
				}
				p2.operator++();
			}
		}
		if (f1) {
			while (true) {
				res.push_back(*p1);
				if (p1 == e1) break;
				p1.operator++();
			}
		}
		if (f2) {
			while (true) {
				res.push_back(*p2);
				if (p2 == e2) break;
				p2.operator++();
			}
		}
		return res;
	}
	void clear() {
		this_node = head->next;
		while (head->next != nullptr) {
			delete head;
			head = this_node;
			if (head->next != nullptr)
				this_node = head->next;
		}
		pFirst = pLast = nullptr;
	}
	bool check_sorted() const{
		if (pFirst == nullptr) return true;
		auto it1 = begin(), it2 = begin();
		if (it1 == last())return true;
		++it2;
		while (true) {
			if (*it2 < *it1) return false;
			if (it2 == last()) break;
			++it1; ++it2;
		}
		return true;
	}
	void merge_sort() {
		if (pLast == pFirst || pFirst == nullptr) return;
		vector<List<val_>> arr; 
		for (auto it = begin();; ++it) {arr.push_back({*it}); if (it == last()) break; }

		while (arr.size() > 1) {
			vector<List<val_>> arr2;

			for (size_t i = 0; i < arr.size()-1; i += 2) {
				arr2.push_back(sorted_merge(arr[i], arr[i + 1]));
			}
			if (arr.size() & 1) {
				arr2.push_back(arr.back());
			}
			arr = arr2;
		}
		clear();
		for (auto it = arr[0].begin();; ++it) {
			push_back(*it);
			if (it == arr[0].last())break;
		}
	}
#undef out_del_range_exc(a)
	/*friend std::ostream& operator<<(std::ostream& os, const List<val_>& list_) {
		node* local_this_node;
		local_this_node = list_.pFirst;
		while (local_this_node != nullptr) {
			os << local_this_node->data << ' ';
			local_this_node = local_this_node->next;
		}
		return os;
	}*/
};