#!/usr/bin/env python
"""Ejemplo de comentario"""
import matplotlib.pyplot as plt
import numpy as np

from funciones_app import *

'''Como las funciones no tienen parametros se debe crear una funcion que pida los datos'''
def pedir_datos ():
    print("\n\t\t.:Ingrese los datos:.")
    ex = float(input("Ingrese 'ex' : "))
    ey = float(input("Ingrese 'ey' : "))
    ez = float(input("Ingrese 'ez' : "))
    eshear = float(input("Ingrese 'eshear' : "))
    theta = float(input("Ingrese 'teta' : "))
    E = float(input("Ingrese 'E' : "))
    poisson = float(input("Ingrese 'poisson' : "))


ex = 10000
ey = 6000
ez = -2000
eshear = -4000
theta = 0
E = 45000
poisson = 0.3
eyield = E*1.2
teta = np.arange(0, 361, 0.1)
rad = np.pi/180

#pedir_datos()

deformacion_xx()
deformacion_yy()
deformacion_zz()
deformacion_xy()
deformacion_1()
deformacion_2()
centro_Mohr()
radio_deformacion()
circulo_3_deformacion()
sen_vs_teta()
circulo_Mohr()
angulo_tension_stress()
angulo_shear_stress()
factor_seguridad_Tresca()
factor_seguridad_VonMisses()



#graficas criterios de Tresca y Sig1, Sig2 y Von Misses
def failure_criterion():
    plt.figure(1) #genera la figura 1
    plt.subplot(211) #ubicacion de la figura 1
    #Rombo de Tresca
    lineas_Tresca()
    plt.plot(xs1,ys1,color="green",label="Tresca")
    plt.plot(xs2,ys2,c="green")
    plt.plot(xs3,ys3,c="green")
    plt.plot(xi1,yi1,c="green")
    plt.plot(xi2,yi2,c="green")
    plt.plot(xi3,yi3,c="green")
    #Sigma
    sigma_1()
    sigma_2()
    plt.plot(sigma1,sigma2,color="blue",marker="o",label="Criterio**")
    #Elipse de Von Misses
    elipse_VonMisses ()
    plt.plot(m,n,color="orangered",label="Von Misses")
    plt.legend(loc="upper right")
    plt.grid() #hace visible la rejilla
    plt.axis("equal") #eje x = eje y
    plt.xlabel("σx")
    plt.ylabel("σy")
    plt.title("Criterios de falla")


#graficas esfuerzo'' vs teta
def stress_vs_teta():
    plt.figure(1)
    plt.subplot(212)
    plt.plot(teta,EXX,label="σ x'x'")
    plt.plot(teta,EXY,label="σ x'y'")
    plt.legend(loc="upper right")
    plt.grid()
    plt.xlabel("σx")
    plt.ylabel("σy")
    plt.title("Esfuerzos")


#graficas de Mohr
def mohr():
    plt.figure(2)
    plt.subplot(211)
    plt.plot(x,y,label="principal")
    plt.plot(x2,y2,"--",label="segundo")
    plt.plot(x3,y3,"--",label="tercero(global)")
    plt.plot(ey,eshear,"*b",label="eyy,exy")
    plt.plot(x1,y1,"--",label="angulo principal",c="black")
    plt.legend(loc="upper right")
    plt.axis("equal")
    plt.grid()
    plt.xlabel("σx")
    plt.ylabel("σy")
    plt.title("Circulo de Mohr")


#grafica deformacion
def deformation():
    plt.figure(2)
    plt.subplot(212)
    plt.plot(xd,yd,label="principal")
    plt.plot(xd2,yd2,"--",label="segundo")
    plt.plot(xd3,yd3,"--",label="tercero(global)")
    plt.legend(loc="upper right")
    plt.axis("equal")
    plt.grid()
    plt.xlabel("σx")
    plt.ylabel("σy")
    plt.title("Circulo de Mohr deformacion")

failure_criterion()
stress_vs_teta()
mohr()
deformation()
plt.show()
