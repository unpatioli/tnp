#ifndef TNP_RNODE_H
#define TNP_RNODE_H

#include <string>
#include <ostream>

#include <boost/convert.hpp>
#include <boost/convert/stream.hpp>

struct boost::cnv::by_default : public boost::cnv::cstream
{
};

namespace tnp {
namespace tn_network {

using namespace boost;

struct types
{
    typedef unsigned int id_t;
    typedef unsigned int count_t;
    typedef unsigned short small_count_t;
    typedef std::string name_t;
    typedef char char_t;
    typedef short length_t;
    typedef int coord_t;
    typedef float frac_t;
};

struct line
{
    types::id_t number;
    types::id_t set;
    types::id_t origin;
    types::name_t name;
};

struct link
{
    types::id_t number;
    types::id_t node;
    types::length_t length;
    types::name_t users;
    types::small_count_t flags;
    types::small_count_t p1, p2, p3, p4;
};

struct onode
{
    types::id_t zone;
    types::id_t number;
    types::coord_t x, y;
    types::small_count_t flags;
};

struct rarc
{
    types::id_t n1, n2;
    types::id_t line;
    types::length_t length;
    types::small_count_t flags;
    types::small_count_t speed;
    types::frac_t freq;
    types::count_t pass;
    types::small_count_t p1, p2, p3, p4;

    friend std::ostream &operator<<(std::ostream &os, const rarc &rarc1);
};

struct rnode
{
    types::id_t number;
    types::coord_t x, y, z;
    types::small_count_t flags;
    types::id_t set;
    types::name_t name;

    friend std::ostream &operator<<(std::ostream &os, const rnode &rnode1);
};

struct routes
{
    types::id_t number;
    types::id_t set;
    types::small_count_t speed;
    types::frac_t freq;
    types::count_t pass;
    types::frac_t to_veh;
    types::small_count_t flags;
    types::small_count_t p1, p2;
    types::frac_t p3;
    types::name_t name;
};

struct rset
{
    types::id_t number;
    types::small_count_t pen_size;
    types::name_t color;
    types::char_t c;
    types::small_count_t flags;
    types::small_count_t speed;
    types::frac_t freq;
    types::count_t pass;
    types::small_count_t p1, p2, p3, p4;
    std::string name;
};

struct rtpoints
{
    types::id_t route;
    types::id_t node;
    types::small_count_t flags;
    types::small_count_t speed;
    types::name_t name;
};

struct rtset
{
    types::id_t number;
    types::id_t type;
    types::small_count_t pen_size;
    types::name_t color;
    types::name_t sign;
    types::small_count_t speed;
    types::frac_t freq;
    types::count_t pass;
    types::frac_t to_veh;
    types::small_count_t flags;
    types::small_count_t p1, p2, p3;
    types::name_t name;
};

struct sarc
{
    types::id_t n1, n2;
    types::id_t line;
    types::length_t length;
    types::count_t users;
    types::small_count_t flags;
    types::small_count_t lanes;
    types::id_t func;
    types::frac_t speed;
    types::frac_t freq;
    types::small_count_t p1;
    types::small_count_t p2;
    types::frac_t p3;
    types::small_count_t p4;

    void init(const std::string &str);

    friend std::ostream &operator<<(std::ostream &os, const sarc &sarc1);
};

struct snode
{
    types::id_t number;
    types::coord_t x, y, z;
    types::small_count_t flags;

    void init(const std::string &str);

    friend std::ostream &operator<<(std::ostream &os, const snode &snode1);
};

struct sset
{
    types::id_t number;
    types::small_count_t pen_size;
    types::name_t color;
    types::char_t c;
    types::name_t users;
    types::small_count_t flags;
    types::small_count_t lanes;
    types::id_t func;
    types::small_count_t speed;
    types::frac_t freq;
    types::small_count_t p1, p2, p3, p4;
    types::name_t name;
};

struct track
{
    types::id_t n1, n2;
    types::coord_t x, y;
};

struct turn
{
    types::id_t n1, n2, n3;
    types::id_t func;
    types::small_count_t green;
    types::small_count_t lanes;
};

struct user
{
    types::id_t type;
    types::name_t id;
    types::frac_t car_to_pas;
    types::frac_t car_to_veh;
    types::frac_t speed_coeff;
    types::name_t name;
};

struct zone
{
    types::id_t number;
    types::name_t color;
    types::name_t name;
};

}} // namespace

#endif //TNP_RNODE_H
