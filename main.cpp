#include "boost/graph/graph_traits.hpp"
#include "boost/graph/adjacency_list.hpp"

#include "tn_network/tn_struct.h"
#include "file_utils/Converter.h"
#include "file_utils/utils.hpp"
#include "graph/BaseGraph.h"

#define MEASURE_TIME

namespace nw = tnp::tn_network;
namespace tfu = tnp::file_utils;
namespace tgr = tnp::graph;

using namespace boost;

typedef tgr::BaseGraph GraphT;

void demo(const GraphT&);
void demo_line(GraphT&, nw::types::id_t);

int main(int argc, char **argv)
{
    // Parse command line
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <Transnet network dir>" << std::endl;
        return EXIT_FAILURE;
    }

    // Create UTF-8 converter
    std::shared_ptr<tfu::Converter> converter(nullptr);
    try {
        converter.reset(new tfu::Converter("cp1251", "utf8"));
    } catch (...) {
        return EXIT_FAILURE;
    }

#ifdef MEASURE_TIME
    auto t0 = std::chrono::high_resolution_clock::now();
#endif

    // Initialize Graph
    GraphT g;
    g.init(argv[1]);

#ifdef MEASURE_TIME
    auto t_graph_init = std::chrono::high_resolution_clock::now();
#endif

#ifdef MEASURE_TIME
    auto ts_graph_init = std::chrono::duration_cast<std::chrono::milliseconds>(t_graph_init - t0);
    std::cout << "Graph init: " << ts_graph_init.count() << " milliseconds." << std::endl;
#endif

    // Some demo operations with Graph
//    demo(g);
    int line = 50;
    if (argc >= 3) {
        line = std::stoi(argv[2]);
    }
    demo_line(g, line);

    return EXIT_SUCCESS;
}

void demo(const GraphT& g)
{
    auto v = g.vertex_d(25);

    tgr::BaseGraph::out_edge_iterator oei, oei_end;
    std::tie(oei, oei_end) = out_edges(v, g.const_graph());
    if (oei != oei_end) {
        std::cout << "Out edges for node " << g.vertex_id(v) << std::endl;
        for (; oei != oei_end; ++oei) {
            std::cout << g.vertex_id(oei->m_source) << " => " << g.vertex_id(oei->m_target) << std::endl;
        }
    }

    tgr::BaseGraph::in_edge_iterator iei, iei_end;
    std::tie(iei, iei_end) = in_edges(v, g.const_graph());
    if (iei != iei_end) {
        std::cout << "In edges for node " << g.vertex_id(v) << std::endl;
        for (; iei != iei_end; ++iei) {
            std::cout << g.vertex_id(iei->m_source) << " => " << g.vertex_id(iei->m_target) << std::endl;
        }
    }

    std::cout << "num_vertices(g) = " << num_vertices(g.const_graph()) << std::endl;
    std::cout << "num_edges(g) = " << num_edges(g.const_graph()) << std::endl;
}

void demo_line(GraphT& g, nw::types::id_t line_id)
{
    int line_count = 0;
    std::set<nw::types::id_t> key_set;
    const int from = 0;
    const int to = 21000;
    std::cout << std::endl << "[" << from << ":" << to << "]:" << std::endl;

    for (int i = from; i < to; ++i) {
        key_set.insert(i);
    }

#ifdef MEASURE_TIME
    auto t0 = std::chrono::high_resolution_clock::now();
#endif

    auto line_set_ptr = g.edges_by_line(key_set);
    std::for_each(line_set_ptr->begin(), line_set_ptr->end(), [&](std::pair<nw::types::id_t, std::string> pair) {
        std::cout << pair.first << ": " << pair.second << std::endl;
        ++line_count;
    });

#ifdef MEASURE_TIME
    auto t1 = std::chrono::high_resolution_clock::now();
#endif

    std::cout << "total lines = " << line_count << std::endl;

#ifdef MEASURE_TIME
    auto ts_query_process = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
    std::cout << "Query process: " << ts_query_process.count() << " milliseconds." << std::endl;
#endif
}