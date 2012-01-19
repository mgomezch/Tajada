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
