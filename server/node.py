import numpy as np

class Node:  # TODO: ノードが長方形の場合も想定したほうが良いかも

    def __init__(self, i, x_, y_, mx, my):
        self.pos = [x_, y_]
        self.r = 10
        self.mx = mx
        self.my = my
        self.link = []
        self.index = i

    def addLink(self, t, n):
        linktype = t
        othernode = n
        if not self.searchLink(n):
            self.link.append([linktype,othernode])

    def searchLink(self, n):
        for link in self.link:
            if n in link:
                return True
        return False

    def getlinktype(self, n):
        for i, link in enumerate(self.link):
            if n in link:
                return self.link[i][0]
        return -1

    def getWidth(self):
        return self.r*2

    def getHeight(self):
        return self.r*2

    def getRadius(self):
        return self.r

    def getPos(self):
        return self.pos

    def getlinkednodes(self):
        linkednodes = []
        for link in self.link:
            linkednodes.append(link[1])
        return linkednodes

    def checklink(self, n):
        links = self.getlinkednodes()
        if len(links) == 0:
            return -1
        if n in links:
            i = links.index(n)
            linktype = self.link[i][0]
            return linktype
        else:
            return -1


    def setMax(self, maxX, maxY):
        self.maxX = maxX
        self.maxY = maxY

    def move(self, x, y):
        self.pos[0] += x
        self.pos[1] += y
        self.checkWall()

    def checkWall(self):  # TODO: これでOK？
        t = 0.0
        if self.pos[0] - self.r < 0:
            self.pos[0] = self.r + t
        elif self.pos[0] + self.r > self.mx:
            self.pos[0] = self.mx - self.r - t
        if self.pos[1] - self.r < 0:
            self.pos[1] = self.r + t
        elif self.pos[1] + self.r > self.my:
            self.pos[1] = self.my - self.r - t

    def mindToWall(self, axis):
        thresh = 50.0
        if axis is 0:
            if self.pos[0] < thresh:
                mindx = self.pos[0]
                return mindx
            elif self.pos[0] > self.mx - thresh:
                mindx = self.pos[0] - self.mx
                return mindx
            else:
                return None
        elif axis is 1:
            if self.pos[1] < thresh:
                mindy = self.pos[1]
                return mindy
            elif self.pos[1] > self.my - thresh:
                mindy = self.pos[1] - self.my
                return mindy
            else:
                return None
