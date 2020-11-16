#include "cSphericalHarmonics.h"
#include <iostream>

const double pi = std::acos(-1);

void cSphericalHarmonics::calculateLegendrePolynomial(double* result, const double& x, const double& y, const double& l, const double& m, const double& T) {

	*result = 0;

	for (double k = m; k <= l; k++) {
		*result += (cMathUtils::factorial(k) * std::pow(x, k-m) * cMathUtils::combination(l, k) * cMathUtils::combination((l + k - 1.0) / 2.0, l) / cMathUtils::factorial(k - m));
	}

	*result *= T* std::pow(y, m);

	
}


void cSphericalHarmonics::calculateSphericalHarmonic(cSphericalHarmonics::points_array* output, const int& l, const int& m) {
	double T = std::pow(2, l);

	int mm;

	if (m < 0) {
		mm = -m;
	}
	else {
		mm = m;
	}

	std::vector<double> values;

	double x, y, p_x, p_y, max_L = 0;

	double* L = (double*)malloc(sizeof(double));

	for (double p = 0.0; p <= 2 * pi; p += (0.01) * pi) {
		p_x = std::cos(mm * p);
		for (double t = 0; t <= pi; t += (0.01) * pi) {
			x = std::cos(t);
			y = std::sin(t);

			calculateLegendrePolynomial(L, x, y, (double)l, (double)mm, T);

			(*L > max_L) ? max_L = *L : max_L = max_L;


			values.push_back(((*L)) * p_x * y * std::sin(p));
			values.push_back(((*L)) * p_x * y * std::cos(p));
			values.push_back(((*L)) * p_x * x);
			values.push_back(x * std::sin(p));
		}
	}

	double pp = 0, tt = 0;

	for (double p = 0.0; p <= 2 * pi; p += (0.01) * pi) {
		p_x = std::cos(mm * p);
		for (double t = 0; t <= pi; t += (0.01) * pi) {
			x = std::cos(t);
			y = std::sin(t);

			calculateLegendrePolynomial(L, x, y, (double)l, (double)mm, T);


			values.push_back(((-*L)) * p_x * y * std::sin(p));
			values.push_back(((-*L)) * p_x * y * std::cos(p));
			values.push_back(((-*L)) * p_x * x);
			values.push_back(x * std::sin(p));
		}
	}



	size_t size = values.size();

	double* points = new double[size];

	unsigned int* ind = new unsigned int[size/2]; // (size / 3) * 4 ---- / nº values(3(x, y, z) + 1 (shade)) * points (2)
	unsigned int size_ind = 0, offset = 0;
	for (int loop = 0; loop <= 1; loop++) {
	std::cout << loop << std::endl;
	offset = size_ind/2;
	for (unsigned int k = 0; k < 201; k++) {
		for (unsigned int i = 0; i < 101; i++) {

			*(ind + size_ind) = offset + i + 0 + (k) * (101);

			*(ind + size_ind + 1) = offset + i + (k + 1) * (101);


			size_ind += 2;
		}
	}
	}
	std::copy(values.begin(), values.end(), points);

	int nn = 0;

	for (int i = 0; i < size; i++) {
		if (nn != 3){
			points[i] /= 3.0*max_L;

			nn++;
		}
		else {

			points[i - 3] += (double)m / 1.5;

			points[i - 1] += (double)l - 2;
			nn = 0;
		}
	}

	*output = *new points_array{ points, size, ind, size/2 };
}
