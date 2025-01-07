#include <iostream>
#include "Bst.h"

using namespace std;
typedef Bst<int> intBST;

void Test01(intBST test);
void Test02();
void Test03();
void Test04(intBST &test);
void Test05(intBST test);
void Test06(intBST test);
void Test07(intBST test);
void Test08(intBST test);
void Test09(intBST test);
void Test10(intBST test);
void Test11(intBST test);
void Test12(intBST test);

int main()
{
   intBST test;

    Test01(test);
    Test02();
    Test03();
    Test04(test);
    Test05(test);
    Test06(test);
    Test07(test);
    Test08(test);
    Test09(test);
    Test10(test);
    Test11(test);
    Test12(test);

    return 0;
}

void Test01(intBST test)
{
    cout << "=== Testing Default Constructor ===" << endl;
    if(test.IsEmpty())
    {
        cout << "Successful initialization" << endl << endl;
    }
    else
    {
        cout << "Unsuccessful initialization" << endl << endl;
    }
}

void Test02()
{
    cout << "=== Testing Copy Constructor ===" << endl;
    intBST n1;
    n1.Insert(15);
    intBST n2(n1);
    n2.InorderTraversal();
    cout << endl << endl;
}

void Test03()
{
    cout << "=== Testing Deep Copy ===" << endl;
    intBST n1;
    n1.Insert(88);
    intBST n2;
    n2 = n1;
    n2.InorderTraversal();
    cout << endl << endl;
}

void Test04(intBST &test)
{
    cout << "=== Testing Insert() ===" << endl;
    test.Insert(50);
    test.Insert(42);
    test.Insert(44);
    test.Insert(63);
    test.Insert(41);

    cout << "Display inserted items" << endl;
    test.InorderTraversal();
    cout << endl << endl;

    cout << "Test inserting duplicate item" << endl;
    test.Insert(44);
    cout << endl;
}

void Test05(intBST test)
{
    cout << "=== Testing InorderTraversal() ===" << endl;
    test.InorderTraversal();
    cout << endl << endl;
}

void Test06(intBST test)
{
    cout << "=== Testing PostorderTraversal() ===" << endl;
    test.PostorderTraversal();
    cout << endl << endl;
}

void Test07(intBST test)
{
    cout << "=== Testing PreorderTraversal() ===" << endl;
    test.PreorderTraversal();
    cout << endl << endl;
}

void Test08(intBST test)
{
    cout << "=== Testing Search() ===" << endl;
    cout << "Test empty search" << endl;
    intBST n1;
    cout << "Search result: " << n1.Search(44) << endl << endl;

    cout << "Test non-existent search (120)" << endl;
    cout << "Search result: " << test.Search(120) << endl << endl;

    cout << "Test found search (44)" << endl;
    cout << "Search result: " << test.Search(44) << endl << endl;
}

void Test09(intBST test)
{
    cout << "=== Testing DeleteNode() ===" << endl;
    cout << "Test data" << endl;
    test.InorderTraversal();
    cout << endl << endl;

    cout << "Test empty tree" << endl;
    intBST n1;
    n1.DeleteNode(44);
    cout << endl;

    cout << "Test non-existent data (120)" << endl;
    test.DeleteNode(120);
    cout << endl;

    cout << "Test existing data (42)" << endl;
    test.DeleteNode(42);
    test.InorderTraversal();
    cout << endl << endl;
}

void Test10(intBST test)
{
    cout << "=== Testing DeleteTree() ===" << endl;
    test.DeleteTree();
    cout << "Data: " << endl;
    test.InorderTraversal();

    cout << "IsEmpty: " << test.IsEmpty() << endl << endl;
}

void Test11(intBST test)
{
    cout << "=== Testing IsEmpty() ===" << endl;
    cout << "Test filled tree" << endl;
    cout << "IsEmpty: " << test.IsEmpty() << endl << endl;

    cout << "Test empty tree" << endl;
    intBST n1;
    cout << "IsEmpty: " << n1.IsEmpty() << endl << endl;
}

void Test12(intBST test)
{
    cout << "=== Testing TreeNodeCount() ===" << endl;
    cout << "Size: " << test.TreeNodeCount() << endl;
}


















