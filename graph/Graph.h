

#include <vector>

class Node
{
protected:
    std::vector<std::unique_ptr<Node>> _children;
    int _id;
public:

    Node(int id) : _id(id) {}

    void appendNode(std::unique_ptr<Node> child)
    {
        _children.push_back(std::move(child));
    }

    virtual int weight()=0;

    const void print(std::ostream &stream, int indention = 0)
    {
        stream << std::string(indention, ' ') << _id << std::endl;
        for (const auto &child: Node::_children)
        {
            child->print(stream, indention + 4);
        }
    }

    virtual ~Node()
    {
        for (auto &child: _children)
        {
            child.reset();
        }
    }
};


class Group : public Node
{
public:

    Group(Group &group) : Node(group._id)
    {
        for (const auto &child:group._children)
        {
            this->_children.push_back(std::move(child));
        }
    }

    Group(int id) : Node(id) {};

    virtual int weight() override
    {
        int weight = 0;
        for (auto &child: _children)
        {
            weight += child->weight();
        }
        return weight;
    }
};

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
};
