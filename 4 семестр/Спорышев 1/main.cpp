//ToDo:
//убрать const в начале
//сделать один intersect на всё
//покрыть тестами
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "figures.h"

TEST_CASE("Figures unit") {
    SECTION("Create array of figures") {
        vector<Figure> test = {Line({0.0, 0.0}, {1.0, 1.0}),
                               Circle({0.0, 0.0}, 1),
                               BrokenLine({{0.0, 0.0},
                                           {1.0, 1.0},
                                           {2.0, 2.0}})};
    }

    SECTION("Intersect Line and Line") {
        Line l1({0.0, 0.0}, {1.0, 1.0});
        Line l2({1.0, 2.0}, {1.0, 3.0});
        vector<fpnt> intersection = l1.intersect_with_line(l2);
        REQUIRE(intersection.size() == 1);
        REQUIRE(abs(intersection[0].x - 1.0) <= EPS);
        REQUIRE(abs(intersection[0].y - 1.0) <= EPS);
    }

    SECTION("Intersect Line and Circle") {
        Line l1({0.0, 0.0}, {1.0, 1.0});
        Circle c1({0.0, 0.0}, 1);
        vector<fpnt> intersection = l1.intersect_with_circle(c1);
        REQUIRE(intersection.size() == 2);
        REQUIRE(abs(intersection[0].x - 0.707107) <= EPS);
        REQUIRE(abs(intersection[0].y - 0.707107) <= EPS);
        REQUIRE(abs(intersection[1].x + 0.707107) <= EPS);
        REQUIRE(abs(intersection[1].y + 0.707107) <= EPS);
    }

    SECTION("Intersect Circle and Circle") {
        Circle c1({0.0, 0.0}, 1);
        Circle c2({0.5, 0.0}, 1);
        vector<fpnt> intersection = c2.intersect_with_circle(c1);
        REQUIRE(intersection.size() == 2);
        REQUIRE(abs(intersection[0].x - 0.25) <= EPS);
        REQUIRE(abs(intersection[0].y + 0.968246) <= EPS);
        REQUIRE(abs(intersection[1].x - 0.25) <= EPS);
        REQUIRE(abs(intersection[1].y - 0.968246) <= EPS);
    }

    SECTION("Intersect Broken Line and Circle") {
        Circle c1({0.0, 0.0}, 1);
        BrokenLine b1({{0.0, 0.0},
                       {1.0, 1.0},
                       {2.0, 2.0}});
        vector<fpnt> intersection = b1.intersect_with_circle(c1);
        REQUIRE(intersection.size() == 4);
        REQUIRE(abs(intersection[0].x - 0.707107) <= EPS);
        REQUIRE(abs(intersection[0].y - 0.707107) <= EPS);
        REQUIRE(abs(intersection[1].x + 0.707107) <= EPS);
        REQUIRE(abs(intersection[1].y + 0.707107) <= EPS);
    }
}