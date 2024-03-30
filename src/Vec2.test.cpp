#include "Vec2.h"
#include "catch.hpp"
#include "Constants.h"

using Catch::Matchers::WithinAbs;
using Catch::Matchers::Equals;


TEST_CASE("Vec2", "[Vec2]") {
    Vec2 v1, v2(1.0, 4.0);

    SECTION("constructors") {
        REQUIRE(v1.x == 0.0);
        REQUIRE(v1.y == 0.0);

        REQUIRE(v2.x == 1.0);
        REQUIRE(v2.y == 4.0);
    }

    SECTION("sum") {
        v1.x = 9.0;
        v2.x = -3.0;
        v1.y = 0.0;
        v2.y = -3.0;
        
        Vec2 vsum = v1 + v2 + Vec2({1, 1});
        CHECK(vsum.x == 7.0);
        CHECK(vsum.y == -2.0);
        vsum += {1, 2};
        CHECK(vsum.x == 8.0);
        CHECK(vsum.y == 0.0);
    }

    SECTION("scalar ops (* /)") {
        v2.x = 1.0;
        v2.y = -3.0;

        Vec2 vmut(v2*20.0);

        CHECK(vmut.x == 10.0);
        CHECK(vmut.y == -30.0);

        vmut *= 2;
        CHECK(vmut.x == 20.0);
        CHECK(vmut.y == -60.0);

        
        vmut = vmut / 4;
        CHECK(vmut.x == 5.0);
        CHECK(vmut.y == -15.0);
    }

    SECTION("GetAbs") {
        v2.x = 0.0;
        v2.y = 2.0;
        CHECK(v2.GetAbs() == 2.0);
        v2.x = 2.0;
        // sqrt(8) = 2.8284271247
        CHECK_THAT(v2.GetAbs(), WithinAbs(2.8, 0.05));
    }

    SECTION("GetRotated") {
        v2.x = 0.0;
        v2.y = 2.0;

        // [TODO]: ver sobre erro acumulado
        float de = 2.5e-07; // n passa 2 ultimos
        // float de = 5e-07; // n passa ultimo
        // float de = 7.5e-07; // passa tds

        CHECK_THAT(v2.GetRotated(PI/2).y, WithinAbs(0., de));
        CHECK_THAT(v2.GetRotated(PI/2).x, WithinAbs(-2., de));

        CHECK_THAT(v2.GetRotated(PI).y, WithinAbs(-2., de));
        CHECK_THAT(v2.GetRotated(PI).x, WithinAbs(0., de));

        CHECK_THAT(v2.GetRotated(PI*2).y, WithinAbs(2., de));
        CHECK_THAT(v2.GetRotated(PI*2).x, WithinAbs(0., de));
        
        CHECK_THAT(v2.GetRotated(4*PI).y, WithinAbs(2., de));
        CHECK_THAT(v2.GetRotated(4*PI).x, WithinAbs(0., de));
    }

    SECTION("GetNormalized") {
        v2.x = 0.0;
        v2.y = 10.0;

        CHECK(v2.GetNormalized().x == 0.0);
        CHECK(v2.GetNormalized().y == 1.0);

        v2.x = 15.0;
        v2.y = 15.0;
        
        float de = 2.5e-07; // n passa 2 ultimos

        Vec2 vec_norm_1 = v2.GetNormalized();

        CHECK_THAT(vec_norm_1.x, WithinAbs(sqrt(2)/2, de));
        CHECK_THAT(vec_norm_1.y, WithinAbs(sqrt(2)/2, de));


        // [TODO]: ver se tudo bem isso falhar
        Vec2 vec_norm_2 = vec_norm_1.GetNormalized();
        CHECK(vec_norm_1.x == vec_norm_2.x);
        CHECK(vec_norm_1.y == vec_norm_2.y);
    }
}