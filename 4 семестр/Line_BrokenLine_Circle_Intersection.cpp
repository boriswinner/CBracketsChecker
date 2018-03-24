#include <iostream>
#include <cmath>
#include <vector>
#define EPS 0.01

using namespace std;

class Line;
class Circle;
class BrokenLine;


typedef struct FloatPoint{
    double x,y;
} fpnt;

class Figure{
public:
    virtual double length() = 0;
    virtual vector<fpnt> intersect_with_line(const Line &that) = 0;
    virtual vector<fpnt> intersect_with_circle(Circle& circle)  = 0;
    virtual vector<fpnt> intersect_with_broken_line(BrokenLine& broken_line)  = 0;
};

class Line: public Figure{
private:
    fpnt p1_, p2_;
public:
    Line(fpnt p1, fpnt p2) : p1_(p1), p2_(p2) {}

    double length () override{
        return pow((p2_.x - p1_.x),2) + pow((p2_.y - p1_.y),2);
    }

    fpnt getFirstPoint() {
        return p1_;
    }

    fpnt getSecondPoint() {
        return p2_;
    }

    vector<fpnt> intersect_with_line(const Line &that) override;

    vector<fpnt> intersect_with_circle(Circle& circle) override;

    vector<fpnt> intersect_with_broken_line(BrokenLine& broken_line) override;

};

class Circle: public Figure{
private:
    fpnt p_;
    double r_;
public:
    Circle(fpnt p, double r) : p_(p), r_(r) {}

    double length () override{
        return 2*M_PI*r_;
    }

    fpnt getCentre() {
        return p_;
    }

    double getRadius() {
        return r_;
    }

    vector<fpnt> intersect_with_line(const Line &that) override;

    vector<fpnt> intersect_with_circle(Circle& circle) override;

    vector<fpnt> intersect_with_broken_line(BrokenLine& broken_line) override;

};

vector<fpnt> Circle::intersect_with_line(const Line &that) {

}

vector<fpnt> Circle::intersect_with_circle(Circle &circle) {
    return vector<fpnt>();
}

vector<fpnt> Circle::intersect_with_broken_line(BrokenLine &broken_line) {
    return vector<fpnt>();
}

class BrokenLine: public Figure{
private:
    vector <fpnt> p_;
public:
    double length () override{
        double sum = 0;
        for (int i = 0; i < p_.size() - 1; ++i){
            sum += pow((p_[i+1].x - p_[i].x),2) + pow((p_[i+1].y - p_[i].y),2);
        }
        return sum;
    }

    int numPoints() {
        return p_.size();
    }

    Line getLine(int index) {
        if (index >= p_.size() || index < 0)
            throw length_error("Index error");
        return Line(p_[index], p_[index + 1]);
    }
    vector<fpnt> intersect_with_line(const Line &that) override;

    vector<fpnt> intersect_with_circle(Circle& circle) override;

    vector<fpnt> intersect_with_broken_line(BrokenLine& broken_line) override;
};

vector<fpnt> BrokenLine::intersect_with_line(const Line &that) {
    return vector<fpnt>();
}

vector<fpnt> BrokenLine::intersect_with_circle(Circle &circle) {
    return vector<fpnt>();
}

vector<fpnt> BrokenLine::intersect_with_broken_line(BrokenLine &broken_line) {
    return vector<fpnt>();
}


vector <fpnt> Line::intersect_with_line(const Line &that) {
    //this function returns a pair of <int, fpnt>, where <int> means:
    // 0 - parallel
    // 1 - coincide
    // 2 - lines intersect
    // 3 - line segments intersect
    // <fpnt> is the intersection point
    double x1 = this->p1_.x;
    double x2 = this->p2_.x;
    double y1 = this->p1_.y;
    double y2 = this->p2_.y;
    double x3 = that.p1_.x;
    double x4 = that.p2_.x;
    double y3 = that.p1_.y;
    double y4 = that.p2_.y;

    if ((y4 - y3)*(x2 - x1) - (x4 - x3)*(y2 - y1) < EPS){
        if (((x4 - x3)*(y1 - y3) - (y4 - y3)*(x1 - x3)) < EPS){
            cout << "Lines coincide";
        } else{
            cout << "Lines are parallel";
        }
    } else {
        double ua = ((x4 - x3)*(y1 - y3) - (y4 - y3)*(x1 - x3))/
                    ((y4 - y3)*(x2 - x1) - (x4 - x3)*(y2 - y1));
        double ub = ((x2 - x1)*(y1 - y3) - (y2 - y1)*(x1 - x3))/
                    ((y4 - y3)*(x2 - x1) - (x4 - x3)*(y2 - y1));

        if (!((ua >= EPS) && (ua - 1 <= EPS) && (ub >= EPS) && (ub - 1 <= EPS))){
            cout << "Lines intersect \n";
        } else{
            cout << "Line segments intersect \n";
        }
        double x = x1 + ua*(x2 - x1);
        double y = y1 + ua*(y2 - y1);
        cout << x << " " << y;
        vector <fpnt> res;
        res.push_back(fpnt{x,y});
        return res;
    }
}

vector<fpnt> Line::intersect_with_circle(Circle &circle) {
    vector<fpnt> result;
    fpnt a = this->getFirstPoint();
    fpnt b = this->getSecondPoint();
    fpnt o = circle.getCentre();
    double r = circle.getRadius();

    a.x -= o.x; a.y -= o.y;
    b.x -= o.x; b.y -= o.y;

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
        }
        else {
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

vector<fpnt> Line::intersect_with_broken_line(BrokenLine& broken_line) {
    vector<fpnt> result;
    for (int i = 0; i < broken_line.numPoints() - 1; i++) {
        Line line = broken_line.getLine(i);
        vector<fpnt> points = this->intersect_with_line(line);
        for (int j = 0; j < points.size(); j++)
            result.push_back(points[j]);
    }
    return result;
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    fpnt t = fpnt{1.0,2.0};
    Line l1({0.0,0.0}, {1.0,1.0});
    Line l2({1.0,2.0}, {1.0,3.0});
    cout << l1.length() << '\n';
    l1.intersect_with_line(l2);
    Circle c1({0.0,0.0},1);
    vector <fpnt> tt = l1.intersect_with_circle(c1);
    //Line l2(fpnt(1.0, 2.0), fpnt(2.0, 3.0), fpnt(0, 0), fpnt(0, 0));
    return 0;
}