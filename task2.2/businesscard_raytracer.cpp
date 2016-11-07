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

constexpr int imageSize = 512;
constexpr int width = 14;
constexpr int height = 6;
// int representation
constexpr int G[] = {8853, 8853, 8946, 10898, 13973, 8805};
// bit representation
//constexpr bool image[height][width] = {
//        {1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1},
//        {1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1},
//        {1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0},
//        {1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0},
//        {1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1},
//        {1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1}
//};


float get_random() {
    return (float) rand() / RAND_MAX;
}

int Tracer(vector vecO, vector vecD, float &t, vector &vecN) {
    t = 1e9;
    int result = 0;

    float p = -vecO.z / vecD.z;
    if (.01 < p) {
        t = p;
        vecN = vector(0, 0, 1);
        result = 1;
    }

    for (int k = width - 1; k >= 0; --k) {
        for (int j = height - 1; j >= 0; --j) {

            // TODO: access image matrix instead
            if (G[j] & 1 << k) {

                vector vecP = vecO + vector(-k, 0, -j - 4);

                float b = vecP % vecD;
                float c = vecP % vecP - 1;
                float q = b * b - c;

                if (q > 0) {
                    float s = -b - sqrt(q);

                    if (s < t && s > .01) {
                        t = s;
                        vecN = !(vecP + vecD * t);
                        result = 2;
                    }
                }
            }
        }
    }

    return result;
}

vector Sampler(vector vecA, vector vecB) {
    float t;
    vector vecC;
    int m = Tracer(vecA, vecB, t, vecC);

    if (!m) {
        return vector(.7, .6, 1) * pow(1 - vecB.z, 4);
    }

    vector vecD = vecA + vecB * t;
    vector vecE = !(vector(9 + get_random(), 9 + get_random(), 16) + vecD * -1);
    vector vecF = vecB + vecC * (vecC % vecB * -2);
    float b = vecE % vecC;

    if (b < 0 || Tracer(vecD, vecE, t, vecC)) {
        b = 0;
    }

    float p = pow(vecE % vecF * (b > 0), 99);
    if (m & 1) {
        vecD = vecD * .2;

        vector vecResult;
        if ((int) (ceil(vecD.x) + ceil(vecD.y)) & 1) {
            vecResult = vector(3, 1, 1);
        } else {
            vecResult = vector(3, 3, 3);
        }
        return vecResult * (b * .2 + .1);
    }
    return vector(p, p, p) + Sampler(vecD, vecF) * 0.5;
}


int main(int argc, char *argv[]) {
    // header
    printf("P6 512 512 255 "); // TODO: use image size variable

    vector vecH = !vector(-6, -16, 0);
    vector vecI = !(vector(0, 0, 1) ^ vecH) * .002;
    vector vecJ = !(vecH ^ vecI) * .002;
    vector vecK = (vecI + vecJ) * -256 + vecH;

    for (int y = imageSize; y--;) {
        for (int x = imageSize; x--;) {

            vector vecResult = vector(13, 13, 13);

            for (int r = 64; r--;) {
                vector vecM = vecI * (get_random() - 0.5) * 99 + vecJ * (get_random() - 0.5) * 99;
                vector vecN = vector(17, 16, 8) + vecM;
                vector vecO = !(vecM * -1 + (vecI * (get_random() + x) + vecJ * (y + get_random()) + vecK) * 16);
                vecResult = Sampler(vecN, vecO) * 3.5 + vecResult;
            }

            printf("%c%c%c", (int) vecResult.x, (int) vecResult.y, (int) vecResult.z);
        }
    }
}