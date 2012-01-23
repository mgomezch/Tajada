Proyecto de [CI4721][] (Lenguajes de programación 2) de [Federico Flaviani][] (99‒31744) y [Manuel Gómez][] (05‒38235) en el trimestre enero–marzo 2012 en la Universidad “Simón Bolívar”.

[CI4721]:            <https://ldc.usb.ve/~emhn/cursos/ci4721>
[Federico Flaviani]: <https://github.com/minender>
[Manuel Gómez]:      <https://github.com/Targen>

* * *

# Tajada: Un lenguaje sabroso

*Tajada* es un lenguaje imperativo con un sistema de tipos estático, delicioso y nutritivo.  Está principalmente basado en la sintaxis de C con algunas variaciones para hacerlo más ameno.  Soporta la sobrecarga de operadores para manipular objetos de todos sus tipos, incluyendo los definidos por el programador, y todo siempre promoviendo una alimentación balanceada y tradicional.

1.  ## Símbolos

    Los programas de Tajada (en adelante, “las tajadas”) son documentos de texto [Unicode][] codificados en [UTF-8][].

[Unicode]: <http://www.unicode.org/versions/Unicode6.0.0> (The Unicode Consortium. The Unicode Standard, Version 6.0.0, (Mountain View, CA: The Unicode Consortium, 2011. ISBN 978‒1‒936213‒01‒6))
[UTF-8]:   <http://www.ietf.org/rfc/rfc3629>              (Yergeau, F., “UTF‐8, a transformation format of ISO 10646”, RFC 2279, January 1998.)

    [Nota: Este documento se basa en y hace referencia a la versión 6.0.0 del estándar Unicode únicamente porque es la más reciente disponible, y la intención es que la especificación de Tajada sea independiente de versiones específicas de otros documentos. —fin de la nota]

    Los **símbolos reservados** de Tajada son ciertas secuencias no vacías de puntos de código Unicode usadas por el lenguaje como parte de su sintaxis.  Los **símbolos** son aquellas secuencias no vacías de puntos de código Unicode consecutivos que ocurren en una tajada, no tienen como subsecuencia a ningún símbolo reservado, y son delimitados por símbolos reservados o el inicio o el final de la tajada.

    [Nota: Este documento utiliza el término “punto de código”, a veces “punto de código Unicode”, para hacer explícita la distinción entre bytes, caracteres y grafemas.  El término se usa en el mismo sentido que “character” y “code point” en el estándar Unicode. —fin de la nota]

    1.  ### Literales de cadena de caracteres

        Un **inicio de literal de cadena de caracteres** es un punto de código “LEFT DOUBLE QUOTATION MARK” (U+201C, “).

        Un **fin de literal de cadena de caracteres** es un punto de código “RIGHT DOUBLE QUOTATION MARK” (U+201D, ”).

        Un **escapador de literal de cadena de caracteres** es un punto de código “REVERSE SOLIDUS” (U+005C, \).

        Un **escapado de literal de cadena de caracteres** es una secuencia de dos puntos de código en la que el primero es un escapador de literal de cadena de caracteres.

        Un **elemento de literal de cadena de caracteres** es un escapado de literal de cadena de caracteres, o un punto de código distinto de un fin de literal de cadena de caracteres y de un escapador de literal de cadena de caracteres.

        Un **fragmento de literal de cadena de caracteres** es una secuencia de puntos de código que comienza con un inicio de literal de cadena de caracteres, seguido de cero o más elementos de literal de cadena de caracteres, seguido de un fin de literal de cadena de caracteres.

        Un **literal de cadena de caracteres** es un fragmento de literal de cadena de caracteres que no es una subsecuencia de ningún *otro* fragmento de literal de cadena de caracteres.   Los literales de cadena de caracteres son símbolos reservados.

        Una tajada nunca contiene un inicio de literal de cadena de caracteres que no forme parte de un literal de cadena de caracteres.

    2.  ### Espacio en blanco

        Un **espacio en blanco** es un símbolo reservado que no tiene efecto otro que delimitar símbolos y otros símbolos reservados.

        1.  #### Comentarios de bloque

            Un **inicio de comentario de bloque** es un punto de código “SINGLE LEFT-POINTING ANGLE QUOTATION MARK” (U+2039: ‹).

            Un **fin de comentario de bloque** es un punto de código “SINGLE RIGHT-POINTING ANGLE QUOTATION MARK” (U+203A, ›).

            Un **comentario de bloque** es un espacio en blanco: es una secuencia de puntos de código que comienza con la ocurrencia de un inicio de comentario de bloque que no ocurra dentro de un literal de cadena de caracteres, seguido de cualquier secuencia de cero o más puntos de código que no sean un fin de comentario de bloque, seguida de un punto de código como el último nombrado.

            Un comentario de bloque es un espacio en blanco.

            Si el punto de código que indica el inicio de un comentario de bloque es usado en un documento fuera de un literal de cadena de caracteres, y no es seguido eventualmente por el correspondiente punto de código que indica el final del comentario de bloque, entonces ese documento no es una tajada.

        2.  #### Comentarios de línea

            Un **fin de línea** es [cualquier punto de código considerado como indicador de fin o separación de líneas o párrafos según Unicode][UNL].

            Un **comentario de línea** es una secuencia de puntos de código que comienza con la ocurrencia del punto de código “DOUBLE SOLIDUS OPERATOR” (U+2AFD, ⫽) que no ocurra dentro de un literal de cadena de caracteres, seguido de una secuencia de cero o más puntos de código que no sean fines de línea, seguido de un fin de línea o del final del documento.

            Un comentario de línea es un espacio en blanco.  Un fin de línea es un espacio en blanco si ocurre fuera de un comentario de bloque y fuera de un literal de cadena de caracteres.

[UNL]: <http://www.unicode.org/versions/Unicode6.0.0/ch05.pdf> (Sección 5.8 (Newline Guidelines) del capítulo 5 (Implementation Guidelines) de la versión 6.0.0 del estándar Unicode (PDF))

        3.  #### Caracteres blancos

            [Todo punto de código Unicode que tenga la propiedad “White_Space”][UWS] es un espacio en blanco si ocurre fuera de un literal de cadena de caracteres, fuera de un comentario de línea y fuera de un comentario de bloque.

[UWS]: <http://www.unicode.org/Public/6.0.0/ucd/PropList.txt>  (Base de datos de caracteres Unicode 6.0.0: lista de propiedades de caracteres (líneas 11–22))

    3.  ### Literales

        1.  #### Enteros

            Un **literal entero** es un símbolo compuesto de una secuencia de uno o más de los siguientes puntos de código:

            *   “DIGIT ZERO”  (U+0030, 0)

            *   “DIGIT ONE”   (U+0031, 1)

            *   “DIGIT TWO”   (U+0032, 2)

            *   “DIGIT THREE” (U+0033, 3)

            *   “DIGIT FOUR”  (U+0034, 4)

            *   “DIGIT FIVE”  (U+0035, 5)

            *   “DIGIT SIX”   (U+0036, 6)

            *   “DIGIT SEVEN” (U+0037, 7)

            *   “DIGIT EIGHT” (U+0038, 8)

            *   “DIGIT NINE”  (U+0039, 9)

            Se interpreta como un número natural escrito en base decimal.

        2.  #### Punto flotante

        3.  #### Cadena de caracteres

        4.  #### Pabellón

    4.  ### Identificadores

        Las **palabras reservadas** del lenguaje son ciertos símbolos usados por el lenguaje como parte de su sintaxis.

        Un **identificador** es un símbolo que no es una palabra reservada ni un literal de ningún tipo.

2.  ## Tipos de datos

    Tajada soporta varios tipos de tipos:

    1.  Los escalares, que se especifican con una palabra clave:

        1.  ### Booleano

            Solo puede tomar dos valores: `true` o `tetero` para representar representar “verdadero”, y `false` o `negrito` para representar “falso”.  El tipo se especifica con la palabra clave `bool` o `café`.

        2.  ### Caracter

            Almacena exactamente un punto de código Unicode cualquiera.  El tipo se especifica con la palabra clave `char` o `caraota`.

        3.  ### Entero

            Almacena un número entero con un rango de valores válidos que incluye al menos todos los valores comprendidos entre los números decimales −2147483648 y 2147483647, ambos inclusive (porque eso es lo que cabe en un entero de 32 bits en C).  El tipo se especifica con la palabra clave `int` o `queso`.

        4.  ### Punto flotante

            Almacena un número de punto flotante con al menos la precisión de un `float` de 32 bits de C.  El tipo se especifica con la palabra clave `float` o `papelón`.

            *TODO*: especificar mejor la precisión.

    2.  Un tipo de tipos estructurados, el **pabellón**, que asocia en un mismo objeto una cantidad *fija* de valores de otros tipos.

    3.  Y tipos definidos en la tajada, los **dulces**, que son simplemente nombres nuevos para otros tipos.

3.  ## Estructura

    Las tajadas son una secuencia de definiciones de variables, y declaraciones y definiciones de tipos, operadores y funciones.

    1.  ### Declaraciones

        2.  ## Dulces

            En Tajada es posible agregar, como azucar sintáctica, definiciones de ciertos **dulces**.  Un dulce es un nombre alternativo para un tipo definido por el programador.

    2.  ### Definiciones

        1.  #### Variables

            Para crear una variable, se escribe su tipo seguido del nombre de la variable.  Por ejemplo,

                queso guayanés;


    3.  ### Instrucciones

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

Agregar ejemplos a todo.

Términos asignados:

*   arroz → arreglo
*   arepa → void

Términos por asignar:

*   carne mechada
