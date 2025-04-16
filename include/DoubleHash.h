#pragma once
#include <iostream>
#include "vector.h"
#include "data.h"

constexpr unsigned short BLOCK_SIZE = 64;
typedef uint8_t block[BLOCK_SIZE];

static const unsigned long long SShOGRNIP[8]{ //Вот эти 8 констант я сделал именно для своего алгоса
    0x315503200003237a,  0x1147746261365bfc,
    0x318500700034370c,  0x311774601901274d,
    0x00003237e3155032,  0x61365a1147746288,
    0x00034370f3185007,  0x1901274b31177460
};

static const unsigned char Pi[256] = {	//s-box	//Нелинейное биективное преобразование
	252, 238, 221, 17, 207, 110, 49, 22, 251, 196, 250, 218, 35, 197, 4, 77,
	233, 119, 240, 219, 147, 46, 153, 186, 23, 54, 241, 187, 20, 205, 95, 193,
	249, 24, 101, 90, 226, 92, 239, 33, 129, 28, 60, 66, 139, 1, 142, 79, 5,
	132, 2, 174, 227, 106, 143, 160, 6, 11, 237, 152, 127, 212, 211, 31, 235,
	52, 44, 81, 234, 200, 72, 171, 242, 42, 104, 162, 253, 58, 206, 204, 181,
	112, 14, 86, 8, 12, 118, 18, 191, 114, 19, 71, 156, 183, 93, 135, 21, 161,
	150, 41, 16, 123, 154, 199, 243, 145, 120, 111, 157, 158, 178, 177, 50, 117,
	25, 61, 255, 53, 138, 126, 109, 84, 198, 128, 195, 189, 13, 87, 223, 245,
	36, 169, 62, 168, 67, 201, 215, 121, 214, 246, 124, 34, 185, 3, 224, 15,
	236, 222, 122, 148, 176, 188, 220, 232, 40, 80, 78, 51, 10, 74, 167, 151,
	96, 115, 30, 0, 98, 68, 26, 184, 56, 130, 100, 159, 38, 65, 173, 69, 70,
	146, 39, 94, 85, 47, 140, 163, 165, 125, 105, 213, 149, 59, 7, 88, 179, 64,
	134, 172, 29, 247, 48, 55, 107, 228, 136, 217, 231, 137, 225, 27, 131, 73,
	76, 63, 248, 254, 141, 83, 170, 144, 202, 216, 133, 97, 32, 113, 103, 164,
	45, 43, 9, 91, 203, 155, 37, 208, 190, 229, 108, 82, 89, 166, 116, 210, 230,
	244, 180, 192, 209, 102, 175, 194, 57, 75, 99, 182 };

static const unsigned char Tau[64] = {//Перестановка байт
	0,   8,  16,  24,  32,  40,  48,  56,
	1,   9,  17,  25,  33,  41,  49,  57,
	2,  10,  18,  26,  34,  42,  50,  58,
	3,  11,  19,  27,  35,  43,  51,  59,
	4,  12,  20,  28,  36,  44,  52,  60,
	5,  13,  21,  29,  37,  45,  53,  61,
	6,  14,  22,  30,  38,  46,  54,  62,
	7,  15,  23,  31,  39,  47,  55,  63
};

//Умножение справа на А над полем GF(2) //преобразование L
static const unsigned long long A[64] = {
    0x8e20faa72ba0b470,    0x47107ddd9b505a38,    0xad08b0e0c3282d1c,    0xd8045870ef14980e,
    0x6c022c38f90a4c07,    0x3601161cf205268d,    0x1b8e0b0e798c13c8,    0x83478b07b2468764,
    0xa011d380818e8f40,    0x5086e740ce47c920,    0x2843fd2067adea10,    0x14aff010bdd87508,
    0x0ad97808d06cb404,    0x05e23c0468365a02,    0x8c711e02341b2d01,    0x46b60f011a83988e,
    0x90dab52a387ae76f,    0x486dd4151c3dfdb9,    0x24b86a840e90f0d2,    0x125c354207487869,
    0x092e94218d243cba,    0x8a174a9ec8121e5d,    0x4585254f64090fa0,    0xaccc9ca9328a8950,
    0x9d4df05d5f661451,    0xc0a878a0a1330aa6,    0x60543c50de970553,    0x302a1e286fc58ca7,
    0x18150f14b9ec46dd,    0x0c84890ad27623e0,    0x0642ca05693b9f70,    0x0321658cba93c138,
    0x86275df09ce8aaa8,    0x439da0784e745554,    0xafc0503c273aa42a,    0xd960281e9d1d5215,
    0xe230140fc0802984,    0x71180a8960409a42,    0xb60c05ca30204d21,    0x5b068c651810a89e,
    0x456c34887a3805b9,    0xac361a443d1c8cd2,    0x561b0d22900e4669,    0x2b838811480723ba,
    0x9bcf4486248d9f5d,    0xc3e9224312c8c1a0,    0xeffa11af0964ee50,    0xf97d86d98a327728,
    0xe4fa2054a80b329c,    0x727d102a548b194e,    0x39b008152acb8227,    0x9258048415eb419d,
    0x492c024284fbaec0,    0xaa16012142f35760,    0x550b8e9e21f7a530,    0xa48b474f9ef5dc18,
    0x70a6a56e2440598e,    0x3853dc371220a247,    0x1ca76e95091051ad,    0x0edd37c48a08a6d8,
    0x07e095624504536c,    0x8d70c431ac02a736,    0xc83862965601dd1b,    0x641c314b2b8ee083
};
//константы для вычисления ключей
static const unsigned char C[12][64] = {
    {
        0x07, 0x45, 0xa6, 0xf2, 0x59, 0x65, 0x80, 0xdd,
        0x23, 0x4d, 0x74, 0xcc, 0x36, 0x74, 0x76, 0x05,
        0x15, 0xd3, 0x60, 0xa4, 0x08, 0x2a, 0x42, 0xa2,
        0x01, 0x69, 0x67, 0x92, 0x91, 0xe0, 0x7c, 0x4b,
        0xfc, 0xc4, 0x85, 0x75, 0x8d, 0xb8, 0x4e, 0x71,
        0x16, 0xd0, 0x45, 0x2e, 0x43, 0x76, 0x6a, 0x2f,
        0x1f, 0x7c, 0x65, 0xc0, 0x81, 0x2f, 0xcb, 0xeb,
        0xe9, 0xda, 0xca, 0x1e, 0xda, 0x5b, 0x08, 0xb1
    },
    {
        0xb7, 0x9b, 0xb1, 0x21, 0x70, 0x04, 0x79, 0xe6,
        0x56, 0xcd, 0xcb, 0xd7, 0x1b, 0xa2, 0xdd, 0x55,
        0xca, 0xa7, 0x0a, 0xdb, 0xc2, 0x61, 0xb5, 0x5c,
        0x58, 0x99, 0xd6, 0x12, 0x6b, 0x17, 0xb5, 0x9a,
        0x31, 0x01, 0xb5, 0x16, 0x0f, 0x5e, 0xd5, 0x61,
        0x98, 0x2b, 0x23, 0x0a, 0x72, 0xea, 0xfe, 0xf3,
        0xd7, 0xb5, 0x70, 0x0f, 0x46, 0x9d, 0xe3, 0x4f,
        0x1a, 0x2f, 0x9d, 0xa9, 0x8a, 0xb5, 0xa3, 0x6f
    },
    {
        0xb2, 0x0a, 0xba, 0x0a, 0xf5, 0x96, 0x1e, 0x99,
        0x31, 0xdb, 0x7a, 0x86, 0x43, 0xf4, 0xb6, 0xc2,
        0x09, 0xdb, 0x62, 0x60, 0x37, 0x3a, 0xc9, 0xc1,
        0xb1, 0x9e, 0x35, 0x90, 0xe4, 0x0f, 0xe2, 0xd3,
        0x7b, 0x7b, 0x29, 0xb1, 0x14, 0x75, 0xea, 0xf2,
        0x8b, 0x1f, 0x9c, 0x52, 0x5f, 0x5e, 0xf1, 0x06,
        0x35, 0x84, 0x3d, 0x6a, 0x28, 0xfc, 0x39, 0x0a,
        0xc7, 0x2f, 0xce, 0x2b, 0xac, 0xdc, 0x74, 0xf5
    },
    {
        0x2e, 0xd1, 0xe3, 0x84, 0xbc, 0xbe, 0x0c, 0x22,
        0xf1, 0x37, 0xe8, 0x93, 0xa1, 0xea, 0x53, 0x34,
        0xbe, 0x03, 0x52, 0x93, 0x33, 0x13, 0xb7, 0xd8,
        0x75, 0xd6, 0x03, 0xed, 0x82, 0x2c, 0xd7, 0xa9,
        0x3f, 0x35, 0x5e, 0x68, 0xad, 0x1c, 0x72, 0x9d,
        0x7d, 0x3c, 0x5c, 0x33, 0x7e, 0x85, 0x8e, 0x48,
        0xdd, 0xe4, 0x71, 0x5d, 0xa0, 0xe1, 0x48, 0xf9,
        0xd2, 0x66, 0x15, 0xe8, 0xb3, 0xdf, 0x1f, 0xef
    },
    {
        0x57, 0xfe, 0x6c, 0x7c, 0xfd, 0x58, 0x17, 0x60,
        0xf5, 0x63, 0xea, 0xa9, 0x7e, 0xa2, 0x56, 0x7a,
        0x16, 0x1a, 0x27, 0x23, 0xb7, 0x00, 0xff, 0xdf,
        0xa3, 0xf5, 0x3a, 0x25, 0x47, 0x17, 0xcd, 0xbf,
        0xbd, 0xff, 0x0f, 0x80, 0xd7, 0x35, 0x9e, 0x35,
        0x4a, 0x10, 0x86, 0x16, 0x1f, 0x1c, 0x15, 0x7f,
        0x63, 0x23, 0xa9, 0x6c, 0x0c, 0x41, 0x3f, 0x9a,
        0x99, 0x47, 0x47, 0xad, 0xac, 0x6b, 0xea, 0x4b
    },
    {
        0x6e, 0x7d, 0x64, 0x46, 0x7a, 0x40, 0x68, 0xfa,
        0x35, 0x4f, 0x90, 0x36, 0x72, 0xc5, 0x71, 0xbf,
        0xb6, 0xc6, 0xbe, 0xc2, 0x66, 0x1f, 0xf2, 0x0a,
        0xb4, 0xb7, 0x9a, 0x1c, 0xb7, 0xa6, 0xfa, 0xcf,
        0xc6, 0x8e, 0xf0, 0x9a, 0xb4, 0x9a, 0x7f, 0x18,
        0x6c, 0xa4, 0x42, 0x51, 0xf9, 0xc4, 0x66, 0x2d,
        0xc0, 0x39, 0x30, 0x7a, 0x3b, 0xc3, 0xa4, 0x6f,
        0xd9, 0xd3, 0x3a, 0x1d, 0xae, 0xae, 0x4f, 0xae
    },
    {
        0x93, 0xd4, 0x14, 0x3a, 0x4d, 0x56, 0x86, 0x88,
        0xf3, 0x4a, 0x3c, 0xa2, 0x4c, 0x45, 0x17, 0x35,
        0x04, 0x05, 0x4a, 0x28, 0x83, 0x69, 0x47, 0x06,
        0x37, 0x2c, 0x82, 0x2d, 0xc5, 0xab, 0x92, 0x09,
        0xc9, 0x93, 0x7a, 0x19, 0x33, 0x3e, 0x47, 0xd3,
        0xc9, 0x87, 0xbf, 0xe6, 0xc7, 0xc6, 0x9e, 0x39,
        0x54, 0x09, 0x24, 0xbf, 0xfe, 0x86, 0xac, 0x51,
        0xec, 0xc5, 0xaa, 0xee, 0x16, 0x0e, 0xc7, 0xf4
    },
    {
        0x1e, 0xe7, 0x02, 0xbf, 0xd4, 0x0d, 0x7f, 0xa4,
        0xd9, 0xa8, 0x51, 0x59, 0x35, 0xc2, 0xac, 0x36,
        0x2f, 0xc4, 0xa5, 0xd1, 0x2b, 0x8d, 0xd1, 0x69,
        0x90, 0x06, 0x9b, 0x92, 0xcb, 0x2b, 0x89, 0xf4,
        0x9a, 0xc4, 0xdb, 0x4d, 0x3b, 0x44, 0xb4, 0x89,
        0x1e, 0xde, 0x36, 0x9c, 0x71, 0xf8, 0xb7, 0x4e,
        0x41, 0x41, 0x6e, 0x0c, 0x02, 0xaa, 0xe7, 0x03,
        0xa7, 0xc9, 0x93, 0x4d, 0x42, 0x5b, 0x1f, 0x9b
    },
    {
        0xdb, 0x5a, 0x23, 0x83, 0x51, 0x44, 0x61, 0x72,
        0x60, 0x2a, 0x1f, 0xcb, 0x92, 0xdc, 0x38, 0x0e,
        0x54, 0x9c, 0x07, 0xa6, 0x9a, 0x8a, 0x2b, 0x7b,
        0xb1, 0xce, 0xb2, 0xdb, 0x0b, 0x44, 0x0a, 0x80,
        0x84, 0x09, 0x0d, 0xe0, 0xb7, 0x55, 0xd9, 0x3c,
        0x24, 0x42, 0x89, 0x25, 0x1b, 0x3a, 0x7d, 0x3a,
        0xde, 0x5f, 0x16, 0xec, 0xd8, 0x9a, 0x4c, 0x94,
        0x9b, 0x22, 0x31, 0x16, 0x54, 0x5a, 0x8f, 0x37
    },
    {
        0xed, 0x9c, 0x45, 0x98, 0xfb, 0xc7, 0xb4, 0x74,
        0xc3, 0xb6, 0x3b, 0x15, 0xd1, 0xfa, 0x98, 0x36,
        0xf4, 0x52, 0x76, 0x3b, 0x30, 0x6c, 0x1e, 0x7a,
        0x4b, 0x33, 0x69, 0xaf, 0x02, 0x67, 0xe7, 0x9f,
        0x03, 0x61, 0x33, 0x1b, 0x8a, 0xe1, 0xff, 0x1f,
        0xdb, 0x78, 0x8a, 0xff, 0x1c, 0xe7, 0x41, 0x89,
        0xf3, 0xf3, 0xe4, 0xb2, 0x48, 0xe5, 0x2a, 0x38,
        0x52, 0x6f, 0x05, 0x80, 0xa6, 0xde, 0xbe, 0xab
    },
    {
        0x1b, 0x2d, 0xf3, 0x81, 0xcd, 0xa4, 0xca, 0x6b,
        0x5d, 0xd8, 0x6f, 0xc0, 0x4a, 0x59, 0xa2, 0xde,
        0x98, 0x6e, 0x47, 0x7d, 0x1d, 0xcd, 0xba, 0xef,
        0xca, 0xb9, 0x48, 0xea, 0xef, 0x71, 0x1d, 0x8a,
        0x79, 0x66, 0x84, 0x14, 0x21, 0x80, 0x01, 0x20,
        0x61, 0x07, 0xab, 0xeb, 0xbb, 0x6b, 0xfa, 0xd8,
        0x94, 0xfe, 0x5a, 0x63, 0xcd, 0xc6, 0x02, 0x30,
        0xfb, 0x89, 0xc8, 0xef, 0xd0, 0x9e, 0xcd, 0x7b
    },
    {
        0x20, 0xd7, 0x1b, 0xf1, 0x4a, 0x92, 0xbc, 0x48,
        0x99, 0x1b, 0xb2, 0xd9, 0xd5, 0x17, 0xf4, 0xfa,
        0x52, 0x28, 0xe1, 0x88, 0xaa, 0xa4, 0x1d, 0xe7,
        0x86, 0xcc, 0x91, 0x18, 0x9d, 0xef, 0x80, 0x5d,
        0x9b, 0x9f, 0x21, 0x30, 0xd4, 0x12, 0x20, 0xf8,
        0x77, 0x1d, 0xdf, 0xbc, 0x32, 0x3c, 0xa4, 0xcd,
        0x7a, 0xb1, 0x49, 0x04, 0xb0, 0x80, 0x13, 0xd2,
        0xba, 0x31, 0x16, 0xf1, 0x67, 0xe7, 0x8e, 0x37
    } 
};


//поигрался с гостом, на основе сжатия сделал свой ужас
//в обозначениях ниже m - блок исходных данных
//h - значение функции сжатия

//обработка на основе компрессии формирует мне *старшую* часть, а нечто мурррррчащее "младшую"

//двойное хэширование снизу) - для него как раз используется вот этот хэш и полиномиальный

template<class val_>
class HASH_TABLE_STRING {

    size_t LOG;
    size_t CONTAINER_SIZE;
    vector<std::pair<int, Data<std::string, val_>>> CONTAINER;  //<удалили/свободно/занято?  /   Data >
    //ПРИ СОЗДАНИИ ХЭШ ТАБЛИЦЫ МЫ ГАРАНТИРУЕМ ЧТО ТАМ МЕСТА НЕ МЕНЬШЕ ЧЕМ СКАЗАЛ ЮЗЕР, но хорошо бы чтоб размер был простым числом, поэтому пытаемся сделать размер больше сказанного
    void resheto_eratosfena(size_t N,size_t R) {//хотел подумать про сегментированную (2,3,5)-факторизацию, но не хватило времени, поэтому здесь старый добрый эратосфен
        vector<bool> p(N + 1, true);
        p[0] = p[1] = false;
        for (size_t i = 2; i <= N; ++i) 
            if (p[i] && i * 1ll * i <= N) 
                for (int j = i * i; j <= N; j += i) 
                    p[j] = false;
        for (int i = R; i < p.size(); i++) {
            if (p[i]) {
                CONTAINER_SIZE = i;
                return;
            }
        }
        CONTAINER_SIZE = R + CONTAINER_SIZE & 1ull;
    }

	static void XORM2(const uint8_t* l, const uint8_t* r, uint8_t* res) {
		for (int i = 0; i < 64; i++) res[i] = l[i] ^ r[i];
	}
    static void XORM2(const uint8_t* l, const uint8_t* r, uint8_t* res,size_t sz) {
        for (int i = 0; i < sz*8; i++) res[i] = l[i] ^ r[i];
    }

    //Все что ниже с буквы S_ - просто функции отображения (выше заданы как раз массивы)
	static void S_Pi(uint8_t* a) {
		block sbr;
		for (int i = 63; i > -1; i--)sbr[i] = Pi[a[i]];
		memcpy(a, sbr, BLOCK_SIZE);
	}
	static void S_P(uint8_t* a) {
		block sbr;
		for (int i = 63; i > -1; i--)sbr[i] = Tau[a[i]];
		memcpy(a, sbr, BLOCK_SIZE);
	}
	static void S_L(uint8_t* a) {
		uint64_t sbr[8];
		memset(sbr, 0x00, BLOCK_SIZE);
		for (int i = 7; i > -1; i--) for (int j = 63; j > -1; j--) if ((a[i] >> j) & 1) sbr[i] ^= A[63 - j];
		memcpy(a, sbr, 64);
	}
    static void SShIP(uint8_t* a) { //По факту как S_L но по моим константам (индексы по кольцу 8)
        uint64_t sbr[8];
        memset(sbr, 0x00, BLOCK_SIZE);
        for (int i = 7; i > -1; i--) for (int j = 63; j > -1; j--) if ((a[i] >> j) & 1) sbr[i%8] ^= A[63 - j];
        memcpy(a, sbr, 64);
    }
    static void GetKeys(uint8_t* K, int i)
    {
        XORM2(K, C[i], K);
        S_Pi(K);
        S_P(K);
        S_L(K);
    }
    static void S_E(uint8_t* K, const uint8_t* m, uint8_t* a)
    {
        int i;
        memcpy(K, K, BLOCK_SIZE);
        XORM2(m, K, a);
        for (i = 0; i < 12; i++)
        {
            S_Pi(a);
            S_P(a);
            S_L(a);
            GetKeys(K, i);
            XORM2(a, K, a);
        }
    }
    static void compress(uint8_t* h, uint8_t* n, const uint8_t* m) {    //ОСНОВНАЯ ФУНКЦИЯ СЖАТИЯ
        block K, sbr;
        XORM2(n, h, K);
        S_Pi(K);
        S_P(K);
        S_L(K);
        S_E(K, m, sbr);
        XORM2(sbr, h, sbr);
        XORM2(sbr, m, h);
    }

public:
    void resetLog() { LOG = 0; }
    size_t Log() { return LOG; }
    HASH_TABLE_STRING(size_t cnt_sz = 1000) {
        resheto_eratosfena(cnt_sz + cnt_sz / 2, cnt_sz); 
        CONTAINER.resize(CONTAINER_SIZE);
    };

    size_t Hash_IzVrat(const std::string& data_) {
        
        block Sigma, v512,tmp,h,N;
        memset(Sigma, 0x00, BLOCK_SIZE);
        memset(tmp, 0x00, BLOCK_SIZE);
        memset(h, 0x00, BLOCK_SIZE);
        memset(N, 0x00, BLOCK_SIZE);
        memset(v512, 0x00, BLOCK_SIZE);
        v512[1] = 0x02;

        //          
        //        SShOGRNIP[i]\/
        //          xor ---->
        //S------->     ----->
        //V0------>g    ---->
        //N-------> ----->
        //          data[i]/\

        const uint8_t* data = reinterpret_cast<const uint8_t*>(data_.data());
        size_t data_size = data_.size();

        uint32_t res = 1;

        for (size_t i = 0; i < data_size; i += 4) {
            LOG++;
            size_t bytes_to_copy = std::min(static_cast<size_t>(64), data_size - i);
            std::memcpy(tmp, data + i, bytes_to_copy);

            SShIP(tmp);
            XORM2(Sigma, Sigma, tmp);
            compress(h, N, data + i);//i-й блок данных
            XORM2(h, N, N);
            XORM2(h, v512, v512);
            XORM2(v512, N, v512);
            res <<= 8;
            for (int j = 0; j < 8; j++) {
                LOG++;
                uint32_t tmp2 = (h[j] ^ (res & (1 << j)));
                res *= tmp2;
            }
        }

        res ^= h[0] | (2 << Sigma[SShOGRNIP[res % 8] % 8]);

        const uint32_t p1 = 0xcc9e2d51;
        const uint32_t p2 = 0x1b873593;
        const uint32_t c1 = 15;
        const uint32_t c2 = 13;
        const uint32_t m = 5;
        const uint32_t n = 0xe6546b64;
        
        uint32_t hashM = SShOGRNIP[res%8];
        
        const int nblocks = data_.size() / 4;
        const uint32_t* blocks = reinterpret_cast<const uint32_t*>(data_.data());

        for (int i = 0; i < nblocks; ++i) {
            LOG++;
            uint32_t k = blocks[i];
            k *= p1;
            k = (k << c1) | (k >> (32 - c1));
            k *= p2;
            hashM ^= k;
            hashM = ((hashM << p2) | (hashM >> (32 - c2))) * m + n;
        }

        const uint8_t* t = reinterpret_cast<const uint8_t*>(data_.data() + nblocks * 4);
        uint32_t k1 = 0;

        switch (data_.size() & 3) {
            case 3: k1 ^= t[2] << 16;
            case 2: k1 ^= t[1] << 8;
            case 1: k1 ^= t[0];
                k1 *= p1;
                k1 = (k1 << c1) | (k1 >> (32 -c1));
                k1 *= p2;
                hashM ^= k1;
        };
        LOG++;

        hashM ^= data_.size();
        hashM ^= hashM >> 16;
        hashM *= SShOGRNIP[res%8];
        hashM ^= hashM >> 13;
        hashM *= SShOGRNIP[(res ^ hashM) % 8];
        hashM ^= hashM >> 16;

        res <<= sizeof(size_t)/4*8;
        res ^= hashM;
        return res % CONTAINER_SIZE;
    }   
    size_t Polinomial_hash(const std::string& s) {
        size_t M = std::max(1000000007ull, CONTAINER_SIZE);
        size_t res = 0;
        size_t t0=1, t1=1;
        size_t cur = 0;
        t0 = 1;
        size_t g1 = 1093;
        for(int i = 0;i<s.size();i++){
            LOG++;
            cur = (cur * g1 + s[i]) % M;
            res = cur;
            if (i > 0) t1 = t0 * g1 % M;
            LOG++;
            t0 = t1;
        }
        res = res % CONTAINER_SIZE;
        return res + !res;
    }
    std::pair<size_t, size_t> Double_hash_coeff(const std::string& key) {
        return std::pair<size_t,size_t>(Hash_IzVrat(key),Polinomial_hash(key));
    }
    void Delete(const std::string& key) {
        size_t pos = 0;
        std::pair<size_t, size_t> coefs = Double_hash_coeff(key);
        vector<bool> was(CONTAINER_SIZE, 0);
        size_t i = 0;
        while (1) {
            pos = (coefs.first + (i * coefs.second % CONTAINER_SIZE ? i * coefs.second % CONTAINER_SIZE : 1)) % CONTAINER_SIZE;
            LOG++;
            if (was[pos]) {
                throw std::logic_error("Cant find element to delete");
            }
            was[pos] = 1;
            LOG++;
            if (CONTAINER[pos].first == 1 && CONTAINER[pos].second.getKey()==key) {
                CONTAINER[pos].first = -1;
                break;
            }
            ++i;
        }
    }
    std::pair<bool, Data<std::string,val_>> find(const std::string& key) {
        size_t pos = 0;
        std::pair<size_t, size_t> coefs = Double_hash_coeff(key);
        vector<bool> was(CONTAINER_SIZE, 0);
        size_t i = 0;
        while (1) {
            pos = (coefs.first + (i * coefs.second % CONTAINER_SIZE ? i * coefs.second % CONTAINER_SIZE : 1)) % CONTAINER_SIZE;
            LOG++;
            if (was[pos]) {
                return { 0, Data<std::string,val_>() };
            }
            was[pos] = 1;
            LOG++;
            if (CONTAINER[pos].first == 1 && CONTAINER[pos].second.getKey() == key) {
                return { 1, CONTAINER[pos].second };
            }
            ++i;
        }
    }


    void insert(const Data<std::string, val_>& d) {
        size_t pos = 0;
        std::pair<size_t, size_t> coefs = Double_hash_coeff(d.getKey());
        vector<bool> was(CONTAINER_SIZE,0);
        size_t i = 0;
        while (1) {
            pos = (coefs.first + (i * coefs.second % CONTAINER_SIZE ? i * coefs.second % CONTAINER_SIZE : 1)) % CONTAINER_SIZE;
            LOG++;
            if (was[pos]) {
                throw std::logic_error("Cant find place to insert");
            }
            LOG++;
            if (CONTAINER[pos].first==1 && CONTAINER[pos].second == d) {
                throw std::logic_error("dublicate data!");
            }
            was[pos] = 1;
            LOG++;
            if (!CONTAINER[pos].first || CONTAINER[pos].first == -1) {
                CONTAINER[pos].first = 1;
                CONTAINER[pos].second = d;
                break;
            }
            ++i;
        }
        return;
    }
};