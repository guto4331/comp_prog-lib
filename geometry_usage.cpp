namespace geometry2d{
    
    const double EPS = 1e-10;
    const double PI = 3.14159265359;
    double dtor(double d){ return d * PI / 180.0; }
    double rtod(double r){ return r * 180.0 / PI; }
	
    // a > 0 -> 1, a == 0 -> 0, a < 0 -> -1
    int sgn(const double a){
        if(abs(a) < EPS) return 0;
        else if(a < -EPS) return -1;
        else return 1;
    }
    
    struct Point{
        double x, y;
        
        Point(double x = 0.0, double y = 0.0) : x(x), y(y) {};
        
        bool operator ==(Point other) const{
            return (x == other.x && y == other.y);
        }
        
        bool operator <(Point other){
            if(sgn(x - other.x) == 0) return sgn(y - other.y) < 0;
            else return sgn(x - other.x) < 0;
        }
        
        bool operator <=(Point other){
            return (*this == other || *this < other);
        }
        
        bool operator >(Point other){
            return !(*this <= other);
        }
        
        bool operator >=(Point other){
            return !(*this < other);
        }
        
        bool operator !=(Point other) const{
            return !(*this == other);
        }
        
        Point operator +() const{
            return *this;
        }
        
        Point operator +(const Point& other) const{
            return { x + other.x, y + other.y };
        }
        
        Point& operator +=(const Point& other){
            x += other.x;
            y += other.x;
            return *this;
        }
        
        Point operator -() const{
            return { -x, -y };
        }
        
        Point operator -(const Point& other) const{
            return { x - other.x, y - other.y };
        }
        
        Point& operator -=(const Point& other){
            x -= other.x;
            y -= other.y;
            return *this;
        }
        
        Point operator *(double k) const{
            return { x * k, y * k };
        }
        
        Point& operator *=(double k){
            x *= k;
            y *= k;
            return *this;
        }
        
        Point operator /(double k) const{
            return { x / k, y / k };
        }
        
        Point& operator /=(double k){
            x /= k;
            y /= k;
            return *this;
        }
        
        double length() const{
            return sqrt(x * x + y * y);
        }
        
        double sqLength() const{
            return x * x + y * y;
        }
        
        double dist(Point other) const{
            double dx = x - other.x;
            double dy = y - other.y;
            return sqrt(dx * dx + dy * dy);
        }
        
        bool isZero(){
            return (x == 0 && y == 0);
        }
        
        //内積
        double dot(Point other) const{
            return x * other.x + y * other.y;
        }
        
        //外積
        double cross(Point other) const{
            return x * other.y - y * other.x;
        }
        
        //単位ベクトル
        Point normalized() const{
            return { x / length(), y / length() };
        }
        
        //法線ベクトルのうち、反時計回りの単位ベクトル
        Point normalUnitVector() const{
            return { -normalized().y, normalized().x };
        }
        
        //原点を中心として arg[rad] 度だけ回転移動した後の座標
        Point rotation(double arg) const{
            double cs = cos(arg), sn = sin(arg);
            return { x * cs - y * sn, x * sn + y * cs };
        }
    };
    ostream& operator<<(ostream& os, const Point& p){ os << p.x << " " << p.y; return os; }
    const Point error_val = {254183.0, -595361.0};
    
    // 内積
    double dot(Point a, Point b){
        return a.x * b.x + a.y * b.y;
    }
    // 外積
    double cross(Point a, Point b){
        return a.x * b.y - a.y * b.x;
    }
    
    // 3 点 A, B, C の位置関係を返す
    // ABから見てBCは左に曲がるのなら +1
    // ABから見てBCは右に曲がるのなら -1
    // ABCの順番で一直線上に並ぶなら +2
    // ACBの順番で一直線上に並ぶなら 0
    // BACの順番で一直線上に並ぶなら -2
    int iSP(const Point& a, const Point& b, const Point& c){
       	if(a == c || b == c) return 0;
		double crval = (b - a).cross(c - b);
        if(crval > 0) return 1;
        else if(crval < 0) return -1;
        else{
            if((a - b).dot(c - b) < 0) return 2;
            else if((a - c).dot(b - c) < 0) return 0;
            else return -2;
        }
    }
        
    // ∠ABC が鋭角なら 0, 直角なら 1, 鈍角なら 2, を返す
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
    
    struct Ray : Line{
        Ray(Point a, Point b) : Line(a, b) {}
    };
    struct Segment : Line{
        Segment(Point a, Point b) : Line(a, b) {}
    };
	
	// 2 直線が平行かどうか
	bool isParallel(Line a, Line b){
		return sgn(a.toVec().cross(b.toVec())) == 0;
	}
	// 垂直かどうか
    bool isOrthogonal(Line a, Line b){
		return sgn(a.toVec().dot(b.toVec())) == 0;
	}
    
    // 2 直線が (< 交点を持つか >, < 座標 > )
    pair<bool, Point> lineIntersection(Line a, Line b){
        if(isParallel(a, b)) return { false, error_val };
        Point ret = b.from + b.toVec() * (a.toVec().cross(a.to - b.from) / a.toVec().cross(b.toVec()));
        return { true, ret };
    }
    // 2 線分が (< 交点を持つか >, < 座標 > )
    pair<bool, Point> segmentIntersection(Segment a, Segment b){
        if(iSP(a.from, a.to, b.from) * iSP(a.from, a.to, b.to) <= 0 && iSP(b.from, b.to, a.from) * iSP(b.from, b.to, a.to) <= 0){
            if(isParallel(a, b)) return { true, error_val };
            else return lineIntersection(a, b);
        }else return { false, error_val };
    }
	
	// 点 a から直線 l に下ろした垂線の足の座標(正射影)
    Point projection(Point a, Line l){
        Point ret = l.from + l.toVec().normalized() * (a - l.from).dot(l.toVec()) / l.toVec().length();
        return ret;
    }
	// 直線 l に対して、点 a と対称な点の座標
    Point reflection(Point a, Line l){
		Point ret = a + (projection(a, l) - a) * 2; return ret;
	}
    
    double dist(Point from, Point to){
    	return sqrt(pow(to.x - from.x, 2) + pow(to.y - from.y, 2));
    }
    double dist(Point p, Line l){
    	return dist(p, projection(p, l));
    }
    double dist(Point p, Ray r){
        if(sgn(r.toVec().dot(p - r.from)) < 0) return dist(p, r.from);
        return dist(p, Line(r));
    }
    double dist(Point p, Segment s){
        if(sgn(s.toVec().dot(p - s.from)) < 0 || sgn((-s.toVec()).dot(p - s.to)) < 0) return min(dist(p, s.from), dist(p, s.to));
        return dist(p, Line(s));
    }
}
using namespace geometry2d;
