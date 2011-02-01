/*
 *videofile.h
 *
 *
 *
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
