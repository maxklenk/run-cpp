#include <stdlib.h>
#include <stdio.h>
#include <math.h>

constexpr int imageSize = 512;

constexpr int width = 14;
constexpr int height = 6;

constexpr int spaceBottom = 5;
constexpr int spaceRight = 3;
constexpr int spaceFront = 0;

constexpr bool image[height][width] = {
        {1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1},
        {1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0},
        {1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0},
        {1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1}
};

struct vector {
    float x, y, z;

    vector() {}

    vector(float a, float b, float c) {
        x = a;
        y = b;
        z = c;
    }


    // Change vector length
    vector operator*(float r) {
        return vector(x * r, y * r, z * r);
    }

    // Sum of two vectors
    vector combine(vector r) {
        return vector(x + r.x, y + r.y, z + r.z);
    }

    // Dot Product: https://en.wikipedia.org/wiki/Dot_product
    float dotProduct(vector r) {
        return x * r.x + y * r.y + z * r.z;
    }

    // Cross product
    vector crossProduct(vector r) {
        return vector(y * r.z - z * r.y, z * r.x - x * r.z, x * r.y - y * r.x);
    }

    // Normalize
    vector normalize() {
        return *this * (float) (1 / sqrt((*this).dotProduct(*this)));
    }

};

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

            if (image[height - j - 1][width - k - 1]) {

                vector vecX = vector((float) -k - spaceRight, (float) spaceFront, (float) -j - spaceBottom);
                vector vecP = vecO.combine(vecX);

                float b = vecP.dotProduct(vecD);
                float c = vecP.dotProduct(vecP) - 1;
                float q = b * b - c;

                if (q > 0) {
                    float s = (float) (-b - sqrt(q));

                    if (s < t && s > .01) {
                        t = s;
                        vecN = vecP.combine(vecD * t).normalize();
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
        return vector(0.7f, 0.6f, 1.0f) * (float) pow(1 - vecB.z, 4);
    }

    vector vecD = vecA.combine(vecB * t);
    vector vecE = vector(9 + get_random(), 9 + get_random(), 16).combine(vecD * -1).normalize();
    vector vecF = vecB.combine(vecC * (vecC.dotProduct(vecB) * -2));
    float b = vecE.dotProduct(vecC);

    if (b < 0 || Tracer(vecD, vecE, t, vecC)) {
        b = 0;
    }

    float p = (float) pow(vecE.dotProduct(vecF) * (float) (b > 0), 99);
    if (m & 1) {
        vecD = vecD * 0.2f;

        vector vecResult;
        if ((int) (ceil(vecD.x) + ceil(vecD.y)) & 1) {
            vecResult = vector(3, 1, 1);
        } else {
            vecResult = vector(3, 3, 3);
        }
        return vecResult * (b * 0.2f + 0.1f);
    }
    return vector(p, p, p).combine(Sampler(vecD, vecF) * 0.5);
}


int main(int argc, char *argv[]) {
    // header
    printf("P6 %i %i 255 ", imageSize, imageSize);

    // initialization
    vector vecH = vector(-6, -16, 0).normalize();
    vector vecI = vector(0, 0, 1).crossProduct(vecH).normalize() * 0.002f;
    vector vecJ = vecH.crossProduct(vecI).normalize() * 0.002f;
    vector vecK = vecH.combine(vecI.combine(vecJ) * -256);
    vector vecX = vector(17, 16, 8);

    // paint each pixel
    for (int y = imageSize; y--;) {
        for (int x = imageSize; x--;) {

            vector vecResult = vector(13, 13, 13);

            for (int r = 64; r--;) {
                vector vecA = vecI * (float) 99 * (get_random() - 0.5);
                vector vecB = vecJ * (float) 99 * (get_random() - 0.5);
                vector vecM = vecA.combine(vecB);
                vector vecN = vecX.combine(vecM);
                vector vecC = vecK.combine(vecJ * (y + get_random())).combine(vecI * (get_random() + x));
                vector vecO = (vecM * -1).combine(vecC * 16).normalize();
                vecResult = vecResult.combine(Sampler(vecN, vecO) * 3.5f);
            }

            printf("%c%c%c", (int) vecResult.x, (int) vecResult.y, (int) vecResult.z);
        }
    }
}