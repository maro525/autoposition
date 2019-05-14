from edge import Edge
from node import Node


class Model:
    self.nodes = []
    self.edge = []

    def __init__(self, iteration_):
        self.iteration = iteration_

    def setNode(self, n_):
        self.nodes = n_

    def setlayout(self):
        for i in range(self.iteration):
            for n1 in self.nodes:
                for n2 in self.nodes:
                    if n1 is not n2:
                        self.calculate(n1, n2)

    def isNext(self, n1_, n2_):
        return True

    def calculate(self, n1_, n2_):
        if isNext(n1_, n2_):
