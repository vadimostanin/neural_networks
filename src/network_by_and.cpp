/*
 * network_by_and.cpp
 *
 *  Created on: Jan 28, 2015
 *      Author: vostanin
 */

#include "network_by_and.h"
#include <cstdio>
#include <iostream>
using namespace std;

static void getTestTrainData( TrainingData & data, int index );
static void dump( vector<double> & input );

void train_network_by_and()
{
	const unsigned int input_count = 2;
	const unsigned int output_count = 1;
	vector<size_t> hiddenLayers;
//	hiddenLayers.push_back( 3 );
	CLayersConfiguration sequence( input_count, output_count, hiddenLayers );

	CNetwork network( sequence );

	string network_filename( "network_and.net" );

	vector<TrainingData> trainData_v;

	const size_t traind_data_count = 4;

	trainData_v.resize( traind_data_count, TrainingData() );

	for( unsigned int file_i = 0 ; file_i < traind_data_count ; file_i++ )
	{
		getTestTrainData( trainData_v[file_i], file_i );
	}

	double error_threshold = 1e-7;

	double relativeErrorTrain = network.Learn( trainData_v, error_threshold, 100000 );
	printf( "relativeErrorTrain=%f\n", relativeErrorTrain ); fflush( stdout );
	network.save( network_filename );

	for( unsigned int file_i = 0 ; file_i < traind_data_count ; file_i++ )
	{
		TrainingData test_input;
		getTestTrainData( test_input, file_i );

		vector<double> output_test;
		double relativeErrorTest = network.Test( test_input.input, output_test );
		dump( output_test );
		double max_value = 0.0;
		for( size_t output_i = 0 ; output_i < output_test.size() ; output_i++ )
		{
			if( max_value < output_test[output_i] )
			{
				max_value = output_test[output_i];
			}
		}

		printf( "relativeErrorTest=%f, value=%f\n", relativeErrorTest, max_value ); fflush( stdout );
	}
}

void test_network_by_and()
{
	const unsigned int input_count = 2;
	const unsigned int output_count = 1;
	vector<size_t> hiddenLayers;
	CLayersConfiguration sequence( input_count, output_count, hiddenLayers );

	string filename = "network_and.net";
	CNetwork network( filename );

	const size_t traind_data_count = 4;

	for( unsigned int file_i = 0 ; file_i < traind_data_count ; file_i++ )
	{
		TrainingData test_input;
		getTestTrainData( test_input, file_i );

		vector<double> output_test;
		network.Test( test_input.input, output_test );
		dump( output_test );
		double max_value = 0.0;

		printf( "out=%f\n", output_test[0] ); fflush( stdout );
	}
}

#include <fstream>

void getTestTrainData( TrainingData & data, int index )
{
	static int all_input_data[][3] = { {0, 0, 0}, {0, 1, 0}, {1, 0, 0}, {1, 1, 1} };

	data.input.resize( 2, 0 );
	data.input[0] = all_input_data[index][0];
	data.input[1] = all_input_data[index][1];

	data.output.push_back( all_input_data[index][2] );
}

void getReverseTestTrainData( TrainingData & data, int index )
{
	static int all_input_data[][3] = { {0, 0, 0}, {0, 1, 0}, {1, 0, 0}, {1, 1, 1} };

	data.input.resize( 1, 0 );
	data.input[0] = all_input_data[index][2];

	data.output.push_back( all_input_data[index][0] );
	data.output.push_back( all_input_data[index][1] );
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

void test_network_reverse()
{
	const unsigned int input_count = 2;
	const unsigned int output_count = 1;
	vector<size_t> hiddenLayers;
	CLayersConfiguration sequence( input_count, output_count, hiddenLayers );

	string filename = "network_and.net";
	CNetwork network( filename );

	network.reverse();

	string filename_reversed = "network_and_reversed.net";
	network.save( filename_reversed );

	const size_t traind_data_count = 4;

	for( unsigned int file_i = 0 ; file_i < traind_data_count ; file_i++ )
	{
		TrainingData test_input;
		getReverseTestTrainData( test_input, file_i );

		vector<double> output_test;
		double relativeErrorTest = network.Test( test_input.input, output_test );
		dump( output_test );

		printf( "relativeErrorTest=%f, out1=%f, out2=%f\n", relativeErrorTest, output_test[0], output_test[1] ); fflush( stdout );
	}
}


