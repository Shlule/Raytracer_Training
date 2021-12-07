#include"RtWeekend.h"
#include"Material.h"
#include"Color.h"
#include"HittableList.h"
#include"Sphere.h"
#include"Camera.h"

#include<iostream>
#include<fstream>

using std::cout;
using std::endl;
// cmake: configure a chaqu fois qu'un rjoute une classe au projet

double  HitSphere (const Point3& center , double radius,const Ray& r){
    Vec3 oc = r.origin() - center;
    
    // ancienne methode
    // //Initialisation de composante a b et c D'un polynome ax²+bx+c
    // double a = dot(r.direction(), r.direction());
    // double b = 2.0 * dot(oc, r.direction());
    // double c =dot(oc,oc) - radius*radius;
    // Calcul du discriminant  
    //double discriminant = b*b - 4*a*c;

    //Maintenat on calcul les memes composantes a,b, et c mais au carré cette fois ci;
    double a =r.direction().lengthSquared();
    double halfB = dot(oc, r.direction());
    double c = oc.lengthSquared() - radius*radius;
    double discriminant = halfB*halfB - a*c;

    if(discriminant < 0){
        return -1.0;
    }else{
         // ceci est la racine positive d'un polynome du second degres 
         // return(-b -sqrt(discrminant))/ (2.0*a);
        // ceci est la racine positive d'un polynome du second degres au carré
        return (-halfB - sqrt(discriminant))/a ;
    }
    
}
// permet de retourner quelle couleur doit s'afficher le pixel
Color RayColor (const Ray& r, const Hittable& world, int depth){
    HitRecord rec;

    // if we've exccedded the ray bounce limit , no more light is gathered.
    if(depth<=0){
        return Color(0,0,0);
    }
    if(world.Hit(r,0.001,infinity,rec)){
        Ray scattered;
        Color attenuation;
        if(rec.mat_ptr->Scatter(r,rec,attenuation,scattered)){
            return attenuation*RayColor(scattered,world,depth-1);
        }
    }
    Vec3 unitDirection = UnitVector(r.direction());
    double t =0.5*(unitDirection.y()+1.0);
    return(1.0-t)*Color(1.0,1.0,1.0)+t*Color(0.5,0.7,1.0);
    
}

int main(){
    // Screen resolution
    const float aspectRatio = 16.0/9.0;
    const int imageWidth =300;
    const int imageHeight = static_cast<int>(imageWidth/aspectRatio);
    const int samplePerPixel = 100;
    const int maxDepth = 50;

    //world

    HittableList world;
    auto materialGround =  make_shared<Lambertian>(Color(0.8,0.8,0.0));
    auto materialCenter = make_shared<Lambertian>(Color(0.7,0.3,0.3));
    auto materialLeft =  make_shared<Metal>(Color(0.8,0.8,0.8));
    auto materialRight = make_shared<Metal>(Color(0.8,0.6,0.2));
    world.add(make_shared<Sphere>(Point3(0,-100.5,-1),100, materialGround));
    world.add(make_shared<Sphere>(Point3(0,0,-1),0.5, materialCenter));
    world.add(make_shared<Sphere>(Point3(-1,0,-1),0.5, materialLeft));
    world.add(make_shared<Sphere>(Point3(1,0,-1),0.5, materialRight));


    

    // Camera Initialisation

    Camera cam;
    

    std::ofstream output;
    output.open("output.ppm");
   


    output<<"P3\n"<<imageWidth<<" "<<imageHeight<< "\n255\n";


    // on fait un balayage vertical des points
    for(int j=imageHeight-1 ;j >= 0 ;j--){
        std::cerr<< "\r Scanlines remaining: "<<j<<' '<<std::flush;
        for (int i =0; i<imageWidth;i++){
            Color colorPixel(0,0,0);
            for(int s =0;s<samplePerPixel;s++){
                double u = (i + RandomDouble()) / (imageWidth-1);
                double v = (j+RandomDouble())/(imageHeight-1);
                Ray r = cam.GetRay(u,v);
                colorPixel+= RayColor (r, world, maxDepth);
            }

            WriteColor(output, colorPixel,samplePerPixel);
        }

    }
    std::cerr<<"\n Done.\n";
    output.close();
    return 0;
}

