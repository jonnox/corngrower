import re,sys

from Tkinter import *

master = Tk()
win = Canvas(master, width=300, height=800)
win.pack()

dw = 0.5
dh = 0.5
ow = 1.0
currentHeight = 799.0
center = 300.0 / 2.0

def processNode(t,s,w,h,l=None):
	sn = int(s)
	if t == 'C':
		return "%c%d(%f,%f)" %(t,sn,float(w) + dw,float(h) + dh)
	elif t == 'B':
		if(sn < 4):
			return "%c%d(%f,%f,%d)" %(t,sn + 1,float(w) + dw,float(h) + dh,int(l))
		else:
			return "%c%d(%f,%f)%c%d(%f,%f,%d)" %('I',1,float(w) + dw,float(h) + dh,
					'B',1,float(w) + dw - ow,float(h) + dh,int(l) + 1)
	
	elif t == 'I':
		if(sn < 4):
		        return "%c%d(%f,%f)" %(t,sn + 1,float(w) + dw,float(h) + dh)
		else:
		        return "%c%d(%f,%f)" %('M',1,float(w) + dw,float(h) + dh)
	elif t == 'M':
		if(sn < 4):
		        return "%c%d(%f,%f)" %(t,sn + 1,float(w) + dw,float(h) + dh)
		else:
		        return "%c%d(%f,%f)" %('E',1,float(w) + dw,float(h) + dh)
	elif t == 'E':
		if(sn < 4):
		        return "%c%d(%f,%f)" %(t,sn + 1,float(w) + dw,float(h) + dh)
		else:
		        return "%c%d(%f,%f)" %('C',0,float(w) + dw,float(h) + dh)

def drawNode(t,s,w,h,l=None):
	global currentHeight
	sn = int(s)
	wn = float(w) / 2
	hn = float(h)
	if t == 'C':
		win.create_rectangle(center - wn, currentHeight - hn ,center + wn, currentHeight ,outline="blue")
		currentHeight = currentHeight - hn
	elif t == 'B':
		win.create_rectangle(center - wn, currentHeight - hn ,center + wn, currentHeight ,outline="black")
	elif t == 'I':
		win.create_rectangle(center - wn, currentHeight - hn ,center + wn, currentHeight ,outline="orange")
	elif t == 'M':
		win.create_rectangle(center - wn, currentHeight - hn ,center + wn, currentHeight ,outline="red")
	elif t == 'E':
		edh = (hn / 4.0)
		win.create_rectangle(center - wn, currentHeight - sn * edh,center + wn, currentHeight + (4 - sn) * edh,outline="green")
		currentHeight = currentHeight + (4 - sn) * edh

#win.create_line(0, 0, 200, 100)
#win.create_line(0, 100, 200, 0, fill="red", dash=(4, 4))
#win.create_rectangle(0, 0.5, 150, 75,outline="blue")

#itemRegex = "([A-Z])([0-9])\(([0-9]*\.?[0-9]+),([0-9]*\.?[0-9]+),([0-9]*\.?[0-9]+)\)"

itemRegex = "([A-Z])([0-9])\(([0-9]*\.?[0-9]+),([0-9]*\.?[0-9]+),?([0-9]+)?\)"

s1 = "E1(0.3,0.4,.3)I4(0.1,0.4,1)"
s2 = "B1(1.0,7.0,1)"

#re.findall(itemRegex,s)

print "Base: %s" %(s2)

for i in range(int(sys.argv[1])):
	nodes = re.findall(itemRegex,s2)
	res = ""
	for j in nodes:
		res = res + processNode(*j)
	print "Step %d: %s" %(i,res)
	s2 = res

nodes = re.findall(itemRegex,s2)
for j in nodes:
	drawNode(*j)

mainloop()
