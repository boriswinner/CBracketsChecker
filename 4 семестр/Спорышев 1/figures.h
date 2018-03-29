#pragma once
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
    virtual double length() {};

    virtual vector<fpnt> intersect_with_line(Line &that) {};

    virtual vector<fpnt> intersect_with_circle(Circle &circle)  {};

    virtual vector<fpnt> intersect_with_broken_line(BrokenLine &broken_line)  {};
};

class Line : public Figure {
private:
    fpnt p1_, p2_;
public:
    Line(fpnt p1, fpnt p2) : p1_(p1), p2_(p2) {}

    double length() override {
        return pow((p2_.x - p1_.x), 2) + pow((p2_.y - p1_.y), 2);
    }

    fpnt getFirstPoint() {
        return p1_;
    }

    fpnt getSecondPoint() {
        return p2_;
    }

    vector<fpnt> intersect_with_line(Line &that) override;

    vector<fpnt> intersect_with_circle(Circle &circle) override;

    vector<fpnt> intersect_with_broken_line(BrokenLine &broken_line) override;

};

class Circle : public Figure {
private:
    fpnt p_;
    double r_;
public:
    Circle(fpnt p, double r) : p_(p), r_(r) {}

    double length() override {
        return 2 * M_PI * r_;
    }

    fpnt getCentre() {
        return p_;
    }

    double getRadius() {
        return r_;
    }

    vector<fpnt> intersect_with_line(Line &that) override;

    vector<fpnt> intersect_with_circle(Circle &circle) override;

    vector<fpnt> intersect_with_broken_line(BrokenLine &broken_line) override;

};

class BrokenLine : public Figure {
private:
    vector<fpnt> p_;
public:
    BrokenLine (vector<fpnt> p): p_(p) {};

    double length() override {
        double sum = 0;
        for (int i = 0; i < p_.size() - 1; ++i) {
            sum += pow((p_[i + 1].x - p_[i].x), 2) + pow((p_[i + 1].y - p_[i].y), 2);
        }
        return sum;
    }

    int numPoints() {
        return p_.size();
    }

    Line getLine(int index) {
        return Line(p_[index], p_[index + 1]);
    }

    vector<fpnt> intersect_with_line(Line &that) override;

    vector<fpnt> intersect_with_circle(Circle &circle) override;

    vector<fpnt> intersect_with_broken_line(BrokenLine &broken_line) override;
};
