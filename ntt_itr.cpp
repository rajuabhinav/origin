#include<bits/stdc++.h>
using namespace std;
#define MOD 17
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
void bitrev(vector<int> & a) {
	vector<int> b(a);
	for (int i = 0; i < a.size(); i++)
		a[rev(i, a.size() - 1)] = b[i];
}

void fft(vector<int> &a, bool inv) {
	if (a.size() < 2) {
		return;
	}
	bitrev(a);
	int n = a.size();
	for (int len = 2; len <= n; len <<= 1) {
		int m = len / 2, wn = 9, temp = n;

		if (inv)
			wn = 2;
		while (temp > len)
			wn *= wn, temp >>= 1;

		for (int k = 0; k < n; k += len) {
			int w = 1;
			for (int i = 0; i < m; i++) {
				int u = a[i + k], v = a[i + m + k] * w % MOD;
				a[i + k] = (u + v) % MOD;

				a[i + k + m] = (u - v) % MOD;
				if (a[i + k + m] < 0)
					a[i + k + m] += MOD;
				w = w * wn;
				if (inv)
					a[i + k] *= 9, a[i + k] %= MOD, a[i + m + k] *= 9, a[i + m
							+ k] %= MOD;
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
	vector<int> ac, bc;
	for (int i = 0; i < n; i++) {
		ac.push_back(a[i]);
	}
	for (int i = 0; i < n; i++) {
		bc.push_back(b[i]);
	}
	fft(ac, false);
	fft(bc, false);
	for (int i = 0; i < ac.size(); i++) {
		ac[i] *= bc[i];
	}
	fft(ac, true);
	for (int i = 0; i < ac.size(); i++)
		a[i] = ac[i];
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
