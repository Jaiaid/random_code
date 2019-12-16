
## Lorenz Curve drawing using python turtle

This is 3d lorenz curve generator in any 2 dimension plane using turtle

Give the parameter $\beta$, $\rho$ and $\sigma$ for the curve and specify any two axes of three which will be drawn. e.g. first axis z and second axis y will draw the curve for z-y plane (not y-z) 

### Usage
```
python2/3 lorenz_curve.py [-h] --param param param param --pos pos pos pos [--axis axis axis] [--screen screen screen screen screen]       
```

##### For help,
-h, --help            
			show this help message and exit
  
#####  required arguments:
--param param param param
			provide three parameters of lorenz curve rho, sigma, beta. e.g --param 1 2 3
                        
  --pos pos pos pos
			 provide initial x,y,z of lorenz curve. e.g --param 1 2 3

##### optional arguments:
  --axis axis axis      
			provide two axis of lorenz curve sequentialy. e.g --axis z x will give curve in z-x plane considering z as x and x as y. Default, x-y plane.

  --screen screen screen screen screen
			provide x,y of lower left and top right. e.g --screen -10 -10 10 10 will give plot of 20x20 with lower left coordinate being (-10, -10). Default, -500, -500, 500, 500.
			
### Requirements

 - python (tested in 2.7 and 3.5)
 - python3-tk for python3 (in ubuntu18.04)


