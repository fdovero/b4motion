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
#include <cv.h>
#include "image.h"

namespace b4m
{
	//Constructeur
	Image::Image ( IplImage* img ):mIplimg( img ) {

	}

	//Destructeur
	Image::~Image () {
		 mIplimg=0;
	}

	// Getter
	IplImage* Image::ipl() const {
		return mIplimg;
	}

	// Setter
	void Image::setIpl( IplImage* img ) {
		mIplimg = img;
	}

	// Désallocation
	void Image::release() {
		cvReleaseImage( &mIplimg );
	}

	// Affectation
	void Image::operator=(IplImage* img) {
		mIplimg = img;
	}

	// Cast
	Image::operator IplImage *() const {
		return mIplimg;
	}

	// Filtre de couleur
	void Image::colorFilter( CvScalar teint) {
		for(int x=0; x < mIplimg->width; x++) {
			for(int y=0; y < mIplimg->height; y++) {
				CvScalar pix = cvGet2D(mIplimg, y, x);
				for(int z=0; z < 3; z++) {
					pix.val[z] = pix.val[z]+teint.val[z];
				}
				cvSet2D(mIplimg, y, x, pix);
			}
		}
	}

	// Inversion B&W
	void Image::colorBlacknWhite() {
		for(int x=0; x < mIplimg->width; x++) {
					for(int y=0; y < mIplimg->height; y++) {
						CvScalar pix = cvGet2D(mIplimg, y, x);
						for(int z=0; z < 3; z++) {
							pix.val[z] = 255-pix.val[z];
						}
						cvSet2D(mIplimg, y, x, pix);
					}
		}
	}

	// Peindre en couleur dominante du pixel
	void Image::colorPaint() {
		for(int x=0; x < mIplimg->width; x++) {
					for(int y=0; y < mIplimg->height; y++) {
						CvScalar pix = cvGet2D(mIplimg, y, x);
						if(pix.val[0]>pix.val[1] && pix.val[0]>pix.val[2]) {
							pix.val[0]=255;
							pix.val[1]=pix.val[2]=0;
						}
						if(pix.val[1]>pix.val[0] && pix.val[1]>pix.val[2]) {
							pix.val[1]=255;
							pix.val[0]=pix.val[2]=0;
						}
						if(pix.val[2]>pix.val[1] && pix.val[2]>pix.val[1]) {
							pix.val[2]=255;
							pix.val[0]=pix.val[1]=0;
						}
						cvSet2D(mIplimg, y, x, pix);
					}
		}
	}

	// Peindre en couleur dominante du pixel
	void Image::colorPaint(CvPoint top_left, CvPoint bottom_right) {
		for(int x=top_left.x; x < bottom_right.x; x++) {
					for(int y=top_left.y; y < bottom_right.y; y++) {
						CvScalar pix = cvGet2D(mIplimg, y, x);
						if(pix.val[0]>pix.val[1] && pix.val[0]>pix.val[2]) {
							pix.val[0]=255;
							pix.val[1]=pix.val[2]=0;
						}
						if(pix.val[1]>pix.val[0] && pix.val[1]>pix.val[2]) {
							pix.val[1]=255;
							pix.val[0]=pix.val[2]=0;
						}
						if(pix.val[2]>pix.val[1] && pix.val[2]>pix.val[1]) {
							pix.val[2]=255;
							pix.val[0]=pix.val[1]=0;
						}
						cvSet2D(mIplimg, y, x, pix);
					}
		}
	}

	// Peindre en couleur dominante du pixel
	void Image::colorPaint2(CvPoint top_left, CvPoint bottom_right) {
		for(int x=top_left.x; x < bottom_right.x; x++) {
					for(int y=top_left.y; y < bottom_right.y; y++) {
						CvScalar pix = cvGet2D(mIplimg, y, x);
						if(pix.val[0]>pix.val[1] && pix.val[0]>pix.val[2]) {
							pix.val[1]=pix.val[2]= 128 - pix.val[0];
							pix.val[0]=255;
						}
						if(pix.val[1]>pix.val[0] && pix.val[1]>pix.val[2]) {
							pix.val[0]=pix.val[2]= 128 - pix.val[1];
							pix.val[1]=255;
						}
						if(pix.val[2]>pix.val[1] && pix.val[2]>pix.val[1]) {
							pix.val[1]=pix.val[0]= 128 - pix.val[2];
							pix.val[2]=255;
						}
						cvSet2D(mIplimg, y, x, pix);
					}
		}
	}
}
