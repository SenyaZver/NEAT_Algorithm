#include "Brain.h"
#include <algorithm>


	//there are used in mutation
void Brain::addHiddenGene(Node_gene* newNode_Gene) {
	//TODO
}
void Brain::addConnection(Connection_gene* newConnection_Gene) {
	//TODO
}
void Brain::changeWeightsRandomly(std::vector<Connection_gene*> connectionGenes) {
	//TODO
}
void Brain::disableGenesRandomly(std::vector<Connection_gene*> connectionGenes) {
	//TODO
}


Brain::Brain(std::vector<Node_gene*> inputGenes, std::vector<Node_gene*> outputGenes, std::vector<Node_gene*> hiddenGenes) {
	this->inputGenes = inputGenes;
	this->outputGenes = outputGenes;
	this->hiddenGenes = hiddenGenes;
	fitnessScore = 0;
}

void Brain::mutate() {
	//TODO
}
void Brain::setFitnessScore() {
	//TODO
}

int Brain::getFitnessScore() {
	return this->fitnessScore;
}
int Brain::getNormalisedFitnessScore() {
	//TODO
	return this->fitnessScore;
}

	//calculating the result
std::vector<double> Brain::getOutput() {
	std::vector<double> output;

	std::set<Node_gene*> calculatedSet(this->inputGenes.begin(), this->inputGenes.end());	//vector->set
	std::set<Node_gene*> availableSet;

	while (!(std::includes(calculatedSet.begin(), calculatedSet.end(),
							outputGenes.begin(), outputGenes.end()))) {
		for (Node_gene* calculatedNode : calculatedSet) {

			for (Connection_gene* connection : calculatedNode->getoutputs()) {
				availableSet.insert(connection->getOutGene());
			}
		}
		//step two finished


	}


	return output;
}

void Brain::setInput(std::vector<Node_gene*> input) {
	this->inputGenes = input;
}







