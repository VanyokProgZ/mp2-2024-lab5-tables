#pragma once
template<class key_T, class data_T>
class Data {
    key_T key;
    data_T data;
public:
    Data() :key(key_T()), data(data_T()) {}
    Data(const key_T& k, const data_T& d) :key(k), data(d) {}

    Data& operator=(const Data& right_) {
        key = right_.key;
        data = right_.data;
        return *this;
    }

    bool operator<(const Data& right_)const { return key < right_.key; }
    bool operator>(const Data& right_)const { return key > right_.key; }
    bool operator<=(const Data& right_)const { return key <= right_.key; }
    bool operator>=(const Data& right_)const { return key >= right_.key; }
    bool operator==(const Data& right_)const { return key == right_.key; }
    bool operator!=(const Data& right_)const { return key != right_.key; }

    data_T& getData() const{ return data; }
    data_T& getData() { return data; }
    void setData(const data_T& right_)const { data = right_; }
    void setKey(const key_T& right_) const{ key = right_; }
    key_T getKey()const { return key; }

    Data swap(Data& right_) {
        Data r(key, data);
        data = right_.data;
        key = right_.key;
        return r;
    }
};