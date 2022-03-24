#include "Brain.h"
#include <algorithm>
#include <stdlib.h>


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

Brain::Brain()
{
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

	std::set<Node_gene*> calculatedSet(this->inputGenes.begin(), this->inputGenes.end()); //vector->set;
	std::set<Node_gene*> availableSet;

	while (true) {

		for (Node_gene* calculatedNode : calculatedSet) {
			for (Connection_gene* connection : calculatedNode->getOutConnections()) {
				Node_gene* geneToAdd = connection->getOutGene();


				if (calculatedSet.find(geneToAdd) == calculatedSet.end()) {

					availableSet.insert(geneToAdd);
				}

			}
		}

		//step two finished


		if (availableSet.empty()) { //stop condition
			break;
		}


		std::set<Node_gene*> setToCalculate;

		for (Node_gene* availableNode : availableSet) {
			std::set<Node_gene*> inputs = availableNode->getInputGenes();

			if (std::includes(calculatedSet.begin(), calculatedSet.end(), inputs.begin(), inputs.end()))
			{
				setToCalculate.insert(availableNode);
			}
		}
		//step three finished



		for (Node_gene* gene : setToCalculate) {
			gene->calculate();
			availableSet.erase(gene);
			calculatedSet.insert(gene);
		}
		//steps four, five and six finished

	}
	
	for (auto result : outputGenes) {
		output.push_back(result->getValue());
	}

	return output;
}

void Brain::createDefault(int inputSize, int hiddenGenesAmount, int outputSize)
{
	for (int i = 0; i < inputSize; i++) {
		inputGenes.push_back(new Node_gene(0));
	}

	for (int i = 0; i < outputSize; i++) {
		outputGenes.push_back(new Node_gene(0));
	}


	for (int i = 0; i < hiddenGenesAmount; i++) {
		Node_gene* hiddenNode = new Node_gene(0);

		double weight = rand() / (RAND_MAX + 1.);

		int innovationNumber = 0;
		for (auto input : inputGenes) {
			weight = rand() / (RAND_MAX + 1.);
			hiddenNode->setInput(input, weight, innovationNumber);
		}

		weight = rand() / (RAND_MAX + 1.);

		for (auto output : outputGenes) {
			weight = rand() / (RAND_MAX + 1.);
			output->setInput(hiddenNode, weight, innovationNumber);
		}
		hiddenGenes.push_back(hiddenNode);
	}
}



void Brain::setInput(std::vector<Node_gene*> input) {
	this->inputGenes = input;
}



std::vector<double> Brain::feedForward(std::vector<int> image)
{
	if (image.size() != this->inputGenes.size()) {
		return std::vector<double>(outputGenes.size());
	}

	for (int i = 0; i < image.size(); i++) {
		this->inputGenes[i]->setValue(image[i]);
	}

	return this->getOutput();
}



void Brain::setOutput(std::vector<Node_gene*> output) {
	this->outputGenes = output;
}







