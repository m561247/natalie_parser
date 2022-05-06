#pragma once

#include "natalie_parser/node/node.hpp"
#include "natalie_parser/node/node_with_args.hpp"
#include "tm/hashmap.hpp"
#include "tm/owned_ptr.hpp"
#include "tm/string.hpp"

namespace NatalieParser {

using namespace TM;

class SplatNode : public Node {
public:
    SplatNode(const Token &token)
        : Node { token } { }

    SplatNode(const Token &token, SharedPtr<Node> node)
        : Node { token }
        , m_node { node } {
        assert(m_node);
    }

    virtual Type type() const override { return Type::Splat; }

    virtual bool is_assignable() const override { return true; }

    const SharedPtr<Node> node() const { return m_node; }

    virtual void transform(Creator *creator) const override {
        creator->set_type("splat");
        if (m_node)
            creator->append(m_node.ref());
    }

protected:
    SharedPtr<Node> m_node {};
};
}
