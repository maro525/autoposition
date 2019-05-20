import json
from pythonosc import osc_message_builder, udp_client
from pythonosc import dispatcher, osc_server


class SendJson:

    def __init__(self, ip, port, sendaddress):
        self.client = udp_client.SimpleUDPClient(ip, port)
        self.sendaddress = sendaddress
        self.dispatcher = dispatcher.Dispatcher()

    def setupserver(self, ip, port, servaddress, func):
        self.servaddress = servaddress
        self.dispatcher.map(self.servaddress, func)
        self.server = osc_server.ThreadingOSCUDPServer(
            (ip, port), self.dispatcher)

    def sendosc(self, jsontext):
        self.client.send_message(self.sendaddress, jsontext)

    def parsedict(self, d):
        jsontext = json.dumps(d)
        return jsontext

    def sendjson(self, d):
        jsontext = self.parsedict(d)
        self.sendosc(jsontext)

    def serv(self):
        print("Serving on {}".format(self.server.server_address))
        self.server.serve_forever()
