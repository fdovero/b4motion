/*
 * frame.h
 *
 *  Created on: 25 janv. 2011
 *      Author: Fabien Dovero
 */

#ifndef B4MFRAME_H_
#define B4MFRAME_H_

#include "cv.h"

namespace b4m
{
     class Frame
     {
         public :
             // Constructeur
             Frame( IplImage* img = 0 ) : mIplimg( img ){

             }

             // Destructeur
             virtual ~Frame(){
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

#endif /* B4MFRAME_H_ */
