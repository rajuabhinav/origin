#include<bits/stdc++.h>
using namespace std;
#define MOD 17
void print(vector<int> &a) {
	cout << endl;
	for (int i = 0; i < a.size(); i++)
		cout << a[i] << " ";
}

void fft(vector<int> &a, bool inv, int wn) {
	if (a.size() < 2) {
		return;
	}
	int n = a.size(), w = 1;

	vector<int> ev, odd;
	for (int i = 0; i < a.size(); i++)
		if (i & 1)
			odd.push_back(a[i]);
		else
			ev.push_back(a[i]);
	fft(ev, inv, wn * wn % MOD);
	fft(odd, inv, wn * wn % MOD);
	for (int i = 0; i < n / 2; i++) {
		int x = (w * odd[i]) % MOD;
		a[i] = ev[i] + x;
		if (a[i] >= MOD)
			a[i] -= MOD;
		a[i + n / 2] = ev[i] - x;
		if (a[i + n / 2] < 0)
			a[i + n / 2] += MOD;
		w *= wn;
		w %= MOD;
		if (inv)
			a[i] *= 9, a[i + n / 2] *= 9;
		a[i] %= MOD;
		a[i + n / 2] %= MOD;
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

	int wn = 9;
	fft(ac, false, wn);
	fft(bc, false, wn);
	for (int i = 0; i < ac.size(); i++) {
		ac[i] *= bc[i];
		ac[i] %= MOD;
	}
	fft(ac, true, 2);
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
