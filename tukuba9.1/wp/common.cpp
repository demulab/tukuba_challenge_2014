/*** WayPoint Maker 2011 http://demura.net ***/

//! 共通関数
/*! 共通関数は今のところ時間取得関数のみ

 \file   common.cpp
 \author Kosei Demura
 \date   2010-09-07
*/


#include "../include/common.h"
#include <sys/time.h>
#include <stddef.h>

double getTime()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);

	return tv.tv_sec + tv.tv_usec * 1e-6;
}

