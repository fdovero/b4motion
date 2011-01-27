/*
 * image.h
 *
 *
 *
 */

#ifndef B4MIMAGE_H_
#define B4MIMAGE_H_

#include "cv.h"

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
