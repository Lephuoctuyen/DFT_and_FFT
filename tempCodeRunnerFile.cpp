#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

using namespace std;

vector<complex<float>> fft(const vector<complex<float>>& vIn, int lenFFT) {
    static vector<complex<float>> w; // Twiddle factors
    static int mstore = 0;           // Stored FFT length
    static int n = 1;                // 2^lenFFT

    if (vIn.empty()) {
        mstore = 0;
        n = 1;
        return vIn;
    }

    int length = vIn.size();
    if (length != (1 << lenFFT)) {
        throw runtime_error("Input size must be a power of two.");
    }

    vector<complex<float>> vOut = vIn;

    if (lenFFT != mstore) {
        mstore = lenFFT;
        n = 1 << lenFFT;
        int le = n / 2;

        w.resize(le - 1);
        for (int j = 0; j < le - 1; j++) {
            w[j] = polar(1.0f, static_cast<float>(-2.0 * M_PI * j / n));
        }
    }

    int le = n;
    int windex = 1;

    for (int l = 0; l < lenFFT; l++) {
        le /= 2;

        // First loop without twiddle factors
        for (int i = 0; i < n; i += 2 * le) {
            auto temp = vOut[i] + vOut[i + le];
            vOut[i + le] = vOut[i] - vOut[i + le];
            vOut[i] = temp;
        }

        int wptr = windex - 1;

        // Subsequent loops with twiddle factors
        for (int j = 1; j < le; j++) {
            auto u = w[wptr];
            for (int i = j; i < n; i += 2 * le) {
                auto temp = vOut[i] + vOut[i + le];
                auto tm = vOut[i] - vOut[i + le];
                vOut[i + le] = u * tm;
                vOut[i] = temp;
            }
            wptr += windex;
        }

        windex *= 2;
    }

    // Bit-reversal permutation
    int j = 0;
    for (int i = 1; i < (n - 1); i++) {
        int k = n / 2;
        while (k <= j) {
            j -= k;
            k /= 2;
        }
        j += k;

        if (i < j) {
            swap(vOut[i], vOut[j]);
        }
    }

    return vOut;
}

int main() {
    vector<complex<float>> input = {1.0, 2.0, 3.0, 4.0};
    int lenFFT = log2(input.size());

    try {
        vector<complex<float>> output = fft(input, lenFFT);
        for (const auto& val : output) {
            cout << val << " ";
        }
        cout << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
