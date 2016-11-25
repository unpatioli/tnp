#ifndef TNP_CONVERTEREXCEPTION_H
#define TNP_CONVERTEREXCEPTION_H

#include <string>
#include <stdexcept>

namespace tnp {
namespace file_utils {

class ConverterException : public std::runtime_error
{
public:
    ConverterException(const std::string &msg = "no msg") : runtime_error("iconv failed to start: " + msg)
    {}
};

}} // namespace


#endif //TNP_CONVERTEREXCEPTION_H
