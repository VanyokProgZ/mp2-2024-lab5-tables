#pragma once
#include <iostream>
#include "data.h"
#define BLACK false
#define RED true

template<typename val_, typename key_t = std::string>
class RBTree {
    struct Vertex {
        Vertex* parent, * left, * right;
        Data<key_t, val_> data;
        bool color;
        Vertex() :parent(nullptr), left(nullptr), right(nullptr), data(0), color(BLACK) {};
        Vertex(const Data<key_t, val_>& data_, bool color_, Vertex* son_, Vertex* doughter_, Vertex* parent_ = nullptr) :parent(parent_), left(son_), right(doughter_), data(data_), color(color_) {        }
        Vertex* bro() noexcept {
            return parent ? (parent->left == this ? parent->right : parent->left) : nullptr;
        }
        Vertex* dad() noexcept {
            return parent;
        }
        Vertex* grandpa() noexcept {
            return parent ? parent->parent : nullptr;
        }
        Vertex* uncle() noexcept {
            return parent ? parent->bro() : nullptr;
        }
        Vertex* son() noexcept { return left; }
        Vertex* doughter()noexcept { return right; }
        bool getcolor()noexcept { return color; }
        bool amiright()noexcept { return parent ? parent->right == this : 0; }
        bool setcolor(bool color_) noexcept { color = color_; return color; }
    };
    Vertex* root;
    size_t LOG_;

    Vertex* SLR(Vertex* center) { //dont link parent->child to top vertex (SRR too)
        //i dont know this is 'swap' for log or no - i will log cmp in rotations and plus 1 like we do 'swap'
        LOG_++;
        Vertex* tmp = center->right;
        if (!tmp) return center;
        LOG_++;
        center->right = tmp->left;
        if (tmp->left)tmp->left->parent = center;
        LOG_++;
        tmp->left = center;
        tmp->parent = center->parent;
        center->parent = tmp;
        return tmp;
    }
    Vertex* SRR(Vertex* center) {
        LOG_++;
        Vertex* tmp = center->left;
        if (!tmp) return center;
        LOG_++;
        center->left = tmp->right;
        if (tmp->right)tmp->right->parent = center;
        LOG_++;
        tmp->right = center;
        tmp->parent = center->parent;
        center->parent = tmp;
        return tmp;
    }
    
    void Color_aft_delete(Vertex* x) {  //pu-pu-puuuu
        Vertex* tmp;
        int last_move = -1;
        while (x != root && !x->getcolor())
        {
            LOG_+=2;
            if (!x->amiright()) {
                LOG_++;
                tmp = x->bro();
                if (tmp && tmp->getcolor()) {//1
                    LOG_+=2;
                    tmp->setcolor(BLACK);
                    x->parent->setcolor(RED);
                    if (root != x->parent) {
                        LOG_+=2;
                        tmp = x->grandpa();
                        if (x->parent->amiright()) {
                            tmp->right = SLR(x->parent);
                        }
                        else {
                            tmp->left = SLR(x->parent);
                        }
                        x->grandpa()->parent = tmp;
                    }
                    else {
                        LOG_++;
                        root = SLR(x->parent);
                    }
                    tmp = x->bro();
                    last_move = 1;
                }
                else if ((!(tmp->left) || !(tmp->left->getcolor())) && (!(tmp->right) || !(tmp->right->getcolor()))) {//2
                    LOG_+=3;//1 from prev if and 2(better case) from this else if
                    tmp->setcolor(RED);
                    LOG_++;
                    x = x->parent;
                    if (last_move == 1) {
                        x->setcolor(BLACK);
                        x = root;
                    }
                    last_move = 2;
                }
                else if (!tmp->right || !tmp->right->getcolor()) {//3
                    LOG_+=3;
                    LOG_++;
                    if (tmp->left)tmp->left->setcolor(BLACK);
                    tmp->setcolor(RED);
                    x->parent->right = SRR(tmp);
                    x->parent->right->parent = x->parent;
                    tmp = x->bro();
                    last_move = 3;
                }
                else {
                    LOG_+=3;
                    tmp->setcolor(tmp->parent->getcolor());
                    tmp->parent->setcolor(tmp->right->setcolor(BLACK));
                    if (tmp->parent != root) {
                        LOG_+=2;
                        tmp = x->grandpa();
                        if (x->parent->amiright()) {
                            tmp->right = SLR(x->parent);
                            tmp->right->parent = tmp;
                        }
                        else {
                            tmp->left = SLR(x->parent);
                            tmp->left->parent = tmp;
                        }
                        x = tmp;
                    }
                    else {
                        LOG_++;
                        root = SLR(x->parent);
                        root->parent = nullptr;
                    }
                    x = root;
                    last_move = 4;
                }
            }
            else {
                LOG_++;
                tmp = x->bro();
                if (tmp->getcolor()) {
                    LOG_++;
                    tmp->setcolor(BLACK);
                    x->parent->setcolor(RED);

                    if (x->parent != root) {
                        LOG_+=2;
                        tmp = x->grandpa();
                        if (x->parent->amiright()) {
                            tmp->right = SRR(x->parent);
                        }
                        else {
                            tmp->left = SRR(x->parent);
                        }
                        x->grandpa()->parent = tmp;
                    }
                    else {
                        LOG_++;
                        root = SRR(x->parent);
                    }
                    tmp = x->bro();
                    last_move = 1;
                }
                else if ((!(tmp->left) || !(tmp->left->getcolor())) && (!(tmp->right) || !(tmp->right->getcolor()))) {
                    LOG_+=3;
                    tmp->setcolor(RED);
                    x = x->parent;
                    LOG_++;
                    if (last_move == 1) {
                        x->setcolor(BLACK);
                        x = root;
                    }
                    last_move = 2;
                }
                else if (!tmp->left || !tmp->left->getcolor()) {
                    LOG_+=3;
                    LOG_++;
                    if (tmp->right) tmp->right->setcolor(BLACK);
                    tmp->setcolor(RED);
                    x->parent->left = SLR(tmp);
                    x->parent->left->parent = x->parent;
                    tmp = x->bro();
                    last_move = 3;
                }
                else {
                    LOG_+=3;
                    tmp->setcolor(x->parent->getcolor());
                    x->parent->setcolor(BLACK);
                    tmp->left->setcolor(BLACK);

                    if (x->parent != root) {
                        LOG_+=2;
                        tmp = x->grandpa();
                        if (x->parent->amiright()) {
                            tmp->right = SRR(x->parent);
                            tmp->right->parent = tmp;
                        }
                        else {
                            tmp->left = SRR(x->parent);
                            tmp->left->parent = tmp;
                        }
                        x = tmp;

                    }
                    else {
                        LOG_++;
                        root = SRR(x->parent);
                    }
                    x = root;
                    last_move = 4;
                }

            }
        }
        x->setcolor(BLACK);
    }
    size_t TBD(Vertex* v) { //test black depth
        if (v == nullptr) return 0;
        auto l = TBD(v->left);
        auto r = TBD(v->right);
        if (l != r) {
            throw std::logic_error("different black height");
        }
        return l + !v->getcolor();
    }
    size_t TCV(Vertex* v) {
        if (v == nullptr)return 0;
        return 1 + TCV(v->left) + TCV(v->right);
    }
    size_t NRR(Vertex* v) {
        if (v == nullptr)return 0;
        auto l = NRR(v->left);
        auto r = NRR(v->right);
        if ((l || r) && v->getcolor()) {
            throw std::logic_error("RED AFTER RED");
        }
        return v->getcolor();
    }
public:
    void NO_RED_RED() {
        NRR(root);
    }
    void TESTER_DEPTH_B() {
        TBD(root);
    }
    size_t TESTER_VERTEX_CNT() {
        return TCV(root);
    }
    RBTree() : root(nullptr),LOG_(0) {};

    ~RBTree() {
        while (root) { Delete(root->data.getKey()); }
    }
    void resetLog() { LOG_ = 0; }   //yes, user cant set log, only reset;)
    size_t Log() { return LOG_; }

    void insert(const Data<key_t, val_>& data_) {
        //here log eq cmp and swap
        if (!root) {
            LOG_++;
            root = new Vertex(data_, RED, nullptr, nullptr);
            root->setcolor(BLACK);
            return;
        }
        Vertex* p = root,*ptr = nullptr;
        
        while (true) {
            if (data_ < p->data) {
                LOG_++;//cmp log
                ptr = p;
                if (p->left)
                    p = p->left;
                else {
                    p->left = new Vertex(data_, RED, nullptr, nullptr, p);
                    p = p->left;
                    break;
                }
                
            }
            else if (data_ > p->data) {
                LOG_++;
                ptr = p;
                if (p->right)
                    p = p->right;
                else {
                    p->right = new Vertex(data_, RED, nullptr, nullptr, p);
                    p = p->right;
                    break;
                }
                
            }
            else if (data_ == p->data) {
                throw std::logic_error("ERROR WHILE INSERT - Key already exists!");
            }
        }

        //color check
        Vertex* tmp,*tmp2;
        while (p->parent->getcolor()) {
            LOG_++;//while cmp log
            if (p->uncle() && p->uncle()->getcolor()) {
                LOG_+=2;//2 because 2 uslovia
                p->grandpa()->setcolor(!p->parent->setcolor(p->uncle()->setcolor(BLACK)));
                p = p->grandpa();
            }
            else if (p->parent->amiright()) {
                LOG_+=2;//two cmp if
                if (!p->amiright()) {
                    p = p->parent;
                    tmp = p->parent;
                    if (p != root) {
                        LOG_+=2; //up and down cmp ifs
                        if (p->amiright()) {
                            tmp->right = SRR(p);
                        }
                        else {
                            tmp->left = SRR(p);
                        }
                    }
                    else {
                        LOG_++;//if cmp (was false and now we here)
                        root = SRR(p);
                    }
                }
                LOG_++;//up if cmp
                (p->grandpa()->setcolor(!p->parent->setcolor(BLACK)));
                
                if (p->grandpa() != root) {
                    LOG_+=2;
                    tmp = p->grandpa()->parent;
                    if (p->grandpa()->amiright()) {
                        tmp->right = SLR(p->grandpa());
                    }
                    else {
                        tmp->left = SLR(p->grandpa());
                    }
                }
                else {
                    LOG_++;
                   root = SLR(p->grandpa());
                }
                    
            }
            else {
                LOG_+=2;//false and false from prev ifs
                if (p->amiright()) {
                    p = p->parent;
                    tmp = p->parent;
                    if (p != root) {
                        LOG_+=2;
                        if (p->amiright()) {
                            tmp->right = SLR(p);
                        }
                        else {
                            tmp->left = SLR(p);
                        }
                    }
                    else {
                        LOG_++;
                        root = SLR(p);
                    }
                }
                LOG_++;
                (p->grandpa()->setcolor(!p->parent->setcolor(BLACK)));

                if (p->grandpa() != root) {
                    LOG_+=2;
                    tmp = p->grandpa()->parent;
                    if (p->grandpa()->amiright()) {
                        tmp->right = SRR(p->grandpa());
                    }
                    else {
                        tmp->left = SRR(p->grandpa());
                    }
                }
                else {
                    LOG_++;
                    root = SRR(p->grandpa());
                }
            }
            LOG_++;
            if (p == root)break;
        }
        root->setcolor(BLACK);
        
    }

    void insert(const key_t& k, const val_& v) {
        Data<key_t, val_> t(k, v);
        insert(t);
    }

    void Delete(const key_t& key_) {

        Vertex* this_v = find_vertex_by_key(key_), * x, * fix_c;
        if (!this_v) {
            LOG_++;
            throw std::logic_error("cant find vertex to delete");
        }
        if (this_v == root && !root->left && !root->right) {
            LOG_+=3;
            delete root;
            root = nullptr;
            return;
        }
        else if (this_v == root && !root->left && root->right) {
            LOG_+=4;//3 this + 1(the best variant) from first if
            x = root->right;
            delete root;
            root = x;
            x->parent = nullptr;
            root->setcolor(BLACK);
            return;
        }
        else if (this_v == root && root->left && !root->right) {
            LOG_+=5;
            x = root->left;
            delete root;
            root = x;
            x->parent = nullptr;
            root->setcolor(BLACK);
            return;
        }
        bool fix_c_p = 0;
        bool deleted_color = this_v->getcolor();
        if (!this_v->left) {
            LOG_+=2;    //one for cmp and one for 'swap'
            x = this_v->right;
            fix_c = this_v->parent;
            fix_c_p = this_v->amiright();
            if (x)x->parent = this_v->parent;
            LOG_+=2;//2 cmp
            if (this_v->amiright()) {
                this_v->parent->right = x;
            }
            else {
                this_v->parent->left = x;
            }
            delete this_v;
        }
        else if (!this_v->right) {
            LOG_+=3;//2 cmp 1 swap
            x = this_v->left;
            fix_c = this_v->parent;
            fix_c_p = this_v->amiright();
            if (x)x->parent = this_v->parent;
            LOG_+=2;
            if (this_v->amiright()) {
                this_v->parent->right = x;
            }
            else {
                this_v->parent->left = x;
            }
            delete this_v;
        }
        else {
            LOG_+=3;
            Vertex* min_right = this_v->right;
            while (min_right->left) min_right = min_right->left;
            deleted_color = min_right->getcolor();
            LOG_++;
            min_right->data = this_v->data.swap(min_right->data);//one 'real swap (data, not ptrs)'
            if (min_right != this_v->right) {
                LOG_+=2;//top and bottom ifs
                min_right->parent->left = min_right->right;
                if (min_right->right)min_right->right->parent = min_right->parent;
                fix_c = min_right->parent;
                fix_c_p = 0;
                x = min_right->parent->left;
                delete min_right;
            }
            else {
                LOG_+=2;
                this_v->right = min_right->right;
                if (min_right->right)min_right->right->parent = this_v;
                fix_c_p = 1;
                fix_c = this_v;
                x = this_v->right;
                delete min_right;
            }

        }
        if (!deleted_color) {
            if (!x) {
                LOG_++;
                x = new Vertex(Data<key_t, val_>(key_t(), val_()), 0, nullptr, nullptr, fix_c);
                LOG_++;
                if (fix_c_p) {
                    fix_c->right = x;
                }else{ fix_c->left = x; }
                Color_aft_delete(x);
                LOG_++;
                if (x->parent->left == x) {
                    x->parent->left = nullptr;
                }
                else {
                    x->parent->right = nullptr;
                }
                LOG_++;
                if (x->left || x->right) throw std::logic_error("when x was able to give birth?");
                delete x;
            }
            else {
                LOG_++;
                Color_aft_delete(x);
            }
        }
        LOG_++;
    }
    Vertex* find_vertex_by_key(const key_t& key_) {
        Vertex* current_ptr = root;
        LOG_++;
        if (!current_ptr)return nullptr;
        while (true) {
            LOG_++;//for ><=
            if (current_ptr->data.getKey() == key_) {
                return current_ptr;
            }
            else if (current_ptr->data.getKey() > key_) {
                LOG_++;//for ptr->child
                if (current_ptr->left) {
                    current_ptr = current_ptr->left;
                }
                else {
                    return nullptr;
                }
            }
            else {
                LOG_++;
                if (current_ptr->right) {
                    current_ptr = current_ptr->right;
                }
                else {
                    return nullptr;
                }
            }
        }
    }
    bool HaveAKey(const key_t& key_) {
        Vertex* res = find_vertex_by_key(key_);
        return res ? true : false;
    }
};



