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

#ifndef VIDEOFILE_H_
#define VIDEOFILE_H_

#include <highgui.h>
#include "videosource.h"

namespace b4m
{
	class VideoFile: public VideoSource {

		public:
			// Constructeur.
			VideoFile( std::string &nomFichier, bool tempsReel = false );
			// Destructeur.
			virtual ~VideoFile();
			// Ouverture (héritée) du fichier vidéo.
			virtual void open();
			// Fermeture du fichier vidéo.
			virtual void close();
			// Récupération d'une frame
			virtual void getFrame( Image &frame );
			// Surcharge de la méthode "open"
			void open( std::string &nomFichier, bool tempsReel );

		private:
			// Lecture "exhaustive"
			void selectNextFrame();
			// Lecture "temps réel"
			void selectCurrentFrame();
			// Capture OpenCV.
			CvCapture* mCapture;
			// "heure" du début de la lecture.
			long long mDebut;
			// Numéro de la dernière frame sélectionnée.
			long long mLastGrabbed;
			// Lecture temps réel (true) ou exhaustive (false).
			bool mRealtime;
			// Chemin du fichier vidéo.
			std::string mFilePath;
			// Frame Rate de la vidéo
			double mFrameRate;
	};
}


#endif /* VIDEOFILE_H_ */
