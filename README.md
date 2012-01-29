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

    2.  ### Espacio en blanco

        Un **espacio en blanco** es un símbolo reservado que no tiene efecto otro que delimitar símbolos y otros símbolos reservados.

        1.  #### Comentarios de bloque

            Un **inicio de comentario de bloque** es un punto de código “SINGLE LEFT-POINTING ANGLE QUOTATION MARK” (U+2039: ‹).

            Un **fin de comentario de bloque** es un punto de código “SINGLE RIGHT-POINTING ANGLE QUOTATION MARK” (U+203A, ›).

            Un **comentario de bloque** es una secuencia de puntos de código que comienza con la ocurrencia de un inicio de comentario de bloque que no ocurra dentro de un literal de cadena de caracteres, seguido de cualquier secuencia de cero o más puntos de código que no sean un fin de comentario de bloque, seguida de un punto de código como el último nombrado.

            Un comentario de bloque es un espacio en blanco.

            Una tajada nunca contiene un inicio de un comentario de bloque que no forme parte ni de un comentario de bloque ni de un literal de cadena de caracteres.

            Una tajada nunca contiene un inicio de literal de cadena de caracteres que no forme parte de un literal de cadena de caracteres, un comentario de línea, o un comentario de bloque.

        2.  #### Comentarios de línea

            Un **fin de línea** es [cualquiera de los siguientes puntos de código:][UNL].

            *   “LINE FEED (LF)”       (U+000A)

            *   “LINE TABULATION”      (U+000B)

            *   “FORM FEED (FF)”       (U+000C)

            *   “CARRIAGE RETURN (CR)” (U+000D)

            *   “NEXT LINE (NEL)”      (U+0085)

            *   “LINE SEPARATOR”       (U+2028)

            *   “PARAGRAPH SEPARATOR”  (U+2029)

            [Nota: Los nombres mostrados para los puntos de código anteriormente enumerados, exceptuando a los dos últimos, no corresponden a la propiedad “Name” (que es vacía para todos ellos) sino a la propiedad “Unicode\_1\_Name”. —fin de la nota]

            Un **inicio de comentario de línea** es un punto de código “DOUBLE SOLIDUS OPERATOR” (U+2AFD, ⫽).

            Un **comentario de línea** es una secuencia de puntos de código que comienza con la ocurrencia de un inicio de comentario de línea que no forme parte de un literal de cadena de caracteres, seguido de una secuencia de cero o más puntos de código que no sean fines de línea, seguido de un fin de línea o del final del documento.

            Un comentario de línea es un espacio en blanco.

            Un fin de línea es un espacio en blanco si ocurre fuera de un comentario de bloque y fuera de un literal de cadena de caracteres.

[UNL]: <http://www.unicode.org/versions/Unicode6.0.0/ch05.pdf> (Sección 5.8 (Newline Guidelines) del capítulo 5 (Implementation Guidelines) de la versión 6.0.0 del estándar Unicode (PDF))

        3.  #### Espacio en blanco individual

            [Todo punto de código Unicode que tenga la propiedad “White\_Space”][UWS] es un espacio en blanco si ocurre fuera de un literal de cadena de caracteres, fuera de un comentario de línea y fuera de un comentario de bloque.

[UWS]: <http://www.unicode.org/Public/6.0.0/ucd/PropList.txt>  (Base de datos de caracteres Unicode 6.0.0: lista de propiedades de caracteres (líneas 11–22))

    3.  ### Otros literales

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

            Un **literal de punto flotante** es un símbolo compuesto de una secuencia de uno o más dígitos, seguido de un punto de código “MIDDLE DOT” (U+00B7, ·), seguido de una secuencia de uno o más dígitos.  La primera secuencia de dígitos se interpreta como si fuera un literal entero y especifica la parte entera del número de punto flotante que el literal de punto flotante representa.  La segunda secuencia de dígitos especifica la parte fraccional del número de punto flotante que el literal de punto flotante representa.  Ambas secuencias se interpretan como números en notación posicional en base decimal con la correspondencia obvia entre dígitos decimales y puntos de código.

            TODO: overflow, underflow, NaN, infinitos, etc

    4.  ### Identificadores

        Las **palabras reservadas** del lenguaje son ciertos símbolos usados por el lenguaje como parte de su sintaxis.

        Un **identificador** es un símbolo que no es una palabra reservada ni un literal de ningún tipo.

2.  ## Tipos de datos

    Cada tipo de datos tiene asociada una **especificación de tipo**.

    1.  ### Escalares

        1.  #### Café

            El **café** es un tipo enumerado que representa valores booleanos.  Solo puede tomar dos valores: la palabra reservada `tetero` representa un valor “verdadero”, y la palabra reservada `negrito` representa un valor “falso”.  La especificación para el tipo café es la palabra reservada `café`.
            `tetero` y `negrito` son literales de café.

        2.  #### Caraota

            La **caraota** es un tipo que almacena exactamente un punto de código Unicode cualquiera.  La especificación para la caraota es la palabra reservada `caraota`.

            Una **caraota literal** es un escapado de literal de cadena de caracteres tal que ninguno de los dos puntos de código formen parte de un literal de cadena de caracteres, ni de un comentario de línea, ni de un comentario de bloque.

            TODO: literales de caraota

        3.  #### Queso

            El **queso** es un tipo que almacena un número entero con un rango de valores válidos que incluye al menos todos los valores comprendidos entre los números decimales −2147483648 y 2147483647, ambos inclusive (porque ese es el rango de un entero de 32 bits en C, y C nos gusta).  La especificación para el queso es la palabra reservada `queso`.

            Un literal entero especifica un valor de tipo queso.  Una tajada no tiene literales enteros cuyo correspondiente número natural no esté dentro del rango del queso.

        4.  #### Papelón

            El **papelón** es un tipo que almacena un número de punto flotante con al menos la precisión y el rango de un `float` de 32 bits de C.  El tipo se especifica con la palabra reservada `papelón`.

            Un literal de punto flotante especifica un valor de tipo papelón.  El valor de tipo papelón correspondiente a un literal de punto flotante es el valor más cercano representable en la implementación de valores de punto flotante, y si hay más de uno igualmente cercano, se toma el de menor valor absoluto.

            TODO: especificar mejor la precisión.

            TODO: overflow, underflow, NaN, infinitos, etc; y si el valor del literal se sale del rango del tipo?  Se toma el valor máximo finito, o infinito, o qué?  Es un error?  Un warning?

    2.  ### Arepa

        La **arepa** es un tipo de tipos estructurados que asocian en un mismo ente a una cantidad *fija* de valores de otros tipos particulares en un orden específico.  Los tipos asociados por una arepa son sus **ingredientes**.  Los ingredientes de una arepa están implícitamente enumerados desde el cero en el órden en el que se especifican, y pueden tener opcionalmente un identificador asociado.  Una arepa puede tener cualquier cantidad de ingredientes del mismo tipo, y cada uno es independiente de los demás.  Ningún par de ingredientes con nombre en una arepa puede compartir un mismo nombre.

        Un **literal de ingrediente** es una especificación de tipo seguida opcionalmente de un identificador.

        `arepa` es una palabra reservada.

        `de` es una palabra reservada.

        `con` es una palabra reservada.

        La especificación de tipo correspondiente a una arepa con cero ingredientes es `arepa`.

        La especificación de tipo correspondiente a una arepa con exactamente un ingrediente es `arepa` seguida de `de`, a su vez seguida del literal de ingrediente correspondiente a su único ingrediente.

        Un **separador de lista** es un punto de código “COMMA” (U+002C).  Un separador de lista es un símbolo reservado si no ocurre dentro de un literal de cadena de caracteres, ni dentro de un comentario de línea, ni dentro de un comentario de bloque.

        `y` es una palabra reservada.

        La especificación de tipo correspondiente a una arepa con más de un ingrediente es `arepa` seguida de `con`, a su vez seguida de cada uno de los literales de ingrediente correspondientes a los ingredientes de la arepa desde el primero y exceptuando el último, siendo seguido cada literal de ingrediente por un separador de lista salvo por el penúltimo ingrediente de la arepa, todo seguido de `y` seguida del literal de ingrediente correspondiente al último ingrediente de la arepa.

        Por ejemplo, cada una de las siguientes líneas contiene una especificación de tipo válida para una arepa:

            arepa

            arepa de queso

            arepa con queso y café

            arepa con papelón, café, café marrón, queso guayanés, arepa de caraota, arepa con papelón, café marrón y queso y queso

        TODO: ver definición de tuplas en Haskell

        Un **inicio de literal estructurado** es un punto de código “LEFT-POINTING DOUBLE ANGLE QUOTATION MARK” (U+00AB).  Un inicio de literal estructurado es un símbolo reservado si no ocurre dentro de un literal de cadena de caracteres, ni dentro de un comentario de línea, ni dentro de un comentario de bloque.

        Un **fin de literal estructurado** es un punto de código “RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK” (U+00BB).  Un fin de literal estructurado es un símbolo reservado si no ocurre dentro de un literal de cadena de caracteres, ni dentro de un comentario de línea, ni dentro de un comentario de bloque.

        TODO: literales de arepa — mejor meterlos en las expresiones, no?

    3.  ### Cachapa

        La **cachapa** es un tipo de tipos unión que asocian en un mismo ente a exactamente un valor cuyo tipo puede ser alguno de un cierto conjunto de al menos dos elementos.  Los tipos asociados por una cachapa son sus **ingredientes**.  Los ingredientes de una cachapa están implícitamente enumerados desde el cero en el órden en el que se especifican, y pueden tener opcionalmente un identificador asociado.

        Una tajada no especifica cachapas donde exista algún par de ingredientes enumerados en su especificación que sean equivalentes.  Ningún par de ingredientes con nombre en una cachapa puede compartir un mismo nombre.

        Una cachapa tiene a lo sumo 256 ingredientes.

        TODO: leer del scott, preguntar y refinar.

3.  ## Estructura

    Las tajadas son una secuencia de declaraciones de dulces, definiciones de variables, y declaraciones y definiciones de operadores y funciones.

    1.  ### Declaraciones

        Las **declaraciones** son asociaciones entre un tipo y un identificador.

        1.  #### Dulces

            `es` es una palabra reservada.

            `dulce` es una palabra reservada.

            Un **terminador de frase** es un punto de código “FULL STOP” (U+002E, .).  Un terminador de frase es un símbolo reservado si no ocurre dentro de un literal de cadena de caracteres, ni dentro de un comentario de línea, ni dentro de un comentario de bloque.

            Una **declaración de dulce** es una especificación de tipo seguida de `es`, seguida de `dulce`, seguida de `de`, seguida de un identificador, seguido de un terminador de frase.

            Un **dulce** es una identificación entre un tipo y un identificador.  Cuando se ha declarado un dulce con un cierto tipo y un cierto identificador, puede sustituirse a partir de ese punto de la tajada cualquier ocurrencia de la especificación de ese tipo por el identificador asociado con el dulce.  En otras palabras, un dulce define un nombre alternativo para un tipo, y su único propósito es permitir al programador agregar a gusto azucar sintáctica a su tajada.

            Una tajada nunca tiene dos declaraciones de dulces para el mismo identificador.

        2.  #### Funciones

        3.  #### Operadores

    2.  ### Definiciones

        1.  #### Variables

            Una **definición de variable** es una secuencia compuesta por un identificador, una `de`, una especificación de tipo y un terminador de frase.  Por ejemplo,

                foo es queso.

            define una variable llamada `guayanés` de tipo `queso`.  La variable es un ente del tipo especificado y puede ser referida por el identificador usado en su definición.

            TODO: alcance y tiempo de vida

        2.  #### Funciones

        3.  #### Operadores

    3.  ### Instrucciones

    4.  ### Expresiones

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
