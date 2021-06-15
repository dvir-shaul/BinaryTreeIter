#pragma once
#include <queue>
#include <iostream>

using namespace std; 

namespace ariel {

    template<typename T>
    class BinaryTree{
        
        private:
            struct Node{
                T value;
                Node *left, *right;
                
                Node(T val) : value(val), left(nullptr), right(nullptr) {}

                ~Node(){
                    delete left;
                    delete right;
                }

                Node(Node&& other) noexcept{
                    value = other.value;
                    other.value = nullptr;

                    left = other.left;
                    other.left = nullptr; 
    
                    right = other.right;
                    other.right = nullptr; 
                }

                Node(Node& other) : value(other.value){
                    if(other.left != nullptr){left = new Node(*other.left);}
                    else{left = nullptr;}

                    if(other.right != nullptr){right = new Node(*other.right);}
                    else{right = nullptr;}
                }

                Node& operator=(Node other) {
                    if(this==other){return *this;}
                    delete right;
                    delete left;

                    if(left){left=new Node(*other.left);}
                    else{left=nullptr;}

                    if(right){right=new Node(*other.right);}
                    else{right=nullptr;}

                    return *this;                  
                }

                Node& operator=(Node&& other) noexcept{

                    if(left){delete left;}
                    if(right){delete right;}

                    left=other.left;
                    right=other.right;
                    value=other.value;

                    other.left=nullptr;
                    other.right=nullptr;

                    return *this;
                }
            };
        Node *root;
        
        public:
            BinaryTree(){root = nullptr;}

             BinaryTree(BinaryTree& other){
                    if(root != nullptr){root = new Node(*other.root);}
                    else{root = nullptr;}
                }

            BinaryTree(BinaryTree&& other) noexcept{
                root  = other.root;
                other.root = nullptr;
            }

            ~BinaryTree(){if(root!=nullptr){delete root;}}

            BinaryTree &add_root(T val){
                if(root != nullptr){
                    root->value = val;
                    return *this;
                }
                root = new Node(val);
                return *this;
                
            }

            Node *isNull(T val) {
                Node *current = nullptr;
                for (auto it = begin(); it != end(); ++it) {
                    if ((*it) == val) {
                        current = it.node;
                        break;
                    }
                }
                return current;
            }

            BinaryTree &add_left(T father, T son){
                if(root == nullptr){throw invalid_argument("root is null");}
                Node *n = isNull(father);
                if (n == nullptr) {throw invalid_argument("add left");}
                if (n->left != nullptr) {
                    n->left->value = son;
                } else {
                    n->left = new Node(son);
                }
                return *this;
            }

            BinaryTree &add_right(T father, T son){
                if(root == nullptr){throw invalid_argument("root is null");}
                Node *n = isNull(father);
                if (n == nullptr) {
                    throw invalid_argument("add right");
                }
                if (n->right != nullptr) {
                    n->right->value = son;
                } else {
                    Node *no = new Node(son);
                    n->right = no;
                }
                return *this;
            }

            BinaryTree& operator=(const BinaryTree other) {
                if (root) {delete root;}
                root  = new Node(*other.root);
                return *this;
            }
            
            BinaryTree& operator=(BinaryTree && other)noexcept {
                if (root) {delete root;}
                root  = other.root;
                other.root = nullptr;
                return *this;
            }

            friend ostream& operator<<(ostream& os, const BinaryTree<T>& t) {
                os << "hey";
                return os;
            }

            class Iterator{

                public:
                    Node *node;

                    queue<Node*> q;

                    void initQueue0(Node* root1){ //Preorder
                        if(root1 != nullptr){
                            q.push(root1);
                            initQueue0(root1->left);
                            initQueue0(root1->right);
                        }
                    }

                    void initQueue1(Node* root1){ //Inorder  
                        if(root1 != nullptr){ 
                            initQueue1(root1->left);
                            q.push(root1);
                            initQueue1(root1->right);
                        }
                    }

                    void initQueue2(Node* root1){
                        if(root1 != nullptr){ //Postorder
                            initQueue2(root1->left);
                            initQueue2(root1->right);
                            q.push(root1);
                        }
                    }    
                    Iterator(Node* ptr = nullptr): node(ptr){} //Default constructor

                    Iterator(Node* ptr, int n): node(ptr){ //Constructor
                        if(n == 0){ //Preorder case
                            initQueue0(ptr);
                            q.push(nullptr);

                            node = q.front();
                            q.pop();
                        }

                        if(n == 1){ //Inorder case
                            initQueue1(ptr);
                            q.push(nullptr);
                            node = q.front();
                            q.pop();
                        }

                        if(n == 2){ //Postorder case
                            initQueue2(ptr);
                            q.push(nullptr);
                            node = q.front();
                            q.pop();
                        }
                    }      
            
                    T& operator*() const{
                        return node->value;
                    }

                    T* operator->() const{
                        return &(node->value);
                    }
                    
                    Iterator& operator++(){
                        if(!q.empty()){
                            this->node = this->q.front();
                            this->q.pop();
                        }
                        return *this;
                    }

                    Iterator operator++(int){
                        Iterator it = *this;
                        this->node = this->q.front();
                        this->q.pop();
                        return it;
                    }

                    bool operator==(const Iterator& p) const{return node == p.node;}
                    
                    bool operator!=(const Iterator& p) const{return node != p.node;}

                    Node *get_node() { return node; }


            };

            Iterator begin_preorder(){return Iterator{root, 0};}

            Iterator end_preorder(){return Iterator{};} 

            Iterator begin_inorder(){return Iterator{root, 1};}

            Iterator end_inorder(){return Iterator{};}

            Iterator begin_postorder(){return Iterator{root, 2};}

            Iterator end_postorder(){return Iterator{};}

            Iterator begin(){return Iterator{root, 1};}
			
            Iterator end(){return Iterator{};}

    };
};