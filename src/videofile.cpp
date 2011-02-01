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
        : mRealtime( tempsReel ), mFilePath( nomFichier ) {}

    // Destructeur
    VideoFile::~VideoFile() {
        close();
    }

    // Ouverture (héritée) du flux
    void VideoFile::open() {
        open( mFilePath, mRealtime );
    }

    // Ouverture (surchargée)
    void VideoFile::open( string &nomFichier, bool tempsReel ) {

        mCapture = cvCreateFileCapture( nomFichier.c_str() );

        if( mCapture == NULL )
        {
            string message( "Impossible d'ouvrir le fichier : " );
            message += nomFichier;
            throw Exception( EX_ERREUR, message.c_str() );
        }

        cvGrabFrame( mCapture );
        cvRetrieveFrame( mCapture );

        mFrameRate = cvGetCaptureProperty( mCapture, CV_CAP_PROP_FPS );
        mFilePath = nomFichier;
        mRealtime = tempsReel;

        ostringstream oss;
        oss << "Fichier " << nomFichier << " (" << mFrameRate << "fps, ";
        oss << cvGetCaptureProperty( mCapture, CV_CAP_PROP_FRAME_WIDTH ) << "x";
        oss << cvGetCaptureProperty( mCapture, CV_CAP_PROP_FRAME_HEIGHT );
        oss << ", Lecture " << ( mRealtime ? "Temps Reel" : "Exhaustive" );

        mInfos = oss.str();
        mDebut = getTimeMillis();
        mLastGrabbed = 0;
    }

    // Fermeture
    void VideoFile::close() {
        if( mCapture )
            cvReleaseCapture( &mCapture );
    }

    // Récupération de frame (héritée)
    void VideoFile::getFrame( Image &frame ) {
        if( mRealtime )
            selectCurrentFrame();
        else
            selectNextFrame();

        frame = cvRetrieveFrame( mCapture );
    }

    // Sélection de frame (mode exhaustif)
    void VideoFile::selectNextFrame() {
        if(! cvGrabFrame( mCapture ))
            throw Exception( EX_MESSAGE, "Fin du fichier atteinte" );

        mLastGrabbed++;
    }

    // Sélection de frame (mode temps réel)
    void VideoFile::selectCurrentFrame( ) {
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
