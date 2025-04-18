#include<iostream>
#include<vector>
#include<complex>

std::vector<std::complex<double>> fft(std::vector<std::complex<double>> &in, int lenFFT) {
    static std::vector<std::complex<double>> w; // Twiddle Factors
    static int mstore = 0; // Store the length of the FFT
    static int n = 1; // 2^lenFFT
    if(in.empty()){
        mstore =0;
        n = 1;
        return in;
    }
    int length = in.size();
    if (lenFFT != log2(length)) { // FFT radix-2 chỉ hoạt động với các chuỗi có độ dài là lũy thừa của 2 
        // Trong hầu hết các trường hợp, người ta có thể điều chỉnh độ dài này bằng cách chọn cửa sổ thời gian quan sát dữ liệu hoặc tần số lấy mẫu, hoặc bằng cách đệm thêm các giá trị 0 vào chuỗi ngắn hơn để đạt được độ dài yêu cầu
        throw std::runtime_error("FFT length must be a power of two and match the input size.");
    }
    std::vector<std::complex<double>> vOut = in; // Kết quả đầu ra của FFT
    if(lenFFT != mstore){
        mstore = lenFFT;
        n = 1 << lenFFT;
        int le = n / 2;
        w.resize(le - 1);
        double arg = 4.0 * atan(1.0) / le; // Tính toán các yếu tố quay π / le
        double wrecurReal = cos(arg);
        double wReal = wrecurReal;
        double wrecurImag = -sin(arg);
        double wImag = wrecurImag;
        for(int j = 0; j < le - 1; j++) {
            w[j] = std::complex<double>(wrecurReal, wrecurImag); // Lưu trữ các yếu tố quay vào mảng w
            double wtempReal = wrecurReal * wReal - wrecurImag * wImag;
            wrecurImag = wrecurReal * wImag + wrecurImag * wReal;
            wrecurReal = wtempReal;
        }
        
    }
}

#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
using namespace std;

vector<complex<float>> fft(const vector<complex<float>>& vIn, int lenFFT) {
    static vector<complex<float>> w;
    static int mstore = 0;
    static int n = 1;

    if (vIn.empty()) {
        mstore = 0;
        n = 1;
        return vIn;
    }

    int length = vIn.size();
        if (lenFFT != log2(length)) {
                throw runtime_error("FFT length must be a power of two and match the input size.");
        }
    vector<complex<float>> vOut = vIn;

    if (lenFFT != mstore) {
        mstore = lenFFT;

        n = 1 << lenFFT;
        int le = n / 2; // N/2 -1

        w.resize(le - 1);

        double arg = 4.0 * atan(1.0) / le;
        double wrecurReal = cos(arg);
        double wReal = wrecurReal;
        double wrecurImag = -sin(arg);
        double wImag = wrecurImag;

        for (int j = 0; j < le - 1; j++) {
            w[j] = polar(1.0f, static_cast<float>(-2.0 * M_PI * j / n));
        }
        // used polar(1.0, -2 * M_PI * k / n) to calculate the twiddle factors
        // w[j] = polar(1.0, -2 * M_PI * j / n); // Lưu trữ các yếu tố quay vào mảng w
        }

        int le = n;
        int windex = 1;
        complex<float> u, tm, temp;

        for (int l = 0; l < lenFFT; l++) { 
            le = le / 2;
            // // Lặp lại đầu tiên không có bội số
            for (int i = 0; i < n; i = i + 2 * le) {
                    temp = vOut[i] + vOut[i + le];
                    vOut[i + le] = vOut[i] - vOut[i + le]; // k + n/2
                    vOut[i] = temp; // k
            }

            int wptr = windex - 1;
            //  Các lần lặp lại sử dụng được lưu trữ W
            for (int j = 1; j < le; j++) {
                u = w[wptr];
                for (int i = j; i < n; i = i + 2 * le) {
                    temp = vOut[i] + vOut[i + le];
                    tm = vOut[i] - vOut[i + le];
                    vOut[i + le] = u*tm ;
                    vOut[i] = temp;
                }

                wptr += windex;
            }

            windex *= 2;
        }   

        int j = 0;
        for (int i = 1; i < (n - 1); i++) {
            int k = n / 2;
            while (k <= j) {
                j = j - k;
                k = k / 2;
            }

            j = j + k;

            if (i < j) {
                temp = vOut[j];
                vOut[j] = vOut[i];
                vOut[i] = temp;
            }
        }

        return vOut;
}

int main(){
        vector<complex<float>> input = {1.0, 2.0, 3.0, 4.0};
        int lenFFT = 2; 
        vector<complex<float>> output = fft(input, lenFFT);
        int a = 1 >> lenFFT;
        cout << a << endl;
        for (const auto& val : output) {
                cout << val << " ";
        }
        cout << endl;
        
        return 0;
}