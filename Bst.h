/***
@author Thien Twee Zian
@since 30/07/2023
@version 1.01
Template BST class
*/

#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED
#include <iostream>
#include <vector>

using namespace std;

/**
This struct is used to contain the information to be stored in the BST as a node,
together with a pointer to the left and right child node respectively.
*/
template<class T>
struct Node
{
    /**
    Contains the object to be stored inside the BST in the node
    */
    T info;

    /**
    Pointer to the left child node
    */
    Node<T> *left;

    /**
    Pointer to the right child node
    */
    Node<T> *right;
};


/**
This class is a template BST class to be used with other projects
*/
template<class T>
class Bst
{
public:
    /**
    Default constructor to initialize a BST
    */
    Bst();   //constructor

    /**
    Default deconstructor to delete the BST, destroying the information stored within
    and changing the parent and child node pointers to nullptr.
    */
    ~Bst();  //deconstructor

    /**
    Constructor to initialize using another BST
    @param otherTree - BST to be used for initialization
    */
    Bst(const Bst& otherTree); //copy constructor

    /**
    Overloaded = operator used for deep copying
    @param otherTree - BST to be used for copying
    */
    const Bst& operator= (const Bst& otherTree); //deep copy

    /**
    Method used to access the nodes in the BST in the InorderTraversal manner.
    By default, it would print out the contents stored in the node.
    */
    void InorderTraversal() const;

    /**
    Method used to access the nodes in the BST in the PreorderTraversal manner.
    By default, it would print out the contents stored in the node.
    */
    void PreorderTraversal() const;

    /**
    Method used to access the nodes in the BST in the PostorderTraversal manner.
    By default, it would print out the contents stored in the node.
    */
    void PostorderTraversal() const;

    /**
    Method used to insert an item into the BST. Would ensure the BST remains sorted
    by comparing the item with nodes, traversing left if its smaller or right if its
    bigger. Will store once it reaches an empty node. Duplicate items will not be
    inserted.
    @param insertItem - Item to be inserted
    */
    void Insert(const T& insertItem);

    /**
    Method used to check if item exist in BST
    @param searchItem - Item to be searched in the BST
    @return bool - True if item exist, false otherwise
    */
    bool Search(const T& searchItem) const;

    /**
    Method used to delete item in the BST.
    @param deleteItem - Item to be deleted.
    */
    void DeleteNode(const T& deleteItem);

    /**
    Method to clear all contents from the BST.
    */
    void DeleteTree();

    /**
    Method used to check if BST is empty.
    @return bool - True if empty, false otherwise
    */
    bool IsEmpty() const;

    /**
    Method to return the size of the BST (Number of nodes)
    @return size - Size of BST
    */
    int TreeNodeCount();

    /**
    Method used to get an item with key. Item will be returned by reference.
    @return bool - True if item found and returned, false otherwise
    */
    bool Get(T& searchItem);

    /**
    Method to get item stored in root. Item will be returned by reference.
    @param element - Item for root node item to be stored in
    */
    void GetRootElement(T& element);

    //Overloaded methods for passing functions
    /**
    Overloaded InorderTraversal method for passing in functions as parameters.
    @param *visit - Pointer to function to be passed in
    */
    void InorderTraversal(void (*visit) (T&)) const;

    /**
    Overloaded PreorderTraversal method for passing in functions as parameters.
    @param *visit - Pointer to function to be passed in
    */
    void PreorderTraversal(void (*visit) (T&)) const;

    /**
    Overloaded PostorderTraversal method for passing in functions as parameters.
    @param *visit - Pointer to function to be passed in
    */
    void PostorderTraversal(void (*visit) (T&)) const;

    /**
    Overloaded InorderTraversal method for passing in functions as parameters.
    Takes in an additional element to store calculations (float type) done.
    @param *visit - Pointer to function to be passed in
    @param element - Used to store data after running function
    */
    template <class K>
    void InorderTraversal(void (*visit) (T&,K&), K& element) const;

private:
    /**
    Pointer to the root node
    */
    Node<T> *m_root;

    /**
    Method used to copy BST from another BST.
    To be used with deep copy constructor and overloaded = function
    @param copiedTreeRoot - Original BST to be copied into
    @param otherTreeRoot - BST to copy from
    */
    void CopyTree(Node<T>* &copiedTreeRoot, Node<T>* otherTreeRoot);

    /**
    Method used to delete all contents in the node and down the tree, with
    the node as parent. To be used with other methods.
    @param p - Pointer to node to be deleted
    */
    void Destroy(Node<T>* &p);

    /**
    Method to delete node from BST.
    @param p - Pointer to node to be deleted
    */
    void DeleteFromTree(Node<T>* &p);

    /**
    Method used to count and get size of BST. To be used with TreeNodeCount().
    @param p - Pointer to node
    @param counter - To store counted node and return size
    */
    int NodeCount(Node<T> *p, int &counter) const;

    /**
    Method used to access the nodes in the BST in the Inorder manner.
    By default, it would print out the contents stored in the node.
    To be used with InorderTraversal().
    */
    void Inorder(Node<T> *p) const;

    /**
    Method used to access the nodes in the BST in the Preorder manner.
    By default, it would print out the contents stored in the node.
    To be used with PreorderTraversal().
    */
    void Preorder(Node<T> *p) const;

    /**
    Method used to access the nodes in the BST in the Postorder manner.
    By default, it would print out the contents stored in the node.
    To be used with PostorderTraversal().
    */
    void Postorder(Node<T> *p) const;

    //Overloaded methods for passing functions
    /**
    Overloaded Inorder method for passing in functions as parameters.
    To be used with InorderTraversal method.
    @param *visit - Pointer to function to be passed in
    */
    void Inorder(Node<T> *p,void (*visit) (T&)) const;

    /**
    Overloaded Preorder method for passing in functions as parameters.
    To be used with PreorderTraversal method.
    @param *visit - Pointer to function to be passed in
    */
    void Preorder(Node<T> *p,void (*visit) (T&)) const;

    /**
    Overloaded Postorder method for passing in functions as parameters.
    To be used with PostorderTraversal method.
    @param *visit - Pointer to function to be passed in
    */
    void Postorder(Node<T> *p,void (*visit) (T&)) const;

    /**
    Overloaded Inorder method for passing in functions as parameters.
    Takes in an additional element to store calculations (float type) done.
    To be used with InorderTraversal method.
    @param *visit - Pointer to function to be passed in
    @param element - Used to store data after running function
    */
    template <class K>
    void Inorder(Node<T> *p, void (*visit) (T&,K&), K& element) const;
};

template<class T>
Bst<T>::Bst()
{
    m_root = nullptr;
}

template<class T>
Bst<T>::~Bst()
{
    Destroy(m_root);
}

template<class T>
void Bst<T>::CopyTree(Node<T>* &copiedTreeRoot, Node<T>* otherTreeRoot)
{
    if (otherTreeRoot == nullptr)
        copiedTreeRoot = nullptr;
    else
    {
        copiedTreeRoot = new Node<T>;
        copiedTreeRoot->info = otherTreeRoot->info;
        CopyTree(copiedTreeRoot->left, otherTreeRoot->left);
        CopyTree(copiedTreeRoot->right, otherTreeRoot->right);
    }
}

template<class T>
void Bst<T>::Destroy(Node<T>* &p)
{
    if (p != nullptr)
    {
        Destroy(p->left);
        Destroy(p->right);
        delete p;
        p = nullptr;
    }
}

template<class T>
Bst<T>::Bst(const Bst& otherTree)
{
    if (otherTree.m_root == nullptr) //otherTree is empty
        m_root = nullptr;
    else
        CopyTree(m_root, otherTree.m_root);
}

template<class T>
const Bst<T>& Bst<T>:: operator= (const Bst& otherTree)
{
    if (this != &otherTree) //avoid self-copy
    {
        if (m_root != nullptr) //if the binary tree is not empty, destroy the binary tree
        {
            Destroy(m_root);
        }
        if (otherTree.m_root == nullptr) //otherTree is empty
        {
            m_root = nullptr;
        }

        else
            CopyTree(m_root, otherTree.m_root);
    }
    return *this;
}

template<class T>
void Bst<T>::InorderTraversal() const
{
    Inorder(m_root);
}

template<class T>
void Bst<T>::PreorderTraversal() const
{
    Preorder(m_root);
}

template<class T>
void Bst<T>::PostorderTraversal() const
{
    Postorder(m_root);
}

template<class T>
void Bst<T>::Inorder(Node<T> *p) const
{
    if (p != nullptr)
    {
        Inorder(p->left);
        cout << p->info << endl;
        Inorder(p->right);
    }
}

template<class T>
void Bst<T>::Preorder(Node<T> *p) const
{
    if (p != nullptr)
    {
        cout << p->info << endl;
        Preorder(p->left);
        Preorder(p->right);
    }
}

template<class T>
void Bst<T>::Postorder(Node<T> *p) const
{
    if (p != nullptr)
    {
        Postorder(p->left);
        Postorder(p->right);
        cout << p->info << endl;
    }
}

template<class T>
void Bst<T>::Insert(const T& insertItem)
{
    Node<T> *current; //pointer to traverse the tree
    Node<T> *trailCurrent = nullptr; //pointer behind current

    //initiate new node for Item to be placed in
    Node<T> *newNode; //pointer to create the node
    newNode = new Node<T>;
    newNode->info = insertItem;
    newNode->left = nullptr;
    newNode->right = nullptr;

    if (m_root == nullptr)
        m_root = newNode;
    else
    {
        current = m_root;
        while (current != nullptr)
        {
            trailCurrent = current;

            //check for same node
            if (current->info == insertItem)
            {
                //used to display error message, uncomment if necessary
                //cout << "The item to be inserted is already in the tree - duplicates are not allowed." << endl;

                return;
            }
            //move down the BST, move till current == nullptr
            else if (current->info > insertItem)
                current = current->left;
            else
                current = current->right;
        }
        //found end of node line
        if (trailCurrent->info > insertItem)
            trailCurrent->left = newNode;
        else
            trailCurrent->right = newNode;
    }
}

template<class T>
bool Bst<T>::Search(const T& searchItem) const
{
    {
        Node<T> *current;
        bool found = false;
        if (m_root == nullptr)
            cout << "Cannot search an empty tree." << endl;
        else
        {
            current = m_root;
            while (current != nullptr && !found)
            {
                if (current->info == searchItem)
                    found = true;
                else if (current->info > searchItem)
                    current = current->left;
                else
                    current = current->right;
            }
        }
        return found;
    }
}

template<class T>
bool Bst<T>::Get(T& searchItem)
{
    {
        Node<T> *current;
        bool found = false;
        if (m_root == nullptr)
            cout << "Cannot search an empty tree." << endl;
        else
        {
            current = m_root;
            while (current != nullptr && !found)
            {
                if (current->info == searchItem)
                {
                    found = true;
                    searchItem = current->info;
                }
                else if (current->info > searchItem)
                    current = current->left;
                else
                    current = current->right;
            }
        }
        return found;
    }
}

template<class T>
void Bst<T>::GetRootElement(T& element)
{
    element = m_root->info;
}

template<class T>
void Bst<T>::DeleteTree()
{
    Destroy(m_root);
}

template<class T>
bool Bst<T>::IsEmpty() const
{
    return (m_root == nullptr);
}

template<class T>
void Bst<T>::DeleteFromTree(Node<T>* &p)
{
    Node<T> *current; //pointer to traverse the tree
    Node<T> *trailCurrent; //pointer behind current
    Node<T> *temp; //pointer to delete the node

    if (p == nullptr) //check if node to delete is empty
    {
        cout << "Error: The node to be deleted does not exist." << endl;
    }

    //check node is leaf node
    else if (p->left == nullptr && p->right == nullptr)
    {
        temp = p;
        p = nullptr;
        delete temp;
    }
    //check node has no left child (has right)
    else if (p->left == nullptr)
    {
        temp = p;
        p = temp->right; //keep right child using p
        delete temp;
    }
    //check node has no right child (has left)
    else if (p->right == nullptr)
    {
        temp = p;
        p = temp->left; //keep left child using p
        delete temp;
    }
    else
    {
        //this method uses the DELETE node's left child most bottom
        //right node to replace the current node position, as the
        //bottom node will always be bigger than everything in the
        //left child tree but smaller than the node's right
        current = p->left; //start from node's left
        trailCurrent = nullptr;

        //move down left child's right till bottom
        while (current->right != nullptr)
        {
            trailCurrent = current;
            current = current->right;
        }

        //replace deleted node with bottom most right node
        p->info = current->info;

        //current did not move, left child of delete node has no
        //right node (bottomed out)
        if (trailCurrent == nullptr)
        {
            //move delete node's left child up one level to
            //take over
            p->left = current->left;
        }

        //while loop completed, current = bottomed right node
        else
        {
            //move bottomed right node up one level to take over
            trailCurrent->right = current->left;
        }

        delete current;
    }
}

template<class T>
void Bst<T>::DeleteNode(const T& deleteItem)
{
    Node<T> *current; //pointer to traverse the tree
    Node<T> *trailCurrent; //pointer behind current
    bool found = false;

    if (m_root == nullptr) //check if tree is empty
    {
        cout << "Cannot delete from an empty tree." << endl;
    }
    else
    {
        current = m_root;
        trailCurrent = m_root;
        //start search
        while (current != nullptr && !found)
        {
            if (current->info == deleteItem) //root check
                found = true;
            else
            {
                trailCurrent = current;
                if (current->info > deleteItem)
                    current = current->left;
                else
                    current = current->right;
            }
        }

        if (current == nullptr) //item not found in tree
        {
            cout << "The item to be deleted is not in the tree." << endl;
        }

        else if (found)
        {
            //found item at root
            if (current == m_root)
            {
                DeleteFromTree(m_root);
            }
            //item to delete is left child
            else if (trailCurrent->info > deleteItem)
            {
                DeleteFromTree(trailCurrent->left);
            }
            //item to delete is right child
            else
            {
                DeleteFromTree(trailCurrent->right);
            }
        }
        else
        {
            cout << "The item to be deleted is not in the tree." << endl;
        }
    }
}

template<class T>
void Bst<T>::InorderTraversal(void (*visit) (T&)) const
{
    Inorder(m_root, *visit);
}

template<class T>
void Bst<T>::PreorderTraversal(void (*visit) (T&)) const
{
    Preorder(m_root, *visit);
}

template<class T>
void Bst<T>::PostorderTraversal(void (*visit) (T&)) const
{
    Postorder(m_root, *visit);
}

template<class T>
void Bst<T>::Inorder(Node<T> *p,void (*visit) (T&)) const
{
    if (p != nullptr)
    {
        Inorder(p->left, *visit);
        (*visit)(p->info);
        Inorder(p->right, *visit);
    }
}

template<class T>
void Bst<T>::Preorder(Node<T> *p,void (*visit) (T&)) const
{
    if (p != nullptr)
    {
        (*visit)(p->info);
        Preorder(p->left, *visit);
        Preorder(p->right, *visit);
    }
}

template<class T>
void Bst<T>::Postorder(Node<T> *p,void (*visit) (T&)) const
{
    if (p != nullptr)
    {
        Postorder(p->left, *visit);
        Postorder(p->right, *visit);
        (*visit)(p->info);
    }
}

template<class T>
int Bst<T>::TreeNodeCount()
{
    //counter stored here instead of NodeCount to prevent recursion from
    //resetting counter to 0
    int counter = 0;
    return NodeCount(m_root, counter);
}

template<class T>
int Bst<T>::NodeCount(Node<T> *p, int &counter) const
{
    if(p == nullptr)
    {
        return counter;
    }
    else
    {
        counter++;
        NodeCount(p->left, counter);
        NodeCount(p->right, counter);
    }
    return counter;
}

template<class T>
template<class K>
void Bst<T>::InorderTraversal(void (*visit) (T&,K&), K& element) const
{
    Inorder(m_root, *visit, element);
}

template<class T>
template<class K>
void Bst<T>::Inorder(Node<T> *p, void (*visit) (T&,K&), K& element) const
{
    if (p != nullptr)
    {
        Inorder(p->left, *visit,element);
        (*visit)(p->info,element);
        Inorder(p->right, *visit,element);
    }
}

#endif // BST_H_INCLUDED
