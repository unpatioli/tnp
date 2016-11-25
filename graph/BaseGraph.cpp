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

void BaseGraph::init(const char *dir_name)
{
    const std::string base(dir_name);

    std::string vertices_str(base + "/__SNode.txt");
    std::string edges_str(base + "/__SArc.txt");

    std::shared_ptr<tfu::Converter> converter(nullptr);
    try {
        converter.reset(new tfu::Converter("cp1251", "utf8"));
    } catch (...) {
        return;
    }

    tfu::read_csv<nw::snode>(vertices_str.c_str(), converter,
                             [this](nw::snode& node) {
                                 auto desc = boost::add_vertex(node, _g);
                                 _desc_map.insert(BimapT::value_type(node.number, desc));
                             });


    tfu::read_csv<nw::sarc>(edges_str.c_str(), converter,
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
