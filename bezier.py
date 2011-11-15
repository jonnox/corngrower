from Tkinter import *

import random as rand

master = Tk()
win = Canvas(master, width=1000, height=600)
win.pack()

def compbez(p0,p1,p2,p3,t):
	return (pow(1.0 - t,3)*p0 + 3.0*pow(1.0 - t,2)*t*p1 +
	                       3.0*(1.0 - t) * pow(t,2) * p2 +
	                        pow(t,3) * p3)

def bez(p0,p1,p2,p3,t):
	return (compbez(p0[0],p1[0],p2[0],p3[0],t),
            compbez(p0[1],p1[1],p2[1],p3[1],t),
            compbez(p0[2],p1[2],p2[2],p3[2],t))


points = [(0.0,300.0,0.0),(20.0,300.0,0.0),(40.0,300.0,0.0)]

x = 40.0

dx = 20.0

y = 0.0

while(x < 980.0):
	x = x + dx
	if(rand.random() < 0.5):
		y = (rand.random() * 20.0) + 280.0
	else:
		y = (rand.random() * 20.0) + 300.0
	points.append((x,y,0.0))

points.append((980.0,300.0,0.0))
points.append((1000.0,300.0,0.0))

dj = 0.01
djB = 0.01 / 17.0

# Create bezier curve for whole leaf
jB = 0.0;
prevB = bez((0.0,100.0,0.0),(250.0,50.0,0.0),(750.0,50.0,0.0),(1000.0,100.0,0.0),0.0)
#while(jB <= 1.0):
#	resB = bez((0.0,100.0,0.0),(250.0,50.0,0.0),(750.0,50.0,0.0),(1000.0,100.0,0.0),jB)
#	win.create_line(prevB[0],prevB[1],resB[0],resB[1],fill="red")
#	prevB = resB
#	jB = jB + djB

for i in range(9):
	j = 0.0;
	prev = bez(points[i*6],points[i*6 + 2],points[i*6 + 4],points[i*6 + 6],0.0)
	while(j <= 1.0):
		res = bez(points[i*6],points[i*6 + 2],points[i*6 + 4],points[i*6 + 6],j)
		j = j + dj

for i in range(17):
	j = 0.0;
	prev = bez(points[i*3],points[i*3 + 1],points[i*3 + 2],points[i*3 + 3],0.0)
	while(j <= 1.0):
		res = bez(points[i*3],points[i*3 + 1],points[i*3 + 2],points[i*3 + 3],j)
		
		resB = bez((0.0,100.0,0.0),(250.0,50.0,0.0),(750.0,50.0,0.0),(1000.0,100.0,0.0),(i + j)/17.0)
		win.create_line(prevB[0],300 + prevB[1], resB[0], 300 + resB[1],fill="red")
		win.create_line(prev[0],prev[1] + prevB[1],res[0],res[1] + resB[1],fill="black")
		prevB = resB
		
		win.create_line(prev[0],prev[1],res[0],res[1],fill="black")
		prev = res
		j = j + dj

win.create_line(0,300,1000,300,fill="green")

win.mainloop()
