#include "Converter.h"
#include "ConverterException.h"
#include "Outbuff.h"

namespace tnp {
namespace file_utils {

Converter::Converter(std::string from, std::string to) :
        _from(from),
        _to(to),
        _cnv(CnvPtrT(iconv_open(to.c_str(), from.c_str()), deleter))
{
    if (_cnv.get() == (iconv_t) -1) {
        throw ConverterException();
    }
}

std::string Converter::convert(const std::string &text)
{
    std::string res = "";

    Outbuff outbuff(text);

    char *ip = (char *) text.c_str();
    char *op = static_cast<char *>(outbuff);
    size_t icount = text.length();
    size_t ocount = text.length() * 2;

    if (iconv(_cnv.get(), &ip, &icount, &op, &ocount) != (size_t) -1) {
        outbuff[text.length() * 2 - ocount] = '\0';
        res = outbuff;
    }

    return res;
}

}} // namespace
