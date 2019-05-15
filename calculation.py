from node import Node
import math

DC1 = 30.0
DC2 = 100.0
DC3 = 0.01
DC4 = 0.01
DC5 = 0.01
DC6 = 10.0
DC7 = 1
DC8 = 1
DC9 = 0
DC10 = math.pi/4.0
DC11 = math.pi/2.0
DC12 = 20000.0


# TODO : 閾値設定
def attractiveforce(n1, n2, axis):
    dx = n1.pos[0] - n2.posa[0]
    dy = n1.pos[1] - n2.pos[1]
    d = getDistance(n1, n2)
    dc = d / DC2
    f = -DC1 * dc
    afx = f * dx / d
    afy = f * dy / d
    return (afx, afy)

# TODO: 閾値設定


def repulsiveforce(n1, n2, axis):
    dx = n1.pos[0] - n2.posa[0]
    dy = n1.pos[1] - n2.pos[1]
    d = getDistance(n1, n2)
    f = DC12 / (d * d)
    rfx = f * (dx / d)
    rfy = f * (dy / d)
    return (rfx, rfy)


def magneticforce(n1, n2, type_, axis):
    d = getDistance(n1, n2)
    dx = n1.pos[0] - n2.pos[1]
    dy = n1.pos[1] - n2.pos[1]
    dk = math.atan2(dy, dx)
    k = getK(type_)
    t = getT(k, dk)
    if d == 0 or t == 0:
        return
    f = getF(d, t, type_)
    mft = getmftype(k, dx, dy, dk, axis)
    if mft == 0:
        return f * (math.fabs(dx) / d)
    elif mft == 1:
        return -f * (math.fabs(dx) / d)
    elif mft == 2:
        return f * (math.fabs(dy) / d)
    elif mft == 3:
        return -f * (math.fabs(dy) / d)


def getmftype(k, dx, dy, dk, axis):
    t = -1

    if k < 0 and getQ(dx, dy) and getB1(k, dk) and axis == 1:
        t = 3
    elif k < 0 and getQ(dx, dy) and getB1(k, dk) and axis == 0:
        t = 0
    elif k < 0 and getQ(dx, dy) and (not getB1(k, dk)) and axis == 1:
        t = 2
    elif k < 0 and getQ(dx, dy) and (not getB1(k, dk)) and axis == 0:
        t = 1
    elif k < 0 and (not getQ(dx, dy) and getB2(k, dk)) and axis == 1:
        t = 2
    elif k < 0 and (not getQ(dx, dy)) and getB2(k, dk) and axis == 0:
        t = 0
    elif k < 0 and (not getQ(dx, dy)) and (not getB2(k, dk)) and axis == 1:
        t = 3
    elif k < 0 and (not getQ(dx, dy)) and (not getB2(k, dk)) and axis == 0:
        t = 1
    elif k >= 0 and getQ(dx, dy) and getB3(k, dk) and axis == 1:
        t = 2
    elif k >= 0 and getQ(dx, dy) and getB3(k, dk) and axis == 0:
        t = 1
    elif k >= 0 and getQ(dx, dy) and (not getB3(k, dk)) and axis == 1:
        t = 3
    elif k >= 0 and getQ(dx, dy) and (not getB3(k, dk)) and axis == 0:
        t = 0
    elif k >= 0 and (not getQ(dx, dy) and getB4(k, dk)) and axis == 1:
        t = 3
    elif k >= 0 and (not getQ(dx, dy)) and getB4(k, dk) and axis == 0:
        t = 1
    elif k >= 0 and (not getQ(dx, dy)) and (not getB4(k, dk)) and axis == 1:
        t = 2
    elif k >= 0 and (not getQ(dx, dy)) and (not getB4(k, dk)) and axis == 0:
        t = 0

    return t


def getQ(dx, dy):
    if (dx < 0 and dy < 0) or (dx >= 0 and dy >= 0):
        return True
    elif (dx < 0 and dy >= 0) or (dx >= 0 and dy < 0):
        return False


def getB1(k, dk):
    if k < -math.pi/2.0 and ((math.pi/2.0 >= dk and dk > math.pi+k) or (k < dk and dk < -math.pi/2.0)):
        return True
    else:
        return False


def getB2(k, dk):
    if k > -math.pi/2.0 and ((-math.pi/2.0 < dk and dk < k) or (math.pi/2.0 < dk and dk < math.pi+k)):
        return True
    else:
        return False


def getB3(k, dk):
    if k < math.pi/2.0 and ((math.pi/2.0 > dk and dk > k) or (k-math.pi < dk and dk < -math.pi/2.0)):
        return True
    else:
        return False


def getB4(k, dk):
    if k > math.pi/2.0 and ((-math.pi/2.0 < dk and dk < k-math.pi) or (math.pi/2.0 < dk and dk < k)):
        return True
    else:
        return False


def getF(d, t, type_):
    if type_ == 0:
        f = DC3 * DC6 * math.pow(d, DC7) * math.pow(t, DC8)
    elif type_ == 1:
        f = DC4 * DC6 * math.pow(d, DC7) * math.pow(t, DC8)
    elif type_ == 2:
        f = DC4 * DC6 * math.pow(d, DC7) * math.pow(t, DC8)
    elif type_ == 3:
        f = DC5 * DC6 * math.pow(d, DC7) * math.pow(t, DC8)
    elif type_ == 4:
        f = DC5 * DC6 * math.pow(d, DC7) * math.pow(t, DC8)
    return f


def getT(k, dk):
    if math.fabs(k-dk) > math.pi:
        t = math.fabs(k-dk-2.0*math.pi)
    else:
        t = math.fabs(k-dk)
    return t


def getK(type_):
    if type_ == 1 or type_ == 2:
        k = DC10
        if type_ == 1 and DC10 > 0:
            k = DC10 - math.pi
        elif type_ == 1 and DC10 <= 0:
            k = DC10 + math.pi
    if type_ == 3 or type_ == 4:
        k = DC11
        if type_ == 3 and DC11 > 0:
            k = DC11 - math.pi
        elif type_ == 3 and DC11 <= 0:
            k = DC11 + math.pi

    if type_ == 0:
        k = DC9
        if math.fabs(k-dk) <= 3.0 / 2.0 * math.pi or math.pi / 2.0 < math.fabs(k-dk):
            if DC9 > 0:
                k = k - math.pi
            else:
                k = k + math.pi

    return k


def getDistance(n1, n2):
    if isIntersect(n1, n2):
        return 10
    if isParallel(n1, n2):
        return abs(n1.pos[0]-n2.pos[0])
    if isVertical(n1, n2):
        return abs(n1.pos[1]-n2.pos[0])

    dx2 = pow(n1.pos[0]-n2.pos[0], 2)
    dy2 = pow(n1.pos[1]-n2.pos[1], 2)

    return sqrt(dx2+dy2)


def isIntersect(n1, n2):
    return False


def isParallel(n1, n2):
    if n1.pos[1] == n2.pos[1]:
        return True
    else:
        return False


def isVertical(n1, n2):
    if n1.pos[0] == n2.pos[0]:
        return True
    else:
        return False
