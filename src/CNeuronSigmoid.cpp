/*
 * CNeuronSigmoid.cpp
 *
 *  Created on: Jan 26, 2015
 *      Author: vostanin
 */

#include "CNeuronSigmoid.h"
#include "CActivationFunctionSigmoid.h"
#include "CActivationFunctionTanh.h"

CNeuronSigmoid::CNeuronSigmoid()
{
	activationFunc = new CActivationFunctionSigmoid( 0.01 );
}

CNeuronSigmoid::~CNeuronSigmoid()
{
}
