#include <iostream>
#include <vector>
using namespace std;

const int mod = 7340033;
const int root = 5;
const int root_1 = 4404020;
const int root_pw = 1 << 20;

// Hàm tính nghịch đảo modulo
int inverse(int x, int m) {
    int result = 1;
    int power = m - 2;
    while (power > 0) {
        if (power & 1) {
            result = (int)(1LL * result * x % m);
        }
        x = (int)(1LL * x * x % m);
        power >>= 1;
    }
    return result;
}

// Hàm thực hiện FFT
void fft(vector<int> & a, bool invert) {
    int n = a.size();

    // Thực hiện phép hoán vị bit (bit-reversal)
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    // Tiến hành phép biến đổi FFT
    for (int len = 2; len <= n; len <<= 1) {
        int wlen = invert ? root_1 : root;
        for (int i = len; i < root_pw; i <<= 1)
            wlen = (int)(1LL * wlen * wlen % mod);

        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < len / 2; j++) {
                int u = a[i + j], v = (int)(1LL * a[i + j + len / 2] * w % mod);
                a[i + j] = u + v < mod ? u + v : u + v - mod;
                a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + mod;
                w = (int)(1LL * w * wlen % mod);
            }
        }
    }

    // Nghịch đảo khi cần thiết
    if (invert) {
        int n_1 = inverse(n, mod);
        for (int & x : a)
            x = (int)(1LL * x * n_1 % mod);
    }
}

int main() {
    // Test Case 1: Simple FFT and Inverse FFT
    vector<int> a = {1, 2, 3, 4};

    // Kiểm tra nếu kích thước mảng không phải là lũy thừa của 2
    int n = a.size();
    int size = 1;
    while (size < n) size <<= 1;  // Tìm lũy thừa gần nhất của 2
    a.resize(size, 0);  // Padding 0 nếu cần thiết

    // Forward FFT
    vector<int> fft_result = a;
    fft(fft_result, false);

    // In ra kết quả FFT
    cout << "FFT result: ";
    for (int x : fft_result) {
        cout << x << " ";
    }
    cout << endl;

    // Inverse FFT
    vector<int> ifft_result = fft_result;
    fft(ifft_result, true);

    // In ra kết quả Inverse FFT
    cout << "Inverse FFT result: ";
    for (int x : ifft_result) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
