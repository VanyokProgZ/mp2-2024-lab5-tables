#pragma once
#include <string>
#include "list.h"
#include "parse_digits.h"


struct psevdo_lexem {
	short type;
	std::string name;
	psevdo_lexem() :type(0), name("") {};
	psevdo_lexem(short t, const std::string& s) :type(t), name(s) {};
};
//std::ostream& operator<<(std::ostream& os, psevdo_lexem& pl) {
//	std::cout << pl.name;
//	return os;
//}
//type:
// 0 - undefined
// 1 - +/-
// 2 - Const
// 3 - variable
// 4 - degree
#define big_degree(a,b) if ((a)>(b))throw std::length_error("TOO BIG DEGREE")
template <typename T>
struct Monom {
	class Degree {
		size_t degree;
	public:
		Degree(size_t deg = 0) :degree(deg) {
			if (degree > 999) throw std::length_error("TOO BIG DEGREE");
		}
		Degree(const Degree& deg) :degree(deg.degree) {};
		~Degree() { }
		bool operator<=(const Degree& right_)const { return degree <= right_.degree; }
		bool operator<(const Degree& right_) const { return degree < right_.degree; }
		bool operator>(const Degree& right_) const { return degree > right_.degree; }
		bool operator>=(const Degree& right_) const { return degree >= right_.degree; }
		bool operator==(const Degree& right_) const { return degree == right_.degree; }
		bool operator!=(const Degree& right_) const { return degree != right_.degree; }

		Degree operator+(const Degree& right_) { if (degree + right_.degree > 999) throw std::length_error("TO BIG DEGREE"); return Degree(degree + right_.degree); }
		Degree operator-(const Degree& right_) { if (degree + right_.degree > 999) throw std::length_error("INCORRECT DEGREE"); return Degree(degree - right_.degree); }
		Degree operator*(const Degree& right_) { if (degree + right_.degree > 999) throw std::length_error("INCORRECT DEGREE"); return Degree(degree * right_.degree); }
		Degree operator/(const Degree& right_) { if (degree + right_.degree > 999 || (degree < right_.degree) || (degree % right_.degree != 0)) throw std::length_error("INCORRECT DEGREE"); return Degree(degree / right_.degree); }
		Degree& operator=(const Degree& right_) { if (&right_ == this)return *this; degree = right_.degree; return *this; }

		size_t get()const noexcept{ return degree; }
		size_t getX() const noexcept { return degree / 100; }
		size_t getY() const noexcept { return (degree - (degree / 100)*100) / 10; }
		size_t getZ() const noexcept { return degree % 10; }

		void set(size_t deg) { big_degree(deg,999); degree = deg; }
		void setX(size_t deg) { big_degree(deg,9); degree = ((degree - degree / 100) + deg * 100); }
		void setY(size_t deg) { big_degree(deg,9); degree = degree - getY() * 10 + deg * 10; }
		void setZ(size_t deg) { big_degree(deg,9); degree = ((degree - degree % 10) + deg); }

		void add(size_t deg) { big_degree(deg, 999); big_degree(deg + get(), 999); (*this).set(deg + get()); }
		void addX(size_t deg) { big_degree(deg,9); big_degree(deg + getX(), 9); (*this).setX(getX() + deg); }
		void addY(size_t deg) { big_degree(deg,9); big_degree(deg + getY(), 9); (*this).setY(getY() + deg); }
		void addZ(size_t deg) { big_degree(deg,9); big_degree(deg + getZ(), 9); (*this).setZ(getZ() + deg); }
	};
#undef big_degree(a,b)
	Degree DEGREE;

	Monom() :DEGREE(000), C(T()) {}
	Monom(const T& c_) : C(c_), DEGREE(000) {};
	Monom(const T& c_, const Degree& deg) : C(c_), DEGREE(deg) {};
	~Monom() {}
	//!ONLY DEGREE CMP OPERATORS!
	bool operator<=(const Monom& right_) { return DEGREE <= right_.DEGREE; }
	bool operator<(const Monom& right_) { return DEGREE < right_.DEGREE; }
	bool operator>(const Monom& right_) { return DEGREE > right_.DEGREE; }
	bool operator>=(const Monom& right_) { return DEGREE >= right_.DEGREE; }
	bool operator==(const Monom& right_) { return DEGREE == right_.DEGREE; }
	bool operator!=(const Monom& right_) { return DEGREE != right_.DEGREE; }

	bool isNull() { return C == T(0); }
	bool EQ(const Monom& right_) { return C == right_.C && DEGREE == right_.DEGREE; }	//==
	bool NE(const Monom& right_) { return C != right_.C || DEGREE != right_.DEGREE; }	//!=
	bool GR(const Monom& right_) { if (DEGREE != right_.DEGREE) throw std::logic_error("different degree!"); return C > right_.C; }	//>
	bool LO(const Monom& right_) { if (DEGREE != right_.DEGREE) throw std::logic_error("different degree!"); return C < right_.C; }	//<
	bool GE(const Monom& right_) { if (DEGREE != right_.DEGREE) throw std::logic_error("different degree!"); return C >= right_.C; }	//>=
	bool LE(const Monom& right_) { if (DEGREE != right_.DEGREE) throw std::logic_error("different degree!"); return C <= right_.C; }	//<=

	T value() const noexcept { return C; }
	void valueAdd(const T& right_) noexcept{ C = C + right_; }
	void valueSet(const T& right_) noexcept{ C = right_; }

	Monom operator+(const Monom& right_) {
		if (DEGREE != right_.DEGREE) throw std::logic_error("different degree!");
		return Monom(C + right_.C, DEGREE);
	}
	Monom operator-(const Monom& right_) {
		if (DEGREE != right_.DEGREE) throw std::logic_error("different degree!");
		return Monom(C - right_.C, DEGREE);
	}
	Monom operator*(const Monom& right_) {
		Degree D;
		D.setX(DEGREE.getX() + right_.DEGREE.getX());
		D.setY(DEGREE.getY() + right_.DEGREE.getY());
		D.setZ(DEGREE.getZ() + right_.DEGREE.getZ());
		return Monom(C * right_.C, D);
	}
	Monom operator*(const T& right_) {
		return Monom(right_ * C, DEGREE);
	}
	
	Monom operator/(const T& right_) {
		return Monom(C/right_, DEGREE);
	}
	Monom& operator=(const Monom& right_) {
		if (&right_ == this)return *this;
		C = right_.C;
		DEGREE = right_.DEGREE;
		return *this;
	}
	friend std::ostream& operator<<(std::ostream& os, const Monom<T>& right_) {	//ONLY FOR COUT POLINOME!!!
		if (right_.value() != T(0)) {
			os << abs(right_.value());
			size_t X = right_.DEGREE.getX(), Y = right_.DEGREE.getY(), Z = right_.DEGREE.getZ();
			if (X) os << "x";
			if (X != 1 && X) os << X;
			if (Y) os << "y";
			if (Y != 1 && Y) os << Y;
			if (Z) os << "z";
			if (Z != 1 && Z) os << Z;
			os << ' ';
		}
		return os;
	}
	//WITHOUT OPERATOR>>

private:
	T C;
};

#define _dig(a) ((a)>=48 && (a)<=57)
#define vars(a) (((a)=='X' || (a)=='Y' || (a)=='Z')||((a)=='x' || (a)=='y' || (a)=='z'))
#define oper(a) ((a)=='+' || (a)=='-')
#define allow(a) (oper(a) || _dig(a) || vars(a) || (a)==' ' || (a)=='.' || (a)=='e' || (a)=='E')

bool check_allow_main_symb(const std::string& s);

bool all_Nums(const std::string& s);

template <typename val_>
class Polinome {
private:
	List<Monom<val_>> polinome;
public:
	Polinome() : polinome(Monom<val_>()) {};
	Polinome(const Monom<val_>& right_) : polinome(right_) {};
	Polinome(const Polinome<val_>& right_) : polinome(right_.polinome) {};
	Polinome(const List<Monom<val_>>& right_) : polinome(right_) { make_uniq(); }
	Polinome(Polinome&& right_) : polinome(std::move(right_.polinome)) { }
	Polinome(const List<val_>& right_) : polinome(){
		size_t sz = 0;
		if(right_.size())
		for (auto it = right_.begin();; ++it) {
			polinome.push_back(Monom<val_>(*it,++sz));
			if (it == right_.last()) break;
		}
		SORT();
	}
	Polinome(const size_t& sz) : polinome(sz, val_(0)) {};
	~Polinome() {};

	Iterator_L<Monom<val_>> begin() const {
		return polinome.begin();
	}
	Iterator_L<Monom<val_>> last() const {
		return polinome.last();
	}

	const List<Monom<val_>>& getList()const noexcept{
		return polinome;
	}
	size_t size() const { return polinome.size(); }

	void clear() { polinome.clear(); }

	void SORT() { polinome.merge_sort(); }

	void make_uniq() {
		SORT();
		Polinome<val_> temp(0);
		if (!size())return;
		auto it = begin();
		if (temp.size()==0) {
			temp.push_back(*it);
			++it;
		}
		while (true) {
			if (*it == *(temp.last())) {
				(*(temp.last())).valueAdd((*it).value());
			}
			else {
				temp.push_back(*it);
			}
			if (it == last())break;
			++it;
		}
		clear();
		auto null_ = val_(0);
		it = temp.begin();
		for (;; ++it) {
			if ((*it).value() != null_) {
				push_back(*it);
			}
			if (it == temp.last())break;
		}
		return;
	}

	bool check_sorted() const{ return polinome.check_sorted(); }

	void push_back(const Monom<val_>& right_) { polinome.push_back(right_); }

	bool operator==(const Polinome& right_)const {
		return polinome == right_.polinome;
	}
	Polinome& operator=(const Polinome& right_) {
		if (&right_ == this)return *this;
		polinome.operator=(right_.polinome);
		return *this;
	}
	Polinome& operator=(Polinome&& right_) {
		polinome.operator=(std::move(right_.polinome));
		return *this;
	}
	Polinome operator*(const val_& right_)const {
		auto res = Polinome(*this);
		for (auto it = res.begin();; ++it) {
			(*it) = (*it) * right_;
			if (it == res.last())break;
		}
		return res;
	}
	Polinome operator+(const Polinome& right_) const{
		if (!check_sorted() || !right_.check_sorted()) throw std::logic_error("Polinoms must be sorted for + ");
		
		auto it1 = begin();
		auto it2 = right_.begin();
		Polinome<val_> res(0);
		auto null_ = val_(0);
		bool f1 = true, f2 = true;
		while (true) {

			if (*it1 == *it2) {
				val_ otn_eps = std::max(std::abs((*it1).value()), std::abs((*it2).value())) <= std::numeric_limits<val_>::epsilon() ? std::numeric_limits<val_>::epsilon() : std::numeric_limits<val_>::epsilon() * std::max(std::abs((*it1).value()), std::abs((*it2).value()));
				if (!(abs(((*it1).value() + (*it2).value()) - null_) <= otn_eps)) {
					res.push_back(Monom<val_>((*it1).value() + (*it2).value(), (*it1).DEGREE.get()));
				}
				if (it1 == last() && it2 == right_.last()) { f1 = f2 = 0; break; };
				if (it1 == last()) { f1 = 0; ++it2; break; }
				if (it2 == right_.last()) { f2 = 0; ++it1; break; }
				++it1;
				++it2;	
			}
			else if (*it1 < *it2) {
				res.push_back(*it1);
				if (it1 == last()) { f1 = 0; break; }
				++it1;
			}
			else {
				res.push_back(*it2);
				if (it2 == right_.last()) { f2 = 0; break; }
				++it2;
			}
			
		}
		if(f1)
		while (true) {
			res.push_back(*it1);
			if (it1 == last())break;
			++it1;
		}
		if (f2)
			while (true) {
				res.push_back(*it2);
				if (it2 == right_.last())break;
				++it2;
			}
		/*if (res.size() == 0) {
			res.push_back(Monom<val_>(0));
		}*/
		return res;
	}
	Polinome operator-(const Polinome& right_) const{
		if (!check_sorted() || !right_.check_sorted()) throw std::logic_error("Polinoms must be sorted for - ");
		return operator+(right_ * val_(-1));
	}
	Polinome operator*(const Polinome& right_)const {
		
		Polinome<val_> res(0);

		for (auto it1 = begin();; ++it1) {
			for (auto it2 = right_.begin();; ++it2) {
				res.push_back((*it1) * (*it2));
				if (it2 == right_.last())break;
			}
			if (it1 == last())break;
		}
		res.make_uniq();
		return res;
	}
	friend std::ostream& operator<<(std::ostream& os, const Polinome<val_>& p) {
		size_t lgth = 0;
		if (p.size() == 0) {
			os << 0;
			return os;
		}
		for (auto it = p.begin();; ++it) {
			auto right_Monom = *it;
			if (lgth) os << ((right_Monom.value()> val_(0)) ? ("+ ") : ((right_Monom.value() < val_(0)) ? "- " : ""));
			else { os << (right_Monom.value() < val_(0) ? "- " : ""); }
			++lgth;
			
			os << right_Monom;
			if (it == p.last()) break;
		}
		return os;
	}
	friend std::istream& operator>>(std::istream& is, Polinome<val_>& p) {
		std::string raw_input;
		is >> std::ws;
		getline(is, raw_input);
		for (auto i = 0; i < raw_input.size(); i++) if (!allow(raw_input.at(i))) throw j_error("Incorrect symbol '" + std::string(1,raw_input[i]) + "' in position " + my_to_String(i));
		const size_t n = raw_input.size();
		vector<std::string> prepare;
		for (size_t i = 0; i < n; i++) {
			if (raw_input[i] == ' ') continue;
			if (i > 0 && vars(raw_input.at(i)) && vars(prepare.back().at(0))) {
				throw j_error("Two polinoms without operation between!");
			}
			if (_dig(raw_input[i])) {
				std::string temp = "";
				while (i < n && !vars(raw_input[i]) && !oper(raw_input[i]) && raw_input[i] != ' ') {
					temp += raw_input[i];
					++i;
				}
				prepare.push_back(temp);
				if (i >= n)break;
				--i;
			}
			else if (raw_input[i] == '+' || raw_input[i] == '-') prepare.push_back((raw_input[i]=='+' ? "+" : "-"));
			else {
				std::string temp = "";
				while (i < n && (!oper(raw_input[i]) || (temp.size() && (temp.back()=='e' || temp.back() == 'E'))) && raw_input[i] != ' ') {
					temp += raw_input[i];
					++i;
				}
				prepare.push_back(temp);
				if (i >= n)break;
				--i;
			}
		}
		//на этом моменте prepare представляет собой массив с разделенными знаками и разделенными на две части мономами - константу и переменные со степенями
		vector<psevdo_lexem> post;
		bool f = 1;
		for (auto lex : prepare) {
			if (f && lex.at(0) != '-') { post.push_back({ 1,"+" }); }
			f = 0;
			if (lex.size() == 1 && oper(lex.at(0))) {
				post.push_back({ 1,lex });
			}
			else if (all_Nums(lex) || lex.at(0)=='.') {
				post.push_back({ 2, lex });
			}
			else {
				if (!vars(lex.at(0))) throw j_error("expected variable in the beginning of the '"+lex+"'");
				bool x = 0, y = 0, z = 0;
				if (!check_allow_main_symb(lex)) throw j_error("Incorrect symbols in '" + lex+"'");
				for (auto i = 0; i < lex.size(); i++) {
					
					if (lex[i] == 'X' || lex[i] == 'x') {
						if (x) throw j_error("More than one X in '" + lex + "'");
						++i; ++x;
						std::string degree = "";
						while (i < lex.size() && _dig(lex.at(i))) degree += lex.at(i++);
						if (degree.size() > 1) throw j_error("X degree cant be more 9!");
						--i;
						post.push_back({ 3,"X"});
						post.push_back({4,degree});
						if (degree == "")post.back().name = "1";
					}else if (lex[i] == 'Y' || lex[i] == 'y') {
						if (y) throw j_error("More than one Y in '" + lex + "'");
						++i; ++y;
						std::string degree = "";
						while (i < lex.size() && _dig(lex.at(i))) degree += lex.at(i++);
						if (degree.size() > 1) throw j_error("Y degree cant be more 9!");
						--i;
						post.push_back({ 3,"Y" });
						post.push_back({ 4,degree });
						if (degree == "") post.back().name = "1";
					}
					else if (lex[i] == 'Z' || lex[i] == 'z') {
						if (z) throw j_error("More than one Z in '" + lex + "'");
						++i; ++z;
						std::string degree = "";
						while (i < lex.size() && _dig(lex.at(i))) degree += lex.at(i++);
						if (degree.size() > 1) throw j_error("Z degree cant be more 9!");
						--i;
						post.push_back({ 3,"Z" });
						post.push_back({ 4,degree });
						if (degree == "")post.back().name = "1";
					}
					
				}
			}
		}
		for (auto i = 1; i < post.size(); i++) {
			if (post.at(i).type == post.at(i - 1).type) throw j_error("Incorrect input: after '" + post.at(i - 1).name + "' cant be '" + post.at(i).name + "'");
		}
		//теперь post имеет логическое разделение на знаки, числа, переменные, степени
		//собираем мономы - каждый из них имеет в начале либо - либо +
		vector<Monom<val_>> psevdPolinom;
		for (auto i = 0; i < post.size(); i++) {

			size_t degreE = 0;
			bool pos = 1;
			val_ Co;
			if (post.at(i).type != 1) throw j_error("Incorrect symbol in '" + post[i].name + "'");
			if (post.at(i).name == "-") pos = 0;
			
			++i;
			if (post.at(i).type == 2) {
				Co = parser_My(post.at(i).name);
				if (!pos) Co = -Co;
				++i;
			}
			else if (post.at(i).type == 3) {
				Co = val_(1);
				if (!pos) Co = -Co;
			}
			else {
			
			}
			
			for (int j = 0; j < 3; j++) {
				if (i == post.size()) break;
				if (post.at(i).name == "X") {
					++i;
					degreE += parser_My(post.at(i).name) * 100;
					++i;
				}
				if (i == post.size())break;
				if (post.at(i).name == "Y") {
					++i;
					degreE += parser_My(post.at(i).name) * 10;
					++i;
				}
				if (i == post.size())break;
				if (post.at(i).name == "Z") {
					++i;
					degreE += parser_My(post.at(i).name);
					++i;
				}
				if (i == post.size() || oper(post.at(i).name.at(0)))break;
			}
			--i;
			psevdPolinom.push_back({ Co, degreE });
		}
		size_t sz1 = p.size();
		if (sz1 != psevdPolinom.size()) throw j_error("Polinome and input must have equal size!");
		sz1 = 0;
		for (auto it = p.begin();; ++it) {
			*it = psevdPolinom.at(sz1++);
			if (it == p.last()) break;
		}
		p.make_uniq();
		return is;
	}
};

template<class val_>
Polinome<val_> operator*(const val_& left_, const Polinome<val_>& right_) {
	Polinome<val_> res = Polinome<val_>(right_);
	for (auto it = res.begin();; ++it) {
		(*it) = (*it) * left_;
		if (it == res.last())break;
	}
	return res;
}