import textwrap
import sys

def main():
    key = ""
    text = ""
    key_array = ""
    text_array = []
    text_str = ""
    padding_int = 0
    last_xor = ""
    line_indicator = 0
    file = open(sys.argv[1], "r")
    Lines = file.readlines()
    
    for line in Lines:
        if line_indicator == 0:
            key = line.strip()
            line_indicator += 1
        else:
            text += line.strip()

    for c in bytearray(key, "utf-8"):
        key_array += "0" + format(c, 'b')

    key_array_12_bits = key_array[0:12]

    for c in bytearray(text, "utf-8"):
        text_str += "0" + format(c, 'b')


    while(len(text_str) % 12):
        text_str += "1"
        padding_int += 1
        text_str += "0"
        padding_int += 1

    padding_binary = ("0" * ( 12 - (len(format(padding_int, 'b')) % 12))) + format(padding_int, 'b')
    
    text_str += padding_binary
    
    total_xor = ""
    output = ""
    text_array = textwrap.wrap(text_str, 12)

    for i in range(int(len(text_str) / 12)):
        if i == 0:
            print("Key in binary (first 12 bits): ", key_array_12_bits)
            print("First 12 bit block (reversed): ", text_str[0:12][::-1])
            for j in range(len(key_array_12_bits)):
                key_j = int(key_array_12_bits[j])
                text_j = int(text_str[0:12][::-1][j])
                total_xor += str(key_j ^ text_j)
            print("Xor                      : ", total_xor, "\n\n")
            output += total_xor
            last_xor = total_xor
        else:
            total_xor = ""
            print("next 12 bit block : ", text_array[i])
            print("Output of last Xor: ", last_xor)

            for j in range(len(text_array[i])):
                key_j = int(last_xor[j])
                text_j = int(text_array[i][j])
                total_xor += str(key_j ^ text_j)
            print("Xor                      : ", total_xor, "\n")

            last_xor = total_xor
            total_xor = ""

            print("Key in binary (first 12 bits): ", key_array_12_bits)
            print("Xor'ed output (reversed)     : ", last_xor[::-1])
            xor_rev = last_xor[::-1]
            for j in range(len(text_array[i])):
                key_j = int(key_array_12_bits[j])
                text_j = int(xor_rev[j])
                total_xor += str(key_j ^ text_j)
            print("Xor                      : ", total_xor, "\n\n\n")
            output += total_xor
            last_xor = total_xor

    print("Result: ", output)

if __name__ == '__main__':
    main()
