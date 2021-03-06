#include "Brain.h"
#include <algorithm>
#include <stdlib.h>


	//there are used in mutation
void Brain::addHiddenGene() {
	std::vector<Node_gene*> allGenes;


	allGenes.insert(allGenes.end(), inputGenes->begin(), inputGenes->end());
	allGenes.insert(allGenes.end(), hiddenGenes->begin(), hiddenGenes->end());

	
	int chosenGeneNumber = rand() % allGenes.size();		//choose random gene
	Node_gene* inGene = allGenes[chosenGeneNumber];


	std::set<Connection_gene*> set = inGene->getOutConnections();
	std::vector<Connection_gene*> connections(set.size());
	std::copy(set.begin(), set.end(), connections.begin());		//creating a vector of gene's connections

	
	int choosenConnectionNumber = rand() % connections.size();		//choose random outConnection of chosen gene		
	

	Connection_gene* connection = connections[choosenConnectionNumber];
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


	int firstChosenNumber = rand() % allGenes.size();		//choose first random gene
	Node_gene* firstGene = allGenes[firstChosenNumber];

	int secondChosenNumber = rand() % allGenes.size();	//choose second random gene
	Node_gene* secondGene = allGenes[secondChosenNumber];
	
	std::set<Node_gene*> outputs = firstGene->getOutputGenes();

	
	if (outputs.find(secondGene) != outputs.end()) {
		double weight = rand() / (RAND_MAX + 1.);	//choose random number close to 1(actually it would be better to be close to 0
		firstGene->setOutput(secondGene, weight, 50);

		//weight = rand() / (RAND_MAX + 1.);		//same
		//secondGene->setInput(firstGene, weight, 50);
	}

}
void Brain::changeWeightsRandomly() {
	for (auto input : *inputGenes) {
		for (auto connection : input->getOutConnections()) {
			if (rand() % 100 < 40) {
				double value = connection->getWeight();
				value = value + rand() / (RAND_MAX + 1.);		//choose random number close to 1
				connection->setWeight(value);
			}
		}
	}
	for (auto gene : *hiddenGenes) {
		for (auto connection : gene->getOutConnections()) {
			if (rand() % 100 < 40) {
				double value = connection->getWeight();
				value = value + rand() / (RAND_MAX + 1.);		//choose random number close to 1
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

Brain::~Brain()
{
	for (auto gene : *inputGenes) {
		for (auto connection : gene->getOutConnections()) {
			delete connection;
		}
	}
	for (auto gene : *hiddenGenes) {
		for (auto connection : gene->getOutConnections()) {
			delete connection;
		}
	}

	for (auto gene : *inputGenes) {
		delete gene;
	}
	for (auto gene : *hiddenGenes) {
		delete gene;
	}
	for (auto gene : *outputGenes) {
		delete gene;
	}


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
	//std::cout << outputGenes->size() << std::endl;
	//vs
	//std::cout << outputGenes[0].size() << std::endl;
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
	//	inputGenes[i]->setValue(image[i]);
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


Brain* Brain::clone() {
	std::vector<Node_gene*>* newInputGenes = new std::vector<Node_gene*>;
	std::vector<Node_gene*>* newOutputGenes = new std::vector<Node_gene*>;
	std::vector<Node_gene*>* newHiddenGenes = new std::vector<Node_gene*>;
	Brain* copy = new Brain();
	copy->inputGenes = newInputGenes;
	copy->outputGenes = newOutputGenes;
	copy->hiddenGenes = newHiddenGenes;


	for (int i = 0; i < (this->inputGenes->size()); i++) {
		Node_gene* inputNode = new Node_gene(0);
		newInputGenes->push_back(inputNode);
	}
	for (int i = 0; i < (this->hiddenGenes->size()); i++) {
		Node_gene* hiddenNode = new Node_gene(0);
		newHiddenGenes->push_back(hiddenNode);
	}
	for (int i = 0; i < (this->outputGenes->size()); i++) {
		Node_gene* outputNode = new Node_gene(0);
		newOutputGenes->push_back(outputNode);
	}


	for (int i = 0; i < inputGenes[0].size(); i++) {
		for (int j = 0; j < hiddenGenes[0].size(); j++) {	
			//chech if hiddenGene[j] is connected to inputgene[i]
			auto temp = inputGenes[0][i]->getOutputGenes();

			if (temp.find(hiddenGenes[0][j]) != temp.end()) {
				double weight = 0;
				for (auto connection : inputGenes[0][i]->getOutConnections()) {
					if (connection->getOutGene() == hiddenGenes[0][j]) {
						weight = connection->getWeight();
					}
				}
				newInputGenes[0][i]->setOutput(newHiddenGenes[0][j], weight, 1337);
			}
		}
	}

	for (int i = 0; i < hiddenGenes[0].size(); i++) {
		for (int j = 0; j < hiddenGenes[0].size(); j++) {

			auto temp = hiddenGenes[0][i]->getOutputGenes();

			//chech if hiddenGene[j] is connected to inputgene[i]
			if (temp.find(hiddenGenes[0][j]) != temp.end()) {
				double weight = 0;
				for (auto connection : hiddenGenes[0][i]->getOutConnections()) {
					if (connection->getOutGene() == hiddenGenes[0][j]) {
						weight = connection->getWeight();
					}
				}
				newHiddenGenes[0][i]->setOutput(newHiddenGenes[0][j], weight, 1337);
			}
		}
	}

	for (int i = 0; i < hiddenGenes[0].size(); i++) {
		for (int j = 0; j < outputGenes[0].size(); j++) {
			auto temp = hiddenGenes[0][i]->getOutputGenes();
			//chech if hiddenGene[j] is connected to inputgene[i]
			if (temp.find(outputGenes[0][j]) != temp.end()) {
				double weight = 0;
				for (auto connection : hiddenGenes[0][i]->getOutConnections()) {
					if (connection->getOutGene() == outputGenes[0][j]) {
						weight = connection->getWeight();
					}
				}
				newHiddenGenes[0][i]->setOutput(newOutputGenes[0][j], weight, 1337);
			}
		}
	}


	
	return copy;

	
}





