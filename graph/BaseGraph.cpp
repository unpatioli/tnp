#include "BaseGraph.h"

#include <boost/iterator/transform_iterator.hpp>

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
                                edge_descriptor desc;
                                std::tie(desc, std::ignore) =
                                        boost::add_edge(_v_desc.at(arc.n1), _v_desc.at(arc.n2), arc, _g);
                                _line_edges[arc.line].push_back(desc);
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

std::shared_ptr<BaseGraph::EdgeDescContainerT>
BaseGraph::edges_by_line(nw::types::id_t id)
{
    auto res = _line_edges.find(id);
    if (res == _line_edges.end()) {
        return std::make_shared<EdgeDescContainerT>();
    }
    return std::make_shared<EdgeDescContainerT>(res->second);
}

std::shared_ptr<BaseGraph::EdgeByLineMap>
BaseGraph::edges_by_line(std::set<nw::types::id_t>& id_set)
{
    // Intersect set with map
    auto tr = [](const LineEdgeIndexT::value_type& pair) -> const LineEdgeIndexT::key_type {
        return pair.first;
    };

    typedef boost::transform_iterator<decltype(tr), LineEdgeIndexT::iterator> key_iter_t;

    std::list<nw::types::id_t> res_lines;
    std::set_intersection(id_set.begin(), id_set.end(),
                          key_iter_t(_line_edges.begin(), tr),
                          key_iter_t(_line_edges.end(), tr),
                          std::back_inserter(res_lines));

    // Populate map
    auto res_ptr = std::make_shared<EdgeByLineMap>();
    auto vertices = get(snode_t(), _g);
    auto edges = get(sarc_t(), _g);

    std::for_each(res_lines.begin(), res_lines.end(), [&](nw::types::id_t line_id) {

        auto edge_desc_set = edges_by_line(line_id);
        if (!edge_desc_set->empty()) {
            std::ostringstream sstream;
            std::for_each(edge_desc_set->begin(), edge_desc_set->end(), [&](edge_descriptor ed) {
                auto source = vertices[ed.m_source];
                auto target = vertices[ed.m_target];
                auto edge = edges[ed];
                sstream << "{ length=" << edge.length << " lanes=" << edge.lanes << " speed=" << edge.speed << " },";
                sstream << "(" << source.x << " ; " << source.y << ")" << "(" << target.x << " ; " << target.y << ");";
            });
            res_ptr->operator[](line_id) = sstream.str();
        }
    });
    return res_ptr;

}

}} // namespace
