#pragma once

#ifndef DEBUG
const uint8_t PROGMEM banner[] = {
0x7f, 0x37, 0xe0, 0xc3, 0x14, 0x2e, 0x53, 0x28, 0x4c, 0x67, 0xb7, 0xdb, 0xed, 0x76, 0xbb, 0xdd, 
0x6e, 0xb7, 0xdb, 0xed, 0x3a, 0x74, 0xa5, 0xb3, 0xdb, 0xed, 0x76, 0xbb, 0x55, 0x0e, 0x91, 0x6a, 
0xee, 0x74, 0x76, 0xbb, 0xdd, 0x6e, 0xb7, 0xdb, 0xed, 0x76, 0xbb, 0x0e, 0xd2, 0x56, 0xa1, 0x12, 
0x7d, 0x98, 0x53, 0x4a, 0x2a, 0xa9, 0x14, 0xd6, 0xa8, 0x52, 0x32, 0xa4, 0xad, 0xa4, 0x92, 0x6a, 
0x24, 0x72, 0xae, 0x64, 0x28, 0x5b, 0x2a, 0xa9, 0xe4, 0x78, 0x82, 0xa3, 0x11, 0xba, 0x73, 0xce, 
0x39, 0xe7, 0x9c, 0x53, 0x52, 0xc5, 0x85, 0x38, 0xe5, 0x9c, 0x73, 0x6e, 0x9c, 0x1d, 0x17, 0xee, 
0x94, 0x73, 0xce, 0xe1, 0x91, 0x14, 0x7f, 0x5b, 0x25, 0x95, 0x54, 0x52, 0x49, 0x25, 0xb7, 0x3b, 
0x08, 0x2f, 0x89, 0xc7, 0xed, 0x76, 0x3b, 0x7f, 0x3a, 0xbd, 0xe3, 0xaf, 0x9d, 0x54, 0x52, 0x49, 
0x25, 0x95, 0x54, 0x52, 0x49, 0x25, 0xa5, 0x52, 0xa5, 0x94, 0x54, 0x52, 0x49, 0xe5, 0xdc, 0x76, 
0xbb, 0x55, 0x7a, 0xab, 0x94, 0x54, 0x52, 0x49, 0x25, 0x95, 0x54, 0x52, 0x49, 0x25, 0xa5, 0x52, 
0x52, 0x49, 0xe5, 0x9c, 0x92, 0xdb, 0xad, 0x92, 0x4e, 0x3a, 0xa9, 0xa4, 0x92, 0x4a, 0x49, 0xe5, 
0x9c, 0x92, 0x4a, 0x3a, 0x27, 0x95, 0x94, 0x4a, 0x49, 0x25, 0x95, 0x54, 0x52, 0xdd, 0xea, 0x53, 
0xeb, 0x7c, 0x7a, 0xab, 0xa4, 0x92, 0xca, 0x39, 0xe7, 0x94, 0x54, 0x52, 0x49, 0x25, 0x95, 0x54, 
0x52, 0x39, 0xa7, 0xe4, 0x76, 0x1d, 0x6b, 0x3a, 0xbd, 0xdd, 0x6e, 0xb7, 0xdb, 0xed, 0x3a, 0xba, 
0xec, 0x76, 0x3b, 0x5a, 0x0b, 0x8d, 0x4a, 0x2a, 0xa9, 0xe4, 0x38, 0x5a, 0x2a, 0xe7, 0x46, 0x16, 
0xde, 0x52, 0x84, 0x88, 0x53, 0x71, 0x22, 0x70, 0xe7, 0x9c, 0x42, 0x22, 0x1f, 0xe6, 0x76, 0xce, 
0x29, 0xec, 0x11, 0xae, 0x64, 0x28, 0x5b, 0x2a, 0xa9, 0xe4, 0x78, 0xe2, 0x53, 0x21, 0x6f, 0xe7, 
0x9c, 0x73, 0x4e, 0x49, 0x25, 0xc3, 0x66, 0x0a, 0x93, 0x4a, 0x49, 0x3b, 0xbe, 0xb6, 0xce, 0xd9, 
0xa5, 0x72, 0x8a, 0xee, 0xb1, 0xe7, 0x9c, 0xc3, 0xdc, 0x8a, 0xf2, 0x91, 0x97, 0xe2, 0x4a, 0x21, 
0xd0, 0x45, 0xf6, 0x38, 0x5b, 0x71, 0xa5, 0x50, 0x47, 0x89, 0xbf, 0xad, 0x92, 0x4a, 0x2a, 0xa9, 
0xa4, 0x92, 0xdb, 0x1d, 0xdd, 0xe3, 0xee, 0xb1, 0xbf, 0x55, 0x52, 0x49, 0x25, 0x95, 0x54, 0x52, 
0x49, 0x25, 0x95, 0x54, 0x3a, 0xd2, 0xf4, 0x56, 0x49, 0x25, 0x95, 0x54, 0x52, 0xc9, 0xed, 0xec, 
0x5b, 0x25, 0x95, 0x54, 0x52, 0x49, 0x25, 0x95, 0x54, 0x72, 0xab, 0xa4, 0x92, 0x4a, 0x2a, 0xa9, 
0xa4, 0x92, 0x4a, 0x2a, 0x9d, 0x8e, 0x6c, 0xab, 0xa4, 0x92, 0x4a, 0x2a, 0xa9, 0xa4, 0x92, 0x4a, 
0x47, 0xb6, 0x55, 0x52, 0x49, 0x25, 0x95, 0x54, 0x52, 0x49, 0x25, 0x95, 0x8e, 0x6c, 0xab, 0xa4, 
0x92, 0x4a, 0x2a, 0xa9, 0xa4, 0xd2, 0x91, 0x6d, 0x95, 0x54, 0x52, 0x49, 0x25, 0x95, 0x54, 0x52, 
0xe9, 0x48, 0xd3, 0x5b, 0x25, 0x95, 0x54, 0x52, 0x49, 0x25, 0x95, 0x54, 0x52, 0x49, 0x25, 0x95, 
0x54, 0x72, 0x1b, 0xed, 0x56, 0x49, 0x25, 0x95, 0x54, 0x52, 0x49, 0x25, 0x95, 0x4e, 0x87, 0x64
};
#else
const uint8_t PROGMEM banner[] = {
0x00
};
#endif

const uint8_t PROGMEM score_sc[] = {
0x19, 0x07, 0xea, 0x54, 0x55, 0xaa, 0x2a, 0xd5, 0x91, 0x29, 0x97, 0x4a, 0xa5, 0x72, 0x15, 0x99, 
0x72, 0xa9, 0x54, 0x2a, 0xa7, 0xb8, 0xa4, 0xaa, 0x64, 0x65, 0x6b, 0x2a, 0xa9, 0xaa, 0x52, 0xa9, 
0xb8, 0x2a, 0x2e
};

const uint8_t PROGMEM men_sc[] = {
0x0f, 0x07, 0xa5, 0xcb, 0x67, 0xb3, 0x92, 0x4a, 0xaa, 0xaa, 0x54, 0x2a, 0x2a, 0xe9, 0xf2, 0x49, 
0xc9, 0x55, 0x39
};

const uint8_t PROGMEM level_sc[] = {
0x0e, 0x07, 0xa5, 0x4e, 0x47, 0xe5, 0x7c, 0x36, 0xa7, 0xc8, 0xa4, 0x4e, 0xc7, 0x55, 0x71, 0x01
};


const uint8_t PROGMEM levelChange[] = {
0x15, 0x07, 0xa5, 0x4e, 0x47, 0x25, 0x55, 0x55, 0x2a, 0x15, 0x95, 0xf3, 0xd9, 0x9c, 0x22, 0x93, 
0xaa, 0x2a, 0x95, 0x8a, 0x4a, 0xea, 0x74, 0x5c, 0x95, 0x03
};

const uint8_t PROGMEM gameOver[] = {
0x29, 0x07, 0x52, 0x2e, 0x95, 0xaa, 0x4a, 0x95, 0xe2, 0x72, 0xaa, 0x92, 0x95, 0x75, 0x54, 0x52, 
0xe5, 0xb3, 0x92, 0x4a, 0xaa, 0xaa, 0x54, 0x2a, 0x6e, 0xe5, 0x52, 0xa9, 0x54, 0x4e, 0x71, 0x39, 
0x9f, 0x4e, 0x39, 0x2e, 0xa9, 0xaa, 0x52, 0xa9, 0xa8, 0xa4, 0xaa, 0x64, 0x65, 0x6b, 0x4a, 0x55, 
0x0a
};

const uint8_t PROGMEM tryAgain[] = {
0x29, 0x07, 0xd3, 0x69, 0xa9, 0xa2, 0x93, 0xaa, 0x92, 0x95, 0xad, 0xa9, 0xf6, 0x4a, 0x4d, 0xef, 
0x54, 0x25, 0x2b, 0xeb, 0xb8, 0x94, 0x4b, 0xa5, 0xaa, 0x52, 0xa5, 0xb8, 0x9c, 0xaa, 0x64, 0x65, 
0x1d, 0x55, 0x2a, 0x25, 0x55, 0x2a, 0x2a, 0xe9, 0xf2, 0x49, 0x49, 0xa9, 0x4a, 0x01
};

const uint8_t PROGMEM menuOption[] = {
0x3f, 0x0f, 0xa5, 0xaa, 0x64, 0x65, 0x6b, 0x2a, 0xa9, 0xaa, 0x52, 0xa9, 0xb8, 0x3a, 0x55, 0x95, 
0xaa, 0x4a, 0x75, 0x5c, 0xce, 0xa7, 0x53, 0x8e, 0x4b, 0xba, 0x7c, 0x36, 0x2b, 0xa9, 0xa4, 0xaa, 
0x4a, 0xa5, 0xe2, 0x56, 0x2e, 0x95, 0xaa, 0x4a, 0x95, 0xe2, 0x72, 0xaa, 0x92, 0x95, 0x75, 0x54, 
0xd2, 0xe5, 0xb3, 0x59, 0x49, 0x25, 0x55, 0x55, 0x2a, 0x15, 0xd2, 0xa5, 0xaa, 0x64, 0x65, 0x6b, 
0x2a, 0xa9, 0xaa, 0x52, 0xa9, 0xb8, 0x3a, 0x55, 0x95, 0xaa, 0x4a, 0x75, 0x5c, 0xe9, 0xb4, 0x54, 
0xf1, 0x39, 0x55, 0xc9, 0xca, 0x3a, 0x2a, 0xa9, 0x2a, 0x59, 0xd9, 0x9a, 0x2a, 0x9d, 0x96, 0x2a, 
0x7e, 0xe5, 0x52, 0xa9, 0xaa, 0x54, 0x29, 0x2e, 0xa7, 0x2a, 0x59, 0x59, 0x47, 0x25, 0x5d, 0x3e, 
0x9b, 0x95, 0x54, 0x52, 0x55, 0xa5, 0x52, 0x21, 0x12
};

const uint8_t PROGMEM menuOption2[] = {
0x3f, 0x1f, 0xa5, 0xaa, 0x64, 0x65, 0x6b, 0x2a, 0xa9, 0xaa, 0x52, 0xa9, 0xb8, 0x3a, 0x55, 0x95, 
0xaa, 0x4a, 0x75, 0x5c, 0xce, 0xa7, 0x53, 0x8e, 0x4b, 0xaa, 0x7c, 0x56, 0x52, 0x49, 0x55, 0x95, 
0x4a, 0xc5, 0xad, 0x5c, 0x2a, 0x55, 0x95, 0x2a, 0xc5, 0xe5, 0x54, 0x25, 0x2b, 0xeb, 0xa8, 0xa4, 
0xca, 0x67, 0x25, 0x95, 0x54, 0x55, 0xa9, 0x54, 0x90, 0x90, 0x54, 0x95, 0xac, 0x6c, 0x4d, 0x25, 
0x55, 0x55, 0x2a, 0x15, 0x57, 0xa7, 0xaa, 0x52, 0x55, 0xa9, 0x8e, 0x2b, 0x9d, 0x96, 0x2a, 0x3e, 
0xa7, 0x2a, 0x59, 0x59, 0x47, 0x25, 0x55, 0x25, 0x2b, 0x5b, 0x53, 0xa5, 0xd3, 0x52, 0xc5, 0xaf, 
0x5c, 0x2a, 0x55, 0x95, 0x2a, 0xc5, 0xe5, 0x54, 0x25, 0x2b, 0xeb, 0xa8, 0xa4, 0xca, 0x67, 0x25, 
0x95, 0x54, 0x55, 0xa9, 0x54, 0x48, 0x75, 0xdc, 0xce, 0x55, 0x32, 0x3a, 0xc7, 0xe9, 0xb8, 0x9c, 
0xab, 0x64, 0x74, 0x0e, 0x8b, 0x59, 0xe5, 0x1c, 0x1c, 0xe5, 0xa4, 0xb2, 0x21, 0x38, 0x9d, 0x8e, 
0x2e, 0x9d, 0x8e, 0x36, 0x1d, 0x6d, 0x3a, 0x1d, 0x5d, 0x3a, 0x1d, 0x1a, 0x83, 0xa6, 0x42, 0x3b
};

const uint8_t PROGMEM menuOptionStart[] = {
0x2c, 0x07, 0xea, 0x54, 0x55, 0xaa, 0x2a, 0xd5, 0x71, 0xa5, 0xd3, 0x52, 0xc5, 0xe7, 0x54, 0x25, 
0x2b, 0xeb, 0xa8, 0xa4, 0xaa, 0x64, 0x65, 0x6b, 0xaa, 0x74, 0x5a, 0xaa, 0xf8, 0x95, 0x4b, 0xa5, 
0xaa, 0x52, 0xa5, 0xb8, 0x9c, 0xaa, 0x64, 0x65, 0x1d, 0x95, 0x54, 0xf9, 0xac, 0xa4, 0x92, 0xaa, 
0x2a, 0x95, 0x4a, 0x01
};

const uint8_t PROGMEM menuArrow[] = {
0x02, 0x07, 0xa5, 0x53, 0x36, 0x09
};

const uint8_t PROGMEM gold_sc[] = {
0x13, 0x07, 0x52, 0x2e, 0x95, 0xaa, 0x4a, 0x95, 0xe2, 0x52, 0x2e, 0x95, 0x4a, 0xe5, 0x14, 0x97, 
0xd4, 0xe9, 0xa8, 0xa4, 0x4a, 0xa5, 0x52, 0x39, 0x45, 0x56, 0x39
};

const uint8_t PROGMEM completeGame[] = {
0x59, 0x1f, 0xa3, 0x8b, 0x2e, 0xa7, 0x64, 0xe7, 0xd2, 0x9d, 0xdc, 0xe7, 0xd2, 0x8e, 0x2e, 0xb6, 
0x6d, 0x7a, 0xba, 0xd8, 0xb6, 0xe9, 0xe9, 0x62, 0xdb, 0xa6, 0xa7, 0x8b, 0x6d, 0x9b, 0x9e, 0x2e, 
0xba, 0xe8, 0x62, 0xdb, 0xa6, 0xa7, 0x8b, 0x6d, 0x9b, 0x9e, 0x2e, 0x9b, 0x9e, 0x6d, 0x9b, 0xcf, 
0xa6, 0xb7, 0xe9, 0xe9, 0x72, 0x69, 0x47, 0x17, 0xdb, 0x36, 0x3d, 0x5d, 0x4e, 0xe9, 0x6d, 0x3e, 
0xba, 0x6c, 0x7a, 0x9b, 0x8f, 0x2e, 0x74, 0x39, 0x97, 0x4e, 0xc7, 0x9c, 0x73, 0x3a, 0x2e, 0x65, 
0x2b, 0x59, 0xc9, 0xca, 0x75, 0x6c, 0xd9, 0x4a, 0x56, 0xb2, 0x72, 0x8e, 0xab, 0x93, 0x95, 0xac, 
0x64, 0x65, 0x23, 0x53, 0xb6, 0x92, 0x95, 0xac, 0x5c, 0x87, 0x2b, 0xe5, 0xd3, 0xe9, 0x5c, 0xc7, 
0xa5, 0x7c, 0x3a, 0x9d, 0x53, 0x64, 0x8e, 0x4b, 0x91, 0x39, 0x2e, 0x2b, 0xd3, 0xe9, 0x9c, 0xe2, 
0xcb, 0x39, 0x1d, 0x97, 0xb2, 0x95, 0xac, 0x64, 0xe5, 0x3a, 0x2e, 0xe5, 0xd3, 0xd9, 0xc8, 0x94, 
0xad, 0x64, 0x25, 0x2b, 0xd7, 0x41, 0x6f, 0xf7, 0xb5, 0xab, 0x4a, 0xa9, 0x52, 0xa9, 0xc9, 0x72, 
0x55, 0xa9, 0xaa, 0x54, 0x55, 0xce, 0x51, 0x49, 0x95, 0x57, 0x2e, 0x2d, 0xb9, 0x94, 0xab, 0x4a, 
0x55, 0xa5, 0xaa, 0x72, 0x1d, 0x2c, 0x1b, 0x5d, 0x74, 0xd1, 0x45, 0x17, 0x5d, 0x74, 0xd1, 0x45, 
0x17, 0x5d, 0x74, 0xd1, 0xc5, 0x94, 0xeb, 0x74, 0x2e, 0xba, 0xe8, 0xa2, 0x8b, 0x2e, 0xba, 0xe8, 
0xa2, 0x8b, 0x2e, 0xba, 0xe8, 0xa2, 0x8b, 0x2e, 0xba, 0xe8, 0xa2, 0x8b, 0x2e, 0xba, 0xe8, 0xa2, 
0x8b, 0x2e, 0xba, 0xe8, 0xa2, 0x8b, 0x2e, 0xba, 0xe8, 0xa2, 0x8b, 0x2e, 0xba, 0xe8, 0xa2, 0x8b, 
0x09
};

const uint8_t PROGMEM completeGame1[] = {
0x10, 0x07, 0x9c, 0x72, 0xa9, 0x54, 0x2a, 0x95, 0xca, 0x29, 0x2e, 0xe9, 0xb2, 0xe9, 0xbc, 0xe3, 
0x52, 0xae, 0x2a, 0x55, 0x95, 0xaa, 0xca, 0x75
};

const uint8_t PROGMEM completeGame2[] = {
0x10, 0x07, 0xb2, 0x2e, 0x95, 0x4a, 0x65, 0xe3, 0x72, 0x3e, 0xa7, 0x7c, 0xca, 0x91, 0x29, 0x97, 
0x4a, 0xa5, 0x52, 0xa9, 0x9c, 0x22, 0x02
};

const uint8_t PROGMEM completeGame3[] = {
0x1b, 0x07, 0xb2, 0x2e, 0x95, 0x4a, 0x65, 0x3b, 0xad, 0x5d, 0x36, 0x9d, 0x77, 0x54, 0xd2, 0x65, 
0xd3, 0xf9, 0xe8, 0x94, 0xab, 0x4a, 0x55, 0xa5, 0xaa, 0x72, 0x1d, 0x97, 0x72, 0x55, 0xa9, 0xaa, 
0x54, 0x55, 0xae, 0x03
};

const uint8_t PROGMEM loadNextGame[] = {
0x57, 0x17, 0xa3, 0x8b, 0x2e, 0x2e, 0x47, 0x17, 0x5d, 0x74, 0xd1, 0x45, 0x17, 0x5d, 0x74, 0xd1, 
0x45, 0x17, 0x5d, 0x72, 0x1f, 0x5d, 0x74, 0xd1, 0x45, 0x17, 0x5d, 0x74, 0xd1, 0x45, 0x17, 0x5d, 
0x74, 0x91, 0x29, 0xba, 0xe8, 0xa2, 0x8b, 0x2e, 0xba, 0xe8, 0xa2, 0x8b, 0x2e, 0xba, 0xe8, 0xa2, 
0x8b, 0x2e, 0xba, 0xe8, 0xa2, 0x8b, 0x2e, 0xb9, 0x8f, 0x2e, 0xb4, 0x49, 0x9d, 0x4e, 0xc7, 0xa5, 
0x5c, 0x2a, 0x95, 0x4a, 0xa5, 0x72, 0x8a, 0x2e, 0x57, 0x95, 0xaa, 0x4a, 0x55, 0xe5, 0x1c, 0x97, 
0x72, 0xa9, 0x54, 0x2a, 0x95, 0x4a, 0x49, 0x14, 0x49, 0x97, 0x4d, 0xe7, 0x1d, 0x97, 0x72, 0x55, 
0xa9, 0xaa, 0x54, 0x55, 0xee, 0xa2, 0x4a, 0xe5, 0x2a, 0x9b, 0xad, 0x5c, 0x2a, 0x2a, 0xe7, 0x52, 
0xa9, 0x54, 0x36, 0x24, 0xdd, 0xd7, 0x57, 0x55, 0x95, 0xaa, 0x2a, 0x35, 0x59, 0xae, 0x2a, 0x55, 
0x95, 0xaa, 0xca, 0x39, 0x2a, 0xa9, 0xf2, 0xca, 0xa5, 0x25, 0x97, 0x72, 0x55, 0xa9, 0xaa, 0x54, 
0x55, 0xae, 0xa3, 0x54, 0x85, 0xac, 0xe8, 0xa2, 0x8b, 0x2e, 0xba, 0xe8, 0xa2, 0x8b, 0x2e, 0xba, 
0xe8, 0xa2, 0x8b, 0x2e, 0xba, 0xe8, 0xa2, 0x8b, 0x2e, 0xba, 0xe8, 0xa2, 0x8b, 0x2e, 0xba, 0xe8, 
0xa2, 0x8b, 0x2e, 0xba, 0xe8, 0xa2, 0x8b, 0x2e, 0xba, 0xe8, 0xa2, 0x8b, 0x2e, 0xba, 0xe8, 0xa2, 
0x8b, 0x2e, 0xba, 0xe8, 0xa2, 0x8b, 0x2e, 0xba, 0xe8, 0xa2, 0x8b, 0x2e, 0x32
};

const uint8_t PROGMEM victory[] = {
0x45, 0x0f, 0xa3, 0x8b, 0x6d, 0xb9, 0x55, 0x4e, 0x29, 0xbb, 0x73, 0xa7, 0x6c, 0x3e, 0xba, 0xe8, 
0xa2, 0x4b, 0x29, 0x3f, 0xdb, 0x4a, 0x11, 0x25, 0x93, 0xa5, 0xe8, 0xb2, 0xd9, 0x4a, 0xa6, 0x2b, 
0x9b, 0x4f, 0x39, 0x5b, 0xc9, 0x88, 0x62, 0x5b, 0xa6, 0x2b, 0x99, 0x9f, 0x4c, 0xd9, 0x6c, 0x25, 
0xf3, 0x93, 0x29, 0xba, 0xc8, 0x14, 0x5d, 0x74, 0x29, 0xe7, 0xa3, 0x8b, 0x2e, 0xba, 0x58, 0xa3, 
0xeb, 0x74, 0xae, 0x93, 0xca, 0x29, 0xed, 0x6e, 0xc5, 0x14, 0x5d, 0x74, 0xd1, 0x45, 0xa7, 0x7c, 
0x4e, 0x91, 0xc5, 0x94, 0x73, 0x3a, 0x97, 0x5f, 0x76, 0x3a, 0xd7, 0xd9, 0x64, 0x7e, 0xd9, 0xe9, 
0x5c, 0x45, 0xa6, 0x7c, 0xae, 0xd3, 0x39, 0x45, 0xe6, 0xb8, 0xa2, 0x8b, 0xee, 0x93, 0xdd, 0x5d, 
0xc9, 0x6a, 0x49, 0x15, 0x5d, 0xbe, 0x72, 0xd1, 0x45, 0x17, 0x5d, 0x74, 0x79
};


// ---------------------------------------------------------------------------------------------------------------------------------
//  Level Elements
// ---------------------------------------------------------------------------------------------------------------------------------


const uint8_t PROGMEM brickDiggingImgs[] = {
10, 8,
0x18, 0x00, 0x60, 0x00, 0x80, 0x00, 0x20, 0x00, 0x40, 0x00, 
0x00, 0x00, 0x60, 0x00, 0x90, 0x00, 0x20, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x80, 0x10, 0x00, 0x20, 0x80, 0x00, 
0x00, 0x80, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x40, 
};


const uint8_t PROGMEM levelElementImgs[] = {
10, 16,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

0xef, 0xef, 0xe0, 0xef, 0xef, 0xef, 0xef, 0x0f, 0xef, 0xef, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 

0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 

0x00, 0x00, 0xff, 0x42, 0x42, 0x42, 0x42, 0xff, 0x00, 0x00, 
0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 

0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

0xef, 0xaf, 0xe0, 0x6f, 0xef, 0xef, 0xed, 0x0f, 0xeb, 0xef, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 

0x00, 0x00, 0xb0, 0xb0, 0x00, 0xb0, 0xb0, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 

//Brick 1

0xef, 0xef, 0xe0, 0xee, 0xee, 0xee, 0xee, 0x0e, 0xef, 0xef, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 

0xee, 0xec, 0xe0, 0xe8, 0xe8, 0xea, 0xe8, 0x08, 0xec, 0xee, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 

0xec, 0xe0, 0xc0, 0xc0, 0x88, 0x80, 0x80, 0x00, 0xe0, 0xec, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 

0xe0, 0x80, 0x00, 0x00, 0x08, 0x00, 0x01, 0x00, 0x86, 0xe0, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 

// Empty Brick

0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

0xe0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 

0xec, 0xe0, 0xc0, 0x80, 0x80, 0x80, 0xc0, 0x00, 0xe0, 0xec, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 

0xef, 0xec, 0xe0, 0xe8, 0xe8, 0xe8, 0xe8, 0x0c, 0xec, 0xef, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 

0xef, 0xef, 0xe0, 0xee, 0xee, 0xee, 0xee, 0x0f, 0xef, 0xef, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 
};


// ---------------------------------------------------------------------------------------------------------------------------------
//  Men
// ---------------------------------------------------------------------------------------------------------------------------------

const uint8_t PROGMEM man_StandingStill[] = { // Standing Still
0x09, 0x0f, 0xb8, 0x96, 0x9f, 0x6a, 0xa2, 0x74, 0xd7, 0xab, 0xcf, 0xcd, 0xbc, 0x9d, 0x75, 0x3b, 
0x2b
};

const uint8_t PROGMEM man1[] = { // Running 1
0x09, 0x0f, 0x5c, 0xa7, 0x3e, 0xf5, 0x4d, 0x96, 0xdb, 0xf5, 0xb9, 0x50, 0xb7, 0x9d, 0x1d
};

const uint8_t PROGMEM man2[] = { // Running 2
0x09, 0x0f, 0x38, 0x97, 0x2a, 0xca, 0x6b, 0x99, 0x8e, 0x39, 0xbd, 0x1d, 0x5b
};

const uint8_t PROGMEM man3[] = { // Running 3
0x09, 0x0f, 0xb8, 0xb2, 0x9f, 0x6a, 0xa2, 0x74, 0x5f, 0xbb, 0x8e, 0x77, 0x3b, 0x7b, 0x3a, 0x5a
};

const uint8_t PROGMEM man_LaddderLeft[] = {
0x09, 0x0f, 0x88, 0x76, 0x9d, 0x7a, 0x99, 0x5d, 0xcb, 0xda, 0x75, 0x6a, 0xd4, 0x6d, 0xd7, 0xb1, 
0x01
};

const uint8_t PROGMEM man_LaddderRight[] = {
0x09, 0x0f, 0xa8, 0xd6, 0x9d, 0x2b, 0xa2, 0xac, 0x93, 0x2a, 0x75, 0xbb, 0x08, 0xb3, 0xdb, 0xb1, 
0x06
};

const uint8_t PROGMEM man7[] = {
0x09, 0x0f, 0xbc, 0x92, 0x4e, 0xa5, 0xfa, 0xec, 0xe5, 0x54, 0xce, 0xc9, 0xd9, 0xd3, 0xf9, 0xec, 
0x36, 0x7a
};

const uint8_t PROGMEM man8[] = {
0x09, 0x0f, 0x38, 0xb3, 0x9f, 0xea, 0xb3, 0x97, 0x77, 0x0a, 0x4b, 0xdb, 0xd9, 0xb6, 0xb3, 0x02
};

const uint8_t PROGMEM man9[] = {
0x09, 0x0f, 0xf8, 0xb6, 0xca, 0xf5, 0x5f, 0xb9, 0xb5, 0xeb, 0xd4, 0x36, 0xee, 0xed, 0x6c, 0xdb, 
0x59, 0x01
};

const uint8_t PROGMEM man10[] = {
0x09, 0x0f, 0xf8, 0xb6, 0xca, 0xf5, 0x5f, 0xb9, 0xb5, 0xeb, 0xd4, 0x36, 0xee, 0xed, 0x6c, 0xdb, 
0x59, 0x01
};

const uint8_t PROGMEM man11[] = {
0x09, 0x0f, 0xbc, 0x92, 0xee, 0x55, 0xa9, 0xa4, 0xd2, 0xaa, 0xad, 0x53, 0xe4, 0xe9, 0xe8, 0xb6, 
0xb3, 0x03
};

const uint8_t PROGMEM man12[] = {
0x09, 0x0f, 0xb8, 0xb2, 0xe9, 0x14, 0x5f, 0xd7, 0xab, 0xcf, 0x85, 0xa2, 0xed, 0x6c, 0xdb, 0x59, 
0x01
};

const uint8_t PROGMEM man_Rebirth_1[] = {
0x09, 0x0f, 0x10, 0x9b, 0xce, 0x6e, 0xb7, 0xdb, 0x75, 0x3a, 0x36
};

const uint8_t PROGMEM man_Rebirth_2[] = {
0x09, 0x0f, 0xe8, 0xd3, 0xe9, 0x74, 0xfc, 0xdb, 0xed, 0x76, 0xbb, 0xdd, 0x6e, 0x67, 0x03
};

const uint8_t PROGMEM man_Rebirth_3[] = {
0x09, 0x0f, 0xe8, 0xd2, 0xd9, 0xed, 0x76, 0xbb, 0x4e, 0xc7, 0xb7, 0xdd, 0x6e, 0xb7, 0xdb, 0xed, 
0x76, 0x36
};

const uint8_t* const men[] = { 
man_StandingStill, man1, man2, man3, man2, man_LaddderLeft, man_LaddderRight, man7, man8, man7, man9, man11, man12, man_Rebirth_1, man_Rebirth_2, man_Rebirth_3
};



// ---------------------------------------------------------------------------------------------------------------------------------
//  Digits
// ---------------------------------------------------------------------------------------------------------------------------------

const uint8_t PROGMEM numbers[] = {
4, 5,
0x0e, 0x11, 0x11, 0x0e, 
0x00, 0x12, 0x1f, 0x10, 
0x12, 0x19, 0x15, 0x12, 
0x0a, 0x11, 0x15, 0x0a, 
0x06, 0x05, 0x1f, 0x04, 
0x17, 0x15, 0x15, 0x09, 
0x0e, 0x15, 0x15, 0x08, 
0x01, 0x19, 0x05, 0x03, 
0x0a, 0x15, 0x15, 0x0a, 
0x12, 0x15, 0x09, 0x06, 
};



// ---------------------------------------------------------------------------------------------------------------------------------
//  Arrows ..
// ---------------------------------------------------------------------------------------------------------------------------------

const uint8_t PROGMEM arrow_TL[] = {
0x04, 0x07, 0x95, 0xdc, 0x46, 0x0b
};

const uint8_t PROGMEM arrow_TL_mask[] = {
0x04, 0x07, 0xa5, 0x72, 0x4e, 0xc9, 0x6d, 0x1a
};

const uint8_t PROGMEM arrow_TM[] = {
0x06, 0x07, 0x98, 0xb2, 0x4b, 0x65, 0xd7, 0x91, 0x01
};

const uint8_t PROGMEM arrow_TM_mask[] = {
0x06, 0x07, 0x5e, 0x2a, 0xe7, 0x9c, 0x73, 0x4e, 0x2a, 0xbb, 0x03
};

const uint8_t PROGMEM arrow_TR[] = {
0x04, 0x07, 0xf8, 0xd2, 0x5b, 0x25, 0x01
};

const uint8_t PROGMEM arrow_TR_mask[] = {
0x04, 0x07, 0xd3, 0x5b, 0x25, 0x9d, 0x93, 0x0a
};

const uint8_t PROGMEM arrow_BL[] = {
0x04, 0x07, 0x56, 0x76, 0x1d, 0x25
};

const uint8_t PROGMEM arrow_BL_mask[] = {
0x04, 0x07, 0xa5, 0x73, 0x52, 0xd9, 0x75, 0x0a
};

const uint8_t PROGMEM arrow_BM[] = {
0x06, 0x07, 0x88, 0xd2, 0x5b, 0x25, 0xb7, 0xb1, 0x01
};

const uint8_t PROGMEM arrow_BM_mask[] = {
0x06, 0x07, 0xb7, 0x4a, 0x3a, 0xe7, 0x9c, 0x73, 0x4a, 0x6e, 0x01
};

const uint8_t PROGMEM arrow_BR[] = {
0x04, 0x07, 0x38, 0xb3, 0x4b, 0xa5, 0x00
};

const uint8_t PROGMEM arrow_BR_mask[] = {
0x04, 0x07, 0xdc, 0x52, 0x39, 0xa7, 0xe4, 0x76
};

const uint8_t PROGMEM arrow_MR[] = {
0x03, 0x07, 0x88, 0xa4, 0x53, 0x36, 0x07
};

const uint8_t PROGMEM arrow_MR_mask[] = {
0x03, 0x07, 0x75, 0x7a, 0xe9, 0x94, 0x02
};

const uint8_t PROGMEM arrow_ML[] = {
0x03, 0x07, 0x54, 0x56, 0x39, 0xc9, 0x04
};

const uint8_t PROGMEM arrow_ML_mask[] = {
0x03, 0x07, 0x56, 0x4e, 0xae, 0xd3, 0x01
};



// const uint8_t PROGMEM arrow_BL_Sml[] = {
// 0x04, 0x07, 0xd4, 0x3a, 0x6a
// };

// const uint8_t PROGMEM arrow_BL_Sml_mask[] = {
// 0x04, 0x07, 0x72, 0x52, 0xd9, 0x75, 0x54
// };

// const uint8_t PROGMEM arrow_BM_Sml[] = {
// 0x06, 0x07, 0x18, 0xd3, 0xdb, 0x48, 0x01
// };

// const uint8_t PROGMEM arrow_BM_Sml_mask[] = {
// 0x06, 0x07, 0x88, 0xb6, 0x4a, 0x2a, 0xa9, 0xe4, 0x64
// };

// const uint8_t PROGMEM arrow_BR_Sml[] = {
// 0x04, 0x07, 0xb8, 0xb3, 0x2b
// };

// const uint8_t PROGMEM arrow_BR_Sml_mask[] = {
// 0x04, 0x07, 0xb8, 0xb2, 0x4b, 0xe5, 0x9c, 0x02
// };

// const uint8_t PROGMEM arrow_TL_Sml[] = {
// 0x04, 0x07, 0xb7, 0xd1, 0x03
// };

// const uint8_t PROGMEM arrow_TL_Sml_mask[] = {
// 0x04, 0x07, 0x9d, 0x53, 0x72, 0x1b, 0x1d
// };

// const uint8_t PROGMEM arrow_TM_Sml[] = {
// 0x06, 0x07, 0x08, 0xb3, 0xeb, 0x58, 0x01
// };

// const uint8_t PROGMEM arrow_TM_Sml_mask[] = {
// 0x06, 0x07, 0x88, 0x96, 0x4a, 0x2a, 0xa9, 0xec, 0x64
// };

// const uint8_t PROGMEM arrow_TR_Sml[] = {
// 0x04, 0x07, 0x78, 0xd3, 0x5b
// };

// const uint8_t PROGMEM arrow_TR_Sml_mask[] = {
// 0x04, 0x07, 0x7c, 0x7a, 0xab, 0xa4, 0x73
// };

// const uint8_t PROGMEM arrow_ML_Sml[] = {
// 0x03, 0x07, 0x54, 0x56, 0x51, 0x02
// };

// const uint8_t PROGMEM arrow_ML_Sml_mask[] = {
// 0x03, 0x07, 0x56, 0x4e, 0x2a, 0xc9, 0x04
// };

// const uint8_t PROGMEM arrow_MR_Sml[] = {
// 0x03, 0x07, 0x18, 0x95, 0xcd, 0x01
// };

// const uint8_t PROGMEM arrow_MR_Sml_mask[] = {
// 0x03, 0x07, 0x88, 0xa4, 0x92, 0x4e, 0x29
// };



const uint8_t PROGMEM arrow_BL_Sml[] = {
0x04, 0x07, 0x72, 0x3a, 0x9d, 0x8e, 0x0a
};
// bytes:6 ratio: 1.200

const uint8_t PROGMEM arrow_BL_Sml_mask[] = {
0x04, 0x07, 0xa5, 0x92, 0x76, 0xbb, 0x5d, 0x01
};

const uint8_t PROGMEM arrow_BM_Sml[] = {
0x06, 0x07, 0xa8, 0xd2, 0xe9, 0x74, 0x3a, 0x2e
};
// bytes:7 ratio: 1.000

const uint8_t PROGMEM arrow_BM_Sml_mask[] = {
0x06, 0x07, 0xde, 0x6e, 0xb7, 0xdb, 0xed, 0x76, 0x07
};

const uint8_t PROGMEM arrow_BR_Sml[] = {
0x04, 0x07, 0xb8, 0xd2, 0xe9, 0x9c, 0x53
};
// bytes:7 ratio: 1.400

const uint8_t PROGMEM arrow_BR_Sml_mask[] = {
0x04, 0x07, 0xd4, 0x76, 0xbb, 0x92, 0x4a, 0x2a
};

const uint8_t PROGMEM arrow_TL_Sml[] = {
0x04, 0x07, 0x9d, 0x4b, 0xa7, 0xa3, 0x03
};
// bytes:6 ratio: 1.200

const uint8_t PROGMEM arrow_TL_Sml_mask[] = {
0x04, 0x07, 0xa5, 0x92, 0x6a, 0xbb, 0xdd, 0x02
};

const uint8_t PROGMEM arrow_TM_Sml[] = {
0x06, 0x07, 0x7c, 0x3a, 0x9d, 0x4e, 0x47, 0x07
};
// bytes:7 ratio: 1.000

const uint8_t PROGMEM arrow_TM_Sml_mask[] = {
0x06, 0x07, 0xb7, 0xdb, 0xed, 0x76, 0xbb, 0xdd, 0x02

};

const uint8_t PROGMEM arrow_TR_Sml[] = {
0x04, 0x07, 0x7c, 0x3a, 0x9d, 0x76, 0x0e
};
// bytes:7 ratio: 1.400

const uint8_t PROGMEM arrow_TR_Sml_mask[] = {
0x04, 0x07, 0xb7, 0xdb, 0xad, 0x54, 0x52, 0x01
};

const uint8_t PROGMEM arrow_ML_Sml[] = {
0x03, 0x07, 0x92, 0xcc
};
// bytes:4 ratio: 1.000

const uint8_t PROGMEM arrow_ML_Sml_mask[] = {
0x03, 0x07, 0x75, 0x9a, 0x10
};

const uint8_t PROGMEM arrow_MR_Sml[] = {
0x03, 0x07, 0x88, 0xe5
};
// bytes:6 ratio: 1.500

const uint8_t PROGMEM arrow_MR_Sml_mask[] = {
0x03, 0x07, 0xf8, 0x74, 0x3a
};