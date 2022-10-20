import numpy as np

ex = 10000
ey = 6000
ez = -2000
eshear = -4000
theta = 0
E = 45000
eyield = E*1.2
poisson = 0.3
teta = np.arange(0, 361, 0.1)
rad = np.pi/180

#       Deformación xx
def deformacion_xx ():
    strain_xx = (1/E) * ( ( ex - ( poisson*(ey + ez) ) ) )
    return strain_xx


#       Deformación yy
def deformacion_yy ():
    strain_yy = (1/E) * ( ( ey - ( poisson*(ex + ez) ) ) )
    return strain_yy


#       Deformación zz
def deformacion_zz ():
    strain_zz = (1/E) * ( ( ez - ( poisson*(ey + ex) ) ) )
    return strain_zz


#       Deformación xy (agregar cuadro de texto)
def deformacion_xy ():
    strain_xy = ( ( (eshear*2*(1+poisson))/E ) )
    return strain_xy


#       Deformación 1
def deformacion_1 ():
    strain_1 = ( (ex+ey)/2 ) + (0.5)*np.sqrt( (ex-ey)**2 + (deformacion_xy()**2) )
    return strain_1


#       Deformacion 2
def deformacion_2 ():
    strain_2 = ( (ex+ey)/2 ) - (0.5)*np.sqrt( (ex-ey)**2 + (deformacion_xy()**2) )
    return strain_2


#       Centro circulo de Mohr
def centro_Mohr ():
    c_M = (ex + ey)/2
    return c_M

#       Radio-Deformación
def radio_deformacion ():
    rd = (0.5) * np.sqrt( (ex - ey)**2 + (deformacion_xy()**2) )
    xd = centro_Mohr() + ( rd * np.cos(teta*rad) )
    yd = rd * np.sin(teta*rad)
    return rd, xd, yd


#       Circulo de deformacíon z

#       Deformación z
def deformacion_z ():
    cd2 = ( deformacion_2() + deformacion_zz() )/2
    rd2 = ( deformacion_2() - deformacion_zz() )/2
    xd2 = cd2 + (rd2 * np.cos(teta*rad))
    yd2 = rd2 * np.sin(teta*rad)
    return cd2, rd2, xd2, yd2


#       Circulo 3 de deformación
def circulo_3_deformacion ():
    cd3 = ( deformacion_1() + deformacion_zz() )/2
    rd3 = ( deformacion_1() - deformacion_zz() )/2
    xd3 = cd3 + ( rd3 * np.cos(teta*rad) )
    yd3 = rd3 * np.sin(teta*rad)
    return cd3, rd3, xd3, yd3


#       Graficas de sen vs teta
def sen_vs_teta ():
    EXX = ( (ex + ey)/2 + (ex - ey) * np.cos(2*teta*rad + theta*rad)/2 + eshear * np.sin(2*teta*rad + theta*rad) )
    EXY = ( -(ex - ey) * np.sin(2*teta*rad + theta*rad)/2 + eshear * np.cos(2*teta*rad + theta*rad) )
    return EXX, EXY


#       Circulo de Mohr
def circulo_Mohr ():
    c = (ex + ey)/2
    r = np.sqrt( ((ex - ey)/2)**2 + eshear**2 )
    x = c + (r * np.cos(teta*rad))
    y = r * np.sin(teta*rad)
    r2 = ( c - r - ez)/2
    c2= c - r - r2
    x2 = c2 + ( r2 * np.cos(teta*rad) )
    y2 = r2 * np.sin(teta*rad)
    r3 = abs( ( (c+r)-ez )/2 )
    c3 = ( (c+r)+ez )/2
    x3 = c3 + (r3 * np.cos(teta*rad))
    y3 = r3 * np.sin(teta*rad)
    y1 = np.arange(-abs(eshear), abs(eshear), 0.1)
    x1 = ( (ey - ex) / (2*eshear) )*y1 +c
    return c, r, x, y, r2, c2, x2, y2, r3, c3, x3, y3, y1, x1


#       elipse de VonMisses
def elipse_VonMisses ():
    q = np.sqrt(2) * eyield * np.cos(teta*rad)
    w = np.sqrt(2)/np.sqrt(3) * eyield * np.sin(teta*rad)
    m = q*np.cos(45*rad) - w*np.sin(45*rad)
    n = q*np.sin(45*rad) + w*np.cos(45*rad)
    return m, n

#       Grafica Tresca
def lineas_Tresca ():
    #       linea superior Tresca
    xs1 = np.arange(-eyield, 0, 0.1)
    ys1 = xs1 + eyield
    xs2 = np.arange(0, eyield, 0.1)
    ys2 = 0*xs2 + eyield
    ys3 = np.arange(0, eyield, 0.1) #cambiar oreden de las variables
    xs3 = 0*ys3 + eyield

    #       linea inferior Tresca
    yi1 = np.arange(-eyield, 0, 0.1)
    xi1 = -eyield + 0*yi1 #cambiar oreden de las variables
    xi2 = np.arange(-eyield, 0, 0.1)
    yi2 = -eyield + 0*xi2
    xi3 = np.arange(0, eyield, 0.1)
    yi3 = xi3 - eyield

    return xs1, ys1, xs2, ys2, ys3, xs3, yi1, xi1, xi2, yi2, xi3, yi3


#       Esfuerzo principal 1- Centro+Radio
def sigma_1 ():
    sigma1 = (ex + ey)/2 + np.sqrt( ( ((ex - ey)/2)**2 ) + (eshear**2) )
    return sigma1


#       Esfuerzo principal w- Centro-Radio
def sigma_2 ():
    sigma2 = (ex + ey)/2 - np.sqrt( ( ((ex - ey)/2)**2 ) + (eshear**2) )
    return sigma2


#       Angulo donde ocurre el esfuerzo a tensión
def angulo_tension_stress ():
    wer= (eshear) / ( ex - centro_Mohr() )
    theta_sigma_max = ( (np.degrees(np.arctan(wer)) )/2 ) + 90
    return theta_sigma_max


#       Angulo donde ocurre el cortante maximo
def angulo_shear_stress ():
    theta_tao_max = ( angulo_tension_stress() - 45)
    return theta_tao_max


#       Factor de seguridad por Tresca
def factor_seguridad_Tresca ():
    S1 = abs(sigma_1())
    S2 = abs(sigma_2())
    tresca = (eyield / (max(S1,S2)) )
    return tresca


#       Factor de seguridad por Von Mises
def factor_seguridad_VonMisses ():
    equivalente_VonMises = np.sqrt( ex**2 + ey**2 - ex*ey + 3*eshear**2 )
    fs_VonMisses = eyield / equivalente_VonMises
    return  fs_VonMisses
