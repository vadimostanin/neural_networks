/*
 * CNeuronSigmoid.h
 *
 *  Created on: Jan 26, 2015
 *      Author: vostanin
 */

#ifndef CNeuronSigmoid_H_
#define CNeuronSigmoid_H_

#include "CNeuronBase.h"
#include "IActivationFunction.h"

class CNeuronSigmoid: public CNeuronBase {
public:
	CNeuronSigmoid();
	~CNeuronSigmoid();
};

#endif /* CNeuronSigmoid_H_ */
