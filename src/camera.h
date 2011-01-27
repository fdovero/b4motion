/*
 * camera.h
 *
 *
 *
 */

#ifndef B4MCAMERA_H_
#define B4MCAMERA_H_

#include <highgui.h>

namespace b4m
{
    class Camera: public VideoSource
    {
        public:
            // Constructeur, on lui passe l'indice de la caméra
            Camera( int index = -1 );

            // Destructeur
            virtual ~Camera();

            // Ouverture (héritée)
            virtual void open();

            // Fermeture (héritée)
            virtual void close();

            // Lecture (héritée)
            virtual void getFrame( Image &frame );

            // Ouverture surchargée ;)
            void open( int index );

        private:
            // La capture OpenCV
            CvCapture* mCapture;

            // L'indice de la caméra
            int mIndice;
    };
}

#endif /* B4MCAMERA_H_ */
