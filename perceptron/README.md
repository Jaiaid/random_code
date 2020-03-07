## Two Feature Perceptron Training Simulation

This program shows training progress of a 2 feature binary classifier perception. At each button ('f') press perceptron will be trained with one sample of data and will show the updated decision boundary (line). How many faulty classification(s) are made from the given training data, will be reported after each iteration in the console. 

#### Compile

compiled using g++7.4.0 in ubuntu18.04
```
g++ 2class2feature_perceptron_simulator.cpp -o <exec name> -lGL -lGLU -lglut
```

#### Training Data Format

The training file is a text file. Each sample will be in a line and will be like this <feature 1 value> <feature 2 value> <class (1/-1)>
An example data file with four sample with two in each class is given below.

```
-100 100 1
50 100 -1
-50 -100 1
100 -100 -1
```

#####Note
Range of the displayed coordinates are x:[-1000,1000] and y:[-1000,1000] . So, if training points are outside these range they will not be shown but training will be affected.

#### Usage

```
<exec name> <training data file>
```

Press 'f' to make a training iteration with next sample in data file. Press 'q' to quit. -1 class is indicated with red point and +1 with blue. Perceptron line is green and axes are white.

