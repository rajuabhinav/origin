#include<bits/stdc++.h>
using namespace std;
typedef complex<double> cd;

void print(vector<int> &a) {
	cout << endl;
	for (int i = 0; i < a.size(); i++)
		cout << a[i] << " ";
}
int rev(int v, int n) {
	int t = 0;
	while (n > 0) {
		t <<= 1;
		t |= v & 1;
		v >>= 1;
		n >>= 1;
	}
	return t;
}
void bitrev(vector<cd> & a) {
	vector<cd> b(a);
	for (int i = 0; i < a.size(); i++)
		a[rev(i, a.size() - 1)] = b[i];
}

void fft(vector<complex<double> > &a, bool inv) {
	if (a.size() < 2) {
		return;
	}
	bitrev(a);
	int n = a.size();
	for (int len = 2; len <= n; len <<= 1) {
		int m = len / 2;
		double ang = 2 * acos(-1) / len;
		if (inv)
			ang = -ang;
		complex<double> one(1.0, 0), wn(cos(ang), sin(ang)), w(1.0, 0);

		for (int k = 0; k < n; k += len) {
			w = cd(1.0, 0);
			for (int i = 0; i < m; i++) {
				cd u = a[i + k], v = a[i + m + k] * w;
				a[i + k] = u + v;
				a[i + k + m] = u - v;
				w = w * wn;
				if (inv)
					a[i + k] /= 2, a[i + m + k] /= 2;
			}
		}
	}
}

void multiply(vector<int> &a, vector<int> &b) {
	int n = max(2 * a.size(), 2 * b.size()), t = 1;
	while (t < n) {
		t <<= 1;
	}
	n = t;
	a.resize(t, 0);
	b.resize(t, 0);
	vector<complex<double> > ac, bc;
	for (int i = 0; i < n; i++) {
		ac.push_back(complex<double>(a[i], 0));
	}
	for (int i = 0; i < n; i++) {
		bc.push_back(complex<double>(b[i], 0));
	}
	fft(ac, false);
	fft(bc, false);
	for (int i = 0; i < ac.size(); i++) {
		ac[i] *= bc[i];
	}
	fft(ac, true);
	for (int i = 0; i < ac.size(); i++)
		a[i] = ac[i].real() + 0.5;
}

int main(int argc, char **argv) {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif

	int n;
	vector<int> a, b;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int t;
		cin >> t;
		a.push_back(t);
	}
	for (int i = 0; i < n; i++) {
		int t;
		cin >> t;
		b.push_back(t);
	}
	print(a);
	print(b);
	multiply(a, b);
	cout << " Multiplication ----" << endl;
	print(a);
	return 0;
}
