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

#ifndef B4MEXCEPTION_H_
#define B4MEXCEPTION_H_

#include <exception>

#define	EX_MESSAGE	0
#define EX_WARNING	1
#define EX_ERREUR	2

namespace b4m {

	class Exception: public std::exception
	{
		public:
			/// Constructeur.
			Exception( unsigned char niveau = EX_MESSAGE, const char* message = "" ) throw ();

			/// Accesseur hérité.
			virtual const char* what() const throw();

			/// Accesseur pour le niveau d'importance.
			unsigned char getNiveau() const throw();

			/// Destructeur.
			virtual ~Exception() throw();

		private:
			/// Niveau d'importance de l'exception.
			unsigned char mNiveau;

			/// Message descriptif.
			const char* mMessage;
   };

}

#endif /* B4MEXCEPTION_H_ */
