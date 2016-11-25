#include "tn_struct.h"

#include <boost/lexical_cast.hpp>

boost::cnv::cstream ccnv;

namespace tnp {
namespace tn_network {

std::ostream &operator<<(std::ostream &os, const rarc &rarc1)
{
    os << "n1: " << rarc1.n1 << "\tn2: " << rarc1.n2 << "\tline: " << rarc1.line << "\tlength: " << rarc1.length
       << "\tflags: " << rarc1.flags << "\tspeed: " << rarc1.speed << "\tfreq: " << rarc1.freq << "\tpass: "
       << rarc1.pass << "\tp1: " << rarc1.p1 << "\tp2: " << rarc1.p2 << "\tp3: " << rarc1.p3 << "\tp4: "
       << rarc1.p4;
    return os;
}


std::ostream &operator<<(std::ostream &os, const rnode &rnode1)
{
    os << "number: " << rnode1.number << " x: " << rnode1.x << " y: " << rnode1.y << " z: " << rnode1.z
       << " flags: " << rnode1.flags << " set: " << rnode1.set << " name: " << rnode1.name;
    return os;
}

void sarc::init(const std::string &str)
{
    std::istringstream sstream(str);
    std::istream_iterator<std::string> it(sstream);

    n1 = convert<types::id_t>(*it++).value();
    n2 = convert<types::id_t>(*it++).value();
    line = convert<types::id_t>(*it++).value();
    length = convert<types::length_t>(*it++).value();
    users = convert<types::count_t>(*it++, ccnv(std::hex)).value();
    flags = convert<types::small_count_t>(*it++, ccnv(std::hex)).value();
    lanes = convert<types::small_count_t>(*it++).value();
    func = convert<types::id_t>(*it++).value();
    speed = convert<types::frac_t>(*it++).value();
    freq = convert<types::frac_t>(*it++).value();
    p1 = convert<types::small_count_t>(*it++).value();
    p2 = convert<types::small_count_t>(*it++).value();
    p3 = convert<types::frac_t>(*it++).value();
    p4 = convert<types::small_count_t>(*it++).value();
}

std::ostream &operator<<(std::ostream &os, const sarc &sarc1)
{
    os << std::dec << "n1: " << sarc1.n1 << " n2: " << sarc1.n2
       << " line: " << sarc1.line << " length: " << sarc1.length
       << std::hex << " users: " << sarc1.users << " flags: " << sarc1.flags
       << std::dec << " lanes: " << sarc1.lanes << " func: " << sarc1.func
       << " speed: " << sarc1.speed << " freq: " << sarc1.freq
       << std::dec << " p1: " << sarc1.p1 << " p2: " << sarc1.p2
       << " p3: " << sarc1.p3
       << std::dec << " p4: " << sarc1.p4
       << std::dec;
    return os;
}


void snode::init(const std::string &str)
{
    std::istringstream sstream(str);
    std::istream_iterator<std::string> it(sstream);

    number = lexical_cast<types::id_t>(*it++);
    x = lexical_cast<types::coord_t>(*it++);
    y = lexical_cast<types::coord_t>(*it++);
    z = lexical_cast<types::coord_t>(*it++);
    flags = convert<types::small_count_t>(*it++, ccnv(std::hex)).value();
}

std::ostream &operator<<(std::ostream &os, const snode &snode1)
{
    os << std::dec << "number: " << snode1.number << " x: " << snode1.x << " y: " << snode1.y << " z: " << snode1.z
       << std::hex << " flags: " << snode1.flags
       << std::dec;
    return os;
}
}} // namespace
