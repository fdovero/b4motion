/*
 * exception.h
 *
 *  Created on: 26 janv. 2011
 *      Author: Fabien Dovero
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
