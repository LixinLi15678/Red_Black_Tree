#include "RedBlackTree.h"

RedBlackTree::RedBlackTree(const RedBlackTree &other) {
    if (other.root == nullptr) {
        return;
    } 
    RBTNode *troot = new RBTNode();
    troot->data = other.root->data;
    troot->color = other.root->color;
    this->root = troot;
    copyTree(troot, other.root);
}

RedBlackTree::~RedBlackTree() {
    deleteTree(this->root);
}

void RedBlackTree::copyTree(RBTNode *orinode, RBTNode *node) {
    if (node == nullptr) {
        return;
    }

    if (node->left != nullptr) {
        RBTNode *left = new RBTNode();
        orinode->left = left;
        left->parent = orinode;
        left->data = node->left->data;
        left->color = node->left->color;
        copyTree(orinode->left, node->left);
    }

    if (node->right != nullptr) {
        RBTNode *right = new RBTNode();
        orinode->right = right;
        right->parent = orinode;
        right->data = node->right->data;
        right->color = node->right->color;
        copyTree(orinode->right, node->right);
    }
}

void RedBlackTree::deleteTree(RBTNode *curr) {
    if(curr == nullptr) {
        return;
    } 
    deleteTree(curr->left);
    deleteTree(curr->right);
    delete curr;
}

// Time Complexity: O(log n), took 1e-06 seconds for each.
void RedBlackTree::Insert(int value) {
    if (this->Contains(value)) {
        throw invalid_argument("Value already exists in the tree");
    }

    this->values.push_back(value);

    RBTNode *newNode = new RBTNode();
    newNode->data = value;
    newNode->color = COLOR_RED;

    // The tree is empty
    if (this->root == nullptr) {
        this->root = newNode;
        this->root->color = COLOR_BLACK;
        this->numItems++;
    } else {
		RBTNode *current = this->root;
		RBTNode *parent = nullptr;

		// find the place to insert
		while (current != nullptr) {
			parent = current;
			if (value < current->data) {
				current = current->left;
			} else {
				current = current->right;
			}
		}

        // insert the new node
		newNode->parent = parent;
		if (value < parent->data) {
			parent->left = newNode;
		} else {
			parent->right = newNode;
		}

		this->numItems++;
		this->InsertFixup(newNode);
	}
}

// Time Complexity: O(log n), took 3e-06 seconds for each.
void RedBlackTree::Remove(int value) {
    // If the tree is empty, throw an exception
    if (this->root == nullptr) {
        throw invalid_argument("The tree is empty");
    }

    // If the value is not in the tree, throw an exception
    if (!this->Contains(value)) {
        throw invalid_argument("The value is not in the tree");
    }

    // Find the node to delete
    RBTNode *current = this->root;
    while (current != nullptr) {
        if (value == current->data) {
            break;
        } else if (value < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    unsigned short int oricolor = current->color;
    RBTNode *fix = nullptr;
    RBTNode *delTemp = nullptr;

    // If the node to delete has no children
    if (current->left == nullptr && current->right == nullptr) {
        // if the node is the root
        if (current == this->root) {
            this->root = nullptr;
        } else {
            // if the node is left child
            if (current == current->parent->left) {
                current->parent->left = nullptr;
            // if the node is right child
            } else {
                current->parent->right = nullptr;
            }
        }
    
    // If the node to delete has one child
    } else if (current->left == nullptr || current->right == nullptr) { 
        // if the node is left child
        if (current->left != nullptr) {
            fix = current->left;
        // if the node is right child
        } else {
            fix = current->right;
        }
        // if the node is the root
        if (current == this->root) {
            this->root = fix;
            fix->parent = nullptr;
        } else {
            fix->parent = current->parent;
            // if the node is left child
            if (current == current->parent->left) {
                current->parent->left = fix;
            // if the node is right child
            } else {
                current->parent->right = fix;
            }
        }

    // If the node to delete has two children
    } else { 
        delTemp = this->getSuccessor(current);
        oricolor = delTemp->color;
        fix = delTemp->right;
        // if the successor is the right child of the node to delete
        if (delTemp->parent == current) {
            // if the successor has a right child
            if (fix != nullptr) {
                fix->parent = delTemp;
            }
        // if the successor is not the child of the node to delete
        } else {
            if (fix != nullptr) {
                fix->parent = delTemp->parent;
            }
            // link the right child of the successor to successor's position
            delTemp->parent->left = fix;
            delTemp->right = current->right;
            current->right->parent = delTemp;
        }

        // if the node is the root
        if (current == this->root) {
            this->root = delTemp;
        } else {
            // if the node is left child
            if (current == current->parent->left) {
                current->parent->left = delTemp;
            // if the node is right child
            } else {
                current->parent->right = delTemp;
            }
        }
        // link
        delTemp->parent = current->parent;
        delTemp->left = current->left;
        current->left->parent = delTemp;
        delTemp->color = current->color;
        
    }

    delete current;
    this->numItems--;

    // we don't need to fix the tree if the color is red
    if (oricolor == COLOR_BLACK) {
        this->RemoveFixup(fix);
    }
}

bool RedBlackTree::Contains(int value) {

    RBTNode *current = this->root;
    while (current != nullptr) {
        if (value == current->data) {
            return true;
        } else if (value < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return false;
}

int RedBlackTree::GetMin() {

    if (this->root == nullptr) {
        throw invalid_argument("Tree is empty");
    }

    int min = this->root->data;
    RBTNode *current = this->root;

    while (current != nullptr) {
        min = current->data;
        if (current->left != nullptr) {
            current = current->left;
        }
        else {
            break;
        }
    }
    return min;
}

int RedBlackTree::GetMax() {
    if (this->root == nullptr) {
        throw invalid_argument("Tree is empty");
    }

    int max = this->root->data;
    RBTNode *current = this->root;

    while (current != nullptr) {
        max = current->data;
        if (current->right != nullptr) {
            current = current->right;
        }
        else {
            break;
        }
    }
    return max;
}

int RedBlackTree::Size() {
    return this->numItems;
}

// Time Complexity: O(log n)
void RedBlackTree::InsertFixup(RBTNode *node) {

    while (node->parent != nullptr && node->parent->color == COLOR_RED) {
        // parent is left child
        if (node->parent == node->parent->parent->left) {
            RBTNode *uncle = node->parent->parent->right;
            // 1. uncle is red, color parent and uncle black, color grandparent red
            if (uncle != nullptr && uncle->color == COLOR_RED) {
                node->parent->color = COLOR_BLACK;
                uncle->color = COLOR_BLACK;
                node->parent->parent->color = COLOR_RED;
                node = node->parent->parent;
                
            // uncle is black
            } else {
                // 2. node is right child, rotate left
                if (node == node->parent->right) {
                    node = node->parent;
                    this->RotateLeft(node);
                }
                // 3. node is left child, color parent black, color grandparent red, rotate right
                node->parent->color = COLOR_BLACK;
                node->parent->parent->color = COLOR_RED;
                this->RotateRight(node->parent->parent);
            }
        // parent is right child
        } else {
            RBTNode *uncle = node->parent->parent->left;
            // 4. uncle is red, color parent and uncle black, color grandparent red
            if (uncle != nullptr && uncle->color == COLOR_RED) {
                node->parent->color = COLOR_BLACK;
                uncle->color = COLOR_BLACK;
                node->parent->parent->color = COLOR_RED;
                node = node->parent->parent;
            // uncle is black
            } else {
                // 5. node is left child, rotate right
                if (node == node->parent->left) {
                    node = node->parent;
                    this->RotateRight(node);
                }
                // 6. node is right child, color parent black, color grandparent red, rotate left
                node->parent->color = COLOR_BLACK;
                node->parent->parent->color = COLOR_RED;
                this->RotateLeft(node->parent->parent);
            }
        }
    }
    this->root->color = COLOR_BLACK;
}

RBTNode* RedBlackTree::getSuccessor(RBTNode *node){
    RBTNode *current = node->right;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

void RedBlackTree::RemoveFixup(RBTNode *node) {
    if (node == nullptr) {
        return;
    }
    while (node != this->root && node->color == COLOR_BLACK) {
        if (node == node->parent->left) {
            RBTNode *sibling = node->parent->right;
            // 1. sibling is red, color sibling black, color parent red, rotate left
            if (sibling->color == COLOR_RED) {
                sibling->color = COLOR_BLACK;
                node->parent->color = COLOR_RED;
                this->RotateLeft(node->parent);
                sibling = node->parent->right;
            }
            // 2. sibling is black, both children are black, color sibling red, move up
            if (sibling->left->color == COLOR_BLACK && sibling->right->color == COLOR_BLACK) {
                sibling->color = COLOR_RED;
                node = node->parent;
            } else {
                // 3. sibling is black, left child is red, right child is black, color left child black, color sibling red, rotate right
                if (sibling->right->color == COLOR_BLACK) {
                    sibling->left->color = COLOR_BLACK;
                    sibling->color = COLOR_RED;
                    this->RotateRight(sibling);
                    sibling = node->parent->right;
                }
                // 4. sibling is black, right child is red, color sibling same as parent, color parent black, color right child black, rotate left
                sibling->color = node->parent->color;
                node->parent->color = COLOR_BLACK;
                sibling->right->color = COLOR_BLACK;
                this->RotateLeft(node->parent);
                node = this->root;
            }
        // node is right child
        } else {
            RBTNode *sibling = node->parent->left;
            // 5. sibling is red, color sibling black, color parent red, rotate right
            if (sibling->color == COLOR_RED) {
                sibling->color = COLOR_BLACK;
                node->parent->color = COLOR_RED;
                this->RotateRight(node->parent);
                sibling = node->parent->left;
            }
            // 6. sibling is black, both children are black, color sibling red, move up
            if (sibling->left->color == COLOR_BLACK && sibling->right->color == COLOR_BLACK) {
                sibling->color = COLOR_RED;
                node = node->parent;
            } else {
                // 7. sibling is black, right child is red, left child is black, color right child black, color sibling red, rotate left
                if (sibling->left->color == COLOR_BLACK) {
                    sibling->right->color = COLOR_BLACK;
                    sibling->color = COLOR_RED;
                    this->RotateLeft(sibling);
                    sibling = node->parent->left;
                }
                // 8. sibling is black, left child is red, color sibling same as parent, color parent black, color left child black, rotate right
                sibling->color = node->parent->color;
                node->parent->color = COLOR_BLACK;
                sibling->left->color = COLOR_BLACK;
                this->RotateRight(node->parent);
                node = this->root;
            }
        }
    }
    node->color = COLOR_BLACK;
}       

// Time complexity: O(1)
void RedBlackTree::RotateLeft(RBTNode *node) {
    RBTNode *right = node->right; // set right node
    node->right = right->left; // set right's left subtree to node's right subtree

    // set right's left subtree's parent to node
    if (right->left != nullptr) {
        right->left->parent = node;
    }
    right->parent = node->parent;
    // if node is root, set right to root
    if (node->parent == nullptr) {
        this->root = right;
    // if node is left child, set right to left child
    } else if (node == node->parent->left) {
        node->parent->left = right;
    } else {
        node->parent->right = right; // put node on right's right
    }
    // put node on right's left
    right->left = node;
    node->parent = right;
}

// Time complexity: O(1)
void RedBlackTree::RotateRight(RBTNode *node) {
    // same as RotateLeft, change "left" to "right" and "right" to "left"
    RBTNode *left = node->left;
    node->left = left->right;
    if (left->right != nullptr) {
        left->right->parent = node;
    }
    left->parent = node->parent;
    if (node->parent == nullptr) {
        this->root = left;
    } else if (node == node->parent->right) {
        node->parent->right = left;
    } else {
        node->parent->left = left;
    }
    left->right = node;
    node->parent = left;
}

string RedBlackTree::ToPrefixString(RBTNode *node) const {
    string prefix = "";

    if (node != nullptr) {
        if (node->color == COLOR_RED) {
            prefix += " R";
        } else {
            prefix += " B";
        }
        prefix += to_string(node->data) + " ";
        prefix += ToPrefixString(node->left);
        prefix += ToPrefixString(node->right);
    }

    return prefix;
}

string RedBlackTree::ToInfixString(RBTNode *node) const {
    string infix = "";

    if (node != nullptr) {
        infix += ToInfixString(node->left);
        if (node->color == COLOR_RED) {
            infix += " R";
        } else {
            infix += " B";
        }
        infix += to_string(node->data) + " ";
        infix += ToInfixString(node->right);
    }

    return infix;
}

string RedBlackTree::ToPostfixString(RBTNode *node) const {
    string postfix = "";

    if (node != nullptr) {
        postfix += ToPostfixString(node->left);
        postfix += ToPostfixString(node->right);
        if (node->color == COLOR_RED) {
            postfix += " R";
        } else {
            postfix += " B";
        }
        postfix += to_string(node->data) + " ";
    }

    return postfix;
}
