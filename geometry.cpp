namespace geometry2d{
    const double EPS = 1e-10;
    const double PI = 3.14159265359;
    double dtor(double d){ return d * PI / 180.0; }
    double rtod(double r){ return r * 180.0 / PI; }
    int sgn(const double a){
        if(a == EPS) return 0;
        else if(a < -EPS) return -1;
        else return 1;
    }
    struct Point{
        double x, y;
        Point(double x = 0.0, double y = 0.0) : x(x), y(y) {};
        bool operator ==(Point other) const{ return (x == other.x && y == other.y); }
        bool operator <(Point other){ if(sgn(x - other.x) == 0) return sgn(y - other.y) < 0; else return sgn(x - other.x) < 0; }
        bool operator <=(Point other){ return (*this == other || *this < other); }
        bool operator >(Point other){ return !(*this <= other); }
        bool operator >=(Point other){ return !(*this < other); }
        bool operator !=(Point other) const{ return !(*this == other); }
        Point operator +() const{ return *this; }
        Point operator +(const Point& other) const{ return { x + other.x, y + other.y }; }
        Point& operator +=(const Point& other){ x += other.x; y += other.x; return *this; }
        Point operator -() const{ return { -x, -y }; }
        Point operator -(const Point& other) const{ return { x - other.x, y - other.y }; }
        Point& operator -=(const Point& other){ x -= other.x; y -= other.y; return *this; }
        Point operator *(double k) const{ return { x * k, y * k }; }
        Point& operator *=(double k){ x *= k; y *= k; return *this; }
        Point operator /(double k) const{ return { x / k, y / k }; }
        Point& operator /=(double k){ x /= k; y /= k; return *this; }
        double length() const{ return sqrt(x * x + y * y); }
        double sqLength() const{ return x * x + y * y; }
        double dist(Point other) const{ double dx = x - other.x; double dy = y - other.y; return sqrt(dx * dx + dy * dy); }
        bool isZero(){ return (x == 0 && y == 0); }
        double dot(Point other) const{ return x * other.x + y * other.y; }
        double cross(Point other) const{ return x * other.y - y * other.x; }
        Point normalized() const{ return { x / length(), y / length() }; }
        Point normalUnitVector() const{ return { -normalized().y, normalized().x }; }
        Point rotation(double arg) const{ double cs = cos(arg), sn = sin(arg); return { x * cs - y * sn, x * sn + y * cs }; }
    };
    const Point error_val = {254183.0, -595361.0};
    double dot(Point a, Point b){ return a.x * b.x + a.y * b.y; }
    double cross(Point a, Point b){ return a.x * b.y - a.y * b.x; }
    int iSP(Point a, Point b, Point c){
        int flag = sgn((b - a).cross(c - a));
        if(flag == 1) return 1;
        else if(flag == -1) return -1;
        else{
            if(sgn((b - a).dot(c - b)) > 0) return 2;
            else if(sgn((a - b).dot(c - a)) > 0) return -2;
            else return 0;
        }
    }
    int angleType(Point a, Point b, Point c){
        double v = (a - b).dot(c - b);
        if(sgn(v) == 0) return 1;
        else return (sgn(v) > 0 ? 0 : 2);
    }
    struct Line{
        Point from, to;
        Line(Point from, Point to) : from(from), to(to) {} ;
        Point toVec() const{ return to - from; }
    };
    typedef Line Ray;
    typedef Line Segment;
    pair<bool, Point> lineIntersection(Line a, Line b){
        if(sgn(a.toVec().cross(b.toVec())) == 0) return { false, error_val };
        Point ret = a.from + b.toVec() * abs((b.to - a.from).cross(b.toVec()) / a.toVec().cross(b.toVec()));
        return { true, ret };
    }
    pair<bool, Point> segmentIntersection(Segment a, Segment b){
        if(iSP(a.from, a.to, b.from) * iSP(a.from, a.to, b.to) <= 0 && iSP(b.from, b.to, a.from) * iSP(b.from, b.to, a.to) <= 0){
            if(a.toVec().cross(b.toVec()) == 0) return { true, error_val };
            else return lineIntersection(a, b);
        }else return { false, error_val };
    }
    double dist(Point from, Point to){ double dx = to.x - from.x; double dy = to.y - from.y; return sqrt(dx * dx + dy * dy); }
    double distBetweenPointAndLine(Point p, Line l){ return abs(l.toVec().cross(p - l.from) / l.toVec().length()); }
    double distBetweenPointAndRay(Point p, Ray r){
        if(sgn((p - r.from).dot(r.toVec())) < 0) return r.from.dist(p);
        else return abs(r.toVec().cross(p - r.from) / r.toVec().length());
    }
    double distBetweenPointAndSegment(Point p, Segment s){
        if(sgn(s.toVec().dot(p - s.from)) < 0 || sgn((-s.toVec()).dot(p - s.to)) < 0) return min(p.dist(s.from), p.dist(s.to));
        else return distBetweenPointAndLine(p, s);
    }
    Point projection(Point a, Line l){
        Point ret = l.from + l.toVec().normalized() * (a - l.from).dot(l.toVec()) / l.toVec().length();
        return ret;
    }
    Point reflection(Point a, Line l){ Point ret = a + (projection(a, l) - a) * 2; return ret; }
}
using namespace geometry2d;