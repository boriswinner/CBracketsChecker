#include "figures.h"
#include <iostream>

const vector<fpnt> Line::intersect_with_line(const Line &that) const {
    double x1 = this->p1_.x;
    double x2 = this->p2_.x;
    double y1 = this->p1_.y;
    double y2 = this->p2_.y;
    double x3 = that.p1_.x;
    double x4 = that.p2_.x;
    double y3 = that.p1_.y;
    double y4 = that.p2_.y;

    double ua = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) /
                ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
    double ub = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) /
                ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

    double x = x1 + ua * (x2 - x1);
    double y = y1 + ua * (y2 - y1);
    vector<fpnt> res;
    res.push_back(fpnt{x, y});
    return res;
}

const vector<fpnt> Line::intersect_with_circle(const Circle &that) const {
    vector<fpnt> result;
    fpnt a = this->get_first_point();
    fpnt b = this->get_second_point();
    fpnt o = that.get_centre();
    double r = that.get_radius();

    a.x -= o.x;
    a.y -= o.y;
    b.x -= o.x;
    b.y -= o.y;

    double A = a.y - b.y;
    double B = b.x - a.x;
    double C = a.x * b.y - b.x * a.y;

    fpnt q;
    q.x = -(A * C) / (A * A + B * B);
    q.y = -(B * C) / (A * A + B * B);

    if (C * C <= r * r * (A * A + B * B) + EPS) {
        if (abs(C * C - r * r * (A * A + B * B)) < EPS) {
            q.x += o.x;
            q.y += o.y;
            result.push_back(q);
        } else {
            double d = r * r - C * C / (A * A + B * B);
            double mult = sqrt(d / (A * A + B * B));
            fpnt v, w;
            v.x = q.x + B * mult + o.x;
            w.x = q.x - B * mult + o.x;
            v.y = q.y - A * mult + o.y;
            w.y = q.y + A * mult + o.y;
            result.push_back(v);
            result.push_back(w);
        }
    }
    return result;
}

const vector<fpnt> Line::intersect_with_broken_line(const BrokenLine &that) const {
    vector<fpnt> result;
    for (int i = 0; i < that.num_points() - 1; i++) {
        Line line = that.get_line(i);
        vector<fpnt> points = this->intersect_with_line(line);
        for (int j = 0; j < points.size(); j++)
            result.push_back(points[j]);
    }
    return result;
}


const vector<fpnt> Circle::intersect_with_line(const Line &that) const {
    return (that.intersect_with_circle(*this));
}

const vector<fpnt> Circle::intersect_with_circle(const Circle &that) const {
    vector<fpnt> result;

    double d = sqrt(
            pow(that.get_centre().x - this->get_centre().x, 2) +
            pow(that.get_centre().y - this->get_centre().y, 2));
    bool nesting = abs(that.get_radius() - this->get_radius()) > d;
    bool no_intersection = d > that.get_radius() + this->get_radius();
    if (!(nesting || no_intersection)) {
        double b = (pow(this->get_radius(), 2) - pow(that.get_radius(), 2) + pow(d, 2)) / (2 * d);
        double a = d - b;
        fpnt p0;
        p0.x = that.get_centre().x + a / d * (this->get_centre().x - that.get_centre().x);
        p0.y = that.get_centre().y + a / d * (this->get_centre().y - that.get_centre().y);
        if (d == that.get_radius() + this->get_radius())
            result.push_back(p0);
        else {
            double h = sqrt(pow(that.get_radius(), 2) - pow(a, 2));
            fpnt p3, p4;
            p3.x = p0.x + (this->get_centre().y - that.get_centre().y) * h / d;
            p3.y = p0.y - (this->get_centre().x - that.get_centre().x) * h / d;
            p4.x = p0.x - (this->get_centre().y - that.get_centre().y) * h / d;
            p4.y = p0.y + (this->get_centre().x - that.get_centre().x) * h / d;
            result.push_back(p3);
            result.push_back(p4);
        }
        return result;
    }

    return result;
}

const vector<fpnt> Circle::intersect_with_broken_line(const BrokenLine &that) const {
    return (that.intersect_with_circle(*this));
}


const vector<fpnt> BrokenLine::intersect_with_line(const Line &that) const {
    return (that.intersect_with_broken_line(*this));
}

const vector<fpnt> BrokenLine::intersect_with_circle(const Circle &that) const {
    vector<fpnt> result;
    for (int i = 0; i < this->num_points() - 1; i++) {
        Line line = this->get_line(i);
        vector<fpnt> points = line.intersect_with_circle(that);
        for (int j = 0; j < points.size(); j++)
            result.push_back(points[j]);
    }
    return result;
}

const vector<fpnt> BrokenLine::intersect_with_broken_line(const BrokenLine &that) const {
    vector<fpnt> result;
    for (int i = 0; i < this->num_points() - 1; i++) {
        Line line = this->get_line(i);
        vector<fpnt> points = line.intersect_with_broken_line(that);
        for (int j = 0; j < points.size(); j++)
            result.push_back(points[j]);
    }
    return result;
}

