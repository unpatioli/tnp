#ifndef TNP_BASEGRAPH_H
#define TNP_BASEGRAPH_H

#include <boost/core/noncopyable.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/bimap.hpp>

#include "tn_network/tn_struct.h"

namespace nw = tnp::tn_network;

namespace tnp {
namespace graph {

class BaseGraph : private boost::noncopyable
{
private:
    struct snode_t
    {
        typedef boost::vertex_property_tag kind;
    };
    typedef boost::property <snode_t, nw::snode> VertexProperty;
    struct sarc_t
    {
        typedef boost::edge_property_tag kind;
    };
    typedef boost::property <sarc_t, nw::sarc> EdgeProperty;
//    typedef boost::adjacency_list <boost::vecS, boost::vecS, boost::bidirectionalS, VertexProperty, EdgeProperty> GraphT;
    using GraphT = boost::adjacency_list <boost::vecS, boost::vecS, boost::bidirectionalS, VertexProperty, EdgeProperty>;

    typedef boost::bimap <
            boost::bimaps::set_of<nw::types::id_t>,
            boost::bimaps::set_of<boost::graph_traits<GraphT>::vertex_descriptor>
    > BimapT;

public:
    BaseGraph();
    virtual ~BaseGraph();

    void init(const char *vertices_fname, const char *edges_fname);

    boost::graph_traits<GraphT>::vertex_descriptor
    vertex_d(nw::types::id_t id) const;

    nw::types::id_t
    vertex_id(boost::graph_traits<GraphT>::vertex_descriptor d) const;

    GraphT& graph() { return _g; }
    const GraphT& const_graph() const { return _g; }

    typedef boost::graph_traits<GraphT>::out_edge_iterator out_edge_iterator;
    typedef boost::graph_traits<GraphT>::in_edge_iterator in_edge_iterator;

private:
    GraphT _g;
    BimapT _desc_map;
    BimapT::left_map& _v_desc = _desc_map.left;
    BimapT::right_map& _v_id = _desc_map.right;
};

}} // namespace

#endif //TNP_BASEGRAPH_H
