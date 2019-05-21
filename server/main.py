from model import Model
from field import Field
from communication import Com

CALC_ITERATION = 1000
NODE_NUM = 50
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


def commandhandler(unused_addr, command, num):
    global field, com, model
    print("command", command, num)
    if command is 0:
        modelinitlize(num)
    elif command is 1:
        recvandsend()
    elif command is 2:
        model.setlayout()
    elif command is 3:
        modelinitlize(num)


def main():
    global model, field, com
    model = Model(CALC_ITERATION)
    field = Field()
    com = Com()
    com.setupclient(IP, SEND_PORT, SENDADDRESS)
    com.setupserver(IP, RECV_PORT, RECVADDRESS, commandhandler)
    com.serv()


if __name__ == '__main__':
    main()