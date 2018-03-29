#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include "figures.h"

void print_fpnt_vector(const vector<fpnt> &tt);

TEST_CASE("Array of figures"){
    SECTION("Create array of figures"){
        vector <Figure> test = {Line({0.0, 0.0}, {1.0, 1.0}),
                                Circle({0.0, 0.0}, 1),
                                BrokenLine({{0.0, 0.0}, {1.0, 1.0}, {2.0,2.0}})};
    }

    SECTION("Intersect Line and Line"){
        Line l1({0.0, 0.0}, {1.0, 1.0});
        Line l2({1.0, 2.0}, {1.0, 3.0});
        vector <fpnt> intersection = l1.intersect_with_line(l2);
        REQUIRE(intersection.size() == 1);
        REQUIRE(intersection[0].x - 1.0 <= EPS);
        REQUIRE(intersection[0].y - 1.0 <= EPS);
    }

    SECTION("Intersect Line and Circle"){
        Line l1({0.0, 0.0}, {1.0, 1.0});
        Circle c1({0.0, 0.0}, 1);
        vector <fpnt> intersection = l1.intersect_with_circle(c1);
        REQUIRE(intersection.size() == 2);
        REQUIRE(intersection[0].x - 0.707107 <= EPS);
        REQUIRE(intersection[0].y - 0.707107 <= EPS);
        REQUIRE(intersection[1].x + 0.707107 <= EPS);
        REQUIRE(intersection[1].y + 0.707107 <= EPS);
    }

    SECTION("Intersect Circle and Circle"){
        Circle c1({0.0, 0.0}, 1);
        Circle c2({0.5,0.0}, 1);
        vector <fpnt> intersection = c2.intersect_with_circle(c1);
        REQUIRE(intersection.size() == 2);
        REQUIRE(intersection[0].x - 0.25 <= EPS);
        REQUIRE(intersection[0].y - 0.968246 <= EPS);
        REQUIRE(intersection[1].x - 0.25 <= EPS);
        REQUIRE(intersection[1].y + 0.968246 <= EPS);
    }

    SECTION("Intersect Broken Line and Circle"){
        Circle c1({0.0, 0.0}, 1);
        BrokenLine b1({{0.0, 0.0}, {1.0, 1.0}, {2.0,2.0}});
        vector <fpnt> intersection = b1.intersect_with_circle(c1);
        REQUIRE(intersection.size() == 4);
        REQUIRE(intersection[0].x - 0.707107 <= EPS);
        REQUIRE(intersection[0].y - 0.707107 <= EPS);
        REQUIRE(intersection[1].x + 0.707107 <= EPS);
        REQUIRE(intersection[1].y + 0.707107 <= EPS);
    }
}

/*int main() {

    fpnt t = fpnt{1.0, 2.0};
    Line l1({0.0, 0.0}, {1.0, 1.0});
    Line l2({1.0, 2.0}, {1.0, 3.0});
    cout << "Line 1 length: " << l1.length() << '\n';
    cout << "Line 1 Intersection with Line 2: \n";
    vector <fpnt> tt = l1.intersect_with_line(l2);
    print_fpnt_vector(tt);
    Circle c1({0.0, 0.0}, 1);
    tt = l1.intersect_with_circle(c1);
    cout << "Line 1 Intersection with Circle 1: \n";
    print_fpnt_vector(tt);
    Circle c2({0.5,0.0}, 1);
    tt = c1.intersect_with_circle(c2);
    cout << "Circle 1 Intersection with Circle 2: \n";
    print_fpnt_vector(tt);
    BrokenLine b1({{0.0, 0.0}, {1.0, 1.0}, {2.0,2.0}});
    tt = b1.intersect_with_circle(c1);
    cout << "Broken Line 1 Intersection with Circle 1: \n";
    print_fpnt_vector(tt);
    return 0;
}*/

void print_fpnt_vector(const vector<fpnt> &tt) {
    for (int i = 0; i < tt.size(); ++i){
        cout << tt[i].x << " " << tt[i].y << '\n';
    }
}