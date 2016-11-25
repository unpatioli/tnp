#include "BaseGraph.h"

#include "file_utils/utils.hpp"

namespace tfu = tnp::file_utils;

namespace tnp {
namespace graph {

BaseGraph::BaseGraph()
{

}

BaseGraph::~BaseGraph()
{

}

void BaseGraph::init(const char *vertices_fname, const char *edges_fname)
{
    std::shared_ptr<tfu::Converter> converter(nullptr);
    try {
        converter.reset(new tfu::Converter("cp1251", "utf8"));
    } catch (...) {
        return;
//        return EXIT_FAILURE;
    }

    tfu::read_csv<nw::snode>(vertices_fname, converter,
                             [this](nw::snode& node) {
                                 auto desc = boost::add_vertex(node, _g);
                                 _desc_map.insert(BimapT::value_type(node.number, desc));
                             });


    tfu::read_csv<nw::sarc>(edges_fname, converter,
                            [this](nw::sarc& arc) {
                                boost::add_edge(_v_desc.at(arc.n1), _v_desc.at(arc.n2), arc, _g);
                            });
}

boost::graph_traits<BaseGraph::GraphT>::vertex_descriptor
BaseGraph::vertex_d(nw::types::id_t id) const
{
    return _v_desc.at(id);
}

nw::types::id_t
BaseGraph::vertex_id(boost::graph_traits<GraphT>::vertex_descriptor d) const
{
    return _v_id.at(d);
}

}} // namespace
