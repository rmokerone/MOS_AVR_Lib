/**********************************************************************
	> File Name: common.h
	> Author: Rmoker
	> Mail: rmokerone@gmail.com 
	> Created Time: Tue 18 Feb 2014 09:08:02 PM CST
 *********************************************************************/

#ifndef _COMMON_H_
#define _COMMON_H_

//包含标准头文件
#include <avr/io.h>

#define NULL 0
/*
 * 基本数据类型定义
 */
typedef unsigned char      uint8;    /*  8bits */

typedef unsigned short int uint16;   /* 16bits */
typedef unsigned long int  uint32;   /* 32bits */

typedef signed char        int8;     /*  8bits */
typedef short int          int16;    /* 16bits */
typedef int                int32;    /* 32bits */

typedef volatile int8      vint8;    /*  8bits */
typedef volatile int16     vint16;   /* 16bits */
typedef volatile int32     vint32;   /* 32bits */

typedef volatile uint8     vuint8;   /*  8bits */
typedef volatile uint16    vuint16;  /* 16bits */
typedef volatile uint32    vuint32;  /* 32bits */

typedef float              float32;  /* 32bits */
typedef double             float64;  /* 64bits */

typedef unsigned char      boolean;  /*  8bits */

#endif
