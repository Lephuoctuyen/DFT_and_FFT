#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

using namespace std;

// Biến đổi FFT (Forward) hoặc IFFT (Inverse) tuỳ theo flag `invert`
void fft(vector<complex<double>>& a, bool invert) {
    int n = a.size();

    // Bit-reversal reordering
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if (i < j)
            swap(a[i], a[j]);
    }

    // Butterfly operation
    for (int len = 2; len <= n; len <<= 1) {
        double angle = 2 * M_PI / len * (invert ? 1 : -1);
        complex<double> wn(cos(angle), sin(angle));

        for (int i = 0; i < n; i += len) {
            complex<double> w(1);
            for (int j = 0; j < len / 2; j++) {
                complex<double> u = a[i + j];
                complex<double> v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wn;
            }
        }
    }

    // Nếu là IFFT, chia cho n để khôi phục biên độ
    if (invert) {
        for (auto &x : a)
            x /= n;
    }
}

int main() {
    vector<complex<double>> a = {1, 2, 3, 4, 4, 3, 2, 1};

    cout << "Input:\n";
    for (auto x : a) cout << x << " ";
    cout << "\n";

    fft(a, false);  // FFT thuận
    cout << "\nFFT:\n";
    for (auto x : a) cout << x << " ";
    cout << "\n";

    fft(a, true);   // FFT nghịch đảo
    cout << "\nInverse FFT:\n";
    for (auto x : a) cout << x << " ";
    cout << "\n";

    return 0;
}
