a = "01100001"
b = "01100010"
c = "01100011"

def pad(string):
    string = int(string) | 0xFFFFFFFF
    return bin(string)[2:]

msg = a + b + c
lenMsgInBin = bin(len(msg))[2:]
print(lenMsgInBin)
msgSch = msg + '1' + '0'*(512 - len(msg) - 1 - len(lenMsgInBin)) + lenMsgInBin

print(msgSch)
print(len(msgSch))
