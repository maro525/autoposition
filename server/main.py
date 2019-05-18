from model import Model
from field import Field
from node import Node

CALC_ITERATION = 1000
NODE_NUM = 50


def main():
    model = Model(CALC_ITERATION)
    field = Field()
    field.initNodes(NODE_NUM)


if __name__ == '__main__':
    main()

# TODO : edge type set
# TODO : クライアント側
