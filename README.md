## CRC Library

Some basic CRC functions demonstrating the different types of CRC algorithms (forward/reflected)

Lookup tables behind defines so only data for desired algorithms is pulled into project

Default algorithms chosen to match Python stdlib binascii.crc_hqx() and binascii.crc32() for consistentcy across tools


## Usage
Use by defining a crc.h/crc.c implementation with the algorithms you want selected
```c
// crc.h
uint16_t crc16(void const* data, size_t len, uint16_t init);
uint32_t crc32(void const* data, size_t len, uint32_t init);

// crc.c
#define CRC_IMPL
#define INCLUDE_CRC16 1
#define INCLUDE_CRC16ARC 0
#define INCLUDE_CRC32 1
#include "crclib.h"
```

For a custom polynomial, generate a new table with gen_crc.py and add it to your crc.c
```bash
./gen_crc.py 16 0xC867 --name crc16cdma >> crc.c
```

```c
// crc.c
#define CRC_IMPL
#include "crclib.h"

static const uint16_t CRC16CDMA_TABLE[256] = {
    0x0000, 0xC867, 0x58A9, 0x90CE, 0xB152, 0x7935, 0xE9FB, 0x219C,
...
    0xB5F0, 0x7D97, 0xED59, 0x253E, 0x04A2, 0xCCC5, 0x5C0B, 0x946C
};

uint16_t crc16cdma(void const* data, size_t len, uint16_t init) {
    return crc16fwd(data, len, init, CRC16CDMA_TABLE);
}
```

## Run Tests
```bash
cc -o crc-test test.c && ./crc-test
```
