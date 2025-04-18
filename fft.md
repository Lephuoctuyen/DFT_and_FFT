https://www.sanfoundry.com/cpp-program-compute-discrete-fourier-transform-using-fast-fourier-transform-approach/
https://leetcode.com/problems/multiply-strings/solutions/2053278/fft-and-ntt-solutions/

https://cp-algorithms.com/algebra/fft.html#discrete-fourier-transform

fft là kỹ thuật cốt lõi biến tín hiệu ở miền thời gian sang miền tần số
Chắc chắn rồi! Dưới đây là ví dụ minh họa cho đoạn:

> “Ngoài ra, do tích của hai đa thức bậc \(n\) là một đa thức bậc \(2(n−1)\), ta cần nhân đôi bậc của mỗi đa thức (một lần nữa bằng cách thêm các số 0). Từ một vector có \(n\) giá trị, ta không thể khôi phục được đa thức mong muốn bậc \(2n−1\) với đầy đủ các hệ số.”

---

### 🔢 **Ví dụ minh họa:**

Giả sử ta có hai đa thức bậc 2 (tức \(n = 3\), vì đa thức bậc 2 có 3 hệ số):

\[
A(x) = 1 + 2x + 3x^2
\]
\[
B(x) = 4 + 5x + 6x^2
\]

### 🎯 Mục tiêu:
Tính tích \(C(x) = A(x) \cdot B(x)\)

Tích này là một đa thức bậc 4 (vì bậc tối đa là \(2 + 2 = 4\)), tức cần **5 hệ số**.

---

### ❌ Nếu ta DFT với 3 điểm (n = 3):

- Khi đó, DFT(A) và DFT(B) có 3 giá trị.
- Tích từng phần tử rồi dùng Inverse DFT cũng chỉ cho ra 3 hệ số → không đủ để khôi phục đầy đủ \(C(x)\), vì nó có tới **5 hệ số**.

→ **Không thể khôi phục đa thức bậc 4 chỉ từ 3 điểm!**

---

### ✅ Giải pháp đúng: Zero-padding

Để đủ số điểm:

- Ta **padding 0** để biến \(A(x)\) và \(B(x)\) thành đa thức bậc 4 (5 hệ số):

\[
A'(x) = 1 + 2x + 3x^2 + 0x^3 + 0x^4
\]
\[
B'(x) = 4 + 5x + 6x^2 + 0x^3 + 0x^4
\]

- Giờ DFT với **5 điểm (n = 5)**.
- Tính DFT(A'), DFT(B'), nhân từng phần tử, rồi Inverse DFT → thu được đủ **5 hệ số** của đa thức tích \(C(x)\).

---

### ✅ Kết quả đúng:

Tích \(A(x) \cdot B(x)\):

\[
C(x) = 4 + 13x + 28x^2 + 27x^3 + 18x^4
\]

---

### 💡 Tổng kết:

- Nếu không zero-pad → **không đủ điểm** để khôi phục đa thức tích đúng.
- Với DFT, để nhân đa thức bậc \(n-1\), ta cần DFT độ dài ít nhất \(2n - 1\), nên ta zero-pad lên **độ dài \(2n\)** cho an toàn (do DFT thường dùng độ dài là luỹ thừa của 2).

---

Nếu bạn muốn mình làm ví dụ này bằng Python hoặc minh họa bằng biểu đồ DFT mình cũng có thể giúp nhé!