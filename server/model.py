from node import Node
from calculation import (attractiveforce, repulsiveforce, repulsiveToWall,
                         magneticforce, inertialforce)
import copy

MINV = 0.05


class Model:

    def __init__(self):
        self.nodes = []
        self.move = []

    def setNode(self, n_):
        self.nodes = copy.copy(n_)
        self.move = [[0, 0]] * len(self.nodes)
        print("NODE SET size ->", len(self.nodes))


    def setlayoutForOnestep(self):
        if len(self.nodes) == 0:
            print("[ERROR]nodes size is 0")
            return
        self.calculate()

    def calculate(self):
        for i1, n1 in enumerate(self.nodes):
            self.move[i1] = [0.0, 0.0]
            for n2 in self.nodes:
                mv = self.getMoveVector(n1, n2)
                if mv is None:
                    continue
                self.move[i1][0] += mv[0]
                self.move[i1][1] += mv[1]
        for i in range(len(self.nodes)):
            self.shift(i, self.move[i])

    def shift(self, i, mv):
        # print("shift", i, mv)
        self.nodes[i].move(mv[0], mv[1])

    def getMoveVector(self, n1, n2):
        if n1 == n2:
            return

        mv = [0, 0]

        print(n1.index)
        if self.isNext(n1, n2):
            afx, afy = attractiveforce(n1, n2)
            mfx, mfy = magneticforce(n1, n2, n1.getlinktype(n2))
            mv = [afx+mfx, afy+mfy]
            print('attractive',afx, afy)
            print('magnatic', mfx, mfy)
        else:
            rfx, rfy = repulsiveforce(n1, n2)
            print('repulsive', rfx, rfy)
            mv = [rfx, rfy]

        rwx, rwy = repulsiveToWall(n1)
        print('repulwall',rwx, rwy)
        ifx, ify = inertialforce(n1, mv)
        ifx, ify = (0, 0)
        mv[0] += (rwx+ifx)
        mv[1] += (rwy+ify)

        mv = [MINV*i for i in mv]

        return mv

    def isNext(self, n1, n2):
        if n1.checklink(n2) == 0:
            return True
        else:
            return False
