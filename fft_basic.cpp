#include<bits/stdc++.h>
using namespace std;

void print(vector<int> &a) {
	cout << endl;
	for (int i = 0; i < a.size(); i++)
		cout << a[i] << " ";
}

void fft(vector<complex<double> > &a, bool inv) {
	if (a.size() < 2) {
		return;
	}
	int n = a.size();
	double pi = acos(-1), ang = 2 * pi / n;
	if (inv)
		ang = -ang;
	complex<double> one(1.0, 0), wn(cos(ang), sin(ang)), w(1.0, 0);

	vector<complex<double> > ev, odd;
	for (int i = 0; i < a.size(); i++)
		if (i & 1)
			odd.push_back(a[i]);
		else
			ev.push_back(a[i]);
	fft(ev, inv);
	fft(odd, inv);
	for (int i = 0; i < n / 2; i++) {
		a[i] = ev[i] + w * odd[i];
		a[i + n / 2] = ev[i] - w * odd[i];
		w *= wn;
		if (inv)
			a[i] /= 2, a[i + n / 2] /= 2;
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
