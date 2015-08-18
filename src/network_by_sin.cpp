/*
 * network_by_sin.cpp
 *
 *  Created on: Jan 28, 2015
 *      Author: vostanin
 */

#include "network_by_sin.h"
#include <cstdio>
#include <ctime>
#include <cmath>
#include <iostream>
#include <fstream>
using namespace std;

static void getTestTrainData( TrainingData & data, int index, int size );
static void dump( vector<double> & input );

class Timer
{
public:
  Timer(const std::string& name)
    : name_ (name),
      start_ (std::clock())
    {
    }
  ~Timer()
    {
	  clock_t now = std::clock();
      double elapsed = (double(now - start_) / CLOCKS_PER_SEC);
      std::cout << "start=" << start_ << "; now=" << now << "; " << name_ << ": " << (elapsed * 1000) << " ms" << std::endl;
    }
private:
  std::string name_;
  std::clock_t start_;
};

#define TIMER(name) Timer timer__(name);

void train_network_by_sin()
{
	const unsigned int input_count = 1;
	const unsigned int output_count = 1;
	vector<size_t> hiddenLayers;
	hiddenLayers.push_back( 10 );
	CLayersConfiguration sequence( input_count, output_count, hiddenLayers );

	CNetwork network( sequence, 1, 0.1 );

	string network_filename( "network_sin.net" );

	vector<TrainingData> trainData_v;

	const size_t traine_data_count = 1000;

	trainData_v.resize( traine_data_count, TrainingData() );

	for( unsigned int traine_i = 0 ; traine_i < traine_data_count ; traine_i++ )
	{
		getTestTrainData( trainData_v[traine_i], traine_i, traine_data_count );
	}

	double error_threshold = 1e-7;

	double relativeErrorTrain = 0.0;
	{
		TIMER("train")

		relativeErrorTrain = network.Learn( trainData_v, error_threshold, 1000 );
	}
	printf( "relativeErrorTrain=%f\n", relativeErrorTrain ); fflush( stdout );
	network.save( network_filename );
}

void test_network_by_sin()
{
	const unsigned int input_count = 2;
	const unsigned int output_count = 1;
	vector<size_t> hiddenLayers;
	CLayersConfiguration sequence( input_count, output_count, hiddenLayers );

	string filename = "network_sin.net";
	CNetwork network( filename );

	const size_t traind_data_count = 40;

	for( unsigned int file_i = 0 ; file_i < traind_data_count ; file_i++ )
	{
		TrainingData test_input;
		getTestTrainData( test_input, file_i, traind_data_count );

		vector<double> output_test;
		network.Test( test_input.input, output_test );
		dump( output_test );

		printf( "expected=%.5f, out=%.5f\n", test_input.output[0], output_test[0] ); fflush( stdout );
	}
}



void getTestTrainData( TrainingData & data, int index, int size )
{
	const double angleMin = (-1) * M_PI;
	const double angleMax = M_PI;
	const double angleStep = ( angleMax - angleMin ) / size;

	double angle = angleMin + angleStep * index;

	double normalizedAngle = angle / M_PI;

	data.input.push_back( normalizedAngle );
	data.output.push_back( sin( angle ) );
}

static void dump( vector<double> & input )
{
	ofstream file( "dump.txt", ios_base::app );

	for( size_t i = 0 ; i < input.size() ; i++ )
	{
		file << input[i] << " " << std::flush;
	}
	file << endl;
	file.close();
}

