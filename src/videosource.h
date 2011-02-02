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

#ifndef B4MVIDEOSOURCE_H_
#define B4MVIDEOSOURCE_H_

#include <string>
#include "image.h"

namespace b4m
{

    class VideoSource
    {
    	public:
			// Destructeur
			virtual ~VideoSource() {

			}

			// Récupération d'infos
			virtual std::string getInfos() {
				return mInfos;
			}

			// Ouverture du flux
			virtual void open() = 0;

			// Fermeture du flux
			virtual void close() = 0;

			// Récupération d'une frame
			virtual void getFrame( Image &frame ) = 0;

        protected:

            // Informations sur le flux
            std::string mInfos;
    };
}


#endif /* B4MVIDEOSOURCE_H_ */
