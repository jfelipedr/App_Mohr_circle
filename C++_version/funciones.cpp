/*Implementation file:
copiar aqui la definicion de las funciones*/
#include <cmath>
#include <algorithm>//para usar std::max()

double ex= 10000,
ey = 6000,
ez = -2000,
eshear = -4000,
theta = 0,
E = 45000,
eyield = E*1.2,
poisson = 0.3,
rad = M_PI/180;
teta = arange(0,361,0.1); //crear vector desde 0 a 360 incrementando de 0.1 cada elemento
//crear vector desde 0 a 360 incrementando de 0.1 cada elemento
//crear vector desde 0 a 360 incrementando de 0.1 cada elemento
//crear vector desde 0 a 360 incrementando de 0.1 cada elemento
//crear vector desde 0 a 360 incrementando de 0.1 cada elemento
//crear vector desde 0 a 360 incrementando de 0.1 cada elemento



//Deformacion xx
double deformacion_xx()
{
    double strain_xx;
    strain_xx = (1/E) * ( ( ex - ( poisson*(ey + ez) ) ) );
    return strain_xx;
}

//Deformacion yy
double deformacion_yy()
{
    double strain_yy;
    strain_yy = (1/E) * ( ( ey - ( poisson*(ex + ez) ) ) );
    return strain_yy;
}

//Deformacion zz
double deformacion_zz ()
{
    double strain_zz;
    strain_zz = (1/E) * ( ( ez - ( poisson*(ey + ex) ) ) );
    return strain_zz;
}

//Deformacion xy
double deformacion_xy()
{
    double strain_xy;
    strain_xy = ( ( (eshear*2*(1+poisson))/E ) );
    return strain_xy;
}

//Deformacion 1
double deformacion_1()
{
    double strain_1;
    strain_1 = ( (ex+ey)/2 ) + (0.5)*sqrt( pow((ex-ey),2) + pow(deformacion_xy(),2) );
    return strain_1;
}

//Deformacion 2
double deformacion_2()
{
    double strain_2;
    strain_2 = ( (ex+ey)/2 ) - (0.5)*sqrt( pow((ex-ey),2) + pow(deformacion_xy(),2) );
    return strain_2;
}

//       Centro circulo de Mohr
double centro_Mohr ()
{
    double  c_M;
    c_M = (ex + ey)/2;
    return c_M;
}

//       Radio-Deformacion
double radio_deformacion ()
{
    double rd, xd, yd;
    rd = (0.5) * sqrt( pow((ex - ey),2) + pow(deformacion_xy(),2) );
    xd = centro_Mohr() + ( rd * cos(teta*rad) );
    yd = rd * sin(teta*rad);
    return rd, xd, yd;
}

//       Circulo de deformacion z

//       Deformacion z
double deformacion_z ()
{
    double cd2, rd2, xd2, yd2;
    cd2 = ( deformacion_2() + deformacion_zz() )/2;
    rd2 = ( deformacion_2() - deformacion_zz() )/2;
    xd2 = cd2 + (rd2 * cos(teta*rad));
    yd2 = rd2 * sin(teta*rad);
    return cd2, rd2, xd2, yd2;
}

//       Circulo 3 de deformacion
double circulo_3_deformacion ()
{
    double cd3, rd3, xd3, yd3;
    cd3 = ( deformacion_1() + deformacion_zz() )/2;
    rd3 = ( deformacion_1() - deformacion_zz() )/2;
    xd3 = cd3 + ( rd3 * cos(teta*rad) );
    yd3 = rd3 * sin(teta*rad);
    return cd3, rd3, xd3, yd3;
}

//       Graficas de sen vs teta
double sen_vs_teta ()
{
    double EXX, EXY;
    EXX = ( (ex + ey)/2 + (ex - ey) * cos(2*teta*rad + theta*rad)/2 + eshear * sin(2*teta*rad + theta*rad) );
    EXY = ( -(ex - ey) * sin(2*teta*rad + theta*rad)/2 + eshear * cos(2*teta*rad + theta*rad) );
    return EXX, EXY;
}

//       Circulo de Mohr
double circulo_Mohr ()
{
    double c, r, x, y, r2, c2, x2, y2, r3, c3, x3, y3, y1, x1;
    c = (ex + ey)/2;
    r = sqrt( pow( ((ex-ey)/2), 2) + pow(eshear,2) );
    x = c + (r * cos(teta*rad));
    y = r * sin(teta*rad);
    r2 = ( c - r - ez)/2;
    c2 = c - r - r2;
    x2 = c2 + ( r2 * cos(teta*rad) );
    y2 = r2 * sin(teta*rad);
    r3 = std::abs( ( (c+r)-ez )/2 );
    c3 = ( (c+r)+ez )/2;
    x3 = c3 + (r3 * cos(teta*rad));
    y3 = r3 * sin(teta*rad);
    y1 = arange(-std::abs(eshear), std::abs(eshear), 0.1);
    x1 = ( (ey - ex) / (2*eshear) )*y1 +c;
    return c, r, x, y, r2, c2, x2, y2, r3, c3, x3, y3, y1, x1;
}

//       elipse de VonMisses
double elipse_VonMisses ()
{
    double q, w, m, n;
    q = sqrt(2)*eyield * cos(teta*rad);
    w = sqrt(2)/sqrt(3)*eyield * sin(teta*rad);
    m = q*cos(45*rad) - w*sin(45*rad);
    n = q*sin(45*rad) + w*cos(45*rad);
    return m, n;
}

//       Grafica Tresca
double lineas_Tresca ()
{
    double xs1, ys1, xs2, ys2, xs3, ys3, yi1, xi1, yi2, xi2, yi3, xi3;

    //       linea superior Tresca
    xs1 = arange(-eyield, 0, 0.1);
    ys1 = xs1 + eyield;
    xs2 = arange(0, eyield, 0.1);
    ys2 = 0*xs2 + eyield;
    ys3 = arange(0, eyield, 0.1); //cambiar oreden de las variables
    xs3 = 0*ys3 + eyield;

    //       linea inferior Tresca
    yi1 = arange(-eyield, 0, 0.1);
    xi1 = -eyield + 0*yi1; //cambiar orden de las variables
    xi2 = arange(-eyield, 0, 0.1);
    yi2 = -eyield + 0*xi2;
    xi3 = arange(0, eyield, 0.1);
    yi3 = xi3 - eyield;

    return xs1, ys1, xs2, ys2, ys3, xs3, yi1, xi1, xi2, yi2, xi3, yi3;
}

//       Esfuerzo principal 1- Centro+Radio
double sigma_1 ()
{
    double sigma1;
    sigma1 = (ex + ey)/2 + sqrt( ( pow( ((ex - ey)/2), 2) ) + pow(eshear,2) );
    return sigma1;
}

//       Esfuerzo principal w- Centro-Radio
double sigma_2 ()
{
    double sigma2;
    sigma2 = (ex + ey)/2 - sqrt( ( pow( ((ex - ey)/2) ,2) ) + pow(eshear,2) );
    return sigma2;
}

//       Angulo donde ocurre el esfuerzo a tensión
double angulo_tension_stress ()
{
    double wer, theta_sigma_max;
    wer = (eshear) / ( ex - centro_Mohr() );
    theta_sigma_max = degrees(atan(wer)/2) + 90;//reemplazar funcion degrees para pasar de rad a deg
    //reemplazar funcion degrees para pasar de rad a deg
    //reemplazar funcion degrees para pasar de rad a deg
    //reemplazar funcion degrees para pasar de rad a deg
    //reemplazar funcion degrees para pasar de rad a deg
    //reemplazar funcion degrees para pasar de rad a deg
    return theta_sigma_max;
}

//       Angulo donde ocurre el cortante maximo
double angulo_shear_stress ()
{
    double theta_tao_max;
    theta_tao_max = ( angulo_tension_stress() - 45);
    return theta_tao_max;
}

//       Factor de seguridad por Tresca
double factor_seguridad_Tresca ()
{
    double S1, S2, tresca;
    S1 = std::abs(sigma_1());
    S2 = std::abs(sigma_2());
    tresca = (eyield / (std::max(S1,S2)) );
    return tresca;
}

//       Factor de seguridad por Von Mises
double factor_seguridad_VonMisses ()
{
    double equivalente_VonMises, fs_VonMisses;
    equivalente_VonMises = sqrt( pow(ex,2) + pow(ey,2) - ex*ey + 3*pow(eshear,2) );
    fs_VonMisses = eyield / equivalente_VonMises;
    return  fs_VonMisses;
}
