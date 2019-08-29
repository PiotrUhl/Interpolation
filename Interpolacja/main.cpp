#include <iostream>
#include <fstream>
#include <cmath>
#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

using namespace std;

double f(double x) {
	return abs(sin(x));
}

class Interpolacja {
	int n;
	double a;
	double b;
	bool opt = false;
	int np;
	double(*fun)(double);
	double h;
	double* X;
	double* fX;
	int npsize = n*np + 1;
	double* Xnp;
	double* fXnp;
	double* LnXnp;
public:
	Interpolacja(double(*_fun)(double), int _n, double _a, double _b, bool _opt, int _np) : fun(_fun), n(_n), a(_a), b(_b), opt(_opt), np(_np) {
		h = (abs(a - b)) / static_cast<double>(n);
		X = new double[n+1];
		fX = new double[n+1];
		Xnp = new double[npsize];
		fXnp = new double[npsize];
		LnXnp = new double[npsize];
		dyskretyzacja();
		tablicowanie();
	}
	~Interpolacja() {
		delete[] X;
		delete[] fX;
		delete[] Xnp;
		delete[] fXnp;
	}
	double Ln(double x) {
		double suma = 0;
		for (int i = 0; i <= n; i++) {
			double iloczyn = 1;
			for (int j = 0; j <= n; j++) {
				if (i != j) {
					iloczyn *= (x - X[j]) / (X[i] - X[j]);
				}
			}
			suma += fX[i] * iloczyn;
		}
		return suma;
	}
	double blad(int i) {
		return abs(fXnp[i] - LnXnp[i]);
	}
	void out(ostream& ostr) {
		ostr.precision(5);
		ostr << "# n = " << n << ", <" << a << ", " << b << ">, np = " << np << ", opt = " << opt << ".\n";
		ostr << "# xnp" << '\t' << "f(xnp)" << '\t' << "Ln(xnp)" << '\t' << "blad(xnp)" << '\n';
		for (int i = 0; i < npsize; i++) {
			ostr << Xnp[i] << '\t' << fXnp[i] << '\t' << LnXnp[i] << '\t' << blad(i);
			if (i <= n)
				ostr << '\t' << X[i] << '\t' << 0;
			ostr << '\n';
		}
	}
private:
	void dyskretyzacja() {
		if (opt) {
			for (int i = 0; i <= n; i++) {
				X[i] = (a + b) / 2 + (b - a) * cos(((2 * i + 1) * M_PI) / (2 * n + 2)) / 2;
				fX[i] = fun(X[i]);
			}
		}
		else {
			for (int i = 0; i <= n; i++) {
				X[i] = i * h + a;
				fX[i] = fun(X[i]);
			}
		}
	}
	void tablicowanie() {
		for (int j = 0; j < npsize; j++) {
			Xnp[j] = a + (h / np)*j;
			fXnp[j] = fun(Xnp[j]);
			LnXnp[j] = Ln(Xnp[j]);
		}
	}
};

int main(int argc, char** argv) {
	string outPath = argv[6];
	Interpolacja inter(f, atoi(argv[1]), atof(argv[2]), atof(argv[3]), atoi(argv[5]), atoi(argv[4]));
	ofstream ofile(argv[6]);
	inter.out(ofile);
	ofile.close();
	return 0;
}