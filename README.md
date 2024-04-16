# Cypher block chaining

## General Info
This is an implementation where you take a key, convert it to binary, and use it in conjuction with a certain order of xor'ing the string to create an "encrypted" string. This makes use of Cipher Block Chaining (CBC) as the underlaying technology to achieve the output.

Description:
 * Here are the steps you should follow:

    > Convert the ascii key to a binary (10101010) representation.
    
    > Convert the ascii text to binary representation.

    > Break the binary text from number 2 up into some larger blocks (you will use 12 bits as your block size, but you theoretically could use anything). If the last block is less than 12, you should add alternating 1’s and 0’s to it until you have 12. Finally, if you added some padding, you should append a final block (of size 12) that contains the number of bits you added. I.e. If I added 4 bits of padding, I would append the block ‘000000000100’ as the final block to be encoded.
   
    > Each of the above (12 bit) blocks will now be encrypted, following this process:
        Take the first block to be encrypted, reverse it, Xor it with the first 12 bits of the key.(store as first block of encrypted output)
        Take the next block and Xor it with the encrypted output of the first block. Reverse the new block, xor it with the first 12 bits of the key. (add to encrypted output stream)
        repeat until all the blocks are encrypted.

## Example
![image](https://github.com/Binary141.com/Cypher-block-chaining/raw/master/usage.png)

## Toolstack
* [Python](https://www.python.org/)
* [C++](https://www.cplusplus.com)

## Build Instructions
Clone repository

        git clone https://github.com/Binary141/Cypher-block-chaining.git

Navigate to project repository

        cd 4510-p15

Python:

        python p15.py encrypt.txt

C++:

        make run
