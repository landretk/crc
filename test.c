#define CRC_IMPL
#define INCLUDE_CRC16 1
#define INCLUDE_CRC16ARC 1
#define INCLUDE_CRC32 1
#define INCLUDE_CRC32BZIP 1
#include "crclib.h"

#include <assert.h>
#include <string.h>
#include <stdio.h>

int main(void) {
    char const testStr[] = "123456789";
    const uint32_t testLen = strlen(testStr);
    uint16_t crc16val = 0;
    uint32_t crc32val = 0;

    // TEST 1

    printf("Test1: CRC computed in one part\n");
    crc16val = crc16(testStr, testLen, CRC16_INIT);
    printf("crc16: 0x%04x\n", crc16val);
    assert(crc16val == CRC16_CHECK);

    crc16val = crc16arc(testStr, testLen, CRC16ARC_INIT);
    printf("crc16arc: 0x%04x\n", crc16val);
    assert(crc16val == CRC16ARC_CHECK);

    crc32val = crc32(testStr, testLen, CRC32_INIT);
    printf("crc32: 0x%04x\n", crc32val);
    assert(crc32val == CRC32_CHECK);

    crc32val = crc32bzip(testStr, testLen, CRC32BZIP_INIT);
    printf("crc32bzip: 0x%04x\n", crc32val);
    assert(crc32val == CRC32BZIP_CHECK);
    printf("\n");

    // TEST 2

    printf("Test 2: CRC computed in two parts\n");
    size_t part1 = testLen/2;
    size_t part2 = testLen - part1;

    crc16val = crc16(testStr, part1, CRC16_INIT);
    crc16val = crc16(testStr+part1, part2, crc16val);
    printf("crc16: 0x%04x\n", crc16val);
    assert(crc16val == CRC16_CHECK);

    crc16val = crc16arc(testStr, part1, CRC16ARC_INIT);
    crc16val = crc16arc(testStr+part1, part2, crc16val);
    printf("crc16arc: 0x%04x\n", crc16val);
    assert(crc16val == CRC16ARC_CHECK);

    crc32val = crc32(testStr, part1, CRC32_INIT);
    crc32val = crc32(testStr+part1, part2, crc32val);
    printf("crc32: 0x%04x\n", crc32val);
    assert(crc32val == CRC32_CHECK);

    crc32val = crc32bzip(testStr, part1, CRC32BZIP_INIT);
    crc32val = crc32bzip(testStr+part1, part2, crc32val);
    printf("crc32bzip: 0x%04x\n", crc32val);
    assert(crc32val == CRC32BZIP_CHECK);
    printf("\n");

    // TEST 3

    printf("Test 3: CRC computed in two parts\n");
    part1 = testLen/3;
    part2 = part1;
    size_t part3 = testLen - part1 - part2;

    crc16val = crc16(testStr, part1, CRC16_INIT);
    crc16val = crc16(testStr+part1, part2, crc16val);
    crc16val = crc16(testStr+part1+part2, part3, crc16val);
    printf("crc16: 0x%04x\n", crc16val);
    assert(crc16val == CRC16_CHECK);

    crc16val = crc16arc(testStr, part1, CRC16ARC_INIT);
    crc16val = crc16arc(testStr+part1, part2, crc16val);
    crc16val = crc16arc(testStr+part1+part2, part3, crc16val);
    printf("crc16arc: 0x%04x\n", crc16val);
    assert(crc16val == CRC16ARC_CHECK);

    crc32val = crc32(testStr, part1, CRC32_INIT);
    crc32val = crc32(testStr+part1, part2, crc32val);
    crc32val = crc32(testStr+part1+part2, part3, crc32val);
    printf("crc32: 0x%04x\n", crc32val);
    assert(crc32val == CRC32_CHECK);

    crc32val = crc32bzip(testStr, part1, CRC32BZIP_INIT);
    crc32val = crc32bzip(testStr+part1, part2, crc32val);
    crc32val = crc32bzip(testStr+part1+part2, part3, crc32val);
    printf("crc32bzip: 0x%04x\n", crc32val);
    assert(crc32val == CRC32BZIP_CHECK);
}