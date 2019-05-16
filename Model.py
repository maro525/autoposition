from node import Node
from calculation import (attractiveforce, repulsiveforce,
                         magneticforce, inertialforce)

MINV = 0.05
NODE_NUM = 50


class Model:

    def __init__(self, iteration_):
        self.iteration = iteration_
        self.nodes = []
        self.move = []

    def setNode(self, n_):
        self.nodes = n_

    def setlayout(self):
        for _ in range(self.iteration):
            self.calculate()

    def setlayoutForOnestep(self):
        self.calculate()

    def calculate(self):
        for i1, n1 in enumerate(self.nodes):
            for n2 in self.nodes:
                self.move[i1] = self.getMoveVector(n1, n2)

        for i in range(len(self.nodes)):
            self.shift(i, self.move[i])

    def shift(self, i, mv):
        self.nodes[i].move(mv)

    def getMoveVector(self, n1, n2):
        if n1 == n2:
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
