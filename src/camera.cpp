/*
 * camera.cpp
 *
 *  Created on: 26 janv. 2011
 *      Author: Fabien Dovero
 */

#include "camera.h"
#include <sstream>
#include "exception.h"

namespace b4m
{
    using namespace std;

    // Constructeur, on initialise l'indice de la caméra, et la capture
    Camera::Camera( int index ): mIndice( index ), mCapture(NULL) {

    }

    // Destructeur, on se contente de fermer le flux vidéo
    Camera::~Camera() {
        close();
    }

    // Ouverture, on _délègue_ le travail à la méthode surchargée
    void Camera::open() {
        open( mIndice );
    }

    // Fermeture, si la capture OpenCV n'est pas déjà désallouée,
    // c'est le moment de le faire.
    void Camera::close() {
        if( mCapture )
            cvReleaseCapture( &mCapture );

        mCapture = NULL;
    }

    void Camera::open( int index ) {
        // Création de la capture
        mCapture = cvCreateCameraCapture( index );

        if( !mCapture )
            throw Exception( EX_ERREUR, "Impossible d'ouvrir la camera" );

        mIndice = index;

        // Remplissage des infos (indice de la caméra et résolution)
        ostringstream oss;
        oss << "Camera " << mIndice;
        oss	<< " (" << cvGetCaptureProperty( mCapture, CV_CAP_PROP_FRAME_WIDTH );
        oss	<< "x"  << cvGetCaptureProperty( mCapture, CV_CAP_PROP_FRAME_HEIGHT ) << ")";
        mInfos = oss.str();
    }

    void Camera::getFrame( Image &frame  ) {
        frame = cvQueryFrame( mCapture );

        if( !frame.ipl() )
            throw Exception( EX_ERREUR, "Echec lors de la lecture de frame" );
    }
}