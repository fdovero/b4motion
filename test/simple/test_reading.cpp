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

#include "exception.h"
#include "image.h"
#include "videofile.h"
#include "camera.h"
#include "utils.h"
#include <iostream>
#include <iomanip>

using namespace b4m;

long long debut_mesure;
long long fin_mesure;

double calculFrameRate() {

    // On récupère l'heure actuelle
    fin_mesure = getTimeMillis();

    // Frame rate : 1 / temps écoulé (en secondes)
    double fps = 1000.0 / (fin_mesure - debut_mesure);

    // On met à jour le début de la mesure
    debut_mesure = fin_mesure;

    return fps;
}

int main( int argc, char* argv[])
{
    // On déclare notre pointeur sur SourceVideo
    VideoSource *src;

    if( argc > 1 ) {
        // Initialisation : fichier vidéo
        std::string path(argv[1]);
        src = new VideoFile( path, (argc > 2) );
    }
    else {
        // Initialisation : webcam
        src = new Camera( 0 );
    }

    // Initialisation du flux vidéo
    try {
        src->open();
    }
    catch( Exception &e ) {
        // Si une exception se produit, on l'affiche et on quitte.
        std::cout << e.what() << std::endl;
        delete src;
        return 10;
    }

    // Si tout va bien, on affiche les informations du flux vidéo.
    std::cout << src->getInfos() << std::endl;

    cvNamedWindow( "video", CV_WINDOW_AUTOSIZE );
    Image img;
    char key = 'a';

    // Début de la mesure du frame rate
    debut_mesure = getTimeMillis();

    while( key != 'q' ) {
        try {
            src->getFrame( img );
        }
        catch(Exception &e) {
            std::cout << "\n" << e.what() << std::endl;
            break;
        }
        cvShowImage( "video", img );
        key = cvWaitKey( 10 );

        // Affichage du frame rate
        std::cout << "\rFrame Rate : " << std::setw(5);
        std::cout << std::left << std::setprecision(4);
        std::cout << calculFrameRate() << " FPS" << std::flush;
    }

    std::cout << std::endl;
    cvDestroyWindow( "video" );
    delete src;
    return 0;
}
