# 📘 Discrete Fourier Transform (DFT) và Fast Fourier Transform (FFT)

## Định nghĩa DFT

Cho dãy tín hiệu rời rạc \( x[n] \) với \( n = 0, 1, \ldots, N-1 \), DFT được định nghĩa là:

\[
X[k] = \sum_{n=0}^{N-1} x[n] \cdot e^{-j\frac{2\pi}{N}kn}, \quad k = 0, 1, \ldots, N-1
\]

Trong đó:
- \( X[k] \) là hệ số phổ tần số tại chỉ số \( k \),
- \( e^{-j\frac{2\pi}{N}kn} \) là nhân tử cơ bản phức (Euler),
- \( N \) là số điểm DFT.

---

## DFT ngược (IDFT)

\[
x[n] = \frac{1}{N} \sum_{k=0}^{N-1} X[k] \cdot e^{j\frac{2\pi}{N}kn}, \quad n = 0, 1, \ldots, N-1
\]

---

## Nhân tử cơ bản (Twiddle factor)

\[
W_N = e^{-j\frac{2\pi}{N}}, \quad \text{và} \quad W_N^{kn} = e^{-j\frac{2\pi}{N}kn}
\]

---

# ⚡ Fast Fourier Transform (FFT)

## Ý tưởng cơ bản

FFT là cách tính DFT hiệu quả hơn bằng cách:
- Tách tín hiệu đầu vào thành **phần chẵn** và **phần lẻ**,
- Áp dụng đệ quy để tính DFT nhỏ hơn,
- Giảm độ phức tạp từ \( \mathcal{O}(N^2) \) xuống \( \mathcal{O}(N \log N) \).

---

## Biểu thức Radix-2 FFT (Cooley-Tukey)

\[
X[k] = X_{\text{even}}[k] + W_N^k \cdot X_{\text{odd}}[k]
\]

\[
X[k + N/2] = X_{\text{even}}[k] - W_N^k \cdot X_{\text{odd}}[k], \quad k = 0, 1, \ldots, \frac{N}{2}-1
\]

Trong đó:
- \( X_{\text{even}}[k] \) là FFT của các mẫu chẵn \( x[0], x[2], \ldots \),
- \( X_{\text{odd}}[k] \) là FFT của các mẫu lẻ \( x[1], x[3], \ldots \),
- \( W_N^k = e^{-j\frac{2\pi}{N}k} \)

---

# 🧠 Một số tính chất quan trọng

- **Tính tuần hoàn**:  
  \[
  X[k+N] = X[k]
  \]

- **Tính tuyến tính**:  
  Nếu \( y[n] = a \cdot x_1[n] + b \cdot x_2[n] \), thì  
  \[
  Y[k] = a \cdot X_1[k] + b \cdot X_2[k]
  \]

- **Biến đổi trượt thời gian**:  
  Nếu \( y[n] = x[(n - n_0) \mod N] \), thì  
  \[
  Y[k] = X[k] \cdot e^{-j\frac{2\pi}{N}k n_0}
  \]

- **Biến đổi nhân thời gian** (Windowing):  
  \[
  x[n] \cdot w[n] \xrightarrow{\text{DFT}} X[k] * W[k] \quad \text{(tích chập tuần hoàn)}
  \]
