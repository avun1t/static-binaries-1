import socket
import threading

LISTEN_PORT = 6667
REMOTE_HOST = 'irc.libera.chat'
REMOTE_PORT = 6667

def handle(client_sock):
    remote_sock = socket.create_connection((REMOTE_HOST, REMOTE_PORT))
    threading.Thread(target=pipe, args=(client_sock, remote_sock)).start()
    threading.Thread(target=pipe, args=(remote_sock, client_sock)).start()

def pipe(src, dst):
    try:
        while True:
            data = src.recv(4096)
            if not data: break
            dst.sendall(data)
    finally:
        src.close()
        dst.close()

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind(('0.0.0.0', LISTEN_PORT))
    s.listen(5)
    while True:
        client, _ = s.accept()
        threading.Thread(target=handle, args=(client,)).start()
