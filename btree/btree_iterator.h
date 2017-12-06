#ifndef BTREE_ITERATOR_H
#define BTREE_ITERATOR_H

#include <iterator>
#include "btree.h"



template<typename T> class btree;
template <typename T> class btree_iterator;
template <typename T> class const_btree_iterator;


template <typename T> class btree_iterator {
public:

    typedef std::ptrdiff_t                 difference_type;
    typedef std::bidirectional_iterator_tag      iterator_category;
    typedef T                              value_type;
    typedef T*                             pointer;
    typedef T&                             reference;

    friend class const_btree_iterator<T>;
    friend class btree<T>;
    reference operator*() const;
    pointer operator->() const;
    btree_iterator& operator++();
    btree_iterator& operator++(int);
    btree_iterator& operator--();
    btree_iterator& operator--(int);

    bool operator==(const btree_iterator<T>& other) const;
    bool operator==(const const_btree_iterator<T>& other) const;
    bool operator!=(const btree_iterator<T>& other) const;
    bool operator!=(const const_btree_iterator<T>& other) const;

    btree_iterator(typename btree<T>::Node *pointee = nullptr, unsigned int index=0);
    btree_iterator(const btree_iterator<T>& rhs):pointee_{rhs.pointee_}, currindex_{rhs.currindex_}{}
    btree_iterator(const const_btree_iterator<T>& rhs):pointee_{rhs.pointee_}, currindex_{rhs.currindex_}{}
private:

    typename btree<T>::Node *pointee_;
    unsigned int currindex_;

    unsigned int getParentIndex(const typename btree<T>::Node *child, const typename btree<T>::Node *parent) const;

};


template <typename T> class const_btree_iterator {

public:

    typedef std::ptrdiff_t                       difference_type;
    typedef std::bidirectional_iterator_tag      iterator_category;
    typedef T                                        value_type;
    typedef const T*                             pointer;
    typedef const T&                             reference;

    friend class btree_iterator<T>;

    reference operator*() const;
    pointer operator->() const;

    //prefix
    const_btree_iterator& operator++();
    const_btree_iterator& operator--();
    //postfix
    const_btree_iterator& operator++(int);
    const_btree_iterator& operator--(int);


    bool operator==(const const_btree_iterator<T>& other) const;
    bool operator!=(const const_btree_iterator<T>& other) const;
    bool operator==(const btree_iterator<T>& other) const;
    bool operator!=(const btree_iterator<T>& other) const ;

    //constructor
    const_btree_iterator(typename btree<T>::Node *pointee = nullptr,unsigned int index=0);
    const_btree_iterator(const btree_iterator<T>& rhs):pointee_{rhs.pointee_}, currindex_{rhs.currindex_}{}
    const_btree_iterator(const const_btree_iterator<T>& rhs):pointee_{rhs.pointee_}, currindex_{rhs.currindex_}{}

private:

    unsigned int getParentIndex(const typename btree<T>::Node *child, const typename btree<T>::Node *parent) const;

    typename btree<T>::Node *pointee_;
    unsigned int currindex_;

};

//implementation of btree_Iterator

//constructor
template <typename T>
btree_iterator<T>::btree_iterator(typename btree<T>::Node *pointee, unsigned int index) : pointee_(pointee),currindex_(index){}


//prefix
template<typename T> btree_iterator<T>&
btree_iterator<T>::operator++() {
    //moving downward to the leftmost child and the first element;
    if(pointee_->children_.at(currindex_+1) != nullptr){
        pointee_=pointee_->children_[currindex_+1];
        currindex_=0;
        while(pointee_->children_[currindex_]!= nullptr){
            pointee_ = pointee_->children_[currindex_];
        }
    //if there is no right children, ++ can only go up or go right
    } else {
        //move right
        if(currindex_ < pointee_->used-1){
            ++currindex_;
            return *this;
            //move up
        } else {
            value_type currValue=pointee_->elem_[currindex_];
            while(pointee_->parent_ != nullptr){
                pointee_ = pointee_->parent_;
                for(currindex_=0; currindex_ < pointee_->used; ++currindex_){
                    if(pointee_->elem_[currindex_]> currValue ) {
                        return *this;
                    }
                }
            }
            //the last element of the tree.
            currindex_ = pointee_->used;
            return *this;
        }
    }
    return *this;
}

template<typename T> btree_iterator<T>&
btree_iterator<T>::operator--() {
//    std::cout<<"BEFORE  index is " <<currindex_ << " element is "<<pointee_->elem_[currindex_]<<"\n";
    //moving down
    if(pointee_->children_[currindex_] != nullptr){
        pointee_ = pointee_->children_[currindex_];
        while(pointee_->children_[pointee_->used] != nullptr){
            pointee_ = pointee_->children_[pointee_->used];
        }
        currindex_ = pointee_->used-1;
    } else if(currindex_ > 0){
        --currindex_;
    }else {
        typename btree<T>::Node *child, *parent;
        child=pointee_;
        parent=pointee_->parent_;
        unsigned int pIdx;
        while(parent != nullptr){
            pIdx = getParentIndex(child,parent);
            if(pIdx > 0){
                currindex_ = pIdx-1;
                pointee_=parent;
                return *this;
            }
            child=parent;
            parent=parent->parent_;
        }
        --currindex_;
        return *this;

    }
    return *this;
}

template <typename T> unsigned int
btree_iterator<T>::getParentIndex(const typename btree<T>::Node *child,const typename btree<T>::Node* parent ) const{
    return static_cast<unsigned>(std::find_if(parent->children_.begin(),parent->children_.end(),
                                           [child](const typename btree<T>::Node* c){
                                                return c==child;
                                           })- parent->children_.cbegin());
}

//postfix
template<typename T> btree_iterator<T>&
btree_iterator<T>::operator++(int) {
    btree_iterator tmp = *this;
    ++*this;
    return tmp;

}

template<typename T> btree_iterator<T>&
btree_iterator<T>::operator--(int) {
    btree_iterator tmp = *this;
    --*this;
    return tmp;
}

//others
template<typename T> bool
btree_iterator<T>::operator ==(const btree_iterator<T>& other) const {
    return (pointee_== other.pointee_ && currindex_==other.currindex_);
}

template<typename T> bool
btree_iterator<T>::operator==(const const_btree_iterator<T>& other) const{
    return (pointee_== other.pointee_ && currindex_==other.currindex_);
};

template <typename T> bool
btree_iterator<T>::operator!=(const btree_iterator<T>& other) const {
    return !operator==(other);
}

template <typename T> bool
btree_iterator<T>::operator!=(const const_btree_iterator<T>& other) const {
    return !operator==(other);
}

template <typename T> typename btree_iterator<T>::pointer
btree_iterator<T>::operator->() const {
    return &(operator*());
}

template<typename T> typename btree_iterator<T>::reference
btree_iterator<T>::operator*() const {
    return pointee_->elem_[currindex_];
}

//implementation of const_btree_Iterator
//
template <typename T>typename const_btree_iterator<T>::reference
const_btree_iterator<T>::operator*() const{
    return pointee_->elem_[currindex_];
};

template <typename T>typename const_btree_iterator<T>::pointer
const_btree_iterator<T>::operator->() const {
    return &(operator*());

}
template <typename T>
const_btree_iterator<T>::const_btree_iterator(typename btree<T>::Node *pointee,unsigned int index) : pointee_(pointee),currindex_(index){}


//postfix
template<typename T> const_btree_iterator<T>&
const_btree_iterator<T>::operator++(int) {
    const_btree_iterator tmp = *this;
    ++*this;
    return tmp;

}

template<typename T> const_btree_iterator<T>&
const_btree_iterator<T>::operator--(int) {
    const_btree_iterator tmp = *this;
    --*this;
    return tmp;
}

//prefix
template<typename T> const_btree_iterator<T>&
const_btree_iterator<T>::operator++() {
    //moving downward to the leftmost child and the first element;
    if(pointee_->children_.at(currindex_+1) != nullptr){
        pointee_=pointee_->children_[currindex_+1];
        currindex_=0;
        while(pointee_->children_[currindex_]!= nullptr){
            pointee_ = pointee_->children_[currindex_];
        }
        //if there is no right children, ++ can only go up or go right
    } else {
        //move right
        if(currindex_ < pointee_->used-1){
            ++currindex_;
            return *this;
            //move up
        } else {
            value_type currValue=pointee_->elem_[currindex_];
            while(pointee_->parent_ != nullptr){
                pointee_ = pointee_->parent_;
                for(currindex_=0; currindex_ < pointee_->used; ++currindex_){
                    if(pointee_->elem_[currindex_]> currValue ) {
                        return *this;
                    }
                }
            }
            //the last element of the tree.
            currindex_ = pointee_->used;
            return *this;
        }
    }
    return *this;
}

template<typename T> const_btree_iterator<T>&
const_btree_iterator<T>::operator--() {
    //moving down
    if(pointee_->children_[currindex_] != nullptr){
        pointee_ = pointee_->children_[currindex_];
        while(pointee_->children_[pointee_->used] != nullptr){
            pointee_ = pointee_->children_[pointee_->used];
        }
        currindex_ = pointee_->used-1;
        //can move up or left
    } else if(currindex_ > 0){
        //move left
        --currindex_;
    }else {
        typename btree<T>::Node *child, *parent;
        child=pointee_;
        parent=pointee_->parent_;
        unsigned int pIdx;
        while(parent != nullptr){
            pIdx = getParentIndex(child,parent);
            if(pIdx > 0){
                currindex_ = pIdx-1;
                pointee_=parent;
                return *this;
            }
            child=parent;
            parent=parent->parent_;
        }

        // If we are here, undefined behaviour
        --currindex_;
        return *this;

    }
    return *this;
}

template <typename T> unsigned int
const_btree_iterator<T>::getParentIndex(const typename btree<T>::Node *child,const typename btree<T>::Node* parent ) const{
    return static_cast<unsigned>(std::find_if(parent->children_.begin(),parent->children_.end(),
                                              [child](const typename btree<T>::Node* c){
                                                  return c==child;
                                              })- parent->children_.cbegin());
}

//others
template<typename T> bool
const_btree_iterator<T>::operator ==(const btree_iterator<T>& other) const {

    return (pointee_== other.pointee_ && currindex_==other.currindex_);
}

template<typename T> bool
const_btree_iterator<T>::operator==(const const_btree_iterator<T>& other) const{

    return (pointee_== other.pointee_ && currindex_==other.currindex_);
};

template <typename T> bool
const_btree_iterator<T>::operator!=(const btree_iterator<T>& other) const {
    return !operator==(other);
}

template <typename T> bool
const_btree_iterator<T>::operator!=(const const_btree_iterator<T>& other) const {
    return !operator==(other);
}
#endif
