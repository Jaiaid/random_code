#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <cstdio>
#include <ctime>
#include <cmath>
#include <vector>
#include <cstdlib>

class perceptron;

double defaultActivationFunction
(
	const std::vector<double> &w,
	const std::vector<double> featureVal
);

void perceptronAlgorithm
(
	perceptron &p, const std::vector<std::vector<double> > &trainData
);


class perceptron
{
	int faultCount, maxIteration;
	std::vector<double> weights;
	double learningFactor;

	void (*trainingFunction)
	(
		perceptron &p, const std::vector<std::vector<double> > &trainData
	); 

public:
	perceptron(int numFeatures)
	{
		srand(time(NULL));
		weights = std::vector<double>(numFeatures + 1);
		learningFactor = 0.5;
		maxIteration = 1000;
		activationFunction = defaultActivationFunction;
		trainingFunction = perceptronAlgorithm;

		for(int l = 0;l < weights.size();l++) weights[l] = rand()%1000;
	}
	
	double (*activationFunction)
	(
		const std::vector<double> &w, const std::vector<double> featureVal
	);
	
	std::vector<double> getWeights()
	{
		return weights;
	}
	
	void setWeights(std::vector<double> w)
	{
		if(w.size() != weights.size()) {
			puts("wrong weight vector");
			return;
		}
		for(int l = 0;l < w.size();l++)
		{
			this->weights[l] = w[l];
		}	
	}
	
	void setLearningFactor(double d)
	{
		learningFactor = d;
	}
	
	double getLearningFactor()
	{
		return learningFactor;
	}
	
	void setMaxIteration(int n)
	{
		maxIteration = n;
	}
	
	void setFaultCount(int fc)
	{
		faultCount = fc;
	}
	
	void setActivationFunction
	(
		double (*f)(const std::vector<double> &w, const std::vector<double> featureVal)
	)
	{
		activationFunction = f;
	}
	
	void setTrainingFunction
	(
		void (*f)
		(
			perceptron &p, const std::vector<std::vector<double> > &trainData
		)
	)
	{
		trainingFunction = f;
	}
	
	int getFaultCount()
	{
		return faultCount;
	}
	
	int getNumFeatures()const
	{
		return weights.size() - 1;
	}
	
	std::vector<double> trainOnce
	(
		const std::vector<std::vector<double> > &trainData
	) //train once
	{
		trainingFunction((*this), trainData);	
		return weights;
	}
	
	std::vector<double> getFullTrained(const std::vector<std::vector<double> > &trainData)
	{
		for(int l = 0;l < trainData.size() && l < maxIteration && faultCount;l++)
		{
			trainOnce(trainData);
		}

		return weights;
	}
};


double defaultActivationFunction(const std::vector<double> &w, const std::vector<double> featureVal)
{
	double pResponse = w[w.size() - 1];
	for(int l = w.size() - 2;l >= 0;l--)
	{
		pResponse += w[l]*featureVal[l]; 
	}

	if(pResponse < 0) return -1.0;
	return 1.0;
}


void perceptronAlgorithm
(
	perceptron &p, const std::vector<std::vector<double> > &trainData
)
{
	double learningFactor = p.getLearningFactor();
	std::vector<double> weights = p.getWeights();
	std::vector<double> tmpW = weights;

	int faultyClassification = 0;
	for(int l = 0;l < trainData.size();l++)
	{
		if(trainData[l].size() != weights.size()) {
			puts("traindata has more/less feature than perceptron configuration");
			return;
		}

		if(trainData[l][trainData[l].size() - 1] != p.activationFunction(tmpW, trainData[l])) {
			bool subtract = false;
			if(trainData[l][trainData[l].size() - 1] < 0) subtract = true;
				
			for(int l1 = trainData[l].size() - 2;l1 >= 0;l1--)
			{
				if(subtract) {
					weights[l1] -= learningFactor*trainData[l][l1];
				}
				else weights[l1] += learningFactor*trainData[l][l1];
			}
			if(subtract) {
				weights[weights.size() - 1] -= learningFactor;
			}
			else weights[weights.size() - 1] += learningFactor; 
			
			faultyClassification++;
		}
	}

	p.setLearningFactor((1.0*faultyClassification)/trainData.size());
	p.setFaultCount(faultyClassification);
	p.setWeights(weights);
}

#endif
