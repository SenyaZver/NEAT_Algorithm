#include "Brain.h"
#include <algorithm>
#include <stdlib.h>


	//there are used in mutation
void Brain::addHiddenGene() {
	std::vector<Node_gene*> allGenes;


	allGenes.insert(allGenes.end(), inputGenes->begin(), inputGenes->end());
	allGenes.insert(allGenes.end(), hiddenGenes->begin(), hiddenGenes->end());

	
	int chosenGene = rand() % allGenes.size();		//choose random gene
	Node_gene* inGene = allGenes[chosenGene];


	std::set<Connection_gene*> set = inGene->getOutConnections();
	std::vector<Connection_gene*> connections(set.size());
	std::copy(set.begin(), set.end(), connections.begin());		//creating a vector of gene's connections

	
	int choosenConnection = rand() % connections.size();		//choose random outConnection of chosen gene		
	

	Connection_gene* connection = connections[choosenConnection];
	Node_gene* outGene = connection->getOutGene();
	double weight = connection->getWeight();


	inGene->getOutConnections().erase(connection);	//delete previous connection
	outGene->getInConnections().erase(connection);

	Node_gene* newGene = new Node_gene(0);
	newGene->setOutput(outGene, weight, 20);
	newGene->setInput(inGene, 1, 20);
	hiddenGenes->push_back(newGene);
}
void Brain::addConnection() {
	std::vector<Node_gene*> allGenes;


	allGenes.insert(allGenes.end(), inputGenes->begin(), inputGenes->end());
	allGenes.insert(allGenes.end(), hiddenGenes->begin(), hiddenGenes->end());


	int firstChosenGene = rand() % allGenes.size();		//choose first random gene
	Node_gene* firstGene = allGenes[firstChosenGene];

	int secondChosenGene = rand() % allGenes.size();	//choose second random gene
	Node_gene* secondGene = allGenes[secondChosenGene];
	
	std::set<Node_gene*> outputs = firstGene->getOutputGenes();

	
	if (outputs.find(secondGene) != outputs.end()) {

		double weight = rand() / (RAND_MAX + 1.);
		firstGene->setOutput(secondGene, weight, 50);

		weight = rand() / (RAND_MAX + 1.);
		secondGene->setInput(firstGene, weight, 50);
	}



}
void Brain::changeWeightsRandomly() {
	for (auto input : *inputGenes) {
		for (auto connection : input->getOutConnections()) {
			if (rand() % 100 < 40) {
				double value = connection->getWeight();
				value = value + rand() / (RAND_MAX + 1.);
				connection->setWeight(value);
			}
		}
	}
	for (auto gene : *hiddenGenes) {
		for (auto connection : gene->getOutConnections()) {
			if (rand() % 100 < 40) {
				double value = connection->getWeight();
				value = value + rand() / (RAND_MAX + 1.);
				connection->setWeight(value);
			}
		}
	}
}
void Brain::disableGenesRandomly() {
	//TODO
}


Brain::Brain(std::vector<Node_gene*>* inputGenes, std::vector<Node_gene*>* outputGenes, std::vector<Node_gene*>* hiddenGenes) {
	this->inputGenes = inputGenes;
	this->outputGenes = outputGenes;
	this->hiddenGenes = hiddenGenes;
	fitnessScore = 0;
}

Brain::Brain()
{

	this->inputGenes = new std::vector<Node_gene*>;
	this->outputGenes = new std::vector<Node_gene*>;
	this->hiddenGenes = new std::vector<Node_gene*>;
	fitnessScore = 0;
}

void Brain::mutate() {

	if (rand() % 100 < 3) {				//3 percent chance to add a connection
		this->addConnection();
	}
	if (rand() % 100 < 5) {				//5 percent chance to add a hidden gene
		this->addHiddenGene();
	}

	this->changeWeightsRandomly();
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

	std::set<Node_gene*> calculatedSet(this->inputGenes->begin(), this->inputGenes->end()); //vector->set;
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
	
	for (auto result : *outputGenes) {
		output.push_back(result->getValue());
	}



	return output;
}

void Brain::createDefault(int inputSize, int hiddenGenesAmount, int outputSize)
{

	for (int i = 0; i < inputSize; i++) {
		inputGenes->push_back(new Node_gene(0));
	}

	for (int i = 0; i < outputSize; i++) {
		outputGenes->push_back(new Node_gene(0));
	}


	for (int i = 0; i < hiddenGenesAmount; i++) {
		Node_gene* hiddenNode = new Node_gene(0);

		double weight = rand() / (RAND_MAX + 1.);

		int innovationNumber = 0;
		for (auto input : *inputGenes) {
			weight = rand() / (RAND_MAX + 1.);
			hiddenNode->setInput(input, weight, innovationNumber);
		}

		weight = rand() / (RAND_MAX + 1.);

		for (auto output : *outputGenes) {
			weight = rand() / (RAND_MAX + 1.);
			output->setInput(hiddenNode, weight, innovationNumber);
		}
		hiddenGenes->push_back(hiddenNode);
	}
}



void Brain::setInput(std::vector<Node_gene*>* input) {
	this->inputGenes = input;
}



std::vector<double> Brain::feedForward(std::vector<int>* image)
{
	
	if (image->size() != this->inputGenes->size()) {
		return std::vector<double>(outputGenes->size());
	}

	//for (int i = 0; i < image->size(); i++) {
	//	inputGenes[i]->setValue((*image)[i]);
	//}
	int i = 0;
	for (auto gene : *inputGenes) {
		double value = (*image)[i];
		gene->setValue(value);
		i++;
	}

	return this->getOutput();
}



void Brain::setOutput(std::vector<Node_gene*>* output) {
	this->outputGenes = output;
}

void Brain::ConnectionPrint() {
	for (auto gene : *hiddenGenes) {
		for (auto connection : gene->getOutConnections()) {
			std::cout << connection->getWeight() << std::endl;
		}
	}
}





