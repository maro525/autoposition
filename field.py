from node import Node
from math import sin, cos, pi


class Field:
    def __init__(self):
        self.nodes = []
        self.edges = []
        self.lx = 800
        self.ly = 800

    def setField(self, x, y):
        self.lx = x
        self.ly = y

    def initNodes(self, num_):
        minl = min(self.lx, self.ly)
        r = minl * (1/2 - 1/8)
        cx = self.lx / 2
        cy = self.ly / 2
        for i in range(num_):
            rad = pi*2*i/num_
            x = cx + r * cos(rad)
            y = cy + r * sin(rad)
            self.nodes.append(Node(x, y, self.lx, self.ly))
