#include <bits/stdc++.h>

#define _   << ' ' <<
#define fst first
#define snd second
#define ASSERT_TL(cond) if (cond) { } else while (true) { }

using namespace std;

struct debug_t {
    template <typename T>
    debug_t& operator<<(const T& obj) {
#       ifdef LOCAL_DEBUG
            cout << obj << flush;
#       endif
        return *this;
    }

    debug_t& write(const char data[ ], size_t n) {
#       ifdef LOCAL_DEBUG
            cout.write(data, n);
            cout << flush;
#       endif
        return *this;
    }
} debug;

typedef unsigned char       uchar;
typedef basic_string<uchar> ustring;
typedef long long           llong;
typedef unsigned long long  ullong;
typedef long double         ldouble;

struct Ball {
    double x, y, r;

    Ball() { }
    Ball(double x, double y, double r): x(x), y(y), r(r) { }

    bool DoesOverlap(const Ball& another) const {
        double dx = x - another.x;
        double dy = y - another.y;
        return dx * dx + dy * dy < (r + another.r) * (r + another.r);
    }

    bool operator<(const Ball& rhs) const {
        return y < rhs.y;
    }
};

const double INITIAL_SPEED_COEFF = .9;
const double SPEED_REDUCTION_COEFF = .5;
const double ZERO = 4e-5;

int w;
vector<Ball> balls;

bool CanPlaceHere(const Ball& ball) {
    for (const auto& b: balls)
        if (ball.DoesOverlap(b))
            return false;
    return true;
}

bool TryMoveDown(Ball& ball, double speed) {
    assert(speed > ZERO);
    double prev = ball.y;
    ball.y -= speed;
    if (CanPlaceHere(ball))
        return true;
    ball.y = prev;
    return false;
}

bool TryMoveRight(Ball& ball, double speed) {
    assert(fabs(speed) > ZERO);
    double prev = ball.x;
    ball.x += speed;
    if (CanPlaceHere(ball))
        return true;
    ball.x = prev;
    return false;
}

bool TryMoveLeft(Ball& ball, double speed) {
    return TryMoveRight(ball, -speed);
}

Ball Drop(Ball ball) {
    auto initial = ball;
#   ifdef LOCAL_DEBUG
        cout << setprecision(5);
#   endif
    debug << "Dropping " << ball.x _ ball.y _ ball.r << "...\n";
    double speed = ball.r * INITIAL_SPEED_COEFF, prev, delta;
    Ball* obstacle;
    int count = 0;
    fall: while (speed > ZERO) {
        debug << ball.x _ ball.y << '\n';
        ASSERT_TL(ball.x - ball.r > -1e-6);
        ASSERT_TL(ball.x + ball.r < w + 1e-6);
        while (prev = ball.y, ball.y - speed > ball.r)
            if (!TryMoveDown(ball, speed)) {
                ball.y -= speed;
                goto bottomCollision;
            }
        ball.y = ball.r;
        if (CanPlaceHere(ball)) {
            //Roll to the left.
            while (speed > ZERO)
                if (!TryMoveLeft(ball, speed))
                    speed *= SPEED_REDUCTION_COEFF;
            break;
        }
    bottomCollision:
        obstacle = nullptr;
        for (auto& b: balls)
            if (ball.DoesOverlap(b)) {
                if (fabs(ball.x - b.x) <= 1e-6)
                    return initial;
                if (obstacle) {
                    speed *= SPEED_REDUCTION_COEFF;
                    count = 0;
                    ball.y = prev;
                    goto fall;
                }
                obstacle = &b;
            }
        ball.y = prev;
        assert(obstacle);
        delta = ball.x > obstacle->x ? speed : -speed;
        if (delta > .0) {
            delta = min(delta, w - (ball.x + ball.r));
            ASSERT_TL(delta >= -1e-6);
            if (delta <= ZERO) {
                speed *= SPEED_REDUCTION_COEFF;
                count = 0;
                continue;
            }
        } else {
            debug << delta _ ball.r _ ball.x _ speed << '\n';
            delta = max(delta, ball.r - ball.x);
            ASSERT_TL(delta <= 1e-6);
            if (delta >= -ZERO) {
                speed *= SPEED_REDUCTION_COEFF;
                count = 0;
                continue;
            }
        }
        if (count == 2 || !TryMoveRight(ball, delta)) {
            speed *= SPEED_REDUCTION_COEFF;
            count = 0;
        } else
            count++;
    }
    debug << "< " << ball.x _ ball.y _ ball.r << " (speed = " << speed << ")\n";
    return ball;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed;
    balls.reserve(10);
    while (cin >> w, w) {
        debug << "w = " << w << '\n';
        int n, d;
        cin >> n >> d;
        double r = d * .5, h = d;
        balls.clear();
        balls.emplace_back(r, r, r);//Bottom left.
        while (--n) {
            cin >> d;
            r = d * .5;
            double y = h + r + ZERO;
            auto cur = min(Drop( { r, y, r } ), Drop( { w - r, y, r } ));
            for (auto& b: balls) {
                if (b.x - ZERO >= r && b.x - ZERO <= w - r)
                    cur = min(cur, Drop( { b.x - ZERO, y, r } ));
                if (b.x + ZERO >= r && b.x + ZERO <= w - r)
                    cur = min(cur, Drop( { b.x + ZERO, y, r } ));
            }
            debug << "Taking " << cur.x _ cur.y _ cur.r << "\n\n";
            h = max(h, cur.y + cur.r);
            balls.push_back(cur);
        }
        cout << setprecision(2) << h << '\n';
        debug << '\n';
    }
}