#!/usr/bin/env python3

from enum import Enum, IntEnum
import argparse

INFO = '''
Some common CRC parameters:
(Check is with ascii string "123456789")

CRC8/SAE-J1850:    0x1D forward, init=0xff, final=0xff, check=0x4b
CRC8/AUTOSAR:      0x2F forward, init=0xff, final=0xff, check=0xdf

CRC16/FALSE-CCITT: 0x1021 forward, init=0xffff, check=0x29b1
CRC16/KERMIT:      0x1021 reflect, init=0x0000, check=0x2189
CRC16/ARC:         0x8005 reflect, init=0x0000, check=0xbb3d

CRC32:             0x04C11DB7 reflect, init=0xffffffff, final=0xffffffff, check=0xcbf43926
CRC32/AUTOSAR:     0xF4ACFB13 reflect, init=0xffffffff, final=0xffffffff, check=0x1697d06a

CRC64/ECMA-182:    0x42F0E1EBA9EA3693 reflect, init=0xffffffffffffffff,
                       final=0xffffffffffffffff, check=0x995dc9bbdf1939fa
'''

class CRCType(Enum):
    Forward = 1,
    Reflected = 2

def bit_reverse(num, width):
    bit_str = '{0:0{1}b}'.format(num, width)
    return int(bit_str[::-1], 2)

def generate_crc(width, type: CRCType, poly):
    table = []

    max_int = ((1 << width) - 1)
    poly = poly & max_int
    poly = poly if type == CRCType.Forward else bit_reverse(poly, width)

    for byte in range(256):
        if type == CRCType.Forward:
            crc = (byte << (width-8))
            for bit in range(8):
                if crc & (1 << (width-1)):
                    crc = ((crc << 1) & max_int) ^ poly
                else:
                    crc = ((crc << 1) & max_int)
        elif type == CRCType.Reflected:
            crc = byte
            for bit in range(8):
                if crc & 1:
                    crc = (crc >> 1) ^ poly
                else:
                    crc = crc >> 1
        table.append(crc)

    return table

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="CRC table generator", epilog=INFO, formatter_class=argparse.RawTextHelpFormatter)

    parser.add_argument('width', help="Bit width of CRC polynomial")
    parser.add_argument('polynomial', help="CRC polynomial e.g. 0x1021 for CRC16-CCITT, 0x04C11DB7 for CRC32")
    parser.add_argument('--name', default=None, help="Name of CRC table")
    parser.add_argument('--reflect', action='store_true', help="Generate reflected table e.g. CRC16-ARC")

    args = parser.parse_args()

    width = int(args.width)
    if width != 8 and width != 16 and width != 32 and width != 64:
        print("Error: width must be one of 8, 16, 32, 64\n")
        parser.print_usage()
        exit(1)
    
    if args.name == None:
        name = "crc" + str(width)
    else:
        name = args.name

    crc_type = CRCType.Reflected if args.reflect else CRCType.Forward

    polynomial = int(args.polynomial, 0)

    table = generate_crc(width, crc_type, polynomial)

    cols = 8
    if width == 64:
        cols = 4

    print(f"static const uint{width}_t {name.upper()}_TABLE[256] = {{")
    for i in range(len(table)//cols):
        for j in range(cols):
            index = i*cols+j
            if j == 0:
                print("    ", end='')
            if (index < len(table)):
                print('0x{0:0{1}X}'.format(table[index], width//4), end='')
            if (index < len(table)-1):
                print(',', end='')
            if j < (cols-1):
                print(' ', end='')
        print("")
    print(f"}};\n")

    print(f"uint{width}_t {name.lower()}(void const* data, size_t len, uint{width}_t init) {{")
    crc_type_str = "ref" if crc_type == CRCType.Reflected else "fwd"
    print(f"    return crc{width}{crc_type_str}(data, len, init, {name.upper()}_TABLE);")
    print(f"}}")
