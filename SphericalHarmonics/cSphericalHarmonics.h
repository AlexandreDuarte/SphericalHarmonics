#pragma once

#include <cmath>
#include <vector>
#include "cMathUtils.h"

class cSphericalHarmonics
{
public:

	struct points_array {
		double* p_array;
		size_t size;
		unsigned int* ind_array;
		size_t size_ind;
	};

public:
	static void calculateLegendrePolynomial(double*, const double&, const double&, const double&, const double&, const double&);
	static void calculateSphericalHarmonic(cSphericalHarmonics::points_array* points, const int&, const int&);

};

