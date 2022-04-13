#pragma once
#include "Node_gene.h"
#include "Connection_gene.h"
#include <set>
#include <vector>

class Connection_gene;
class Node_gene;

class Brain
{
private:

//	std::vector<Connection_gene*> connectionGenes;
	std::vector<Node_gene*>* inputGenes;
	std::vector<Node_gene*>* outputGenes;
	std::vector<Node_gene*>* hiddenGenes;
	int fitnessScore;

	//there are used in mutation
	void addHiddenGene();
	void addConnection();
	void changeWeightsRandomly();
	void disableGenesRandomly();

public:
	Brain(std::vector<Node_gene*>* inputGenes, std::vector<Node_gene*>* outputGenes, std::vector<Node_gene*>* hiddenGenes);
	Brain();

	void mutate();
	void setFitnessScore();

	int getFitnessScore();
	int getNormalisedFitnessScore();


	//create a one layered perseptron
	void createDefault(int inputSize, int outputSize, int hiddenGenesAmount);

	//calculating the result, should be private, but i'll keep it for the first test
	std::vector<double> getOutput();

	//getting input and calculating the result
	std::vector<double> feedForward(std::vector<int>* image);
	


	//debug functions
	void setInput(std::vector<Node_gene*>* input);
	void setOutput(std::vector<Node_gene*>* output);
	
	void ConnectionPrint();


};

