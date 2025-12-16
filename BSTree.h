#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

using namespace std;

template <typename T> 
class BSTree{
    private:
        int nelem;
        BSNode<T> *root;

        BSNode<T>* search(BSNode<T>* n, T e) const{
            if(n == nullptr){
                throw runtime_error("El valor especificado no se encuentra");
            }
            else if( e < n->elem){
                return search(n->left, e);
            }
            else if(e > n->elem){
                return search(n->right, e);
            }
            else return n;
        }

        BSNode<T>* insert(BSNode<T>* n, T e){
            if(n == nullptr){
                nelem++;
                return new BSNode(e);
            }                
            if (n->elem == e){
                throw runtime_error("El elemento ya existe");
            }
            else if(e < n->elem){
                n->left = insert(n->left, e);
            }
            else if(e > n->elem){
                n->right = insert(n->right, e);
            }
            
            return n;
        }

        void print_inorder(ostream &out, BSNode<T>* n) const{
            if(n != nullptr){
                print_inorder(out, n->left);
                out << n->elem << " ";
                print_inorder(out, n->right);
            }
        }

        BSNode<T>* remove_max(BSNode<T>* n){
            if (n->right == nullptr){
                return n->left;
            }
            else{
                n->right = remove_max(n->right);
                return n;
            }

        }

         T max(BSNode<T>* n) const{
            if(n == nullptr){
                throw runtime_error("El árbol está vacío");
            }
            else if(n->right != nullptr){
                return max(n->right);
            }
            else{
                return n->elem;
            }
       
        }

        BSNode<T>* remove(BSNode<T>* n, T e){
            if (n == nullptr){
                throw runtime_error("El valor especificado no se encuentra");
            }
            else if(e < n->elem){
                n->left = remove(n->left, e);
            }
            else if (e > n->elem){
                n->right = remove(n->right, e);
            }

        
            else{            
                if (n->left != nullptr && n->right != nullptr){ 
                    n->elem = max(n->left);
                    n->left = remove_max(n->left);                
                    nelem--;
                    return n;
                }
                else if(n->left != nullptr){               
                    BSNode<T>* sustituto = n->left;         
                    delete n;                            
                    nelem--;
                    return sustituto;                       
                }
                else if(n->right != nullptr){               
                    BSNode<T>* sustituto = n->right;   
                    delete n;
                    nelem--;
                    return sustituto;
                }
                else{
                    delete n;                            
                    nelem--;
                    return nullptr;                        
                }
            }
            return n;
        }

        
        void delete_cascade(BSNode<T>* n) {
        if (n != nullptr) {
            delete_cascade(n->left);
            delete_cascade(n->right);
            delete n;
        }
    }
 
    public:
        BSTree(): root(nullptr), nelem(0) {};
        	
        ~BSTree(){
            delete_cascade(root);
        } 
        int size() const{
            return nelem;
        }
        
        T search(T e) const{
            BSNode<T>* encontrado = search(root, e);
            return encontrado->elem; 
        }

        T operator[](T e) const{
            return search(e);
        }

        void insert(T e){
            root = insert(root, e);
        }

        friend ostream& operator<<(ostream &out, 
        const BSTree<T> &bst){
            bst.print_inorder(out, bst.root);
            return out;
        }

        void remove(T e){
            root = remove(root, e);
        }


    
};

#endif


