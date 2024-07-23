# Distribucion-Proporcional-de-procesos
Distribucion Proporcional de procesos en la memoria

# Sistema Multiprogramado Monoprocesador

## Descripción

Este proyecto implementa un simulador de un sistema multiprogramado monoprocesador en un ambiente de paginación. El objetivo es determinar el tiempo que le lleva al sistema ejecutar los procesos (Turnaround Time) ingresados al sistema.

### Características
- **Distribución Proporcional**: Tamaño de bloque de memoria = 512 bytes.
- **Tamaño de la RAM**: 2MB.
- **Datos de entrada**: 
  - Nombre del Proceso
  - Tamaño en bytes, KB, MB o GB
  - Tiempo de acceso en milisegundos
  - Tiempo de transferencia en milisegundos
  - Tiempo promedio de ejecución en milisegundos
  - Máximo 6 procesos
- **Datos de salida**: 
  - Tiempo de Fallas
  - Turnaround Time por proceso

## Estructura del Proyecto

- **funciones.h**: Encabezado que contiene las declaraciones de las funciones utilizadas en el programa.
- **main.cpp**: Archivo principal que contiene la lógica del programa.

## Compilación y Ejecución

### Requisitos

- g++ (GCC)
- C++11 o superior

### Compilación

```bash
g++ -o sistema_multiprogramado DistProporcionalMemoria.cpp
