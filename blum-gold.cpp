#include <iostream>
#include <math.h>
#include <vector>
#include <bitset>
#include <cassert>

using namespace std;

void ext_gcd(int a, int b, int *c, int *d)
{
    int m = a, n = b;
    int xm = 1, ym = 0;
    int xn = 0, yn = 1; /////////////////////////////extended_euclidean
    int q, r, xr, yr;
    while (n != 0)
    {
        q = m / n;
        r = m % n;
        xr = xm - q * xn;
        yr = ym - q * yn;
        m = n;
        xm = xn;
        ym = yn;
        n = r;
        xn = xr;
        yn = yr;
    }
    *c = xm;
    *d = ym;
}

bool isPrime(int x)
{
    if (x >= 2)
    {
        for (int i = 2; i <= sqrt(x); i++) //////check so nguyen to
        {
            if (x % i == 0)
            {
                return false;
            }
        }
        return true;
    }
    return false;
}
bool isBinary(const string &str)
{
    for (char c : str)
    {
        if (c != '0' && c != '1')
            return false;
    }
    return true;
}
void strtobit(string m, string *m1)
{
    if (isBinary(m))
    {
        *m1 = m; // Input is already a binary string
    }
    else
    {
        string a = "";
        for (char c : m)
        {
            bitset<8> bits(c);
            *m1 += bits.to_string();
        }
    }
}

string bitToStr(const string &bits_string)
{
    string result;

    for (size_t i = 0; i < bits_string.length(); i += 8)
    {
        string byte = bits_string.substr(i, 8);
        char character = static_cast<char>(bitset<8>(byte).to_ulong());
        result += character;
    }

    return result;
}

int bbs(long long x0, int p, int q)
{
    long long N = p * q;
    x0 = (x0 * x0) % N;
    return x0;
}
void BSSgeberate(int x0, int h, int l, int p, int q, string *b, int *x_end, int *i)
{
    long long current_X = x0;

    while (l > 0)
    {
        current_X = bbs(current_X, p, q);
        cout << "x" << (*i)++ << " : " << current_X << "    ||    ";
        string bitX = bitset<8>(current_X).to_string();
        cout << "To bits : " << bitX << "    ||    ";
        string least_bits = bitX.substr(bitX.size() - h); /// size 8-3 =5, substr = 8 -5 =3. lays 3 bit phai
        cout << "Least bits : " << least_bits << endl;
        *b += least_bits;

        l -= h;

        if (l < h && l != 0) // xu ly khoi bit cuoi
        {
            current_X = bbs(current_X, p, q);
            cout << "x" << (*i)++ << " : " << current_X << "    ||    ";
            string bitX = bitset<8>(current_X).to_string();
            cout << "To bits : " << bitX << "    ||    ";
            string least_bits = bitX.substr(bitX.size() - l);
            cout << "Least bits : " << least_bits << endl;

            *b += least_bits;
            *x_end = bbs(current_X, p, q);
            cout << "x" << *i << " : " << *x_end << endl
                 << endl;

            break;
        }
        if (l == 0)
        {
            *x_end = bbs(current_X, p, q);
            cout << "x" << *i << " : " << *x_end << endl
                 << endl;

            break;
        }
    }
}

int phi(int n)
{
    int result = n;
    for (int p = 2; p * p <= n; ++p)
    {
        if (n % p == 0)
        {
            while (n % p == 0)
                n /= p;
            result -= result / p;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

int power_mod(int a, int b, int n)
{
    int phi_n = phi(n);

    b = b % phi_n;
    int result = 1;
    a = a % n;
    while (b > 0)
    {
        if (b % 2 == 1)
        {
            result = (result * a) % n;
        }
        a = (a * a) % n;
        b = b / 2;
    }
    return result;
}
string XOR(string &m1, string &b)
{
    string c;
    for (size_t i = 0; i < m1.length(); i++) // kieu du lieu k dau
    {
        c += to_string((m1[i] - '0') ^ (b[i] - '0'));
    }
    return c;
}

int main()
{
    int p, q;

    int i = 1, x0, x_end; // cap private key(p,q).

    string m1;
    string b_1, c_bits, m;

    cout << "Nhap 2 so nguyen to p, q:" << endl;

    do
    {
        cout << "p : ";
        cin >> p;
        cout << endl;
    } while (!isPrime(p) || !(p % 4 == 3)); // Nhap 2 so nguyen to
    do
    {
        cout << "q: ";
        cin >> q;
        cout << endl;
    } while (!isPrime(q) || !(q % 4 == 3));

    long long N = p * q;

    cout << "  ///////////////////////////////////////////////////////////////////////" << endl;
    cout << " //////////////////////        Khoi tao KEY      ///////////////////////" << endl;
    cout << "///////////////////////////////////////////////////////////////////////" << endl
         << endl;
    cout << "Nhap r bat ky sao cho 0< r <N :" << endl;
    cout << "r : ";
    cin >> x0;
    cout << "||||||||||||||||||||||||||||||||     TA CO       ||||||||||||||||||||||||||" << endl;
    cout << "p :" << p << "     " << "q : " << q << endl;
    cout << "PUBLIC KEY N : " << N << endl;
    cout << "PRIVATE KEY (p,q) : (" << p << "," << q << ")" << endl;
    cout << endl
         << endl;
    cout << "  ///////////////////////////////////////////////////////////////////////" << endl;
    cout << " //////////////////////           MA HOA         ///////////////////////" << endl;
    cout << "///////////////////////////////////////////////////////////////////////" << endl
         << endl;

    ////////////////////////////////////////////////////////
    cout << "Nhap message can duoc ma hoa." << endl ///
         << "m : ";                                 ///
    cin >> m;                                       ///
    cout << endl;                                   ///
    cout << "Message m: " << m << endl;             ///
                                                    ///
    strtobit(m, &m1);                               ///
    ///////////////////////////////////////////////////
    //////////////////  Hoac    //////////////////////
    // cout << "Nhap chuoi bit can duoc ma hoa." << endl
    //      << " m : ";
    // cin >> m1;
    // cout << endl;
    // m1 là tin nhan duoi dang bit
    cout << "Message m to bits string : " << m1 << endl;

    int k = (int)log2(N);
    int h = (int)ceil(log2(k));
    int l = m1.length();
    cout << "USING BSS TO GENERATE RANDOM BITS STRING:" << endl
         << endl;
    x0 = x0 * x0 % N;
    cout << "x0 :" << x0 << endl;

    BSSgeberate(x0, h, l, p, q, &b_1, &x_end, &i); //////bss
    cout << "Random bits string (encrypt) b : " << b_1 << endl;

    c_bits = XOR(m1, b_1);
    cout << "Sau khi XOR. c = m XOR b : " << c_bits << endl;

    cout << "Tin nhan duoc gui di co dang (c,x_end) : (" << c_bits << "," << x_end << ")" << endl;
    ///////////////////////////////////////////////////////////////////////
    //////////////////////        DECRYPTION        ///////////////////////
    ///////////////////////////////////////////////////////////////////////

    cout << endl
         << endl;
    cout << "  ///////////////////////////////////////////////////////////////////////" << endl;
    cout << " //////////////////////          GIAI MA         ///////////////////////" << endl;
    cout << "///////////////////////////////////////////////////////////////////////" << endl
         << endl;
    int a, b, x_0;
    long long d_p, d_q, u_p, u_q;
    string b_2, result;
    cout << "Qua trinh giai ma se tien hanh nhu sau :" << endl;
    cout << "Dung thuat toan Extended_Euclidean de tim cap so (a,b) sao cho ap + bq =1 : " << endl;

    ext_gcd(p, q, &a, &b); ///////////////////////////////////// extended_euclidean
    cout << "a : " << a << endl;
    cout << "b : " << b << endl
         << endl;

    // d_p = round(pow((p + 1) / 4, i));
    // d_p %= (p - 1);
    d_p = power_mod((p + 1) / 4, i, p - 1);
    // d_q = round(pow((q + 1) / 4, i));
    // d_q %= (q - 1);
    d_q = power_mod((q + 1) / 4, i, q - 1);
    cout << "d_p : " << d_p << endl;
    cout << "d_q : " << d_q << endl
         << endl;

    // u_p = round(pow(x_end, d_p));
    // u_p = u_p % p;
    u_p = power_mod(x_end, d_p, p);
    // u_q = round(pow(x_end, d_q));
    // u_q = u_q % q;
    u_q = power_mod(x_end, d_q, q);
    cout
        << "u_p : " << u_p << endl
        << "u_q : " << u_q << endl
        << endl;
    x_0 = ((a * p * u_q + b * q * u_p) % N + N) % N; /////// thay vi %N thì lam nhu vay de xu ly viec mod cua so am
    cout << "Tinh ( a*p*u_q + b*q*u_p ) mod N " << endl
         << "x0 : " << x_0 << endl
         << endl;

    cout << "UsSING BSS TO GENERATE RANDOM BITS STRING:" << endl
         << endl;
    i = 1;
    BSSgeberate(x_0, h, l, p, q, &b_2, &x_end, &i); ///// goi lai ham nen se bị du x_end
    cout << "Random bits string (decrypt) b : " << b_2 << endl;
    result = XOR(c_bits, b_2);
    cout << "Sau khi giai ma ta se duoc (decrypt) :" << endl
         << "Plaintext :" << result << endl
         << "Message :  " << m1 << endl;

    assert(result == m1);

    // string text = bitToStr(result);
    // cout << "Text" << text;
}