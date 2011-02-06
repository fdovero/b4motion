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
             Image( IplImage* img = 0 ) : mIplimg( img ){

             }

             // Destructeur
             virtual ~Image(){
                 mIplimg=0;
             }

             // Getter
             IplImage* ipl() const {
                 return mIplimg;
             }

             // Setter
             void setIpl( IplImage* img ) {
                 mIplimg = img;
             }

             // Désallocation
             void release() {
                 cvReleaseImage( &mIplimg );
             }

             // Affectation
             void operator=(IplImage* img) {
            	 mIplimg = img;
             }

             // Cast
             operator IplImage *() const {
            	 return mIplimg;
             }

         protected:
             // L'IplImage* encapsulé
             IplImage* mIplimg;
     };
}

#endif /* B4MIMAGE_H_ */
