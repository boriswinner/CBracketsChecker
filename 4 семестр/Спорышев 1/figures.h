#pragma once

#include <utility>
#include <vector>
#include <cmath>

#define EPS 0.01

using namespace std;

class Line;

class Circle;

class BrokenLine;


typedef struct FloatPoint {
    double x, y;
} fpnt;

class Figure {
public:
    virtual const double length() {};

    virtual const vector<fpnt> intersect_with_line(const Line &that) const {}

    virtual const vector<fpnt> intersect_with_circle(const Circle &that) const {}

    virtual const vector<fpnt> intersect_with_broken_line(const BrokenLine &that) const {}
};

class Line : public Figure {
private:
    fpnt p1_, p2_;
public:
    Line(fpnt p1, fpnt p2) : p1_(p1), p2_(p2) {}

    const double length() override {
        return pow((p2_.x - p1_.x), 2) + pow((p2_.y - p1_.y), 2);
    }

    const fpnt get_first_point() const {
        return p1_;
    }

    const fpnt get_second_point() const {
        return p2_;
    }

    const vector<fpnt> intersect_with_line(const Line &that) const override;

    const vector<fpnt> intersect_with_circle(const Circle &that) const override;

    const vector<fpnt> intersect_with_broken_line(const BrokenLine &that) const override;

};

class Circle : public Figure {
private:
    fpnt p_;
    double r_;
public:
    Circle(fpnt p, double r) : p_(p), r_(r) {}

    const double length() override {
        return 2 * M_PI * r_;
    }

    const fpnt get_centre() const {
        return p_;
    }

    const double get_radius() const {
        return r_;
    }

    const vector<fpnt> intersect_with_line(const Line &that) const override;

    const vector<fpnt> intersect_with_circle(const Circle &that) const override;

    const vector<fpnt> intersect_with_broken_line(const BrokenLine &that) const override;

};

class BrokenLine : public Figure {
private:
    vector<fpnt> p_;
public:
    explicit BrokenLine(vector<fpnt> p) : p_(std::move(p)) {};

    const double length() override {
        double sum = 0;
        for (int i = 0; i < p_.size() - 1; ++i) {
            sum += pow((p_[i + 1].x - p_[i].x), 2) + pow((p_[i + 1].y - p_[i].y), 2);
        }
        return sum;
    }

    const int num_points() const {
        return p_.size();
    }

    const Line get_line(const int index) const {
        return {p_[index], p_[index + 1]};
    }

    const vector<fpnt> intersect_with_line(const Line &that) const override;

    const vector<fpnt> intersect_with_circle(const Circle &that) const override;

    const vector<fpnt> intersect_with_broken_line(const BrokenLine &that) const override;
};
