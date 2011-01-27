/*
 * exception.cpp
 *
 *
 *
 */

#include <exception.h>

namespace b4m
{
	Exception::Exception( unsigned char niveau, const char* message ) throw ()
        :mNiveau( niveau ), mMessage( message ) {

	}

    const char* Exception::what() const throw() {
        return mMessage;
    }

    unsigned char Exception::getNiveau() const throw() {
        return mNiveau;
    }

    Exception::~Exception() throw() {

    }
}
