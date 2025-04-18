#include<vector>
#include<complex>
#include<cmath>
#include<iostream>
#include<algorithm>

// dft convert time domain to frequency domain standard DFT (Discrete Fourier Transform)
std::vector<std::complex<double>> dft(const std::vector<std::complex<double>>& in){
    int length = static_cast<int>(in.size()); // used static case to avoid error range. Because size_t (in.size) very large, while int is smaller than size_t (int with 32 bit, size_t with 64 bit)
    if(length == 0) return in; // input is digital zero, return vector zero

    const double PI = std::acos(-1); // PI constant security, clear, beautifull, standard C++ modern
    std::vector<std::complex<double>> out(length); // initialization output vector same size with input vector
    for(size_t k = 0; k < length; ++k){
        out[k] = 0;
        for(size_t n = 0; n < length; ++n){
            double angle = 2 * PI * k * n/ length;
            out[k] += in[n] * std::polar(1.0, -angle); // polar form of complex number polar real and polar imaginary real = rho * cos(theta); imag = rho * sin(theta); is euler formula   
        }
    }
    return out; // return output vector
}

std::vector<std::complex<double>> idft(const std::vector<std::complex<double>>& in){
    int length = static_cast<int>(in.size());
    if(length == 0) return in; // input is digital zero, return vector zero
    
    const double PI = std::acos(-1); // PI constant security, clear, beautifull, standard C++ modern
    std::vector<std::complex<double>> out(length); // initialization output vector same size with input vector
    for(size_t n = 0; n < length; ++n){
        out[n] = 0;
        for(size_t k = 0; k < length; ++k){
            double angle = 2 * PI * k * n/ length;
            out[n] += in[k] * std::polar(1.0, angle); // polar form of complex number polar real and polar imaginary real = rho * cos(theta); imag = rho * sin(theta); is euler formula 
        }
        out[n] /= length; 
    }
    return out;
}

int main(){
    std::vector<std::complex<double>> input = {1.0, 2.0, 3.0, 4.0}; // input vector
    std::vector<std::complex<double>> output = dft(input); // call dft function to convert time domain to frequency domain
    std::cout << "DFT Output:" << std::endl;
    for(const auto& val : output){
        std::cout << val << std::endl; // print output vector
    }
    std::vector<std::complex<double>> idft_output = idft(output); // call idft function to convert frequency domain to time domain
    std::cout << "IDFT Output:" << std::endl;
    for(const auto& val : idft_output){
        std::cout << val << std::endl; // print output vector
    }
    return 0;
}