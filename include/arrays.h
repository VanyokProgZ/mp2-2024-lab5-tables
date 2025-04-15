#pragma once
#include "vector.h"
#include "data.h"


template<typename val_>
class unsorted_array {
	size_t LOG;
	vector<Data<std::string, val_>> data;
public:
	void resetLog() { LOG = 0; }
	size_t Log() { return LOG; }
	unsorted_array() :data(),LOG(0) {};
	void insert(const Data<std::string, val_>& v) { 
		auto fr = find_by_name(v.getKey());
		if (!fr.first)
			data.push_back(v);
		else
			throw std::logic_error("element with that key already exists");
		LOG++; 
	}
	void Delete_by_name(const std::string& name) {
		for (size_t i = 0; i < data.size(); i++) {
			LOG+=2;
			if (data[i].getKey() == name) {
				LOG++;
				auto tmp = data[i];
				data[i] = data.back();
				data[data.size() - 1] = tmp;
				data.pop_back();
				LOG++;
				return;
			}
		}
		throw std::logic_error("Cant find element to delete from unsorted array");
	}
	std::pair<bool, Data<std::string, val_>> find_by_name(const std::string& name) {
		for (size_t i = 0; i < data.size(); i++) {
			LOG += 2;
			if (data[i].getKey() == name) {
				return { 1,data[i] };
			}
		}
		return { 0, Data<std::string, val_>() };
	}
	size_t size() { return data.size(); }
	vector<Data<std::string, val_>> GET_VECTOR() {
		return data;
	}
};




template<class val_>
class sorted_array {
	size_t LOG;
	vector<Data<std::string, val_>> data;
public:
	void resetLog() { LOG = 0; }
	size_t Log() { return LOG; }
	sorted_array() :data(), LOG(0) {};
	size_t lower_bound(const std::string& name) {
		size_t l = 0, r = data.size(),mid;
		while (l < r) {
			LOG += 2;
			mid = (l + r) / 2;
			if (data[mid] < name) {
				l = mid + 1;
			}
			else {
				r = mid;
			}
		}
		return l;
	}
	std::pair<bool, Data<std::string, val_>> find_by_name(const std::string& name) {
		auto ind = lower_bound(name);
		LOG++;
		if (data[ind].getKey() == name) {
			return { ind, data[ind] };
		}
		else {
			return { -1, Data<std::string,val_>() };
		}
	}
	void insert(const Data<std::string, val_>& v) {
		auto ind = lower_bound(v->getKey());
		LOG++;
		if (data[ind].getKey() == v->getKey()) {
			throw std::logic_error("Element with that key already exists");
		}
		else {
			data.push_back(data.back());
			for (size_t i = data.size() - 2; i > ind; i--) {
				LOG += 1;
				data[i] = data[i - 1];
			}
		}
	}
	void Delete(const std::string& v) {
		auto ind = lower_bound(v);
		LOG++;
		if (data[ind].getKey() != v) {
			throw std::logic_error("Cant find element with that key");
		}
		else {
			for (size_t i = ind; i<data.size()-1; i++) {
				LOG++;
				data[i] = data[i+1];
			}
			data.pop_back();
		}
	}

	size_t size() { return data.size(); }
	vector<Data<std::string, val_>> GET_VECTOR() {
		return data;
	}
};