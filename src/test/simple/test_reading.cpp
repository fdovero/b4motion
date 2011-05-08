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

#include "../../b4m/exception.h"
#include "../../b4m/image.h"
#include "../../b4m/videofile.h"
#include "../../b4m/camera.h"
#include "../../b4m/utils.h"
#include <iostream>
#include <iomanip>

using namespace std;
using namespace b4m;

long long debut_mesure;
long long fin_mesure;

CvPoint top_left= cvPoint(360,280);
CvPoint bottom_right= cvPoint(360,280);

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
    CvVideoWriter *writer = 0;
    int isColor = 1;
    int fps     = 30;  // or 30
    int frameW  = 640; // 744 for firewire cameras
    int frameH  = 480; // 480 for firewire cameras
    writer=cvCreateVideoWriter("out.avi",CV_FOURCC('P','I','M','1'),
                                   fps,cvSize(frameW,frameH),isColor);


    if( argc > 1 ) {
        // Initialisation : fichier vidéo
        string path(argv[1]);
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
        cout << e.what() << endl;
        delete src;
        return 10;
    }

    // Si tout va bien, on affiche les informations du flux vidéo.
    cout << src->getInfos() << endl;

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
            cout << "\n" << e.what() << endl;
            break;
        }
        /*CvScalar scalaire;
        scalaire.val[0] = 120;
        scalaire.val[1] = scalaire.val[2] = 0;
        img.colorFilter(scalaire);*/

        img.colorPaint2(top_left,bottom_right);
        if (bottom_right.x < 720) {
        	bottom_right.x++;
        }
        if (bottom_right.y < 576) {
        	bottom_right.y++;
        }
        if (top_left.x > 0) {
        	top_left.x--;
        }
        if (top_left.y > 0) {
        	top_left.y--;
        }

        //img.colorBlacknWhite();

        cvShowImage( "video", img );
        cvWriteFrame(writer,img);
        key = cvWaitKey( 10 );

        // Affichage du frame rate
        cout << "\rFrame Rate : " << setw(5);
        cout << left << setprecision(4);
        cout << calculFrameRate() << " FPS" << flush;
    }

    cout << endl;
    cvDestroyWindow( "video" );
    delete src;
    return 0;
}
