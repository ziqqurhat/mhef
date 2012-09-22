#include "data.h"

static const unsigned char decryption_table[] = {
    0xcb, 0x96, 0x85, 0xa6, 0x5f, 0x3e, 0xab, 0x03, 0x50, 0xb7, 0x9c, 0x5c, 0xb2, 0x40, 0xef, 0xf6,
    0xff, 0x61, 0x15, 0x29, 0xa2, 0xf1, 0xec, 0x52, 0x35, 0x28, 0xd9, 0x68, 0x24, 0x36, 0xc4, 0x74,
    0x26, 0xe2, 0xd5, 0x8c, 0x47, 0x4d, 0x2c, 0xfa, 0x86, 0x66, 0xc1, 0x4f, 0x0b, 0x81, 0x5b, 0x1b,
    0xc0, 0x0a, 0xfd, 0x17, 0xa4, 0xa9, 0x6d, 0x63, 0xad, 0xf3, 0xf4, 0x6e, 0x8d, 0x89, 0x14, 0xdd,
    0x59, 0x87, 0x4a, 0x30, 0xce, 0xfe, 0x3f, 0x7e, 0x06, 0x49, 0xa5, 0x04, 0x5e, 0xd0, 0xde, 0xe8,
    0x0f, 0xd4, 0x13, 0x1f, 0xba, 0xb9, 0x69, 0x71, 0x3d, 0xe4, 0xdc, 0x58, 0x90, 0x34, 0x3a, 0x3c,
    0xca, 0x10, 0x76, 0xc7, 0xc8, 0x45, 0x33, 0xc3, 0x92, 0x1d, 0x2b, 0x1c, 0x8f, 0x6f, 0x05, 0x07,
    0x38, 0x57, 0x51, 0xd6, 0xda, 0x2d, 0xb3, 0xc6, 0x2e, 0x64, 0x32, 0x1e, 0x43, 0xb1, 0x5d, 0xe1,
    0xbb, 0x8e, 0x9d, 0x72, 0x77, 0xf2, 0x27, 0xc9, 0x7f, 0x9e, 0xaa, 0x6a, 0x2f, 0x6c, 0xf9, 0x48,
    0xe7, 0xa0, 0x09, 0x56, 0xb8, 0xbd, 0x20, 0x41, 0xcd, 0x95, 0x80, 0xd7, 0x23, 0x0c, 0x42, 0xe5,
    0xae, 0x8b, 0x7d, 0xbc, 0x54, 0x39, 0xbf, 0x65, 0x01, 0x88, 0xe0, 0x7b, 0xb6, 0x16, 0x18, 0x4b,
    0xcc, 0x22, 0x5a, 0xb5, 0xeb, 0xfc, 0xf8, 0x9b, 0x4e, 0xe6, 0xa8, 0xbe, 0x67, 0x73, 0x97, 0x94,
    0x00, 0x62, 0xb4, 0xd2, 0x21, 0x25, 0x11, 0x82, 0xdb, 0x93, 0x02, 0x84, 0x7c, 0xd3, 0xb0, 0xa3,
    0x91, 0xa7, 0xf7, 0x55, 0x70, 0x7a, 0x08, 0x75, 0x8a, 0x53, 0x79, 0xfb, 0x9f, 0x46, 0xf5, 0x83,
    0xd8, 0x0e, 0xe9, 0xed, 0x12, 0xd1, 0xdf, 0xf0, 0x37, 0x2a, 0x44, 0x19, 0x9a, 0x31, 0xcf, 0xa1,
    0xaf, 0xe3, 0x3b, 0x1a, 0x4c, 0x78, 0xc2, 0x60, 0xee, 0x98, 0x6b, 0x0d, 0x99, 0xea, 0xc5, 0xac
};

static const unsigned char encryption_table[] = {
    0xc0, 0xa8, 0xca, 0x07, 0x4b, 0x6e, 0x48, 0x6f, 0xd6, 0x92, 0x31, 0x2c, 0x9d, 0xfb, 0xe1, 0x50,
    0x61, 0xc6, 0xe4, 0x52, 0x3e, 0x12, 0xad, 0x33, 0xae, 0xeb, 0xf3, 0x2f, 0x6b, 0x69, 0x7b, 0x53,
    0x96, 0xc4, 0xb1, 0x9c, 0x1c, 0xc5, 0x20, 0x86, 0x19, 0x13, 0xe9, 0x6a, 0x26, 0x75, 0x78, 0x8c,
    0x43, 0xed, 0x7a, 0x66, 0x5d, 0x18, 0x1d, 0xe8, 0x70, 0xa5, 0x5e, 0xf2, 0x5f, 0x58, 0x05, 0x46,
    0x0d, 0x97, 0x9e, 0x7c, 0xea, 0x65, 0xdd, 0x24, 0x8f, 0x49, 0x42, 0xaf, 0xf4, 0x25, 0xb8, 0x2b,
    0x08, 0x72, 0x17, 0xd9, 0xa4, 0xd3, 0x93, 0x71, 0x5b, 0x40, 0xb2, 0x2e, 0x0b, 0x7e, 0x4c, 0x04,
    0xf7, 0x11, 0xc1, 0x37, 0x79, 0xa7, 0x29, 0xbc, 0x1b, 0x56, 0x8b, 0xfa, 0x8d, 0x36, 0x3b, 0x6d,
    0xd4, 0x57, 0x83, 0xbd, 0x1f, 0xd7, 0x62, 0x84, 0xf5, 0xda, 0xd5, 0xab, 0xcc, 0xa2, 0x47, 0x88,
    0x9a, 0x2d, 0xc7, 0xdf, 0xcb, 0x02, 0x28, 0x41, 0xa9, 0x3d, 0xd8, 0xa1, 0x23, 0x3c, 0x81, 0x6c,
    0x5c, 0xd0, 0x68, 0xc9, 0xbf, 0x99, 0x01, 0xbe, 0xf9, 0xfc, 0xec, 0xb7, 0x0a, 0x82, 0x89, 0xdc,
    0x91, 0xef, 0x14, 0xcf, 0x34, 0x4a, 0x03, 0xd1, 0xba, 0x35, 0x8a, 0x06, 0xff, 0x38, 0xa0, 0xf0,
    0xce, 0x7d, 0x0c, 0x76, 0xc2, 0xb3, 0xac, 0x09, 0x94, 0x55, 0x54, 0x80, 0xa3, 0x95, 0xbb, 0xa6,
    0x30, 0x2a, 0xf6, 0x67, 0x1e, 0xfe, 0x77, 0x63, 0x64, 0x87, 0x60, 0x00, 0xb0, 0x98, 0x44, 0xee,
    0x4d, 0xe5, 0xc3, 0xcd, 0x51, 0x22, 0x73, 0x9b, 0xe0, 0x1a, 0x74, 0xc8, 0x5a, 0x3f, 0x4e, 0xe6,
    0xaa, 0x7f, 0x21, 0xf1, 0x59, 0x9f, 0xb9, 0x90, 0x4f, 0xe2, 0xfd, 0xb4, 0x16, 0xe3, 0xf8, 0x0e,
    0xe7, 0x15, 0x85, 0x39, 0x3a, 0xde, 0x0f, 0xd2, 0xb6, 0x8e, 0x27, 0xdb, 0xb5, 0x32, 0x45, 0x10
};

static unsigned int key1 = 0x2345;
static unsigned int key2 = 0x7f8d;

void data_init_key(unsigned int block) {
    key1 = block >> 16;
    if (key1 == 0)
        key1 = 0x2345;
    key2 = block & 0xffff;
    if (key2 == 0)
        key2 = 0x7f8d;
}

static unsigned int data_next_key() {
    key1 = key1 * 0x2345 % 0xffd9;
    key2 = key2 * 0x7f8d % 0xfff1;
    return (key1 << 16) + key2;
}

int data_decrypt(unsigned char *data, unsigned int size) {
    if ((size % 4) != 0)
        return -1;
    unsigned int pos;
    for (pos = 0; pos < size; pos += 4) {
        data[pos] = decryption_table[data[pos+0]];
        data[pos+1] = decryption_table[data[pos+1]];
        data[pos+2] = decryption_table[data[pos+2]];
        data[pos+3] = decryption_table[data[pos+3]];
        *(unsigned int*)(data + pos) ^= data_next_key();
    }
    return 0;
}

int data_encrypt(unsigned char *data, unsigned int size) {
    if ((size % 4) != 0)
        return -1;
    unsigned int pos;
    for (pos = 0; pos < size; pos += 4) {
        *(unsigned int*)(data + pos) ^= data_next_key();
        data[pos] = encryption_table[data[pos]];
        data[pos+1] = encryption_table[data[pos+1]];
        data[pos+2] = encryption_table[data[pos+2]];
        data[pos+3] = encryption_table[data[pos+3]];
    }
    return 0;
}

void data_parse_toc(unsigned int *data, file_info toc[]) {
    unsigned int i;
    for (i = 0; i < FILE_COUNT; i++) {
        toc[i].offset = data[i] * 2048;
        toc[i].size = (data[i+1] - data[i]) * 2048;
        toc[i].encrypted = 1;
    }
    for (i = FILE_COUNT + 1; i < SIZE_COUNT; i++) {
        toc[data[i]].size = data[i+1];
        toc[data[i]].encrypted = 0;
    }
}
