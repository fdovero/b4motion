/*
 * videosource.h
 *
 *
 *
 */

#ifndef B4MVIDEOSOURCE_H_
#define B4MVIDEOSOURCE_H_

#include <string>
#include "image.h"

namespace b4m
{

    class VideoSource
    {
    	public:
			// Destructeur
			virtual ~VideoSource() {

			}

			// Récupération d'infos
			virtual std::string getInfos() {
				return mInfos;
			}

			// Ouverture du flux
			virtual void open() = 0;

			// Fermeture du flux
			virtual void close() = 0;

			// Récupération d'une frame
			virtual void getFrame( Image &frame ) = 0;

        protected:

            // Informations sur le flux
            std::string mInfos;
    };
}


#endif /* B4MVIDEOSOURCE_H_ */
