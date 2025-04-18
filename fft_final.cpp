#include<iostream>
#include<vector>
#include<complex>


std::vector<std::complex<double>> fft(const std::vector<std::complex<double>>&a, bool invert){
    int a = static_cast<int>(a.size()); // use static_case because a.size()is 64 bit but int is 32 bit
    
    // Bit-reversal reordering 
    /*
    Bit-reversal reodering help to rearrage the input data in FFT algorithm. 
    Because 
    */
}