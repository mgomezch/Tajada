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

        [Nota: Cuando se hace referencia por primera vez en este documento a un punto de código particular de Unicode, normalmente se escribe entre un inicio de literal de cadena de caracteres y un final de literal de cadena de caracteres el valor de la propiedad “Name” del punto de código, seguido de un punto de código “SPACE” (U+0020,  ), luego un punto de código “LEFT PARENTHESIS” (U+0028, (), luego la expresión del punto de código de interés en el formato especificado por la primera sección del apéndice A del [estándar Unicode 6.0.0], luego un punto de código “COMMA” (U+002C, ,), luego otro punto de código “SPACE” (U+0020,  ), luego el punto de código de interés y finalmente un punto de código “RIGHT PARENTHESIS” (U+0029, )).  Si para el punto de código de interés la propiedad “Name” se define como la cadena vacía, se usará algún otro nombre para el punto de código.  Si el punto de código no representa por sí solo a un glifo, se podría omite junto con la coma y el espacio que le preceden. —fin de la nota más inútil jamás escrita en una especificación de un lenguaje]

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

            Un **comentario de bloque** es una secuencia de puntos de código que comienza con la ocurrencia de un inicio de comentario de bloque que no ocurra dentro de un literal de cadena de caracteres, seguido de cualquier secuencia de cero o más puntos de código que no sean un fin de comentario de bloque, seguida de un punto de código como el último nombrado.

            Un comentario de bloque es un espacio en blanco.

            Una tajada nunca contiene un inicio de un comentario de bloque que no forme parte ni de un comentario de bloque ni de un literal de cadena de caracteres.

        2.  #### Comentarios de línea

            Un **fin de línea** es [cualquiera de los siguientes puntos de código:][UNL].

            *   “LINE FEED (LF)”       (U+000A)

            *   “LINE TABULATION”      (U+000B)

            *   “FORM FEED (FF)”       (U+000C)

            *   “CARRIAGE RETURN (CR)” (U+000D)

            *   “NEXT LINE (NEL)”      (U+0085)

            *   “LINE SEPARATOR”       (U+2028)

            *   “PARAGRAPH SEPARATOR”  (U+2029)

            [Nota: Los nombres mostrados para los puntos de código anteriormente enumerados, exceptuando a los dos últimos, no corresponden a la propiedad “Name” (que es vacía para todos ellos) sino a la propiedad “Unicode_1_Name”. —fin de la nota]

            Un **inicio de comentario de línea** es un punto de código “DOUBLE SOLIDUS OPERATOR” (U+2AFD, ⫽).

            Un **comentario de línea** es una secuencia de puntos de código que comienza con la ocurrencia de un inicio de comentario de línea que no forme parte de un literal de cadena de caracteres, seguido de una secuencia de cero o más puntos de código que no sean fines de línea, seguido de un fin de línea o del final del documento.

            Un comentario de línea es un espacio en blanco.

            Un fin de línea es un espacio en blanco si ocurre fuera de un comentario de bloque y fuera de un literal de cadena de caracteres.

[UNL]: <http://www.unicode.org/versions/Unicode6.0.0/ch05.pdf> (Sección 5.8 (Newline Guidelines) del capítulo 5 (Implementation Guidelines) de la versión 6.0.0 del estándar Unicode (PDF))

        3.  #### Espacio en blanco individual

            [Todo punto de código Unicode que tenga la propiedad “White_Space”][UWS] es un espacio en blanco si ocurre fuera de un literal de cadena de caracteres, fuera de un comentario de línea y fuera de un comentario de bloque.

[UWS]: <http://www.unicode.org/Public/6.0.0/ucd/PropList.txt>  (Base de datos de caracteres Unicode 6.0.0: lista de propiedades de caracteres (líneas 11–22))

    3.  ### Literales

        1.  #### Enteros

            Un **dígito** es cualquiera de los siguientes puntos de código:

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

            Un **literal entero** es un símbolo compuesto de una secuencia de uno o más dígitos.  Se interpreta como un número natural escrito en notación posicional en base decimal.

        2.  #### Punto flotante

            Un **literal de punto flotante** es un símbolo compuesto de una secuencia de uno o más dígitos, seguido de un punto de código “FULL STOP” (U+002E, .), seguido de una secuencia de uno o más dígitos.  La primera secuencia de dígitos se interpreta como si fuera un literal entero y especifica la parte entera del número de punto flotante que el literal de punto flotante representa.  La segunda secuencia de dígitos especifica la parte fraccional del número de punto flotante que el literal de punto flotante representa.  Ambas secuencias se interpretan como números en notación posicional en base decimal con la correspondencia obvia entre dígitos decimales y puntos de código.  El número de punto flotante representado por el símbolo es el valor más cercano representable en la implementación de valores de punto flotante, y si hay más de uno igualmente cercano, se toma el de menor valor absoluto.

            TODO: overflow, underflow, NaN, infinitos, etc

    4.  ### Identificadores

        Las **palabras reservadas** del lenguaje son ciertos símbolos usados por el lenguaje como parte de su sintaxis.

        Un **identificador** es un símbolo que no es una palabra reservada ni un literal de ningún tipo.

2.  ## Tipos de datos

    Tajada soporta varios tipos de tipos:

    1.  Los escalares, que se especifican con una palabra reservada:

        1.  ### Café

            El café es un tipo enumerado que representa valores booleanos.  Solo puede tomar dos valores: la palabra reservada `tetero` representa un valor “verdadero”, y la palabra reservada `negrito` representa un valor “falso”.  El tipo se especifica con la palabra reservada `café`.

        2.  ### Caraota

            Almacena exactamente un punto de código Unicode cualquiera.  El tipo se especifica con la palabra reservada `caraota`.

        3.  ### Queso

            Almacena un número entero con un rango de valores válidos que incluye al menos todos los valores comprendidos entre los números decimales −2147483648 y 2147483647, ambos inclusive (porque ese es el rango de un entero de 32 bits en C, y C nos gusta).  El tipo se especifica con la palabra reservada `queso`.

        4.  ### Papelón

            Almacena un número de punto flotante con al menos la precisión y el rango de un `float` de 32 bits de C.  El tipo se especifica con la palabra reservada `papelón`.

            *TODO*: especificar mejor la precisión.

    2.  Un tipo de tipos estructurados, el **pabellón**, que asocia en un mismo objeto una cantidad *fija* de valores de otros tipos.

    3.  Y tipos definidos en la tajada, los **dulces**, que son simplemente nombres nuevos para otros tipos.

3.  ## Estructura

    Las tajadas son una secuencia de definiciones de variables, y declaraciones y definiciones de tipos, operadores y funciones.

    1.  ### Declaraciones

        2.  ## Dulces

            En Tajada es posible agregar definiciones de ciertos **dulces**.  Un dulce es un nombre alternativo para un tipo definido por el programador.

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
