#include <stdlib.h>
#include <stdio.h>
#include <math.h>


struct vector {
    float x, y, z;

    vector() {}

    vector(float a, float b, float c) {
        x = a;
        y = b;
        z = c;
    }

    // Sum of two vectors
    vector operator+(vector r) {
        return vector(x + r.x, y + r.y, z + r.z);
    }

    // Change vector length
    vector operator*(float r) {
        return vector(x * r, y * r, z * r);
    }


    // TODO: these operators may not be used in their original usage, find named functions for them
    // some kind of distance https://en.wikipedia.org/wiki/Dot_product
    float operator%(vector r) {
        return x * r.x + y * r.y + z * r.z;
    }

    // ?
    vector operator^(vector r) {
        return vector(y * r.z - z * r.y, z * r.x - x * r.z, x * r.y - y * r.x);
    }

    // ?
    vector operator!() {
        return *this * (1 / sqrt(*this % *this));
    }
};


constexpr int width = 14;
constexpr int height = 6;
// int representation
constexpr int G[] = {8853, 8853, 8946, 10898, 13973, 8805};
// bit representation
constexpr bool image[height][width] = {
        {1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1},
        {1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0},
        {1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0},
        {1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1}
};


float get_random() {
    return (float) rand() / RAND_MAX;
}

int Tracer(vector o, vector d, float &t, vector &n) {
    t = 1e9;
    int m = 0;
    float p = -o.z / d.z;

    if (.01 < p) {
        t = p, n = vector(0, 0, 1), m = 1;
    }


    for (int k = width; k--;) {
        for (int j = height; j--;) {
            if (G[j] & 1 << k) {

                vector p = o + vector(-k, 0, -j - 4);
                float b = p % d;
                float c = p % p - 1;
                float q = b * b - c;

                if (q > 0) {
                    float s = -b - sqrt(q);
                    if (s < t && s > .01) {
                        t = s;
                        n = !(p + d * t);
                        m = 2;
                    }
                }
            }
        }
    }

    return m;
}

vector Sampler(vector o, vector d) {
    float t;
    vector n;
    int m = Tracer(o, d, t, n);

    if (!m) {
        return vector(.7, .6, 1) * pow(1 - d.z, 4);
    }

    vector h = o + d * t;
    vector l = !(vector(9 + get_random(), 9 + get_random(), 16) + h * -1);
    vector r = d + n * (n % d * -2);
    float b = l % n;

    if (b < 0 || Tracer(h, l, t, n)) {
        b = 0;
    }

    float p = pow(l % r * (b > 0), 99);
    if (m & 1) {
        h = h * .2;
        return ((int) (ceil(h.x) + ceil(h.y)) & 1 ? vector(3, 1, 1) : vector(3, 3, 3)) * (b * .2 + .1);
    }
    return vector(p, p, p) + Sampler(h, r) * .5;
}


int main(int argc, char *argv[]) {
    // header
    printf("P6 512 512 255 ");

    vector g = !vector(-6, -16, 0);
    vector a = !(vector(0, 0, 1) ^ g) * .002;
    vector b = !(g ^ a) * .002, c = (a + b) * -256 + g;

    for (int y = 512; y--;) {
        for (int x = 512; x--;) {

            vector p(13, 13, 13);

            for (int r = 64; r--;) {
                vector t = a * (get_random() - .5) * 99 + b * (get_random() - .5) * 99;
                p = Sampler(vector(17, 16, 8) + t,
                            !(t * -1 + (a * (get_random() + x) + b * (y + get_random()) + c) * 16)) * 3.5 + p;
            }

            printf("%c%c%c", (int) p.x, (int) p.y, (int) p.z);
        }
    }
}