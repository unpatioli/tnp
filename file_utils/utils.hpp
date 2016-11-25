#ifndef TNP_UTILS_HPP
#define TNP_UTILS_HPP

#include <list>
#include <iostream>
#include <fstream>
#include <boost/lexical_cast.hpp>

#include "Converter.h"

namespace tnp {
namespace file_utils {

using namespace boost;

template <typename StructT>
std::list<StructT> read_csv(const char *filename,
                            std::shared_ptr<tnp::file_utils::Converter> converter)
{
    std::list<StructT> tn_struct_list;

    std::ifstream file(filename, std::ios::in);
    if (!file.good()) {
        return tn_struct_list;
    }

    std::string line;
    std::getline(file, line);
    std::string decoded_str(converter->convert(line));

    StructT tn_struct;

    while (std::getline(file, line)) {
        decoded_str = converter->convert(line);

        try {
            tn_struct.init(decoded_str);
        } catch (bad_lexical_cast& e) {
            std::cerr << e.what() << std::endl;
            break;
        }

        tn_struct_list.push_back(tn_struct);
    }
    return tn_struct_list;
}

template <typename StructT>
void read_csv(const char *filename,
              std::shared_ptr<tnp::file_utils::Converter> converter,
              std::function<void (StructT&)> func)
{
    std::ifstream file(filename, std::ios::in);
    if (!file.good()) {
        return;
    }

    // Skip first line
    std::string line, decoded_line;
    std::getline(file, line);
//    decoded_line = converter->convert(line);

    StructT tn_struct;

    while (std::getline(file, line)) {
        decoded_line = converter->convert(line);

        try {
            tn_struct.init(decoded_line);
        } catch (bad_lexical_cast& e) {
            std::cerr << e.what() << std::endl;
            break;
        }

        func(tn_struct);
    }
}

}} // namespace

#endif //TNP_UTILS_H
