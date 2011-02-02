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

#ifndef B4MCAMERA_H_
#define B4MCAMERA_H_

#include "videosource.h"
#include <highgui.h>

namespace b4m
{
    class Camera: public VideoSource
    {
        public:
            // Constructeur, on lui passe l'indice de la caméra
            Camera( int index = -1 );

            // Destructeur
            virtual ~Camera();

            // Ouverture (héritée)
            virtual void open();

            // Fermeture (héritée)
            virtual void close();

            // Lecture (héritée)
            virtual void getFrame( Image &frame );

            // Ouverture surchargée
            void open( int index );

        private:
            // La capture OpenCV
            CvCapture* mCapture;

            // L'indice de la caméra
            int mIndice;
    };
}

#endif /* B4MCAMERA_H_ */
