from node import Node
from calculation import (attractiveforce, repulsiveforce,
                         magneticforce, inertialforce)
import copy

MINV = 0.05
NODE_NUM = 50


class Model:

    def __init__(self, iteration_):
        self.iteration = iteration_
        self.nodes = []
        self.move = []

    def setNode(self, n_):
        self.nodes = copy.copy(n_)
        self.move = [[0, 0]] * len(self.nodes)
        print("NODE SET size ->", len(self.nodes))

    def setlayout(self):
        for _ in range(self.iteration):
            self.calculate()

    def setlayoutForOnestep(self):
        if len(self.nodes) == 0:
            print("[ERROR]nodes size is 0")
            return
        self.calculate()

    def calculate(self):
        for i1, n1 in enumerate(self.nodes):
            print(i1, self.move[i1])
            for n2 in self.nodes:
                mv = self.getMoveVector(n1, n2)
                print("mv", mv)
                self.move[i1][0] += mv[0]
                self.move[i1][1] += mv[1]

        for i in range(len(self.nodes)):
            self.shift(i, self.move[i])

    def shift(self, i, mv):
        print(i, mv)
        self.nodes[i].move(mv[0], mv[1])

    def getMoveVector(self, n1, n2):
        if n1 == n2:
            print("n1 == n2")
            return

        mv = [0, 0]

        if self.isNext(n1, n2):
            afx, afy = attractiveforce(n1, n2)
            mfx, mfy = magneticforce(n1, n2, n1.getlinktype())
            mv = [afx+mfx, afy+mfy]
        else:
            rfx, rfy = repulsiveforce(n1, n2)
            mv = [rfx, rfy]

        ifx, ify = inertialforce(n1, mv)
        mv[0] += ifx
        mv[1] += ify

        mv = [MINV*i for i in mv]

        return mv

    def isNext(self, n1, n2):
        if n1.getlinktype() == 0:
            return False
        else:
            return True
