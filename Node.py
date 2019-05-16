
class Node:  # TODO: ノードが長方形の場合も想定したほうが良いかも

    def __init__(self, x_, y_, mx, my):
        self.pos = [x_, y_]
        self.r = 10
        self.mx = mx
        self.my = my
        self.linktype = 0

    def setLink(self, t, n):
        self.linktype = t
        self.othernode = n

    def getWidth(self):
        return self.r*2

    def getHeight(self):
        return self.r*2

    def getRadius(self):
        return self.r

    def getPos(self):
        return self.pos

    def getlinktype(self):
        return self.linktype

    def setMax(self, maxX, maxY):
        self.maxX = maxX
        self.maxY = maxY

    def move(self, x, y):
        self.pos[0] += x
        self.pos[1] += y
        self.checkWall()

    def checkWall(self):  # TODO: これでOK？
        if self.pos[0] - self.r:
            self.pos[0] = self.r
        elif self.pos[0] + self.r:
            self.pos[0] = self.mx - self.r
        if self.pos[1] - self.r:
            self.pos[1] = self.r
        elif self.pos[1] + self.r:
            self.pos[1] = self.my - self.r
