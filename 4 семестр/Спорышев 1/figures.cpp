#include "figures.h"
#include <iostream>

vector<fpnt> Line::intersect_with_line(Line &that) {
    double x1 = this->p1_.x;
    double x2 = this->p2_.x;
    double y1 = this->p1_.y;
    double y2 = this->p2_.y;
    double x3 = that.p1_.x;
    double x4 = that.p2_.x;
    double y3 = that.p1_.y;
    double y4 = that.p2_.y;

    if ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1) < EPS) {
        if (((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) < EPS) {
            cout << "Lines coincide";
        } else {
            cout << "Lines are parallel";
        }
    } else {
        double ua = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) /
                    ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
        double ub = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) /
                    ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

        if (!((ua >= EPS) && (ua - 1 <= EPS) && (ub >= EPS) && (ub - 1 <= EPS))) {
            cout << "Lines intersect \n";
        } else {
            cout << "Line segments intersect \n";
        }
        double x = x1 + ua * (x2 - x1);
        double y = y1 + ua * (y2 - y1);
        //cout << x << " " << y;
        vector<fpnt> res;
        res.push_back(fpnt{x, y});
        return res;
    }
}

vector<fpnt> Line::intersect_with_circle(Circle &circle) {
    vector<fpnt> result;
    fpnt a = this->getFirstPoint();
    fpnt b = this->getSecondPoint();
    fpnt o = circle.getCentre();
    double r = circle.getRadius();

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

vector<fpnt> Line::intersect_with_broken_line(BrokenLine &broken_line) {
    vector<fpnt> result;
    for (int i = 0; i < broken_line.numPoints() - 1; i++) {
        Line line = broken_line.getLine(i);
        vector<fpnt> points = this->intersect_with_line(line);
        for (int j = 0; j < points.size(); j++)
            result.push_back(points[j]);
    }
    return result;
}


vector<fpnt> Circle::intersect_with_line(Line &that) {
    return (that.intersect_with_circle(*this));
}

vector<fpnt> Circle::intersect_with_circle(Circle &circle) {
    vector<fpnt> result;

    double d = sqrt(pow(circle.getCentre().x - this->getCentre().x, 2) + pow(circle.getCentre().y - this->getCentre().y, 2));
    bool nesting = abs(circle.getRadius() - this->getRadius()) > d;
    bool no_intersection = d > circle.getRadius() + this->getRadius();
    if (!(nesting || no_intersection)) {
        double b =(pow(this->getRadius(), 2) - pow(circle.getRadius(), 2) + pow(d, 2)) / (2 * d);
        double a = d - b;
        fpnt p0;
        p0.x = circle.getCentre().x + a / d * (this->getCentre().x - circle.getCentre().x);
        p0.y = circle.getCentre().y + a / d * (this->getCentre().y - circle.getCentre().y);
        if (d == circle.getRadius() + this->getRadius())
            result.push_back(p0);
        else {
            double h = sqrt(pow(circle.getRadius(), 2) - pow(a, 2));
            fpnt p3, p4;
            p3.x = p0.x + (this->getCentre().y - circle.getCentre().y) * h / d;
            p3.y = p0.y - (this->getCentre().x - circle.getCentre().x) * h / d;
            p4.x = p0.x - (this->getCentre().y - circle.getCentre().y) * h / d;
            p4.y = p0.y + (this->getCentre().x - circle.getCentre().x) * h / d;
            result.push_back(p3);
            result.push_back(p4);
        }
        return result;
    }

    return result;
}

vector<fpnt> Circle::intersect_with_broken_line(BrokenLine &broken_line) {
    return (broken_line.intersect_with_circle(*this));
}


vector<fpnt> BrokenLine::intersect_with_line(Line &that) {
    return (that.intersect_with_broken_line(*this));
}

vector<fpnt> BrokenLine::intersect_with_circle(Circle &circle) {
    vector<fpnt> result;
    for (int i = 0; i < this->numPoints() - 1; i++) {
        Line line = this->getLine(i);
        vector<fpnt> points = line.intersect_with_circle(circle);
        for (int j = 0; j < points.size(); j++)
            result.push_back(points[j]);
    }
    return result;
}

vector<fpnt> BrokenLine::intersect_with_broken_line(BrokenLine &broken_line) {
    vector<fpnt> result;
    for (int i = 0; i < this->numPoints() - 1; i++) {
        Line line = this->getLine(i);
        vector<fpnt> points = line.intersect_with_broken_line(broken_line);
        for (int j = 0; j < points.size(); j++)
            result.push_back(points[j]);
    }
    return result;
}

