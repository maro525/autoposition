from model import Model
from field import Field
from node import Node
from sendjson import SendJson

CALC_ITERATION = 1000
NODE_NUM = 50
IP = "127.0.0.1"
SEND_PORT = 5775
RECV_PORT = 5665
SENDADDRESS = "/positions"
RECVADDRESS = "/command"
model = None
field = None
sj = None


def recvandsend():
    model.setlayoutForOnestep()
    d = field.getNodes()
    sj.sendjson(d)


def commandhandler(unused_addr, command, num):
    print("command", command, num)
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
    sj = SendJson(IP, SEND_PORT, RECVADDRESS)
    field.initNodes(NODE_NUM)
    model.setNode(field.nodes)
    sj.setupserver(IP, RECV_PORT, RECVADDRESS, commandhandler)
    sj.serv()


if __name__ == '__main__':
    main()

# TODO : edge type set
