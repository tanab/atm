#include <node.h>
#include <algorithm>

using namespace std;

Node::Node(Node *parent)
    : m_parent(parent), m_result_children(), m_letter_children(LETTER_CHILDREN_SIZE) {}

Node::Node(const Node &other)
    : m_parent(other.m_parent),
      m_result_children(other.m_result_children),
      m_letter_children(other.m_letter_children) {}

Node::~Node() {
    // TODO: Do we need to delete children too or not?
    removeAllChildren();
    m_result_children.clear();
    m_letter_children.clear();
}

Node &Node::operator=(const Node &other) {
    // TODO: Do we need to delete existing children first?
    m_parent = other.m_parent;
    m_result_children = other.m_result_children;
    m_letter_children = other.m_letter_children;
    return *this;
}

void Node::removeAllChildren() {
    for (auto &child : m_result_children) {
        child->removeAllChildren();
    }
    m_result_children.remove_if([](Node *node) {
        delete node;
        return true;
    });
    for_each(m_letter_children.begin(), m_letter_children.end(), [](Node *&node) {
        if (node != nullptr) {
            node->removeAllChildren();
            delete node;
            node = nullptr;
        }
    });
}

void Node::addChild(Node *child) {
    if (child->letterNode()) {
        //TODO: What if node for given letter index already exists?
        m_letter_children[letterIndex(child->letter())] = child;
    } else {
        m_result_children.push_back(child);
    }
    child->m_parent = this;
}
