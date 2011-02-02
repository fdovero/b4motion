/* This file is part of B4motion
 * Copyright (C) 2011 Fabien Dovero
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
