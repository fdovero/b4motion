/*
 *utils.cpp
 *
 *
 *
 */

#include "utils.h"
#ifdef __unix__
	#include <time.h>
	#include <sys/time.h>
#else
	#include <windows.h>
#endif

namespace b4m
{
	long long getTimeMillis()
	{
	#ifdef __unix__
		// --------------- Sous GNU/Linux ---------------
		// On récupère l'heure dans une structure "timeval"
		timeval tv;
		gettimeofday( &tv, NULL );
		// On la convertit en millisecondes à partir des secondes et
		// des microsecondes
		long long l = tv.tv_usec / 1000;
		l += tv.tv_sec * 1000;
	#else
		// ---------------- Sous Windows ----------------
		// La fonction GetTickCount() de windows.h nous
		// donne directement un timestamp en millisecondes
		long long l= GetTickCount();
	#endif

	return l;
	}

}
