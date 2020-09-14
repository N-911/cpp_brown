#include "test_runner.h"
#include <cassert>
#include <deque>
#include <iostream>

using namespace std;


struct Node {
  Node(int v, Node* p)
    : value(v)
    , parent(p)
  {}

  int value;
  Node* left = nullptr;
  Node* right = nullptr;
  Node* parent;
};


class NodeBuilder {
public:
  Node* CreateRoot(int value) {
    nodes.emplace_back(value, nullptr);
    return &nodes.back();
  }

  Node* CreateLeftSon(Node* me, int value) {
    assert( me->left == nullptr );
    nodes.emplace_back(value, me);
    me->left = &nodes.back();
    return me->left;
  }

  Node* CreateRightSon(Node* me, int value) {
    assert( me->right == nullptr );
    nodes.emplace_back(value, me);
    me->right = &nodes.back();
    return me->right;
  }

private:
  deque<Node> nodes;
};


Node* f(Node* c_node) {
    if (c_node->left == nullptr) {
        return c_node;
    } else {
        return f (c_node->left);
    }
}

/*
Node* f(Node* c_node) {
    assert(c_node);

    while (c_node->left) {
        c_node = c_node->left;
    }
    return c_node;
}
*/

Node* Next2(Node* node) {
    auto next_node = node;
    int value_current = node->value;

    if (node->right == nullptr && node->parent == nullptr) {
        return nullptr;
    }

    else if (node->right) {
        next_node = node->right;
        next_node = f(next_node);
    }
    else if (node->parent) {
        auto parent_node = node->parent;

        for ( ; parent_node->value < value_current; parent_node = parent_node->parent) {
            if (parent_node->parent == nullptr) {
                return nullptr;
            }
        }
        int value_parent = parent_node->value;  //
        auto node_temp = parent_node;   //

        next_node = f (node_temp->right);
        if ( value_parent < next_node->value) {
            next_node = parent_node;
        }
        else {
            next_node = node_temp;
        }
    }

    return next_node;
}

Node* Next(Node* node) {
    assert(node);

    if (node->right) {
        return f(node->right);
    }

    if (node->parent && node->parent->left == node) {
        return  node->parent;
    }

    while (node->parent && node == node->parent->right) {
        node = node->parent;
    }
    return node->parent;
}


void Test1() {
  NodeBuilder nb;

  Node* root = nb.CreateRoot(50);
  ASSERT_EQUAL( root->value, 50 );

  Node* l = nb.CreateLeftSon(root, 2);
  Node* min = nb.CreateLeftSon(l, 1);
  Node* r = nb.CreateRightSon(l, 4);
  ASSERT_EQUAL( min->value, 1);
  ASSERT_EQUAL( r->parent->value, 2 );

  nb.CreateLeftSon(r, 3);
  nb.CreateRightSon(r, 5);

  r = nb.CreateRightSon(root, 100);
  l = nb.CreateLeftSon(r, 90);
  Node* last = nb.CreateRightSon(r, 101);

  nb.CreateLeftSon(l, 89);
  r = nb.CreateRightSon(l, 91);

  ASSERT_EQUAL( Next(l)->value, 91);
  ASSERT_EQUAL( Next(root)->value, 89 );
  ASSERT_EQUAL( Next(min)->value, 2 );
  ASSERT_EQUAL( Next(r)->value, 100);
  ASSERT( Next(last)== nullptr);

  while (min) {
    cout << min->value << '\n';
    min = Next(min);
  }
}

void Test2() {
    NodeBuilder nb;

    Node* n1;
    Node* n2;
    Node* n3;
    Node* n4;
    Node* n5;
    Node* n50;
    Node* n89;
    Node* n90;
    Node* n91;
    Node* n100;
    Node* n101;


    Node* root = nb.CreateRoot(50);
    n50 = root;
    ASSERT_EQUAL( root->value, 50 );

    Node* l = nb.CreateLeftSon(root, 2);
    n2 = l;
    Node* min = nb.CreateLeftSon(l, 1);
    n1 = min;
    Node* r = nb.CreateRightSon(l, 4);
    n4 = r;
    ASSERT_EQUAL( min->value, 1);
    ASSERT_EQUAL( r->parent->value, 2 );

    n3 = nb.CreateLeftSon(r, 3);
    n5 = nb.CreateRightSon(r, 5);

    r = nb.CreateRightSon(root, 100);
    n100 = r;
    l = nb.CreateLeftSon(r, 90);
    n90 = l;
    n101 = nb.CreateRightSon(r, 101);

    n89 = nb.CreateLeftSon(l, 89);
    r = nb.CreateRightSon(l, 91);
    n91 = r;


    ASSERT_EQUAL( Next(n1)->value, 2 );
    ASSERT_EQUAL( Next(n2)->value, 3 );
    ASSERT_EQUAL( Next(n3)->value, 4 );
    ASSERT_EQUAL( Next(n4)->value, 5 );
    ASSERT_EQUAL( Next(n5)->value, 50 );
    ASSERT_EQUAL( Next(n50)->value, 89 );
    ASSERT_EQUAL( Next(n89)->value, 90 );
    ASSERT_EQUAL( Next(n90)->value, 91 );
    ASSERT_EQUAL( Next(n91)->value, 100 );
    ASSERT_EQUAL( Next(n100)->value, 101 );
    ASSERT_EQUAL((size_t)Next(n101), (size_t)nullptr );


    ASSERT_EQUAL( Next(min)->value, 2 );
    ASSERT_EQUAL( Next(l)->value, 91);
    ASSERT_EQUAL( Next(root)->value, 89 );
    ASSERT_EQUAL( Next(r)->value, 100);

}

void TestRootOnly() {
  NodeBuilder nb;
  Node* root = nb.CreateRoot(42);
  ASSERT( Next(root) == nullptr);
};


int main() {
  TestRunner tr;
  RUN_TEST(tr, Test1);
  RUN_TEST(tr, Test2);
  RUN_TEST(tr, TestRootOnly);
  return 0;
}
