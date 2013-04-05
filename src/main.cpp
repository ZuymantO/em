

//============================================================================
// Name        : OpenCvTest.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#import "opencv2/opencv.hpp"
#include "opencv/cvaux.hpp"
#include "FormList.hpp"
#include "Form.hpp"
#include <deque>

using namespace std;
using namespace cv;

void callbackCapture(IplImage* img){
  cout << "Image arrive " << endl;

}

void invert (IplImage* img)
{

  uchar *p, *line;
  assert (img->depth == IPL_DEPTH_8U && img->nChannels == 1); //en gris 8 bit
  // parcours des lignes de l'image
  // on positionne le pointeur "line" sur le début de l'image
  // et on le fait avancer de la taille d'une ligne à chaque itération
  // jusqu'à tomber sur l'octet suivant le dernier pixel de l'image
  for (line = (uchar*) img->imageData;
       line < (uchar*) img->imageData + img->imageSize;
       line += img->widthStep)
    {
      // parcours de la ligne "line"
      // on positionne le pointeur p sur le début de la ligne
      // et on le fait avancer de la taille d'un pixel à chaque itération
      // jusqu'à tomber sur le dernier pixel de la ligne
      for (p = line; p < line + img->width; ++p)
	*p = 255 - *p;

    }
}

string concat(const string& str, double val){
  std::stringstream sstm;
  sstm << str << val;
  return sstm.str();
}

void getProp(CvCapture* cap, Mat &img, int w, int h){
  Scalar col = cv::Scalar(255, 0, 250, 200);
  double fs = .8;
  int ft = 0, x1 = 20, x2 = 260 ;

  double width = cvGetCaptureProperty (cap, CV_CAP_PROP_FRAME_WIDTH);
  double height = cvGetCaptureProperty(cap, CV_CAP_PROP_FRAME_HEIGHT);
  double frct = cvGetCaptureProperty (cap, CV_CAP_PROP_FRAME_COUNT);
  double fps = cvGetCaptureProperty(cap, CV_CAP_PROP_FPS);
  double form = cvGetCaptureProperty (cap, CV_CAP_PROP_FORMAT);
  double mod = cvGetCaptureProperty(cap,  CV_CAP_PROP_MODE);
  double bri = cvGetCaptureProperty (cap, CV_CAP_PROP_BRIGHTNESS);
  double cont = cvGetCaptureProperty(cap, CV_CAP_PROP_CONTRAST);
  double sat = cvGetCaptureProperty (cap, CV_CAP_PROP_SATURATION);
  double hue = cvGetCaptureProperty(cap,  CV_CAP_PROP_HUE);
  putText(img, concat("Largeur   : ", width), cv::Point(x1,100), ft, fs, col) ;
  putText(img, concat("Hauteur : ", height), cv::Point(x1,120), ft, fs, col) ;
  putText(img, concat("FPS     : ", fps), cv::Point(x1,140), ft, fs, col) ;
  putText(img, concat("#Frame  : ", frct), cv::Point(x1,160), ft, fs, col) ;
  putText(img, concat("Format  : ", form), cv::Point(x1,180), ft, fs, col) ;
  putText(img, concat("Mode  : ", mod), cv::Point(x1,200), ft, fs, col) ;
  putText(img, concat("Brillance     : ", bri), cv::Point(x1,220), ft, fs, col) ;
  putText(img, concat("Contraste : ", cont), cv::Point(x1,240), ft, fs, col) ;
  putText(img, concat("Saturation : ", sat), cv::Point(x1,260), ft, fs, col) ;
  putText(img, concat("Hue : ", hue), cv::Point(x1,280), ft, fs, col) ;

  double gain = cvGetCaptureProperty (cap, CV_CAP_PROP_GAIN);
  double expo = cvGetCaptureProperty(cap, CV_CAP_PROP_EXPOSURE);
  double rgb = cvGetCaptureProperty (cap, CV_CAP_PROP_CONVERT_RGB);
  double whitb_b = cvGetCaptureProperty(cap, CV_CAP_PROP_WHITE_BALANCE_BLUE_U);
  double rect = cvGetCaptureProperty (cap, CV_CAP_PROP_RECTIFICATION);
  double monoc = cvGetCaptureProperty (cap, CV_CAP_PROP_MONOCROME);
  double gamma = cvGetCaptureProperty(cap, CV_CAP_PROP_GAMMA);
  double sharp = cvGetCaptureProperty(cap, CV_CAP_PROP_SHARPNESS);
  double autoexp = cvGetCaptureProperty (cap, CV_CAP_PROP_AUTO_EXPOSURE);
  double temp = cvGetCaptureProperty(cap, CV_CAP_PROP_TEMPERATURE);
  putText(img, concat("Gain   : ", gain), cv::Point(x2,100), ft, fs, col) ;
  putText(img, concat("Expo  : ", expo), cv::Point(x2,120), ft, fs, col) ;
  putText(img, concat("RGB     : ", rgb), cv::Point(x2,140), ft, fs, col) ;
  putText(img, concat("BalanceB : ", whitb_b), cv::Point(x2,160), ft, fs, col) ;
  putText(img, concat("Rectif  : ", rect), cv::Point(x2,180), ft, fs, col) ;
  putText(img, concat("Monocrome  : ", monoc), cv::Point(x2,200), ft, fs, col) ;
  putText(img, concat("Gamma     : ", gamma), cv::Point(x2,220), ft, fs, col) ;
  putText(img, concat("Sharpness : ", sharp), cv::Point(x2,240), ft, fs, col) ;
  putText(img, concat("Auto Exp : ", autoexp), cv::Point(x2,260), ft, fs, col) ;
  putText(img, concat("Temperature : ", temp), cv::Point(x2,280), ft, fs, col) ;

  //double trigger = cvGetCaptureProperty (cap, CV_CAP_PROP_TRIGGER);
  //double trigdelay = cvGetCaptureProperty (cap, CV_CAP_PROP_TRIGGER_DELAY);
  //double whitb_r = cvGetCaptureProperty(cap, CV_CAP_PROP_WHITE_BALANCE_RED_V);
  //double zoom = cvGetCaptureProperty (cap, CV_CAP_PROP_ZOOM);
  //double foc = cvGetCaptureProperty(cap, CV_CAP_PROP_FOCUS);
  //double guid = cvGetCaptureProperty(cap, CV_CAP_PROP_GUID);
  //double isospeed= cvGetCaptureProperty (cap, CV_CAP_PROP_ISO_SPEED);
  //double bckli = cvGetCaptureProperty(cap, CV_CAP_PROP_BACKLIGHT);
  //double pan = cvGetCaptureProperty (cap, CV_CAP_PROP_PAN);
  //double roll = cvGetCaptureProperty(cap, CV_CAP_PROP_ROLL);
  //double iris = cvGetCaptureProperty (cap, CV_CAP_PROP_IRIS);
  //double sett = cvGetCaptureProperty(cap, CV_CAP_PROP_SETTINGS);
  //putText(img, concat("Width   : ", width), cv::Point(10,20), ft, fs, col) ;
  //putText(img, concat("Height  : ", height), cv::Point(10,40), ft, fs, col) ;
  //putText(img, concat("FPS     : ", fps), cv::Point(10,60), ft, fs, col) ;
  //putText(img, concat("Fram ct : ", frct), cv::Point(10,80), ft, fs, col) ;
  //putText(img, concat("Width   : ", width), cv::Point(10,20), ft, fs, col) ;
  //putText(img, concat("Height  : ", height), cv::Point(10,40), ft, fs, col) ;
  //putText(img, concat("FPS     : ", fps), cv::Point(10,60), ft, fs, col) ;
  //putText(img, concat("Fram ct : ", frct), cv::Point(10,80), ft, fs, col) ;
  //putText(img, concat("Fram ct : ", frct), cv::Point(10,80), ft, fs, col) ;


}

void drawForms(FormList &flt, Mat &img, Scalar &colorDelim, int sizeStrokeDelim){
	deque<Form>::iterator it = flt.forms.begin();
	  while (it != flt.forms.end())
	    {
	      Form* f = it._M_cur;
	      if(f != NULL)
	      {
	    	  rectangle(img, f->rect.tl(), f->rect.br(), colorDelim, sizeStrokeDelim);
	    	  putText(img, f->name, cv::Point(f->rect.x+5, f->rect.y-2), 1.8, sizeStrokeDelim, colorDelim) ;
	      }
	      it++;
	    }


}
Form *foundBestRect(Rect &r, FormList &fl, int ratio){
	Form f;
	  while (!fl.forms.empty())
	    {
	      f = fl.forms.front();
	      if((f.rect.x+ratio <= r.x || f.rect.y+ratio <= r.y) && f.rect.x-ratio >= r.y || f.rect.y-ratio >= r.y ){
	    	  return &f;
	      }
	    }
	  return  NULL;
	}


FormList* markForm(vector<Rect> &found_filtered, FormList &fl, FormList* rfl){
  // Diminuer les accès disque.

	int ratio = 100;
	bool b = rfl->forms.empty();
	for (unsigned int i = 0; i < found_filtered.size(); i++)
    {
      Rect r = found_filtered[i];
      //Rect r1;
      r.x += cvRound(r.width * 0.15);
      r.width = cvRound(r.width * 0.75);
      r.y += cvRound(r.height * 0.07);
      r.height = cvRound(r.height * 0.75);

      Form f;
      Form *tmp;
      if(b){
    	  f.id = fl.forms.size() +i+1;
    	  f.delay = 100;
    	  f.stillAlive = true;
    	  f.name = concat("Man ", fl.forms.size() +i+1);
    	  f.rect = r;
    	  rfl->forms.push_back(f);
      }else
      {
    	  tmp = (foundBestRect(r, *rfl, ratio));
    	  if(tmp == NULL){
    		  f.id = tmp->id;
    		  f.delay = 100;
    		  f.stillAlive = true;
        	  f.name = tmp->name ; // concat("Man ", fl.forms.size() +i+1);
        	  f.rect = r;
    	  }else{
    		  f.id = tmp->id;
    		  f.name = tmp->name;
    		  f.delay = 100;
    		  f.rect = r;
    		  f.stillAlive = true;
    	  }
      }



//      rectangle(img, r.tl(), r.br(), colorDelim, sizeStrokeDelim);
//      putText(img, concat("Man ", i), cv::Point(r.x+5, r.y-2), 1.8, sizeStrokeDelim, colorDelim) ;
    }
}

void foundForm(vector<Rect> &found, vector<Rect> &found_filtered){
  unsigned int i, j;
  for (i = 0; i < found.size(); i++)
    {
      Rect r = found[i];
      for (j = 0; j < found.size(); j++)
	if (j != i && (r & found[j]) == r) break;
      if (j == found.size())
	found_filtered.push_back(r);
    }
}


int main (int argc, const char * argv[])
{

  string f = "limitless.avi";
  VideoCapture cap(f); // remplacer 0 par f si positionné.
  cap.set(CV_CAP_PROP_FRAME_WIDTH, (320));
  cap.set(CV_CAP_PROP_FRAME_HEIGHT, (240));
  cap.set(CV_CAP_PROP_POS_FRAMES , 5500); // deplacer le curseur d'une video
  if (!cap.isOpened())
    return -1;

  Scalar colorDelim = Scalar(0,255,0);
  int sizeStrokeDelim = 1;


  // TODO revoir l'algo de reconnaissance
  /*
   * Revoir la détection de silhouette humain
   *
   * Implémenter la reconnaissance faciale
   *
   * Fusionner la reconnaissance faciale et de la silouhaite.
   * Augmenter le cadre de la reconnaissance faciale (un focus de très près)
   * Sinon considérer la reconnaissance de forme
   *
   * /

   /*
   *
   *  Autre méthode à implémenter Où on gèrera tout nous même en ajoutant des durées de vie ?
   *  HOG est une très bonne technique mais ici on ne maîtrise pas trop ce qui est fait
   *  1 prendre un frame
   *  2 detecter son background et foreground
   *  3 extraire le background
   *  4 soustraire pour n'avoir rien que le devant.
   *  5 entralacer le bground au fground pour obtenir le contour des élèments movible
   *  6 Chercher une technique pour tracker les objets détecter pour les compter
   *  7 Reussir à faire de mê  Et c'est dans la poche reste plus qu'à optimiser et ajouter des fonctions.
   */

  Mat img;
  namedWindow("[Eyes Motion] Experimental Detection", CV_WINDOW_AUTOSIZE);
  HOGDescriptor hog;
  hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
  //vector<Rect> found, found_filtered;
  vector<Rect> tempo;
  FormList formsL;
  FormList rfL;
  while (true)
    {
      vector<Rect> found, found_filtered;
      cap >> img;
      if (img.empty())
	continue;
      // Recherche des formes mouvantes
      hog.detectMultiScale(img, found, 0, Size(8,8), Size(32,32), 1.05, 2);

      Rect r(10, 30, 200,200);
      Rect r2(5,60,120,120);
      Size s = r.size() - r2.size();
      rectangle(img, r.tl(), r.br(), Scalar(0,255,255), sizeStrokeDelim);
      r.height = s.height;
      r.width = s.width;
      rectangle(img, r.tl(), r.br(), Scalar(0,0,255), sizeStrokeDelim);
      rectangle(img, r2.tl(), r2.br(), Scalar(255,0,0), sizeStrokeDelim);
     // rectangle(img, r1.tl(), r1.br(), Scalar(255,255,255), sizeStrokeDelim);
      // A optimiser
      // Se tenir à distance pour la détection.
      // La détection faciale completera la détection de pres
      foundForm(found, found_filtered);
      markForm(found_filtered, formsL, &rfL);
      drawForms(rfL, img, colorDelim, sizeStrokeDelim);
      imshow("[Eyes Motion] Experimental Detection", img);
      rfL.forms.clear();
      if (waitKey(10) >= 0)
	break;
    }
  return 0;
}
