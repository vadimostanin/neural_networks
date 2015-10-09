/*
 * CRandomGenerator.h
 *
 *  Created on: Jan 27, 2015
 *      Author: vostanin
 */

#ifndef CRANDOMGENERATOR_H_
#define CRANDOMGENERATOR_H_

#include <vector>
#include "Weight.h"
using namespace std;

class CRandomGenerator
{
public:
	CRandomGenerator( double range_low, double range_high, double range_precision );
	~CRandomGenerator();

	double getValue();
	void fillVector( std::vector<Weight> & values );
	void fillVector( std::vector<double> & values );
private:
	double m_Low;
	double m_High;
	double m_Precision;
};

#endif /* CRANDOMGENERATOR_H_ */
