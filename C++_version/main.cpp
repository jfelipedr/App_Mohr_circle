/*main del programa*/
#include <iostream>
#include <cmath>
#include "funciones.h"


int main()
{
    //llamar funciones
    double ex, ey, ez, eshear, theta, E, eyield, poisson, rad;
    ex = 10000;
    ey = 6000;
    ez = -2000;
    eshear = -4000;
    theta = 0;
    E = 45000;
    eyield = E*1.2;
    poisson = 0.3;
    rad = M_PI/180;
    //teta = arange(0,361,0.1); crear vector desde 0 a 360 incrementando de 0.1 cada elemento

	return 0;
}

//Deformación xx
double deformacion_XX(double E, double ex, double poisson, double ey, double ez)
{
    double DeformacionXX;
    DeformacionXX = (1/E) * ( ( ex - ( poisson *(ey + ez) ) ) );
    return DeformacionXX;
}

//Deformación yy
double deformacion_YY(double E, double ey, double poisson, double ex, double ez)
{
    double DeformacionYY;
    DeformacionYY = (1/E) * ( ( ey - ( poisson *(ex + ez) ) ) );
    return DeformacionYY;
}

//Deformación zz
double deformacion_ZZ(double E, double ez, double poisson, double ey, double ex)
{
    double DeformacionZZ;
    DeformacionZZ = (1/E) * ( ( ez - ( poisson *(ey + ex) ) ) );
    return DeformacionZZ;
}

//Deformación xy (agregar cuadro de texto)
double deformacion_XY(double eshear, double poisson, double E)
{
    double DeformacionXY;
    DeformacionXY = ( ( ( eshear *2*(1+poisson) )/E ) );
    return DeformacionXY;
}

//Deformación 1
double deformacion_1(double ex, double ey)
{
    double Deformacion1;
    Deformacion1 = ( (ex+ey)/2 ) + 0.5*sqrt( (ex-ey)^2 + ( (DeformacionXY)^2) );//solucionar defxY
    return Deformacion1;
}

//Deformacion 2
double deformacion_2(double ex, double ey)
{
    double Deformacion2;
    Deformacion2 = ( (ex+ey)/2 ) - 0.5*sqrt( (ex-ey)^2 + ( (DeformacionXY)^2) );
    return Deformacion2;
}

//Centro-Deformación
double cd(double ex, double ey)
{
    double cd;
    cd = (ex + ey)/2;
    return cd;
}

//Radio-Deformación
double radio_deformacion()
{
    rd = (0.5) * sqrt((ex - ey)**2 + ((DeformacionXY)**2))
    xd = cd + (rd * cos(teta*rad))
    yd = rd * sin(teta*rad)
}


//Circulo de deformacíon z

//Deformación z
double deformacion_3()
{
    Deformacion3 = DeformacionZZ
    cd2 = (Deformacion2 + Deformacion3)/2
    rd2 = (Deformacion2 - Deformacion3)/2
    xd2 = cd2 + (rd2 * cos(teta*rad))
    yd2 = rd2 * sin(teta*rad)
}

//Circulo 3 de deformación
cd3 = (Deformacion1 + Deformacion3)/2
rd3 = (Deformacion1 - Deformacion3)/2
xd3 = cd3 + (rd3 * cos(teta*rad))
yd3 = rd3 * sin(teta*rad)

//             Graficas de sen vs teta
EXX = ((ex + ey)/2 + (ex - ey) * cos(2*teta*rad + theta*rad)/2
        + eshear * sin(2*teta*rad + theta*rad))
EXY = (-(ex - ey) * sin(2*teta*rad + theta*rad)/2
        + eshear * cos(2*teta*rad + theta*rad))

//             Circulo de Mohr
c = (ex + ey)/2
r = sqrt(((ex - ey)/2)**2 + eshear**2)
x = c + (r * cos(teta*rad))
y = r * sin(teta*rad)
r2 = ((c-r) - ez)/2
c2= c-r-r2
x2 = c2 + (r2 * cos(teta*rad))
y2 = r2 * sin(teta*rad)
r3 = abs(((c+r)-ez)/2)
c3 = ((c+r)+ez)/2
x3 = c3 + (r3 * cos(teta*rad))
y3 = r3 * sin(teta*rad)
y1 = arange(-abs(eshear),abs(eshear),0.1)
x1 = ((ey - ex) / (2*eshear))*y1 +c

//             elipse de VonMisses
q = sqrt(2)*eyield * cos(teta*rad)
w = sqrt(2)/sqrt(3)*eyield * sin(teta*rad)
m = q*cos(45*rad) - w*sin(45*rad)
n = q*sin(45*rad) + w*cos(45*rad)

//             linea superior Tresca
xs1 = arange(-eyield,0,0.1)
ys1 = xs1 + eyield
xs2 = arange(0,eyield,0.1)
ys2 = 0*xs2 + eyield
ys3 = arange(0,eyield,0.1) //cambiar oreden de las variables
xs3 = 0*ys3 + eyield

//             linea inferior Tresca
yi1 = arange(-eyield,0,0.1)
xi1 = -eyield + 0*yi1 //cambiar oreden de las variables
xi2 = arange(-eyield,0,0.1)
yi2 = -eyield + 0*xi2
xi3 = arange(0,eyield,0.1)
yi3 = xi3 - eyield


// Calculo del centro del circulo de Mohr
Centro = (ex + ey)/2

// Calculo del radio del circulo de Mohr
Radio = sqrt((((ex - ey)/2)**2) + ((eshear)**2))

// Esfuerzo principal 1- Centro+Radio
sigma1 = (ex + ey)/2 + sqrt((((ex - ey)/2)**2) + ((eshear)**2))

// Esfuerzo principal w- Centro-Radio
sigma2 = (ex + ey)/2 - sqrt((((ex - ey)/2)**2) + ((eshear)**2))

// Angulo donde ocurre el esfuerzo a tensión
wer= (eshear)/(ex - Centro)
thetasigmamax = ( (degrees(atan(wer)) )/2)+ 90

// Angulo donde ocurre el cortante maximo
thetataomax = (thetasigmamax - 45)

//Factor de seguridad por Tresca
S1 = abs(sigma1)
S2 = abs(sigma2)
tresca = (eyield / (max(S1,S2)) )

//Factor de seguridad por Von Mises
//Esfuerzo equivalente de Von Mises
equivalendevonmises = sqrt( ex**2 +ey**2 -ex*ey +3*eshear**2 )
fsvonmises = eyield / equivalendevonmises
