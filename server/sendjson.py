import json
from pythonosc import osc_message_builder, udp_client
from pythonosc import dispatcher, osc_server


class SendJson:

    def __init__(self, ip, port, sendaddress):
        self.client = udp_client.SimpleUDPClient(ip, port)
        self.sendaddress = sendaddress

    def setupserver(self, servaddress, func):
        self.servaddress = address
        dispatcher = dispatcher.Dispatcher()
        dispatcher.map(self.servaddress, func)

    def sendosc(self, jsontext):
        self.client.send_message(self.sendaddress, jsontext)

    def parsedict(self, d):
        jsontext = json.dumps(d)
        return jsontext

    def sendjson(self, d):
        jsontext = self.parsedict(d)
        self.sendosc(jsontext)
