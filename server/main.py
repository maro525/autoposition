from model import Model
from field import Field
from node import Node
from sendjson import SendJson

CALC_ITERATION = 1000
NODE_NUM = 50
IP = "127.0.0.1"
PORT = 5885
SENDADDRESS = "/positions"
RECVADDRESS = "/command"

model = None
field = None
sj = None


def recvandsend():
    model.setlayoutForOnestep()
    d = field.getNodes()
    sj.sendjson(d)


def dispatch(command, num):
    if command is 0:
        field.setField(num)
    elif command is 1:
        recvandsend()
    elif command is 2:
        model.setlayout()


def main():
    global model, field, sj
    model = Model(CALC_ITERATION)
    field = Field()
    sj = SendJson(IP, PORT, RECVADDRESS)
    field.initNodes(NODE_NUM)
    model.setNode(field.nodes)
    sj.setupserver(RECVADDRESS, dispatch)


if __name__ == '__main__':
    main()

# TODO : edge type set
