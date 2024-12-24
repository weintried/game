import socket
import json

def main():
    host = 'localhost'
    port = 12345

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((host, port))
        data = s.recv(1024)
        # print('Received', repr(data))
        json_data = json.loads(data.decode('utf-8'))
        print(json_data)

if __name__ == "__main__":
    main()