#include <vector>
#include <iostream>
//#include <iomanip>

/**
 * Abstract base class for all kinds of node objects.
 */
class Node
{
protected:
    std::vector<std::unique_ptr<Node>> _children;
    int _id;
public:

    Node(int id) : _id(id) {}

    void appendNode(std::unique_ptr<Node> &&node)
    {
        _children.push_back(std::move(node));
    }

    virtual int weight()=0;

    int getId() { return _id; }

    virtual void print(std::ostream &stream, int indention = 0)
    {
        stream << std::string(indention, ' ') << getId() << std::endl;
        for (const auto &child: Node::_children)
        {
            child->print(stream, indention + 2);
        }
    }

    virtual ~Node()
    {
        for (auto &&child: _children)
        {
            child.reset();
        }
    }
};

/**
 * A container node having zero or more child nodes
 */
class Group : public Node
{
public:

    Group(int id) : Node(id) {};

    virtual int weight() override
    {
        int weight = 0;
        for (const auto &child: _children)
        {
            weight += child->weight();
        }
        return weight;
    }
};

/**
 * A leaf node, specifying a weight
 */
class Leaf : public Node
{
private:
    using Node::appendNode;
    int _weight;
public:
    Leaf(int id, int weight) :
            Node(id),
            _weight(weight) {};

    virtual int weight() override
    {
        return this->_weight;
    }

    virtual void print(std::ostream &stream, int indention = 0) override
    {
        std::cout.fill(' ');
        stream << std::string(indention, ' ')
               //<< std::setw(3) << std::left << _id
               << getId()
               << " : " << weight() << std::endl;
    }
};

/**
 * A node delegating to another subgraph
 */
class Proxy : public Node
{
private:
    Node *node;
    using Node::appendNode;
public:
    Proxy(int id, Node *node) : Node(id), node(node) {}

    virtual int weight() override
    {
        return node->weight();
    }

    void print(std::ostream &stream, int indention = 0) override
    {
        stream << std::string(indention, ' ')
               //<< std::setw(3) << std::left << _id
               << getId()
               << " -> " << node->getId()
               << std::endl;
    }
};
