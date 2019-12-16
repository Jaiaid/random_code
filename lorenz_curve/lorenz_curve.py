import argparse
import turtle
import math as m

"""This is 3d lorenz curve generator in any 2 dimension plane using turtle

    Lorenz curve equ.
    dx/dt = sigma * (y - x)
    dy/dt = x * (rho - z) - y
    dz/dt = x * y - beta * z
"""



if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=
        """
        This is 3d lorenz curve generator in any 2 dimension plane using turtle
        Give the parameter beta, rho and sigma for the curve and specify any two axis of 
        three which will be drawn. e.g. first axis z and second axis y will draw the curve for
        z-y plane (not y-z) 
        """
    )

    parser.add_argument('--param', metavar='param', type=float, nargs=3, required=True, 
        help='provide three parameters of lorenz curve rho, sigma, beta. e.g --param 1 2 3')

    parser.add_argument('--pos', metavar='pos', type=float, nargs=3, required=True, 
        help='provide initial x,y,z of lorenz curve. e.g --param 1 2 3')

    parser.add_argument('--axis', metavar='axis', type=str, nargs=2, default=['x', 'y'], choices=['x', 'y', 'z'], 
        help="""provide two axis of lorenz curve sequentialy. e.g --axis z x  will give curve in z-x plane considering z as x and x as y.  Default x-y plane"""
        )

    parser.add_argument('--screen', metavar='screen', type=float, nargs=4, default=[-500, -500, 500, 500], 
        help="""provide x,y of lower left and top right. e.g --screen -10 -10 10 10 will give plot of 20x20 with lower left coordinate being (-10, -10).    Default -500, -500, 500, 500.
            """
    )

    args = parser.parse_args()
    
    turtle.setworldcoordinates(args.screen[0], args.screen[1], args.screen[2], args.screen[3])

    rho = args.param[0]
    sigma = args.param[1]
    beta = args.param[2]
    position = {'x': args.pos[0], 'y': args.pos[1], 'z': args.pos[2]}
    v = {'x': 0, 'y': 0, 'z': 0}

    t = turtle.Turtle()
    t.color("red")

    t.setpos(position[args.axis[0]], position[args.axis[1]])

    turtle.setup( width = 1000, height = 1000, startx = None, starty = None) 

    while True:
        try:
            v['x'] = sigma * (position['y'] - position['x'])
            v['y'] = position['x'] * (rho - position['z']) - position['y']
            v['z'] = position['x'] * position['y'] - beta * position['z']
            
            if v[args.axis[0]] == 0:
                h_deg = 90 if v[args.axis[1]] >= 0 else 270 
            else:
                h_deg = 180 * m.atan(v[args.axis[1]] / v[args.axis[0]]) / m.pi + 180
            
            vel = m.sqrt(v['x']**2 + v['y']**2 + v['z']**2)
            t.setheading(h_deg)

            position['x'] += v['x'] / vel
            position['y'] += v['y'] / vel
            position['z'] += v['z'] / vel

            t.setposition(position[args.axis[0]], position[args.axis[1]])
        except KeyboardInterrupt:
            break

    print("Exiting")
