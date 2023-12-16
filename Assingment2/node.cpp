#include "node.h"
Node::Node(bool sentinel) : is_sentinel(sentinel), next(nullptr), prev(nullptr), value(-1) {}

// Use to construct a regular node
Node::Node(int v, Node *nxt, Node *prv) : value(v), next(nxt), prev(prv), is_sentinel(false) {}

// Return whether a node is a sentinel node
// Use it to check if we are at the ends of a list
bool Node::is_sentinel_node()
{
    return is_sentinel;
}

// Return the value of a node
int Node::get_value()
{
    return value;
}