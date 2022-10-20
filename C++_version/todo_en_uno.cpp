/*app todo en uno, de ejemplo*/
/*main del programa*/
#include <iostream>
#include <cmath>//para usar Pi


int main()
{
    //llamar funciones
    double ex, ey, ez, eshear, theta, E, yield, poisson, rad,
    DeformacionXX,DeformacionYY,DeformacionZZ,DeformacionXY,Deformacion1,Deformacion2,
    cd,rd,xd,yd,
    Deformacion3,cd2, rd2, xd2, yd2,
    cd3,rd3,xd3,yd3,
    EXX,EXY,
    c,r,x,y,r2,c2,x2,y2,r3,c3,x3,y3,y1,x1,
    sig1,sig2,
    q,w,m,n,
    xs1,ys1,xs2,ys2,ys3,xs3,
    yi1,xi1,xi2,yi2,xi3,yi3;




    ex = 10000;
    ey = 6000;
    ez = -2000;
    eshear = -4000;
    theta = 0;
    E = 45000;
    yield = E*1.2;
    poisson = 0.3;
    rad = M_PI/180;
    //teta = arange(0,361,0.1); crear vector desde 0 a 360 incrementando de 0.1 cada elemento

    DeformacionXX = (1/E) * ( ( ex - ( poisson *(ey + ez) ) ) );
    DeformacionYY = (1/E) * ( ( ey - ( poisson *(ex + ez) ) ) );
    DeformacionZZ = (1/E) * ( ( ez - ( poisson *(ey + ex) ) ) );
    DeformacionXY = ( ( ( eshear *2*(1+poisson) )/E ) );
    Deformacion1 = ( (ex+ey)/2 ) + 0.5*sqrt( pow((ex-ey),2) + ( pow(DeformacionXY,2) ) );//solucionar defxY
    Deformacion2 = ( (ex+ey)/2 ) - 0.5*sqrt( pow((ex-ey),2) + ( pow(DeformacionXY,2) ) );

    //Centro-Deformación
    cd = (ex + ey)/2;

    //Radio- Deformación
    rd = (0.5) * sqrt( pow((ex - ey),2) + ( pow(DeformacionXY,2) ) );
    xd = cd + (rd * cos(teta*rad));
    yd = rd * sin(teta*rad);

    //Circulo de deformacíon z
    //Deformación z
    Deformacion3 = DeformacionZZ;
    cd2 = (Deformacion2 + Deformacion3)/2;
    rd2 = (Deformacion2 - Deformacion3)/2;
    xd2 = cd2 + (rd2 * cos(teta*rad));
    yd2 = rd2 * sin(teta*rad);

    //Circulo 3 de deformación
    cd3 = (Deformacion1 + Deformacion3)/2;
    rd3 = (Deformacion1 - Deformacion3)/2;
    xd3 = cd3 + (rd3 * cos(teta*rad));
    yd3 = rd3 * sin(teta*rad);

    //Graficas de sen vs teta
    EXX = (ex + ey)/2 + (ex - ey)*cos(2*teta*rad + theta*rad)/2 + eshear*sin(2*teta*rad + theta*rad);
    EXY = -(ex - ey) * sin(2*teta*rad + theta*rad)/2 + eshear*cos(2*teta*rad + theta*rad);

    //Circulo de Mohr
    //(EXX - a).^2 + EXY^2 = c.^2;
    c = (ex + ey)/2;
    r = sqrt( pow( ((ex - ey)/2), 2) + pow(eshear,2) );
    x = c + (r * cos(teta*rad) );
    y = r * sin(teta*rad);
    r2 = ( (c-r) - ez)/2;
    c2= c-r-r2;
    x2 = c2 + (r2 * cos(teta*rad));
    y2 = r2 * sin(teta*rad);
    r3 = abs( ( (c+r)-ez )/2 );
    c3 = ( c + r + ez )/2;
    x3 = c3 + ( r3 * cos(teta*rad) );
    y3 = r3 * sin(teta*rad);
    y1 = -abs(eshear):0.01:abs(eshear);
    x1 = ( (ey - ex) / (2*eshear) )*y1 +c;

    //criterio de falla REVISAR
    sig1 = str2num(app.sigma1.Value):0.01:str2num(app.sigma1.Value);
    sig2 = str2num(app.sigma2.Value);

    //elipse de VonMisses
    q = sqrt(2)*yield * cos(teta*rad);
    w = sqrt(2)/sqrt(3)*yield * sin(teta*rad);
    m = q*cos(45*rad) - w*sin(45*rad);
    n = q*sin(45*rad) + w*cos(45*rad);

    //linea superior Tresca
    xs1 = -yield:0.03:0;
    ys1 = xs1 + yield;
    xs2 = 0:0.03:yield;
    ys2 = 0*xs2 + yield;
    ys3 = 0:0.03:yield; //cambiar oreden de las variables
    xs3 = 0*ys3 + yield;

    //linea inferior Tresca
    yi1 = -yield:0.03:0;
    xi1 = -yield + 0*yi1; //cambiar oreden de las variables
    xi2 = -yield:0.03:0;
    yi2 = -yield + 0*xi2;
    xi3 = 0:0.03:yield;
    yi3 = xi3 - yield;

/*
    //graficas criterios de falla
    plot(app.GraficaFS,xs1,ys1,xs2,ys2,xs3,ys3,xi1,yi1,xi2,yi2,xi3,yi3,sig1,sig2,'*m',m,n,'r');

    //graficas esfuerzo'' vs teta
    plot(app.GraficaStress,teta,EXX, teta,EXY);
    legend(app.GraficaStress,["σ x'x'","σ x'y'"],'Location','Best');

    //graficas de Mohr
    plot(app.GraficaMohr,x,y,x2,y2,'--',x3,y3,'--',ey,eshear,'*b',x1,y1,'--k');
    legend(app.GraficaMohr,["principal","segundo","tercero(global)","eyy,exy", "angulo principal"],'Location','Best');

    //grafica deformacion
    plot(app.GraficaDef,xd,yd,xd2,yd2,'--',xd3,yd3,'--');
    legend(app.GraficaDef,["principal","segundo","tercero(global)"],'Location','Best');

    //Factor de seguridad por Tresca
    S1 = abs(sig1);
    S2 = abs(sig2);
    tresca = (app.Yield.Value / (max(S1,S2)));
    app.Tresca.Value = num2str(tresca);

    //Factor de seguridad por Von Mises
    //Esfuerzo equivalente de Von Mises
    Eequivalendevonmises = sqrt(ex^2+ey^2-ex*ey+3*eshear^2);
    fsvonmises = (app.Yield.Value)/(Eequivalendevonmises);
    app.VonMises.Value = num2str(fsvonmises);
*/

	return 0;
}
