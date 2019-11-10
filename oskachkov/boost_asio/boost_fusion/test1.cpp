#include "test.h"
#include <boost/fusion/include/sequence.hpp>
#include <boost/fusion/include/algorithm.hpp>
#include <boost/fusion/include/vector.hpp>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/fusion/include/pair.hpp>


using namespace boost::fusion;

struct employee
{
    std::string name;
    int age;
};


// Without BOOST_PP_VARIADICS support :
BOOST_FUSION_ADAPT_STRUCT(
    employee,
    (auto, age)
    (auto, name)
)

struct AppendToTextBox
{
    int i;

    AppendToTextBox():i(0){}

    template <typename T>
    void operator()(T& t) const {
        printf("  --%s--%s--  \n",
               typeid(t).name(),
               boost::lexical_cast<std::string>(t).c_str()
               );
    }

};

template <typename Sequence>
void process(const Sequence & seq)
{
    boost::fusion::for_each(seq, AppendToTextBox<Sequence>());
}

void Test::test1()
{
    employee e;
    e.age = 3;
    e.name = "asas";

    for_each(e, AppendToTextBox());
}

