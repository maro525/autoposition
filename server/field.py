from node import Node
from math import sin, cos, pi
import random


class Field:
    def __init__(self):
        self.nodes = []

    def setField(self, fieldsize):
        self.lx = fieldsize
        self.ly = fieldsize

    def setFieldXY(self, x, y):
        self.lx = x
        self.ly = y

    def initialize(self, nodenum_):
        self.nodes.clear()
        self.initNodes(nodenum_)
        self.setLink()

    def initNodes(self, nodenum_):
        minl = min(self.lx, self.ly)
        r = minl * (1/2 - 1/8)
        cx = self.lx / 2
        cy = self.ly / 2
        print("cx", cx, "cy", cy)
        for i in range(nodenum_):
            rad = pi*2*i/nodenum_
            x = cx + r * cos(rad)
            y = cy + r * sin(rad)
            self.nodes.append(Node(i, x, y, self.lx, self.ly))

    def setLink(self):
        nodesize = len(self.nodes)
        kk = int(nodesize * 3 / 5)
        linknode = random.choices(range(nodesize), k=kk)
        size = len(linknode)
        for i in range(size):
            type = 0
            if i is size-1:
                other_index = linknode[0]
            else:
                other_index = linknode[i+1]
            if i == other_index:
                continue
            self.nodes[i].addLink(type, self.nodes[other_index])
            self.nodes[other_index].addLink(type, self.nodes[i])

    '''
    {
        "nodes" : [
            {
                "x" : **, "y" : **, "w" : ** , "h" : **
            }
            {
                "x" : **, "y" : **, "w" : ** , "h" : **
            }
            ....
        ]
    }
    '''

    def getNodes(self):
        dic = {}
        nodes = []
        for n in self.nodes:
            nodeinfo = {}
            nodeinfo["x"] = n.pos[0]
            nodeinfo["y"] = n.pos[1]
            nodeinfo["w"] = n.r
            nodeinfo["h"] = n.r
            links = n.getlinkednodes()
            indexes = self.getNodeIndexes(links)
            nodeinfo["link"] = indexes
            nodes.append(nodeinfo)
        dic["nodes"] = nodes
        return dic

    def getNodeIndexes(self, nodes):
        indexes = []
        for n in nodes:
            index = self.nodes.index(n)
            indexes.append(index)
        return indexes
