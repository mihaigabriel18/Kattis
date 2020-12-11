#include <iostream>
#include <vector>
#include <utility>

using std::cin;
using std::cout;
using std::vector;
using std::max;
using std::min;

////////////////////////////////////////////////////////////////////////////////

void fast() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

////////////////////////////////////////////////////////////////////////////////

class Point {
public:
    int x, y;

    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }

    int justEndMe(Point& aux) {
        return this->x * aux.y - this->y * aux.x;/////////////////////////////////////////////////
    }

    ~Point() {}
};

class Line {
public:
    Point *p1, *p2;

    Line(Point *p1, Point *p2) {
        this->p1 = p1;
        this->p2 = p2;
    }

    ~Line() {}
};

class LineEq {
public:
    int a, b, c;

    LineEq(Point& p1, Point& p2) {
        this->a = p2.y - p1.y;
        this->b = p2.x - p1.x;
        this->c = (p1.y - p1.x) * this->b;
    }

    ~LineEq() {}
};

class Intersection {
public:
    // the function checks if point q lies on line segment 'pr' 
    static bool onSegment(Point p, Point q, Point r) {
        if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
            q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
            return true;

        return false;
    }

    // To find orientation of ordered triplet (p, q, r). 
    // The function returns following values 
    // 0 --> p, q and r are colinear 
    // 1 --> Clockwise 
    // 2 --> Counterclockwise 
    static int orientation(Point p, Point q, Point r) {
        int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

        if (val == 0) return 0;  // colinear 

        return (val > 0)? 1: 2; // clock or counterclock wise 
    }

    static bool isIntersect(Line& l1, Line& l2) {
        int o1 = orientation(*l1.p1, *l1.p2, *l2.p1);
        int o2 = orientation(*l1.p1, *l1.p2, *l2.p2);
        int o3 = orientation(*l2.p1, *l2.p2, *l1.p1);
        int o4 = orientation(*l2.p1, *l2.p2, *l1.p2);

        if (o1 != o2 && o3 != o4)
            return true;

        if (o1 == 0 && onSegment(*l1.p1, *l2.p1, *l1.p2)) return true;

        if (o2 == 0 && onSegment(*l1.p1, *l2.p2, *l1.p2)) return true;

        if (o3 == 0 && onSegment(*l2.p1, *l1.p1, *l2.p2)) return true;

        if (o4 == 0 && onSegment(*l2.p1, *l1.p2, *l2.p2)) return true;

        return false; // Doesn't fall in any of the above cases 
    }
};

class Polygon {
public:
    vector<Point*> points;

    Polygon() {}

    void addPoint(Point *p) {
        this->points.push_back(p);
    }

    double area() {
        // TODO
    }

    bool isInside(Point point) {
        if (points.size() < 3) return false;

        Point extreme = {INT32_MAX, point.y};

        int count = 0, i = 0, next = 0;
        do {
            int next = (i + 1) % points.size();

            Line l_polygon(points[i], points[next]);
            Line l_mypoint(&point, &extreme);
            if (Intersection::isIntersect(l_polygon, l_mypoint)) {

                // check if p is on segment between i and next
                if (Intersection::orientation(*points[i], point, *points[next]))
                    return Intersection::onSegment(*points[i], point, *points[next]);

                count++;
            }
            i = next;
        } while (i != next);

        return count&1; // same as count % 2 == 1
    }

    ~Polygon() {
        for (int i = points.size()-1; i >= 0; i--) {
            delete points[i];
        }
    }
};

/**
 * Returns point of intersection or null if the lines do not intersect
 */
Point intersectionOfTwoLines(LineEq e1, LineEq e2) { // O(1)
    Point res(0, 0);
    res.x = (e1.b*e2.c - e1.c*e2.b) / (e1.a*e2.b - e1.b*e2.a);
    res.y = (e1.c*e2.a - e1.a*e2.c) / (e1.a*e2.b - e1.b*e2.a);

    return res;
}

////////////////////////////////////////////////////////////////////////////////
int main() {
    fast();

    int numObjects;
    cin >> numObjects;

    vector<Polygon> allObjects();
    for (int i = 0; i < numObjects; i++) {
        int numSides;
        cin >> numSides;
        allObjects[i]();

        for (int j = 0; j < numSides; j++) {
            int inNode, outNode;
            cin >> inNode >> outNode;
            Point *p = new Point(inNode, outNode);
            allObjects[i].addPoint(p);
        }
    }

    return 0;
}