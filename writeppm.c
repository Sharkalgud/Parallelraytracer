//
// Torbert, 3 February 2014
//
#include <stdio.h>
#include <math.h>
//
#define WIDTH 640
#define HEIGHT 480
double ex=0.50000;
double ey=0.50000;
double ez=-1.000000;
double pz=0.00000;
//light coordinates
double lx=0.0000;
double ly=1.00000;
double lz=-0.500000;
double arr[3][4];
//
int main(void)
{
   //initalize the sphere array
   arr[0][0]=0.5;
   arr[0][1]=0.5;
   arr[0][2]=0.166667;
   arr[0][3]=0.166667;
   arr[1][0]=0.833333;
   arr[1][1]=0.500000;
   arr[1][2]=0.500000;
   arr[1][3]=0.166667;
   arr[2][0]=0.333333;
   arr[2][1]=0.666667;
   arr[2][2]=0.666667;
   arr[2][3]=0.333333;
   int rgb[HEIGHT][WIDTH][3] ; // red-green-blue for each pixel
   //
   int y , x, j ;
   double Tmin=10000000;
   int black;//check if there is a sphere in ray's path
   //
   FILE* fout ;
   //
   for( y = 0 ; y < HEIGHT ; y++ )
   {
      for( x = 0 ; x < WIDTH ; x++)
      {
         black=-1;
         double px=1.0-(1.0*(WIDTH-x)/(WIDTH));
         double py=1.0*(HEIGHT-y)/(HEIGHT);
         //calculate unit vector components of r
         double magr= sqrt(((px-ex)*(px-ex))+((py-ey)*(py-ey))+((pz-ez)*(pz-ez)));
         double rx=(px-ex)/magr;
         double ry=(py-ey)/magr;
         double rz=(pz-ez)/magr;
         //for floor T= (0.333-ey)/ry
         //loop over spheres
         Tmin=1000000000;
         //
         for(j=0;j<3;j++)
         {
            
            //find b and c constant to calculate T for sphere1
            double b=2*((rx*(ex-arr[j][0]))+(ry*(ey-arr[j][1]))+(rz*(ez-arr[j][2])));
            double c=(ex-arr[j][0])*(ex-arr[j][0])+(ey-arr[j][1])*(ey-arr[j][1])+(ez-arr[j][2])*(ez-arr[j][2])-arr[j][3]*arr[j][3];
            //
            if(b*b-4*c>=0)// checking if it is hit or miss
            {
               double T1=(-1*b+sqrt(b*b-4*c))/2;
               double T2=(-1*b-sqrt(b*b-4*c))/2;
               double T;
               if(T1<T2)
                  T=T1;
               else
                  T=T2;
               if(T<Tmin)
               {
                  Tmin=T;
                  black=j;
               }
            }
         }
         double T= (0.333-ey)/ry;
         if(T<Tmin && T>=0)//check if you see floor in front of me
         {
            Tmin=T;
            black=3;
         }
         //
         if(black==0)
         {
            double xi=ex+Tmin*rx;
            double yi=ey+Tmin*ry;
            double zi=ez+Tmin*rz;
            //normal vector with sphere
            double nx=(xi-arr[0][0])/arr[0][3];
            double ny=(yi-arr[0][1])/arr[0][3];
            double nz=(zi-arr[0][2])/arr[0][3];
            //unit vectors with light
            double mag=sqrt(((xi-lx)*(xi-lx))+((yi-ly)*(yi-ly))+((zi-lz)*(zi-lz)));
            double sx=(xi-lx)/mag;
            double sy=(yi-ly)/mag;
            double sz=(zi-lz)/mag;
            double dot=nx*sx+ny*sy+nz*sz;
            if(dot<0)
            {
               dot=0;
            }
            rgb[y][x][0] = 0   ; // red
            rgb[y][x][1] = 0 ; // green
            rgb[y][x][2] = (int)(255*0.5-0.5*255*dot); // blue
         }
         else if(black==1)
         {
            double xi=ex+Tmin*rx;
            double yi=ey+Tmin*ry;
            double zi=ez+Tmin*rz;
            //normal vector with sphere
            double nx=(xi-arr[1][0])/arr[1][3];
            double ny=(yi-arr[1][1])/arr[1][3];
            double nz=(zi-arr[1][2])/arr[1][3];
            //unit vectors with light
            double mag=sqrt(((xi-lx)*(xi-lx))+((yi-ly)*(yi-ly))+((zi-lz)*(zi-lz)));
            double sx=(xi-lx)/mag;
            double sy=(yi-ly)/mag;
            double sz=(zi-lz)/mag;
            double dot=nx*sx+ny*sy+nz*sz;
            if(dot<0)
            {
               dot=0;
            }
            rgb[y][x][0] = 0   ; // red
            rgb[y][x][1] = (int)(255*0.5-0.5*255*dot); // green
            rgb[y][x][2] = 0   ; // blue
         }
         else if(black==2)
         {
            double xi=ex+Tmin*rx;
            double yi=ey+Tmin*ry;
            double zi=ez+Tmin*rz;
            //normal vector with sphere
            double nx=(xi-arr[2][0])/arr[2][3];
            double ny=(yi-arr[2][1])/arr[2][3];
            double nz=(zi-arr[2][2])/arr[2][3];
            //unit vectors with light
            double mag=sqrt(((xi-lx)*(xi-lx))+((yi-ly)*(yi-ly))+((zi-lz)*(zi-lz)));
            double sx=(xi-lx)/mag;
            double sy=(yi-ly)/mag;
            double sz=(zi-lz)/mag;
            double dot=nx*sx+ny*sy+nz*sz;
            if(dot<0)
            {
               dot=0;
            }
            rgb[y][x][0] = (int)(255*0.5-0.5*255*dot)   ; // red
            rgb[y][x][1] = 0 ; // green
            rgb[y][x][2] = 0   ; // blue
         }
         else if(black==3)
         {
            double xi=ex+Tmin*rx;
            double yi=ey+Tmin*ry;
            double zi=ez+Tmin*rz;
            //normal vector with sphere
            double nx=0;
            double ny=1;
            double nz=0;
            //unit vectors with light
            double mag=sqrt(((xi-lx)*(xi-lx))+((yi-ly)*(yi-ly))+((zi-lz)*(zi-lz)));
            double sx=(xi-lx)/mag;
            double sy=(yi-ly)/mag;
            double sz=(zi-lz)/mag;
            double dot=nx*sx+ny*sy+nz*sz;
            if(dot<0)
            {
               dot=0;
            }
            rgb[y][x][0]=(int)(255*0.5-0.5*255*dot);
            rgb[y][x][1]=(int)(255*0.5-0.5*255*dot);
            rgb[y][x][2]=0;
         }
         else
         {
            rgb[y][x][0] = 0   ; // red
            rgb[y][x][1] = 0 ; // green
            rgb[y][x][2] = 0   ; // blue
         }
      }
   }
   //actual shadows are done with another nested loop that does same stuff except with light source instead of eye
   //
   //
   //
   fout = fopen( "circles.ppm" , "w" ) ;
   //
   fprintf( fout , "P3\n" ) ;
   fprintf( fout , "%d %d\n" , WIDTH , HEIGHT ) ;
   fprintf( fout , "255\n" ) ;
   //
   for( y = 0 ; y < HEIGHT ; y++ )
   {
      for( x = 0 ; x < WIDTH ; x++)
      {
         fprintf( fout , "%d %d %d\n" ,
          rgb[y][x][0] , rgb[y][x][1] , rgb[y][x][2] ) ;
      }
   }
   close( fout ) ;
   //
   return 0 ;
}
//
// end of file
//
