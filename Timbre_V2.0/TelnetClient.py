import telnetlib as tl

HOST = "192.168.0.199"
PUERTO = 35
TIMEOUT = 30


tn = tl.Telnet(HOST, PUERTO, TIMEOUT)
tn.write("A?/;".encode('ascii') + b"\n")
print(tn.read_all().decode('ascii'))
