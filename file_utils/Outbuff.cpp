#include <cstdlib>

#include "Outbuff.h"
#include "ConverterException.h"

namespace tnp {
namespace file_utils {

Outbuff::Outbuff(const std::string &text)
{
    if ((_outbuff = (char *) malloc(text.length() * 2 + 1)) == NULL) {
        throw ConverterException();
    }
}

Outbuff::~Outbuff()
{
    free(_outbuff);
}

}} // namespace