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

#ifndef B4MIMAGE_H_
#define B4MIMAGE_H_

#include <cv.h>

namespace b4m
{
     class Image
     {
         public :

    	 	 // Constructeur
             Image( IplImage* img = 0);

             // Destructeur
             virtual ~Image();

             // Getter
             IplImage* ipl() const;

             // Setter
             void setIpl( IplImage* img );

             // Désallocation
             void release();

             // Affectation
             void operator=(IplImage* img);

             // Cast
             operator IplImage *() const;

             //Filtre de couleur
             void colorFilter( CvScalar teint );

             //Inversion B&W
             void colorBlacknWhite();

             //Peindre en couleur dominante
             void colorPaint();

             //Peindre en couleur dominante
             void colorPaint(CvPoint top_left, CvPoint bottom_right);

             //Peindre en couleur dominante
             void colorPaint2(CvPoint top_left, CvPoint bottom_right);

         protected:
             // L'IplImage* encapsulé
             IplImage* mIplimg;
     };
}

#endif /* B4MIMAGE_H_ */
