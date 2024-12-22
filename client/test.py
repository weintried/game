
class Player:
    def __init__(self, name):
        self.ID: int = None
        self.position: tuple[float, float] = (0, 0)
        self.state: str = "idle"

def get_server_respoen():
    # get response from server, which is a json string
    response = ...
    for player in response["players"]:
        player = Player(player["name"])
        player.ID = player["ID"]
        player.position = player["position"]
        player.state = player["state"]
        print(player.ID, player.position, player.state)


