#ifndef TNP_BASEGRAPH_H
#define TNP_BASEGRAPH_H

#include <map>
#include <boost/core/noncopyable.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/bimap.hpp>

#include "tn_network/tn_struct.h"

namespace nw = tnp::tn_network;

namespace tnp {
namespace graph {

class BaseGraph : private boost::noncopyable
{
public:
    struct snode_t
    {
        typedef boost::vertex_property_tag kind;
    };
    typedef boost::property <snode_t, nw::snode> vertex_property;
    struct sarc_t
    {
        typedef boost::edge_property_tag kind;
    };
    typedef boost::property <sarc_t, nw::sarc> edge_property;
    typedef boost::adjacency_list <boost::vecS, boost::vecS, boost::bidirectionalS,
            vertex_property, edge_property> GraphT;

    typedef boost::graph_traits<GraphT>::vertex_descriptor vertex_descriptor;
    typedef boost::graph_traits<GraphT>::edge_descriptor edge_descriptor;
    typedef boost::graph_traits<GraphT>::out_edge_iterator out_edge_iterator;
    typedef boost::graph_traits<GraphT>::in_edge_iterator in_edge_iterator;

    typedef std::vector<edge_descriptor> EdgeDescContainerT;

private:
    typedef boost::bimap <
            boost::bimaps::set_of<nw::types::id_t>,
            boost::bimaps::set_of<vertex_descriptor>
    > BimapT;

    typedef std::map<nw::types::id_t, EdgeDescContainerT> LineEdgeIndexT;

public:
    BaseGraph();
    virtual ~BaseGraph();

    void init(const char *dir_name);

    boost::graph_traits<GraphT>::vertex_descriptor
    vertex_d(nw::types::id_t id) const;

    nw::types::id_t
    vertex_id(boost::graph_traits<GraphT>::vertex_descriptor d) const;

    std::shared_ptr<BaseGraph::EdgeDescContainerT> edges_by_line(nw::types::id_t id);

    typedef std::map<nw::types::id_t, std::string> EdgeByLineMap;
    std::shared_ptr<EdgeByLineMap> edges_by_line(std::set<nw::types::id_t>& id_set);

    GraphT& graph() { return _g; }
    const GraphT& const_graph() const { return _g; }

private:
    GraphT _g;
    BimapT _desc_map;
    BimapT::left_map& _v_desc = _desc_map.left;
    BimapT::right_map& _v_id = _desc_map.right;

    LineEdgeIndexT _line_edges;
};

}} // namespace

#endif //TNP_BASEGRAPH_H
