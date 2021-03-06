/*
 * Easy to modify to work on any target.
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "salt.h"

void randombytes(unsigned char *p_bytes, unsigned long long length)
{
    (void) p_bytes;
    (void) length;
}

static uint8_t client_sk_sec[64] = {
    0x55, 0xf4, 0xd1, 0xd1, 0x98, 0x09, 0x3c, 0x84,
    0xde, 0x9e, 0xe9, 0xa6, 0x29, 0x9e, 0x0f, 0x68,
    0x91, 0xc2, 0xe1, 0xd0, 0xb3, 0x69, 0xef, 0xb5,
    0x92, 0xa9, 0xe3, 0xf1, 0x69, 0xfb, 0x0f, 0x79,
    0x55, 0x29, 0xce, 0x8c, 0xcf, 0x68, 0xc0, 0xb8,
    0xac, 0x19, 0xd4, 0x37, 0xab, 0x0f, 0x5b, 0x32,
    0x72, 0x37, 0x82, 0x60, 0x8e, 0x93, 0xc6, 0x26,
    0x4f, 0x18, 0x4b, 0xa1, 0x52, 0xc2, 0x35, 0x7b
};
static uint8_t client_ek_sec[32] = {
    0x77, 0x07, 0x6d, 0x0a, 0x73, 0x18, 0xa5, 0x7d,
    0x3c, 0x16, 0xc1, 0x72, 0x51, 0xb2, 0x66, 0x45,
    0xdf, 0x4c, 0x2f, 0x87, 0xeb, 0xc0, 0x99, 0x2a,
    0xb1, 0x77, 0xfb, 0xa5, 0x1d, 0xb9, 0x2c, 0x2a
};
static uint8_t client_ek_pub[32] = {
    0x85, 0x20, 0xf0, 0x09, 0x89, 0x30, 0xa7, 0x54,
    0x74, 0x8b, 0x7d, 0xdc, 0xb4, 0x3e, 0xf7, 0x5a,
    0x0d, 0xbf, 0x3a, 0x0d, 0x26, 0x38, 0x1a, 0xf4,
    0xeb, 0xa4, 0xa9, 0x8e, 0xaa, 0x9b, 0x4e, 0x6a
};
static uint8_t host_sk_sec[64] = {
    0x7a, 0x77, 0x2f, 0xa9, 0x01, 0x4b, 0x42, 0x33,
    0x00, 0x07, 0x6a, 0x2f, 0xf6, 0x46, 0x46, 0x39,
    0x52, 0xf1, 0x41, 0xe2, 0xaa, 0x8d, 0x98, 0x26,
    0x3c, 0x69, 0x0c, 0x0d, 0x72, 0xee, 0xd5, 0x2d,
    0x07, 0xe2, 0x8d, 0x4e, 0xe3, 0x2b, 0xfd, 0xc4,
    0xb0, 0x7d, 0x41, 0xc9, 0x21, 0x93, 0xc0, 0xc2,
    0x5e, 0xe6, 0xb3, 0x09, 0x4c, 0x62, 0x96, 0xf3,
    0x73, 0x41, 0x3b, 0x37, 0x3d, 0x36, 0x16, 0x8b 
};
static uint8_t host_ek_sec[32] = {
    0x5d, 0xab, 0x08, 0x7e, 0x62, 0x4a, 0x8a, 0x4b,
    0x79, 0xe1, 0x7f, 0x8b, 0x83, 0x80, 0x0e, 0xe6,
    0x6f, 0x3b, 0xb1, 0x29, 0x26, 0x18, 0xb6, 0xfd,
    0x1c, 0x2f, 0x8b, 0x27, 0xff, 0x88, 0xe0, 0xeb
};
static uint8_t host_ek_pub[32] = {
    0xde, 0x9e, 0xdb, 0x7d, 0x7b, 0x7d, 0xc1, 0xb4,
    0xd3, 0x5b, 0x61, 0xc2, 0xec, 0xe4, 0x35, 0x37,
    0x3f, 0x83, 0x43, 0xc8, 0x5b, 0x78, 0x67, 0x4d,
    0xad, 0xfc, 0x7e, 0x14, 0x6f, 0x88, 0x2b, 0x4f
};
static uint8_t m1[46] = {
    0x2a, 0x00, 0x00, 0x00, // 42
    0x53, 0x43, 0x76, 0x32, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x85, 0x20, 0xf0, 0x09, 0x89, 0x30,
    0xa7, 0x54, 0x74, 0x8b, 0x7d, 0xdc, 0xb4, 0x3e,
    0xf7, 0x5a, 0x0d, 0xbf, 0x3a, 0x0d, 0x26, 0x38,
    0x1a, 0xf4, 0xeb, 0xa4, 0xa9, 0x8e, 0xaa, 0x9b,
    0x4e, 0x6a
};
static uint8_t m2[42] = {
    0x26, 0x00, 0x00, 0x00, // 38
    0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0xde, 0x9e,
    0xdb, 0x7d, 0x7b, 0x7d, 0xc1, 0xb4, 0xd3, 0x5b,
    0x61, 0xc2, 0xec, 0xe4, 0x35, 0x37, 0x3f, 0x83,
    0x43, 0xc8, 0x5b, 0x78, 0x67, 0x4d, 0xad, 0xfc,
    0x7e, 0x14, 0x6f, 0x88, 0x2b, 0x4f
};
static uint8_t m3[124] = {
    0x78, 0x00, 0x00, 0x00, // 120
    0x06, 0x00, 0xe4, 0x7d, 0x66, 0xe9, 0x07, 0x02,
    0xaa, 0x81, 0xa7, 0xb4, 0x57, 0x10, 0x27, 0x8d,
    0x02, 0xa8, 0xc6, 0xcd, 0xdb, 0x69, 0xb8, 0x6e,
    0x29, 0x9a, 0x47, 0xa9, 0xb1, 0xf1, 0xc1, 0x86,
    0x66, 0xe5, 0xcf, 0x8b, 0x00, 0x07, 0x42, 0xba,
    0xd6, 0x09, 0xbf, 0xd9, 0xbf, 0x2e, 0xf2, 0x79,
    0x87, 0x43, 0xee, 0x09, 0x2b, 0x07, 0xeb, 0x32,
    0xa4, 0x5f, 0x27, 0xcd, 0xa2, 0x2c, 0xbb, 0xd0,
    0xf0, 0xbb, 0x7a, 0xd2, 0x64, 0xbe, 0x1c, 0x8f,
    0x6e, 0x08, 0x0d, 0x05, 0x3b, 0xe0, 0x16, 0xd5,
    0xb0, 0x4a, 0x4a, 0xeb, 0xff, 0xc1, 0x9b, 0x6f,
    0x81, 0x6f, 0x9a, 0x02, 0xe7, 0x1b, 0x49, 0x6f,
    0x46, 0x28, 0xae, 0x47, 0x1c, 0x8e, 0x40, 0xf9,
    0xaf, 0xc0, 0xde, 0x42, 0xc9, 0x02, 0x3c, 0xfc,
    0xd1, 0xb0, 0x78, 0x07, 0xf4, 0x3b, 0x4e, 0x25
};
static uint8_t m4[124] = {
    0x78, 0x00, 0x00, 0x00, // 120
    0x06, 0x00, 0xb4, 0xc3, 0xe5, 0xc6, 0xe4, 0xa4,
    0x05, 0xe9, 0x1e, 0x69, 0xa1, 0x13, 0xb3, 0x96,
    0xb9, 0x41, 0xb3, 0x2f, 0xfd, 0x05, 0x3d, 0x58,
    0xa5, 0x4b, 0xdc, 0xc8, 0xee, 0xf6, 0x0a, 0x47,
    0xd0, 0xbf, 0x53, 0x05, 0x74, 0x18, 0xb6, 0x05,
    0x4e, 0xb2, 0x60, 0xcc, 0xa4, 0xd8, 0x27, 0xc0,
    0x68, 0xed, 0xff, 0x9e, 0xfb, 0x48, 0xf0, 0xeb,
    0x84, 0x54, 0xee, 0x0b, 0x12, 0x15, 0xdf, 0xa0,
    0x8b, 0x3e, 0xbb, 0x3e, 0xcd, 0x29, 0x77, 0xd9,
    0xb6, 0xbd, 0xe0, 0x3d, 0x47, 0x26, 0x41, 0x10,
    0x82, 0xc9, 0xb7, 0x35, 0xe4, 0xba, 0x74, 0xe4,
    0xa2, 0x25, 0x78, 0xfa, 0xf6, 0xcf, 0x36, 0x97,
    0x36, 0x4e, 0xfe, 0x2b, 0xe6, 0x63, 0x5c, 0x4c,
    0x61, 0x7a, 0xd1, 0x2e, 0x6d, 0x18, 0xf7, 0x7a,
    0x23, 0xeb, 0x06, 0x9f, 0x8c, 0xb3, 0x81, 0x73
};
static uint8_t msg1[34] = {
    0x1e, 0x00, 0x00, 0x00, // 30[] => 0x010505050505
    0x06, 0x00, 0x50, 0x89, 0x76, 0x9d, 0xa0, 0xde,
    0xf9, 0xf3, 0x72, 0x89, 0xf9, 0xe5, 0xff, 0x6e,
    0x78, 0x71, 0x0b, 0x97, 0x47, 0xd8, 0xa0, 0x97,
    0x15, 0x91, 0xab, 0xf2, 0xe4, 0xfb
};
static uint8_t msg2[34] = {
    0x1e, 0x00, 0x00, 0x00, // 30 => 0x010505050505
    0x06, 0x00, 0x82, 0xeb, 0x9d, 0x36, 0x60, 0xb8,
    0x29, 0x84, 0xf3, 0xc1, 0xc1, 0x05, 0x1f, 0x87,
    0x51, 0xab, 0x55, 0x85, 0xb7, 0xd0, 0xad, 0x35,
    0x4d, 0x9b, 0x5c, 0x56, 0xf7, 0x55
};

static salt_ret_t client_io_write(salt_io_channel_t *p_wchannel)
{
    uint8_t *expected;
    uint32_t expected_size;

    static uint8_t i = 0;

    switch (i) {
        case 0:
            expected = m1;
            expected_size = sizeof(m1);
            break;
        case 1:
            expected = m4;
            expected_size = sizeof(m4);
            break;
        case 2:
            expected = msg1;
            expected_size = sizeof(msg1);
            break;

    }

    i++;

    if (p_wchannel->size_expected == expected_size && memcmp(expected, p_wchannel->p_data, expected_size) == 0) {
        p_wchannel->size = p_wchannel->size_expected;
        return SALT_SUCCESS;
    }

    return SALT_ERROR;

}

static salt_ret_t client_io_read(salt_io_channel_t *p_rchannel)
{
    static uint8_t i = 0;

    switch (i) {
        case 0:
            memcpy(p_rchannel->p_data, m2, 4);
            p_rchannel->size = 4;
            break;
        case 1:
            memcpy(p_rchannel->p_data, &m2[4], 38);
            p_rchannel->size = 38;
            break;
        case 2:
            memcpy(p_rchannel->p_data, m3, 4);
            p_rchannel->size = 4;
            break;
        case 3:
            memcpy(p_rchannel->p_data, &m3[4], 120);
            p_rchannel->size = 120;
            break;
        case 4:
            memcpy(p_rchannel->p_data, msg2, 4);
            p_rchannel->size = 4;
            break;
        case 5:
            memcpy(p_rchannel->p_data, &msg2[4], 30);
            p_rchannel->size = 30;
            break;

    }

    i++;

    return SALT_SUCCESS;
}

bool test_client_handshake(void) {

    salt_channel_t channel;
    salt_ret_t ret;
    uint8_t hndsk_buffer[SALT_HNDSHK_BUFFER_SIZE];

    ret = salt_create(&channel, SALT_CLIENT, client_io_write, client_io_read, NULL);
    ret = salt_set_signature(&channel, client_sk_sec);
    ret = salt_init_session_using_key(&channel,
                                      hndsk_buffer,
                                      SALT_HNDSHK_BUFFER_SIZE,
                                      client_ek_pub,
                                      client_ek_sec);

    ret = salt_handshake(&channel, NULL);

    if (ret != SALT_SUCCESS) {
        return false;
    }

    /* Write echo bytes 010505050505 */
    uint8_t echo_bytes[6] = {0x01, 0x05, 0x05, 0x05, 0x05, 0x05};
    salt_msg_t msg_out;
    ret = salt_write_begin(hndsk_buffer, sizeof(hndsk_buffer), &msg_out);
    ret = salt_write_next(&msg_out, echo_bytes, sizeof(echo_bytes));
    ret = salt_write_execute(&channel, &msg_out, false);
    if (ret != SALT_SUCCESS) {
        return false;
    }

    salt_msg_t msg_in;
    ret = salt_read_begin(&channel, hndsk_buffer, sizeof(hndsk_buffer), &msg_in);
    if (msg_in.read.message_size == sizeof(echo_bytes) && memcmp(echo_bytes, msg_in.read.p_payload, sizeof(echo_bytes)) == 0) {
        return true;
    }

    (void) host_sk_sec;
    (void) host_ek_pub;
    (void) host_ek_sec;

    return false;
}

int main(void) {
    assert(test_client_handshake());
    return 0;    
}