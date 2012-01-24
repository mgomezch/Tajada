Proyecto de [CI4721](https://ldc.usb.ve/~emhn/cursos/ci4721) (Lenguajes de programación 2) de [Federico Flaviani][] (99‒31744) y [Manuel Gómez][] (05‒38235) en el trimestre enero–marzo 2012 en la Universidad “Simón Bolívar”.

[Federico Flaviani]: <https://github.com/minender>
[Manuel Gómez]:      <https://github.com/Targen>



* * *



Tajada: Un lenguaje sabroso
===========================

*Tajada* es un lenguaje imperativo con un sistema de tipos estático, delicioso y nutritivo.  Está principalmente basado en la sintaxis de C con algunas variaciones para hacerlo más ameno.  Soporta la sobrecarga de operadores para manipular objetos de todos sus tipos, incluyendo los definidos por el programador, y todo siempre promoviendo una alimentación balanceada.



Tipos de datos
--------------

Tajada soporta varios tipos de tipos:

*   Los escalares:
    *   **Booleano**: Solo puede tomar dos valores: `true` o `tetero` para representar representar “verdadero”, y `false` o `negrito` para representar “falso”.  El tipo se especifica con la palabra clave `bool` o `café`.

    *   **Caracter**: Almacena exactamente un punto de código Unicode cualquiera.  El tipo se especifica con la palabra clave `char` o `caraota`.

    *   **Entero**: Almacena un número entero con un rango de valores válidos que incluye al menos todos los valores comprendidos entre los números decimales −2147483648 y 2147483647, ambos inclusive (porque eso es lo que cabe en un entero de 32 bits en C).  El tipo se especifica con la palabra clave `int` o `queso`.

    *   **Punto flotante**: Almacena un número de punto flotante con al menos la precisión de un `float` de 32 bits de C.  El tipo se especifica con la palabra clave `float` o `papelón`.

        TODO: especificar mejor la precisión.

*   Los de colección:
    *   **Arreglo**: Agrupa una cantidad *fija* de valores de un mismo tipo *escalar* en una estructura indexada por enteros consecutivos que comienzan en cero.

    *   **Cadena**: TODO

*   Y un tipo estructurado, el **pabellón**, que consiste en…

    TODO: tuplas con uniones y eso

    *   **Tupla**:

*   Definición de operadores

Variables
---------

Las variables

Funciones
---------



Llamada a funciones
-------------------

Escribir como es el paso de parámetros de las funciones importante.


Equivalencia y compatibilidad de tipos
--------------------------------------

Tajada soporta compatibilidad de los tipos `int` y `float` para los operadores aritméticos y las asignaciones.

`float` opAritmetico `int` y `int` opAritmetico `float` devuelven un elemento del tipo `float`, donde los operadores aritméticos son:

Una instrucción LVal=RVal; es válida cuando LVal es un expresión de tipo `float` y RVal es una expresión de tipo `int` (no viceversa) y el resultado 
entero de la expresión RVal se transforma automaticamente en `float`.

Tajada no tiene compatibilidad entre los tipos `char` e `int` ni tampoco entre `int` y `bool`.

Asignación
----------

La aignación en Tajada es de la forma LVal:=RVal; donde LVal y RVal son expresiones del mismo tipo o compatibles.

Estructuras de control
----------------------

Tajada tiene tres estructuras de control: una de selección, de iteración y de selección controlada.

La sintaxis de la estructura de selección es de la siguiente forma:s

Expresiones
-----------

Las expresiones en Tajada se clasifican en: aritméticas, Lógicas, de Algebra Lineal (tuplas).

Las expresiones aritméticas estan definidas recursivamente de la siguiente manera:

Si x es una variable de tipo `int` o `float`, entonces x es una expresión aritmética.

Si c es una constante númerica, entonces c es una expresión aritmética

Si e1 y e2 son expresiones aritméticas, entonces también lo son: e1+e2, e1*e2, e1/e2, e1-e2, -e1, (e1). (falta arreglo y registro)


Las expresiones lógicas estan definidas recursivamente de la siguiente manera:

Si x es una variable de tipo `bool`, entonces x es una expresión lógica.

True y false son expresiónes lógicas.

Si e1 y e2 son expresiones aritméticas, entonces son expresiones lógicas: e1<e2, e1<=e2, e1>e2, e1>=e2, e1==e2 y e1!=e2.

Si e1 y e2 son caracteres, entonces es una expresión lógica: e1==e2 y e1!=e2.

Si e1 y e2 son expresiones lógicas, entonces lo son también: e1==e2, e1!=e2, !e1, e1&&e2, e1||e2, (e1). (falta arreglo y registro)


Definir las expresiones de Algebra Lineal.

Chequeos en tiempo de ejecución
-------------------------------



Estructura
----------

Los programas de Tajada se escriben como documentos de texto Unicode (codificados en UTF-8).  Consisten de una secuencia de definiciones de tipos, variables, operadores y funciones.



* * *


Nota histórica
--------------

La idea original era hacer un lenguaje con operaciones relacionales y salió de [las observaciones de Matthew Might sobre la similitud de muchos componentes de scripts de UNIX con operadores relacionales][L1].  Sin embargo, esto requeriría manejar memoria dinámicamente y eso escapa el alcance y los objetivos del curso.  La sintaxis relacional estaba ~~siendo copiada descaradamente de~~inspirada en [esta información sobre un lenguaje de consultas llamado ISBL][L2].  Escribimos algunos [trozos de código][L3] basados en esa idea.

La estructura de este documento está basada en [la especificación del lenguaje Decaf][L4] del [curso CS143 (Compilers)][L5] de la [Universidad Stanford][L6].

[L1]: <http://matt.might.net/articles/sql-in-the-shell>
[L2]: <http://www.dcs.warwick.ac.uk/people/academic/Meurig.Beynon/CS319/pdf/RelMod.pdf>
[L3]: <http://github.com/Targen/Tajada/raw/master/sample/misc.rel>
[L4]: <http://www.stanford.edu/class/cs143/handouts/020_Decaf_Specification.pdf>
[L5]: <http://www.stanford.edu/class/cs143>
[L6]: <http://www.stanford.edu/>



* * *



Cosas por hacer
---------------

Términos asignados:

*   arroz → arreglo
*   arepa → void

Términos por asignar:

*   carne mechada
