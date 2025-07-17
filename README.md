## CRC Library

Some basic CRC functions demonstrating the different types of CRC algorithms (forward/reflected)

Lookup tables behind defines so only data for desired algorithms is pulled into project


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
