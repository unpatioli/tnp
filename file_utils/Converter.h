#ifndef TNP_CONVERTER_H
#define TNP_CONVERTER_H

#include <iconv.h>
#include <string>

namespace tnp {
namespace file_utils {

auto deleter = [](iconv_t cnv) { iconv_close(cnv); };

class Converter
{
    std::string _from;
    std::string _to;

    typedef std::unique_ptr<void, decltype(deleter)> CnvPtrT;
    CnvPtrT _cnv;

public:
    Converter(std::string from, std::string to);

    std::string convert(const std::string& text);
};

}} // namespace

#endif //TNP_CONVERTER_H
