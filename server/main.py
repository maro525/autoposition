from model import Model
from field import Field
from communication import Com
import time

CALC_ITERATION = 100
FIELD_SIZE = 800
NODE_NUM = 2
IP = "127.0.0.1"
SEND_PORT = 5775
RECV_PORT = 5665
SENDADDRESS = "/positions"
RECVADDRESS = "/command"
model = None
field = None
com = None


def recvandsend():
    global field, model, com
    model.setlayoutForOnestep()
    d = field.getNodes()
    com.sendjson(d)


def modelinitlize(num):
    field.initialize(num)
    model.setNode(field.nodes)
    d = field.getNodes()
    com.sendjson(d)

def setlayout():
    global field, model, com
    for i in range(CALC_ITERATION):
        print("ITER:",i)
        recvandsend()
        time.sleep(0.1)


def commandhandler(unused_addr, command, num):
    global field, com, model
    print("command", command, num)
    if command is 0:
        modelinitlize(num)
    elif command is 1:
        recvandsend()
    elif command is 2:
        setlayout()


def main():
    global model, field, com
    model = Model()
    field = Field()
    field.setField(FIELD_SIZE)
    com = Com()
    com.setupclient(IP, SEND_PORT, SENDADDRESS)
    com.setupserver(IP, RECV_PORT, RECVADDRESS, commandhandler)
    com.serv()


if __name__ == '__main__':
    main()
