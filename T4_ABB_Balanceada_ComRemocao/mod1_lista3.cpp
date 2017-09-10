#include "mod1_lista3.h"
#include <iostream>

Avl::Avl()
: _root(nullptr), _cursor(nullptr)
{
    this->_root = nullptr;
    this->_cursor = nullptr;
}


Avl::Avl(const int key)
{
	this->_root = nullptr;
	this->_cursor = nullptr;
	this->insert(key);
}


Avl::Avl(const Avl& orig)
: _root(nullptr), _cursor(nullptr)
{
    this->_root = nullptr;
    this->_cursor = nullptr;
	this->copy_rec(orig._root);
}


Avl::~Avl()
{
	this->delete_rec(this->_root);
}


int Avl::height()
{
    return height_rec(this->_root);
}


void Avl::insert(int key)
{
    this->_root = insert_rec(this->_root, key);
}


void Avl::remove(int key)
{
    AvlNode * originalCursor = this->_cursor;
	
	// Acha o no com a chave recebida (se nao existir, retorna)
    this->first();
    while (key != this->_cursor->_key && this->next());
    if (key != this->_cursor->_key) {
        this->_cursor = originalCursor;
        return;
    }
	AvlNode * nodeToRemove = this->_cursor;
	
	/// Casos de um no a ser removido:
	// 1. Nenhuma sub-arvore
	if (nodeToRemove->_right == nullptr &&
		nodeToRemove->_left == nullptr) {
		if (nodeToRemove->_up != nullptr) {
			if (nodeToRemove->_up->_right != nullptr &&
				key == nodeToRemove->_up->_right->_key)
				nodeToRemove->_up->_right = nullptr;
			else
				nodeToRemove->_up->_left = nullptr;
		}
		else {
			delete nodeToRemove;
			this->_cursor = nullptr;
			this->_root = nullptr;
			return;
		}
		
		this->_cursor = nodeToRemove->_up;
		delete nodeToRemove;
	}
	
	// 2. Uma sub-arvore
    else if (nodeToRemove->_right == nullptr ||
			 nodeToRemove->_left == nullptr) {
		AvlNode * subTreeRoot;
		
		if (nodeToRemove->_right != nullptr)
			subTreeRoot = nodeToRemove->_right;
		else
			subTreeRoot = nodeToRemove->_left;
		
		subTreeRoot->_up = nodeToRemove->_up;
		
		if (nodeToRemove->_up != nullptr) {
			this->_cursor = nodeToRemove->_up;
			
			if (key == this->_cursor->_right->_key)
				this->_cursor->_right = subTreeRoot;
			else
				this->_cursor->_left = subTreeRoot;
		}
		else {
			this->_root = subTreeRoot;
			this->_cursor = subTreeRoot;
		}
		
		delete nodeToRemove;
    }
	
	// 3. Duas sub-arvores
	else {
		this->prev();
		int prevKey = this->_cursor->_key;
		
		this->remove(prevKey);
		
		nodeToRemove->_key = prevKey;
	}
	
	this->_root->_balance_factor = height_rec(this->_root->_right) - height_rec(this->_root->_left);
	this->_root = this->balance(this->_root);
    this->_cursor = originalCursor;
}


void Avl::show(const std::string& title)
{
    std::cout << title << std::endl;
    show_rec(_root);
    std::cout << std::endl;
}


bool Avl::first()
{
    if (this->_root == nullptr) {
        return false;
    }
    
    this->_cursor = this->_root;
    while (this->_cursor->_left != nullptr) {
        this->_cursor = this->_cursor->_left;
    }
    
    return true;
}


bool Avl::last()
{
    if (this->_root == nullptr) {
        return false;
    }
    
    this->_cursor = this->_root;
    while (this->_cursor->_right != nullptr) {
        this->_cursor = this->_cursor->_right;
    }
    
    return true;
}


bool Avl::next()
{
    if (this->_root == nullptr) {
        return false;
	}
	
	AvlNode * cursor = this->_cursor;
	this->last();
	if (cursor->_key == this->_cursor->_key) {
		return false;
	}
	this->_cursor = cursor;
	
    if (this->_cursor->_right != nullptr) {
        this->_cursor = this->_cursor->_right;
        
        while (this->_cursor->_left != nullptr) {
            this->_cursor = this->_cursor->_left;
        }
        
        return true;
    }
    else {
        while (this->_cursor != nullptr) {
            if (this->_cursor->_up != nullptr &&
                this->_cursor->_key < this->_cursor->_up->_key) {
                this->_cursor = this->_cursor->_up;
                return true;
            }
            
            this->_cursor = this->_cursor->_up;
        }
    }
    
    return false;
}


bool Avl::prev()
{
    if (this->_root == nullptr) {
        return false;
    }
	
	AvlNode * cursor = this->_cursor;
	this->first();
	if (cursor->_key == this->_cursor->_key) {
		return false;
	}
	this->_cursor = cursor;
    
    if (this->_cursor->_left != nullptr) {
        this->_cursor = this->_cursor->_left;
        
        while (this->_cursor->_right != nullptr) {
            this->_cursor = this->_cursor->_right;
        }
        
        return true;
    }
	else {
        while (this->_cursor != nullptr) {
            if (this->_cursor->_up != nullptr &&
                this->_cursor->_key > this->_cursor->_up->_key) {
                this->_cursor = this->_cursor->_up;
                return true;
            }
            
            this->_cursor = this->_cursor->_up;
        }
    }
    return false;
}


int Avl::value()
{
    if (this->_root == nullptr) {
        return 0;
    }
    return this->_cursor->_key;
}


void Avl::show_rec(AvlNode* node)
{
    if (node != nullptr)
    {
        std::cout << "<";
        std::cout << node->_key;
        show_rec(node->_left);
        show_rec(node->_right);
        std::cout << ">";
    }
    else
    {
        std::cout << ".";
    }
}


void Avl::copy_rec(AvlNode * root)
{
	if (root == nullptr) {
		return;
	}
	
	this->insert(root->_key);
	this->copy_rec(root->_left);
	this->copy_rec(root->_right);
}


void Avl::delete_rec(AvlNode * root) {
	if (root == nullptr) {
		return;
	}
	
	this->delete_rec(root->_left);
	this->delete_rec(root->_right);
	delete root;
}



int Avl::height_rec(AvlNode * root)
{
    if (root == nullptr) {
        return -1;
    }
    
    if (root->_balance_factor == 1)
        return 1 + height_rec(root->_right);
    else
        return 1 + height_rec(root->_left);
}


AvlNode * Avl::insert_rec(AvlNode * root, int key)
{
    if (root == nullptr)
    {
        root = new AvlNode;
        root->_key = key;
        root->_up = nullptr;
        root->_left = nullptr;
        root->_right = nullptr;
        root->_balance_factor = 0;
		this->_root = root;
        this->_cursor = root;
        return root;
    }
    else if (key < root->_key)
    {
        root->_left = insert_rec(root->_left, key);
        root->_left->_up = root;
    }
    else if (key >= root->_key)
    {
        root->_right = insert_rec(root->_right, key);
        root->_right->_up = root;
    }
	
    root->_balance_factor = height_rec(root->_right) - height_rec(root->_left);
    root = balance(root);
	
    return root;
}


// Funcoes de rotacao e balanceamento
AvlNode * Avl::rr_rotation(AvlNode * root)
{
    AvlNode * up = root->_up;
    AvlNode * newRoot = root->_left;
    AvlNode * right = root->_right;
    
    newRoot->_right = root;
    root->_left = right;
    root->_up = newRoot;
    newRoot->_up = up;
    
    if (right != nullptr)
        right->_up = root;
    
    root->_balance_factor = 0;
    newRoot->_balance_factor = 0;
    
    return newRoot;
}


AvlNode * Avl::ll_rotation(AvlNode * root)
{
    AvlNode * up = root->_up;
    AvlNode * newRoot = root->_right;
    AvlNode * left = newRoot->_left;
    
    newRoot->_left = root;
    root->_right = left;
    root->_up = newRoot;
    newRoot->_up = up;
    
    if (left != nullptr)
        left->_up = root;
    
    root->_balance_factor = 0;
    newRoot->_balance_factor = 0;
    
    return newRoot;
}


AvlNode * Avl::rl_rotation(AvlNode * root)
{
    AvlNode * r_up = root->_up;
    AvlNode * r_right = root->_right;
    AvlNode * r_left = root->_left;
    AvlNode * newRoot = r_right->_left;
    AvlNode * rr_right = r_right->_right;
    AvlNode * nr_left = newRoot->_left;
    AvlNode * nr_right = newRoot->_right;

    root->_up = newRoot;
    root->_left = r_left;
    root->_right = nr_left;
    newRoot->_up = r_up;
    newRoot->_left = root;
    newRoot->_right = r_right;
    r_right->_up = newRoot;
    r_right->_left = nr_right;
    r_right->_right = rr_right;
    
    if (r_up != nullptr) {
        if (r_up->_key < newRoot->_key)
            r_up->_right = newRoot;
        else
            r_up->_left = newRoot;
    }
    
    if (r_left != nullptr)
        r_left->_up = root;
    
    if (nr_left != nullptr)
        nr_left->_up = root;
    
    if (nr_right != nullptr)
        nr_right->_up = r_right;
    
    if (rr_right != nullptr)
        rr_right->_up = r_right;
    
    newRoot->_balance_factor = height_rec(newRoot->_right) - height_rec(newRoot->_left);
    root->_balance_factor = height_rec(root->_right) - height_rec(root->_left);
    r_right->_balance_factor = height_rec(r_right->_right) - height_rec(r_right->_left);
    
    return newRoot;
}


AvlNode * Avl::lr_rotation(AvlNode * root)
{
    AvlNode * r_up = root->_up;
    AvlNode * r_left = root->_left;
    AvlNode * r_right = root->_right;
    AvlNode * rl_left = r_left->_left;
    AvlNode * newRoot = r_left->_right;
    AvlNode * nr_right = newRoot->_right;
    AvlNode * nr_left = newRoot->_left;
    
    root->_up = newRoot;
    root->_right = r_right;
    root->_left = nr_right;
    newRoot->_up = r_up;
    newRoot->_right = root;
    newRoot->_left = r_left;
    r_left->_up = newRoot;
    r_left->_right = nr_left;
    r_left->_left = rl_left;
    
    if (r_up != nullptr) {
        if (r_up->_key < newRoot->_key)
            r_up->_right = newRoot;
        else
            r_up->_left = newRoot;
    }
    
    if (r_right != nullptr)
        r_right->_up = root;
    
    if (nr_right != nullptr)
        nr_right->_up = root;
    
    if (nr_left != nullptr)
        nr_left->_up = r_left;
    
    if (rl_left != nullptr)
        rl_left->_up = r_left;
    
    newRoot->_balance_factor = height_rec(newRoot->_right) - height_rec(newRoot->_left);
    root->_balance_factor = height_rec(root->_right) - height_rec(root->_left);
    r_left->_balance_factor = height_rec(r_left->_right) - height_rec(r_left->_left);
    
    return newRoot;
}


AvlNode * Avl::balance(AvlNode * root)
{
    AvlNode * up = root->_up;
    
    if (root->_balance_factor > 1) {
        if (root->_right->_balance_factor == 1) {
            root = ll_rotation(root);
            
            if (up != nullptr)
                up->_right = root;
        }
        else {
            root = rl_rotation(root);
        }
    }
    else if (root->_balance_factor < -1) {
        if (root->_left->_balance_factor == -1) {
            root = rr_rotation(root);
            
            if (up != nullptr)
                up->_left = root;
        }
        else {
            root = lr_rotation(root);
        }
    }
    
    return root;
}

