#ifndef TNP_OUTBUFF_H
#define TNP_OUTBUFF_H

#include <string>

namespace tnp {
namespace file_utils {

class Outbuff
{
    char *_outbuff;

public:
    Outbuff(const std::string &text);

    ~Outbuff();

    operator char *() const
    { return _outbuff; }

    char &operator[](int i)
    { return _outbuff[i]; }
};

}} // namespace


#endif //TNP_OUTBUFF_H
