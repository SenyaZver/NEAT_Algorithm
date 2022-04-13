#pragma once
#include "Node_gene.h"
#include "Connection_gene.h"
#include "Brain.h"
#include <set>
#include <vector>
#include <iostream>

int main() {

	Brain* example = new Brain();
	example->createDefault(30, 10, 2);


	//input example
	std::vector<int> input { 55, 55, 57, 59, 61, 63, 66, 69, 72, 76, 80, 84, 88, 88, 56, 30, 35, 40, 48, 57, 61, 61, 59, 59, 57, 57, 56, 56, 56, 55 };
	//for (int i = 0; i < 30; i++) {
	//	(*input)[i] = i;
	//}

	std::vector<double> result = example->feedForward(&input);


	std::cout << "result is ";
	for (auto it : result) {
		std::cout << it << " ";
	}

	//example->ConnectionPrint();
	std::cout << std::endl;
	

	
	Brain* copy = example->clone();


	std::vector<double> newResult = copy->feedForward(&input);

	std::cout << "result is ";
	for (auto it : newResult) {
		std::cout << it << " ";
	}
	std::cout << std::endl;
}

