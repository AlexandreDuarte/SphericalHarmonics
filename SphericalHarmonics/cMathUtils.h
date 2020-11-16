#pragma once

#include <iostream>


class cMathUtils
{

public:

	static double factorial(const double& n) {
		double result = 1.0;
		for (double i = 1; i <= n; i++) {
			result *= i;
		}
		return result;
	}

	static double factorial(const double& n, const double& k) {
		double result = 1.0;
		for (double i = n - k + 1; i <= n; i++) {
			result *= i;
		}
		return result;
	}

	static double combination(const double& n, const double& k) {
		return (double)factorial(n, k) / factorial(k);
	}


	static int sign(const int& n) {
		if (n % 2 == 0) {
			return 1;
		}
		return -1;
	}


};

