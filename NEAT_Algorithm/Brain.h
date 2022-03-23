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
	std::vector<Node_gene*> inputGenes;
	std::vector<Node_gene*> outputGenes;
	std::vector<Node_gene*> hiddenGenes;

//	std::vector<Connection_gene*> connectionGenes;

	int fitnessScore;

	//there are used in mutation
	void addHiddenGene(Node_gene* newNode_Gene);
	void addConnection(Connection_gene* newConnection_Gene);
	void changeWeightsRandomly(std::vector<Connection_gene*> connectionGenes);
	void disableGenesRandomly(std::vector<Connection_gene*> connectionGenes);

public:
	Brain(std::vector<Node_gene*> inputGenes, std::vector<Node_gene*> outputGenes, std::vector<Node_gene*> hiddenGenes);
	Brain();

	void mutate();
	void setFitnessScore();

	int getFitnessScore();
	int getNormalisedFitnessScore();

	//calculating the result
	std::vector<double> getOutput();
	
	void setInput(std::vector<Node_gene*> input);

	void setOutput(std::vector<Node_gene*> output);
	


};

