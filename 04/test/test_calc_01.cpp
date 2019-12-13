#include <UnitTest++/UnitTest++.h>
#include "Calc.h"

SUITE(Calc_Tests)
{
    TEST(Calc_Min)
    {
        Calc cl;
        CHECK_EQUAL(2, cl.min(2, 4));
        CHECK_EQUAL(-3, cl.min(-1, -3));
        CHECK_EQUAL(0, cl.min(0, 0xFFFFFF));
    }
    TEST(Calc_Max)
    {
        Calc cl;
        CHECK_EQUAL(4, cl.max(2, 4));
        CHECK_EQUAL(-1, cl.max(-1, -3));
        CHECK_EQUAL(0xFFFFFF, cl.max(0, 0xFFFFFF));
    }
}