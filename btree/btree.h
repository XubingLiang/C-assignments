/**
 * The btree is a linked structure which operates much like
 * a binary search tree, save the fact that multiple client
 * elements are stored in a single node.  Whereas a single element
 * would partition the tree into two ordered subtrees, a node 
 * that stores m client elements partition the tree 
 * into m + 1 sorted subtrees.
 */

#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <cstddef>
#include <utility>
#include <map>
#include <vector>
#include <queue>


// we better include the iterator
#include "btree_iterator.h"

template<typename T> class btree;

template<typename T>
std::ostream& operator<<(std::ostream& os, const btree<T>& t);

template <typename T> 
class btree {
 public:
    friend class btree_iterator<T>;
    friend class const_btree_iterator<T>;

    typedef btree_iterator<T> iterator;
    typedef const_btree_iterator<T> const_iterator;

    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
//

  btree(size_t maxNodeElems = 40): maxNodeElem_{maxNodeElems}{
      root_ = new Node(nullptr, maxNodeElem_);
  }

  btree(const btree<T>& original);

  btree(btree<T>&& original);

  btree<T>& operator=(const btree<T>& rhs);


  btree<T>& operator=(btree<T>&& rhs);


  friend std::ostream& operator<< <T> (std::ostream& os, const btree<T>& tree);

  /**
   * The following can go here
   * -- begin() 
   * -- end() 
   * -- rbegin() 
   * -- rend() 
   * -- cbegin() 
   * -- cend() 
   * -- crbegin() 
   * -- crend() 
   */
    iterator begin();
    iterator end();
    iterator begin() const;
    iterator end() const;
    reverse_iterator rbegin();
    reverse_iterator rend();

    const_iterator cbegin() const;
    const_iterator cend() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;

    iterator find(const T& elem);

    const_iterator find(const T& elem) const;


  std::pair<iterator, bool> insert(const T& elem);

  ~btree();


private:
    struct Node {
        Node(Node* parent= nullptr, size_t maxNodeElems=40):
                parent_{parent},
                elem_(maxNodeElems),
                children_{maxNodeElems+1, nullptr},
                used{0} {};

        ~Node() {
            for(unsigned int i =0; i< children_.size();++i){
                if(children_[i] != nullptr){
                    delete children_[i];
                }
            }
        } ;



        Node(Node *parent,Node *from) : children_(from->children_.size(), nullptr){
            parent_ = parent;
            used = from->used;
            elem_= from->elem_;
            for(unsigned int i =0; i< from->children_.size();++i){
                if(from->children_[i] != nullptr){
                    children_[i] = new Node(this, from->children_[i]);
                }
            }
        }

        Node* parent_;
        std::vector<T> elem_;
        std::vector<Node*> children_;
        unsigned int used;
    };

    typename std::pair<iterator,bool> doInsert(const T& elem, Node* n);

    Node* root_;
    size_t maxNodeElem_;
};

//copy constructor
template <typename T>
btree<T>::btree(const btree<T>& original):maxNodeElem_{original.maxNodeElem_}{
    root_ = new Node(nullptr, original.root_);
}

//move construtor
template <typename T>
btree<T>::btree(btree<T>&& original):root_(original.root_),maxNodeElem_(std::move(original.maxNodeElem_)){
    if (this != &original)
        original.root_ = nullptr;
}

//copy assignment
template <typename T> btree<T>&
btree<T>::operator=(const btree<T>& rhs){
    if(this != &rhs){
        delete root_;
        maxNodeElem_ = rhs.maxNodeElem_;
        root_=new Node(nullptr,rhs.root_);
    }
    return *this;

}

//move assignment
template <typename T> btree<T>&
btree<T>::operator=(btree<T>&& rhs){
    if(this != &rhs){
        delete root_;
        root_ = rhs.root_;
        maxNodeElem_= std::move(rhs.maxNodeElem_);
        rhs.root_= nullptr;
        rhs.maxNodeElem_=0;
    }
    return *this;
}
//ostream
template <typename T> std::ostream&
operator<< (std::ostream& os, const btree<T>& tree){
    std::queue<typename btree<T>::Node*> temp;
    temp.push(tree.root_);
    typename btree<T>::Node* tem_node;
    while(!temp.empty()){
        tem_node = temp.front();
        temp.pop();
        for(unsigned int i = 0; i < tem_node->used;++i){
            os << tem_node->elem_[i] << " ";
        }
        for(unsigned int i =0; i< tem_node->children_.size();++i){
            if(tem_node->children_[i]!= nullptr){
                temp.push(tem_node->children_[i]);
            }
        }
    }
    return os;
}



//find function
template <typename T> typename btree<T>::iterator
btree<T>::find(const T& elem) {
    if(root_ ->used == 0 ) return end();
    Node *temp = root_;
    while(true){
        auto node_itr= std::lower_bound(temp->elem_.begin(),temp->elem_.begin()+temp->used,elem);
        unsigned index= static_cast<unsigned> (std::distance(temp->elem_.begin(),node_itr));
        if(temp->elem_[index] == elem && index < temp->used){
            return iterator(temp, index);
        }

        if(temp->children_[index]== nullptr){
            return end();
        }
        temp=temp->children_[index];
    }
}

template <typename T> typename btree<T>::const_iterator
btree<T>::find(const T& elem) const {
    if(root_ ->used ==0 ) return cend();
    Node *temp = root_;
    while(true){
        auto node_itr= std::lower_bound(temp->elem_.begin(),temp->elem_.begin()+temp->used,elem);
        unsigned index= static_cast<unsigned> (std::distance(temp->elem_.begin(),node_itr));;
        if(temp->elem_[index] == elem && index < temp->used){
            return const_iterator(temp, index);
        }

        if(temp->children_[index]== nullptr){
            return cend();
        }
        temp=temp->children_[index];
    }
};

template <typename T> std::pair<typename btree<T>::iterator, bool>
btree<T>::insert(const T& elem){
    Node *temp = root_;
    if(temp->used == 0 ){
        temp->elem_[0]=elem;
        ++(temp->used);
        return std::pair<iterator,bool>{iterator{temp,0},true};
    }
    while(true){
        auto node_itr= std::lower_bound(temp->elem_.begin(),temp->elem_.begin()+temp->used,elem);
        unsigned index= static_cast<unsigned> (std::distance(temp->elem_.begin(),node_itr));;
        if(temp->elem_[index] == elem ){
            return std::pair<iterator,bool>{iterator{temp,index},false};
        }
        if(temp ->used < maxNodeElem_){
            temp->elem_.insert(temp->elem_.begin()+index,elem);
            ++(temp->used);
            temp->elem_.pop_back();
            return std::pair<iterator,bool>{iterator{temp,index},true};
        }

        if(temp->children_[index] == nullptr){
            temp->children_[index] = new Node(temp,maxNodeElem_);
        }
        temp = temp->children_[index];
    }

};


//descructor
template <typename T>
btree<T>::~btree(){
    delete root_;
}


///////iterator function
//iterator function
template <typename T> typename btree<T>::iterator
btree<T>::begin() const {
    using namespace std;
    if(root_->used == 0 ){
        return iterator(nullptr,0);
    }
    Node *temp = root_;
    while( temp->children_[0] != nullptr){
        temp= temp->children_[0];
    }
    return iterator(temp,0);
}

template <typename T> typename btree<T>::iterator
btree<T>::end() const{
    return iterator(root_,root_->used);
}

template <typename T> typename btree<T>::iterator
btree<T>::begin() {
    using namespace std;
    if(root_->used == 0 ){
        return iterator(nullptr,0);
    }
    Node *temp = root_;
    while( temp->children_[0] != nullptr){
        temp= temp->children_[0];
    }
    return iterator(temp,0);
}

template <typename T> typename btree<T>::iterator
btree<T>::end(){
    return iterator(root_,root_->used);
}

template <typename T> typename btree<T>::reverse_iterator
btree<T>::rbegin()  {
    return reverse_iterator(end());
}

template <typename T> typename btree<T>::reverse_iterator
btree<T>::rend() {
    return reverse_iterator(begin());
}

template <typename T> typename btree<T>::const_iterator
btree<T>::cbegin() const {
    if(root_->used == 0 ){
        return const_iterator(nullptr,0);
    }
    Node *temp = root_;
    while( temp->children_[0] != nullptr){
        temp= temp->children_[0];
    }
    return const_iterator(temp,0);
}

template <typename T> typename btree<T>::const_iterator
btree<T>::cend() const {
    return const_iterator(root_,root_->used);
}

template <typename T> typename btree<T>::const_reverse_iterator
btree<T>::crbegin() const {
    return const_reverse_iterator(cend());
}

template <typename T> typename btree<T>::const_reverse_iterator
btree<T>::crend() const {
    return const_reverse_iterator(cbegin());
}



#endif
