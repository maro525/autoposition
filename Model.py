from edge import Edge
from node import Node
from calculation import *


class Model:

    def __init__(self, iteration_):
        self.iteration = iteration_
        self.nodes = []
        self.edge = []
        self.move = []

    def setNode(self, n_):
        self.nodes = n_

    def setlayout(self):
        for _ in range(self.iteration):
            self.calculate()

    def calculate(self):
        for i1, n1 in enumerate(self.nodes):
            for n2 in self.nodes:
                self.move[i1] = self.getMove(n1, n2)

    def getMove(self, n1, n2):
        if n1 == n2:
            return

        mv = (0, 0)

        if self.isNext(n1, n2):
            af = self.getAttractiveForce(n1, n2)
            mf = self.getMagneticForce(n1, n2)
            mv[0] = af[0] + mf[0]
            mv[1] = af[1] + mf[1]
        else:
            rf = self.getRepulsiveForce(n1, n2)
            mv[0] = rf[0]
            mv[1] = rf[1]

        return mv

    # return (afx, afy)
    # afx = attractive force on x axis
    # afy = attractive force on y axis
    def getAttractiveForce(self, n1, n2):
        afx = attractiveforce(n1, n2, 0)
        afy = attractiveforce(n1, n2, 1)
        return (afx, afy)

    def getRepulsiveForce(self, n1, n2):
        rfx = repulsiveforce(n1, n2, 0)
        rfy = repulsiveforce(n1, n2, 1)
        return (rfx, rfy)

    def getMagneticForce(self, n1, n2):
        mfx = magneticforce(n1, n2, self.getEdgeType(n1, n2), 0)
        mfy = magneticforce(n1, n2, self.getEdgeType(n1, n2), 1)
        return (mfx, mfy)

    def isNext(self, n1, n2):  # TODO:nodeどうしの隣接関係をedgeデータから確認
        return True

    # 1: 関連
    # 2: 集約親
    # 3: 集約子
    # 4: 継承親
    # 5: 継承子
    def getEdgeType(self, n1, n2):  # TODO: edge同士の関係
        return 1

    # return (1, 0) or (0, 1)
    # 1 : parent 0 : child
    def getRelation(self, n1, n2):  # TODO: 親子関係の抽出
        return 1
