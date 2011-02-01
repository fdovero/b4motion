/*
 * videofile.cpp
 *
 *
 *
 */

#include <videofile.h>
#include <exception.h>
#include <utils.h>
#include <sstream>
namespace b4m
{
	using namespace std;
	// Constructeur
	VideoFile::VideoFile( string &nomFichier, bool tempsReel )
	: mRealtime( tempsReel ), mFilePath( nomFichier ) {

	}

	// Destructeur : on ferme le flux
	VideoFile::~VideoFile() {
		close();
	}

	// Ouverture : on appelle la méthode surchargée
	void VideoFile::open( ) {
		open( mFilePath, mRealtime );
	}

	// Ouverture (surchargée)
	void VideoFile::open( string &nomFichier, bool tempsReel ) {
		// Initialisation de la capture
		mCapture = cvCreateFileCapture( nomFichier.c_str() );
		// Vérification
		if( mCapture == NULL ) {
			string message( "Impossible d'ouvrir le fichier : " );
			message += nomFichier;
			throw Exception( EX_ERREUR, message.c_str() );
		}
		// On "grabbe" la première frame du flux pour obtenir des informations
		cvGrabFrame( mCapture );
		// Récupération des informations et mise à jour de l'attribut mInfos
		mFrameRate = cvGetCaptureProperty( mCapture, CV_CAP_PROP_FPS );
		mFilePath = nomFichier;
		mRealtime = tempsReel;
		ostringstream oss;
		oss << "Fichier " << nomFichier << " (" << mFrameRate << "fps, ";
		oss << cvGetCaptureProperty( mCapture, CV_CAP_PROP_FRAME_WIDTH ) << "x";
		oss << cvGetCaptureProperty( mCapture, CV_CAP_PROP_FRAME_HEIGHT );
		oss << ", Lecture " << ( mRealtime ? "Temps Reel" : "Exhaustive" );
		mInfos = oss.str();
		// On initialise le compteur de frames à 0.
		mLastGrabbed = 0;
	}

	// Fermeture du flux
	void VideoFile::close() {
		if( mCapture ) {
			cvReleaseCapture( &mCapture );
		}
		mCapture = NULL;
	}

	// Récupération d'une frame
	void VideoFile::getFrame( Image &frame ) {
		if( mRealtime ) {
			selectCurrentFrame(); // mode "temps réel"
		}
		else {
			selectNextFrame();
		}
		// mode "exhaustif"
		frame = cvRetrieveFrame( mCapture ); // décompression de la frame
	}

	// Sélection de la prochaine frame de la vidéo.
	void FichierVideo::selectNextFrame() {
		if(! cvGrabFrame( mCapture )) {
			throw Exception( EX_MESSAGE, "EOF" );
		}
		// On incrémente le compteur de frames
		mLastGrabbed++;
	}

	void VideoFile::selectCurrentFrame() {
		long long position_ms = ( getTimeMillis() - mDebut );

		if( !cvSetCaptureProperty( mCapture, CV_CAP_PROP_POS_MSEC, position_ms ) ) {
			long long nbframes = cvRound( position_ms * mFrameRate / 1000 );
			while( mLastGrabbed > nbframes ) {
				cvWaitKey( 5 );
				position_ms = getTimeMillis() - mDebut;
				nbframes = cvRound( position_ms * mFrameRate / 1000 );
			}
			while( mLastGrabbed < nbframes ) {
				selectNextFrame();
			}
		}
		selectNextFrame();
	}
}
