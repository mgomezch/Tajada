Proyecto de [CI4721][] (Lenguajes de programación 2) de [Federico Flaviani][] (99‒31744) y [Manuel Gómez][] (05‒38235) en el trimestre enero–marzo 2012 en la Universidad “Simón Bolívar”.

[CI4721]:            <https://ldc.usb.ve/~emhn/cursos/ci4721>
[Federico Flaviani]: <https://github.com/minender>
[Manuel Gómez]:      <https://github.com/Targen>

* * *

# Tajada: Un lenguaje sabroso

*Tajada* es un lenguaje imperativo con un sistema de tipos estático, delicioso y nutritivo.  Está principalmente basado en la sintaxis de C con algunas variaciones para hacerlo más ameno.  Soporta la sobrecarga de operadores para manipular entes de todos sus tipos, incluyendo los definidos por el programador, y todo siempre promoviendo una alimentación balanceada y tradicional.

1.  ## Símbolos

    Los programas de Tajada (en adelante, “las tajadas”) son documentos de texto [Unicode][] codificados en [UTF-8][].

[Unicode]: <http://www.unicode.org/versions/Unicode6.0.0> (The Unicode Consortium. The Unicode Standard, Version 6.0.0, (Mountain View, CA: The Unicode Consortium, 2011. ISBN 978‒1‒936213‒01‒6))
[UTF-8]:   <http://www.ietf.org/rfc/rfc3629>              (Yergeau, F., “UTF‐8, a transformation format of ISO 10646”, RFC 2279, January 1998.)

    [Nota: Este documento se basa en y hace referencia a la versión 6.0.0 del estándar Unicode únicamente porque es la más reciente disponible, y la intención es que la especificación de Tajada sea independiente de versiones específicas de otros documentos. —fin de la nota]

    Los **símbolos reservados** de Tajada son ciertas secuencias no vacías de puntos de código Unicode usadas por el lenguaje como parte de su sintaxis.  Los **símbolos** son aquellas secuencias no vacías de puntos de código Unicode consecutivos que ocurren en una tajada, no tienen como subsecuencia a ningún símbolo reservado, y son delimitados por símbolos reservados o el inicio o el final de la tajada.

    [Nota: Este documento utiliza el término “punto de código”, a veces “punto de código Unicode”, para hacer explícita la distinción entre bytes, caracteres y grafemas.  El término se usa en el mismo sentido que “character” y “code point” en el estándar Unicode. —fin de la nota]

    1.  ### Literales de cadena de caracteres

        [Nota: Cuando se hace referencia por primera vez en este documento a un punto de código particular de Unicode, normalmente se escribe entre un inicio de literal de cadena de caracteres y un fin de literal de cadena de caracteres el valor de la propiedad “Name” del punto de código, seguido de un punto de código “SPACE” (U+0020,  ), luego un punto de código “LEFT PARENTHESIS” (U+0028, **(**), luego la expresión del punto de código de interés en el formato especificado por la primera sección del apéndice A del [estándar Unicode 6.0.0], luego un punto de código “COMMA” (U+002C, **,**), luego otro punto de código “SPACE” (U+0020,  ), luego el punto de código de interés en letra negrilla, y finalmente un punto de código “RIGHT PARENTHESIS” (U+0029, **)**).  Si para el punto de código de interés la propiedad “Name” se define como la cadena vacía, se usará algún otro nombre para el punto de código.  Si el punto de código no representa por sí solo a un grafema, se podría omitir junto con la coma y el espacio que le preceden. —fin de la nota más inútil jamás escrita en una especificación de un lenguaje]

        Un **inicio de literal de cadena de caracteres** es un punto de código “LEFT DOUBLE QUOTATION MARK” (U+201C, **“**).

        Un **fin de literal de cadena de caracteres** es un punto de código “RIGHT DOUBLE QUOTATION MARK” (U+201D, **”**).

        Un **escapador de caracter** es un punto de código “REVERSE SOLIDUS” (U+005C, **\\**).

        Un **escapado de caracter** es una secuencia de dos puntos de código en la que el primero es un escapador de caracter, y si le precede (no inclusive) alguna secuencia consecutiva de escapadores de caracteres, la secuencia tiene un número par de puntos de código (y podría, por lo tanto, ser vacía).  El último punto de código de un escapado de caracter se denomina su **caracter escapado**.

        Un **elemento de literal de cadena de caracteres** es un escapado de caracter, o un punto de código distinto de un fin de literal de cadena de caracteres y de un escapador de caracter.

        Un **fragmento de literal de cadena de caracteres** es una secuencia de puntos de código que comienza con un inicio de literal de cadena de caracteres que no forme parte de un escapado de caracter, ni de un comentario de línea, ni de un comentario de bloque, seguido de cero o más elementos de literal de cadena de caracteres, seguido de un fin de literal de cadena de caracteres.

        Un **literal de cadena de caracteres** es un fragmento de literal de cadena de caracteres que no es una subsecuencia de ningún *otro* fragmento de literal de cadena de caracteres.   Los literales de cadena de caracteres son símbolos reservados.

        Un literal de cadena de caracteres especifica o representa a la secuencia de puntos de código obtenida por la concatenación de todos los caracteres representados por sus elementos de literal de cadena de caracteres en el mismo orden en que éstos aparecen en el literal de cadena de caracteres.  El punto de código representado por un elemento de literal de cadena de caracteres es el último de los que lo componen.

    2.  ### Espacio en blanco

        Un **espacio en blanco** es un símbolo reservado que no tiene efecto otro que delimitar símbolos y otros símbolos reservados.

        1.  #### Comentarios de bloque

            Un **inicio de comentario de bloque** es un punto de código “SINGLE LEFT-POINTING ANGLE QUOTATION MARK” (U+2039: **‹**).

            Un **fin de comentario de bloque** es un punto de código “SINGLE RIGHT-POINTING ANGLE QUOTATION MARK” (U+203A, **›**).

            Un **fragmento de comentario de bloque** es una secuencia de puntos de código que comienza con la ocurrencia de un inicio de comentario de bloque que no ocurra dentro de un literal de cadena de caracteres, ni de un escapado de caracter, ni de un comentario de línea, seguido de cualquier secuencia de cero o más puntos de código que no sean un fin de comentario de bloque, seguida de un fin de comentario de bloque.

            Un **comentario de bloque** es un fragmento de comentario de bloque que no es una subsecuencia de ningún *otro* fragmento de comentario de bloque.  Un comentario de bloque es un espacio en blanco.

        2.  #### Comentarios de línea

            Un **fin de línea** es [cualquiera de los siguientes puntos de código][UNL].

            *   “LINE FEED (LF)”       (U+000A)

            *   “LINE TABULATION”      (U+000B)

            *   “FORM FEED (FF)”       (U+000C)

            *   “CARRIAGE RETURN (CR)” (U+000D)

            *   “NEXT LINE (NEL)”      (U+0085)

            *   “LINE SEPARATOR”       (U+2028)

            *   “PARAGRAPH SEPARATOR”  (U+2029)

            [Nota: Los nombres mostrados para los puntos de código anteriormente enumerados, exceptuando a los dos últimos, no corresponden a la propiedad “Name” (que es vacía para todos ellos) sino a la propiedad “Unicode\_1\_Name”. —fin de la nota]

            Un **inicio de comentario de línea** es un punto de código “DOUBLE SOLIDUS OPERATOR” (U+2AFD, **⫽**).

            Un **comentario de línea** es una secuencia de puntos de código que comienza con la ocurrencia de un inicio de comentario de línea que no forme parte de un literal de cadena de caracteres, ni de un escapado de caracter, ni de un comentario de bloque, seguido de una secuencia de cero o más puntos de código que no sean fines de línea, seguido de un fin de línea o del final del documento.

            Un comentario de línea es un espacio en blanco.

            Un fin de línea es un espacio en blanco si ocurre fuera de un comentario de bloque, fuera de un comentario de línea, fuera de un literal de cadena de caracteres y fuera de un escapado de caracter.

            Una tajada nunca contiene un inicio de comentario de bloque que no forme parte ni de un comentario de bloque, ni de un literal de cadena de caracteres, ni de un escapado de caracter, ni de un comentario de línea.

            Una tajada nunca contiene un inicio de literal de cadena de caracteres que no forme parte de un literal de cadena de caracteres, un comentario de línea, o un comentario de bloque.

[UNL]: <http://www.unicode.org/versions/Unicode6.0.0/ch05.pdf> (Sección 5.8 (Newline Guidelines) del capítulo 5 (Implementation Guidelines) de la versión 6.0.0 del estándar Unicode (PDF))

        3.  #### Espacio en blanco individual

            [Todo punto de código Unicode que tenga la propiedad “White\_Space”][UWS] es un **espacio en blanco individual**, que es un espacio en blanco, si ocurre fuera de un literal de cadena de caracteres, fuera de un escapado de caracter, fuera de un comentario de línea, fuera de un comentario de bloque y fuera de un fin de línea.

[UWS]: <http://www.unicode.org/Public/6.0.0/ucd/PropList.txt> (Base de datos de caracteres Unicode 6.0.0: lista de propiedades de caracteres (líneas 11–22))

    3.  ### Otros literales

        1.  #### Enteros

            Un **dígito** es cualquiera de los siguientes puntos de código:

            *   “DIGIT ZERO”  (U+0030, **0**)

            *   “DIGIT ONE”   (U+0031, **1**)

            *   “DIGIT TWO”   (U+0032, **2**)

            *   “DIGIT THREE” (U+0033, **3**)

            *   “DIGIT FOUR”  (U+0034, **4**)

            *   “DIGIT FIVE”  (U+0035, **5**)

            *   “DIGIT SIX”   (U+0036, **6**)

            *   “DIGIT SEVEN” (U+0037, **7**)

            *   “DIGIT EIGHT” (U+0038, **8**)

            *   “DIGIT NINE”  (U+0039, **9**)

            Un **fragmento de literal entero** es una secuencia de uno o más dígitos.  Un **literal entero** es un fragmento de literal entero que no es una subsecuencia de ningún *otro* fragmento de literal entero, ni de un literal de cadena de caracteres, ni de un espacio en blanco, y su primer punto de código sigue inmediatamente al último punto de código de algún símbolo reservado, o al inicio del documento.  Un literal entero es un símbolo reservado.  Se interpreta como un número natural escrito en notación posicional en base decimal.

        2.  #### Punto flotante

            Un **separador de literal de punto flotante** es un punto de código “MIDDLE DOT” (U+00B7, **·**) que no ocurra dentro de un literal de cadena de caracteres, un escapado de caracter o un espacio en blanco.  Un separador de literal de punto flotante es un símbolo reservado.

            Un **literal de punto flotante** es una secuencia compuesta de un literal entero, seguido de un separador de literal de punto flotante, seguido de otro literal entero.  Un literal de punto flotante representa un valor numérico de punto flotante.  El primer literal entero especifica la parte entera del valor representado.  El valor del segundo literal entero es igual a la parte fraccional del número de punto flotante representado multiplicada por 10ⁿ⁺¹, donde `n` es el número de dígitos que componen a ese literal entero.

            TODO: overflow, underflow, NaN, infinitos, etc

    4.  ### Identificadores

        Las **palabras reservadas** del lenguaje son ciertos símbolos usados por el lenguaje como parte de su sintaxis.

        Un **identificador** es un símbolo que no es una palabra reservada ni un literal entero.

2.  ## Tipos de datos

    Cada tipo de datos tiene asociada una **especificación de tipo**.

    1.  ### Escalares

        1.  #### Café

            `tetero` es una palabra reservada.

            `negrito` es una palabra reservada.

            `café` es una palabra reservada.

            El **café** es un tipo enumerado que representa valores booleanos.  Solo puede tomar dos valores: `tetero` representa un valor “verdadero”, y `negrito` representa un valor “falso”.

            La especificación de tipo del café es `café`.

            `tetero` y `negrito` son literales de café.

        2.  #### Caraota

            `caraota` es una palabra reservada.

            La **caraota** es un tipo que almacena exactamente un punto de código Unicode cualquiera.

            La especificación de tipo de la caraota es `caraota`.

            Un **literal de caraota** es un escapado de caracter tal que ninguno de sus dos puntos de código formen parte de un literal de cadena de caracteres, ni de un comentario de línea, ni de un comentario de bloque.

        3.  #### Queso

            `queso` es una palabra reservada.

            El **queso** es un tipo que almacena un número entero con un rango de valores válidos que incluye al menos todos los valores comprendidos entre los números decimales −2147483648 y 2147483647, ambos inclusive (porque ese es el rango de un entero de 32 bits en C, y C nos gusta).  El rango específico es definido por la implementación.

            La especificación de tipo del queso es `queso`.

            Un literal entero especifica un valor cuyo tipo es el queso.

        4.  #### Papelón

            `papelón` es una palabra reservada.

            El **papelón** es un tipo que almacena un número de punto flotante con al menos la precisión y el rango de un `float` de 32 bits de C.  El rango específico es definido por la implementación.

            La especificación de tipo del papelón es `papelón`.

            Un literal de punto flotante especifica un valor de tipo papelón.  El valor de tipo papelón correspondiente a un literal de punto flotante es el valor más cercano representable en la implementación de valores de punto flotante, y si hay más de uno igualmente cercano, se toma el de menor valor absoluto.

            TODO: especificar bien la precisión (“hazlo como C” en este caso probablemente tiene tanto contenido semántico como “purple monkey dishwasher”); hablar, quizás, de ISO/IEC/IEEE 60559:2011

            TODO: overflow, underflow, NaN, infinitos, etc; y si el valor del literal se sale del rango del tipo?  Se toma el valor máximo finito, o infinito, o qué?  Es un error?  Un warning?  Nada?

    2.  ### Arepa

        La **arepa** es un tipo de tipos estructurados que asocian en un mismo ente a una cantidad *fija* de valores de otros tipos particulares en un orden específico.  Los tipos asociados por una arepa son sus **ingredientes**.  Los ingredientes de una arepa están implícitamente enumerados por enteros desde el cero en el orden en el que se especifican, y pueden tener opcionalmente un identificador asociado (su **nombre**).  Una arepa puede tener cualquier cantidad de ingredientes del mismo tipo, y cada uno es independiente de los demás.  Ningún par de ingredientes con nombre en una arepa puede compartir un mismo nombre.

        Un **literal de ingrediente** es una secuencia compuesta de una especificación de tipo, o una secuencia compuesta de un inicio de paréntesis, seguido de una especificación de tipo, seguido de un identificador, seguido de un fin de paréntesis.

        `arepa` es una palabra reservada.

        `viuda` es una palabra reservada.

        `de` es una palabra reservada.

        `con` es una palabra reservada.

        La especificación de tipo correspondiente a una arepa con cero ingredientes es `arepa` seguida de `viuda`.

        La especificación de tipo correspondiente a una arepa con exactamente un ingrediente es `arepa` seguida de `de`, a su vez seguida del literal de ingrediente correspondiente a su único ingrediente.

        Un **separador de lista** es un punto de código “COMMA” (U+002C, **,**).  Un separador de lista es un símbolo reservado si no ocurre dentro de un literal de cadena de caracteres, ni dentro de un comentario de línea, ni dentro de un comentario de bloque.

        `y` es una palabra reservada.

        La especificación de tipo correspondiente a una arepa con más de un ingrediente es `arepa` seguida de `con`, a su vez seguida de cada uno de los literales de ingrediente correspondientes a los ingredientes de la arepa desde el primero y exceptuando el último, siendo seguido cada literal de ingrediente por un separador de lista salvo por el penúltimo ingrediente de la arepa, todo seguido de `y` seguida del literal de ingrediente correspondiente al último ingrediente de la arepa.

        Por ejemplo, cada una de las siguientes líneas contiene una especificación de tipo válida para una arepa:

            arepa

            arepa de queso

            arepa con queso y café

            arepa con papelón, queso, café, café, café marrón, queso guayanés, arepa de arepa de arepa de arepa de arepa viuda ‹arepaception!›, caraota, arepa con papelón, café marrón y queso y queso

        Una **arepa rellena** es un valor de algún tipo de arepa.  Un **relleno** de una arepa rellena es cualquiera de los valores asociados por la arepa rellena.  Cada relleno de una arepa rellena corresponde a exactamente un ingrediente de la arepa correspondiente a la arepa rellena, y se puede identificar por el índice de su ingrediente correspondiente, o por su nombre, si existe.

    3.  ### Cachapa

        TODO: cachapas con arroz requieren tipos completos, no tipos

        La **cachapa** es un tipo de tipos unión que asocian en un mismo ente a exactamente *un* valor cuyo tipo puede ser alguno de un cierto conjunto de al menos dos elementos.  Los tipos asociados por una cachapa son sus **ingredientes**.  Los ingredientes de una cachapa están implícitamente enumerados por enteros desde el cero en el órden en el que se especifican, y pueden tener opcionalmente un identificador asociado.

        Una tajada no especifica cachapas donde exista algún par de ingredientes enumerados en su especificación que sean equivalentes.  Ningún par de ingredientes con nombre en una cachapa puede compartir un mismo nombre.

        La implementación puede definir un límite superior para el número de ingredientes de una cachapa; éste no debe ser menor que 256.

        `cachapa` es una palabra reservada.

        `o` es una palabra reservada.

        La especificación de tipo correspondiente a una cachapa es `cachapa` seguida de `con`, a su vez seguida de cada uno de los literales de ingrediente correspondientes a los ingredientes de la cachapa desde el primero y exceptuando el último, siendo seguido cada literal de ingrediente por un separador de lista salvo por el penúltimo ingrediente de la cachapa, todo seguido de `o` seguida del literal de ingrediente correspondiente al último ingrediente de la cachapa.

    4.  ### Arroz

        El **arroz** es un tipo de tipos de colección que asocian en un mismo ente a una cantidad fija de valores, todos de un mismo tipo (el tipo del **contenido** del arroz), y asocia a cada uno un número entero no negativo único entre ellos y menor que su cantidad (la **posición** de cada valor del arroz).  Dos arroces son equivalentes si sus tipos de contenido son equivalentes.

        `arroz` es una palabra reservada.

        La especificación de tipo correspondiente a un arroz es `arroz` seguida de `con`, a su vez seguida de la especificación de tipo correspondiente a su tipo de contenido.

        La **especificación completa de tipo** para un valor cuyo tipo sea un arroz es un literal entero seguido de `tazas`, seguida de `de`, seguida de `arroz`, seguida de `con`, seguida de la especificación completa del tipo de contenido del arroz.

        La cantidad de entes asociados por un arroz no es parte de su definición ni está asociada a él, pero sí es parte de la definición de sus valores.  El número de entes del tipo de contenido de su tipo que un valor de un arroz asocia es su **tamaño**.  El tamaño de un valor de un arroz es inmutable.

3.  ## Estructura

    Una tajada es una secuencia compuesta de una secuencia de cero o más declaraciones de dulces, definiciones de variables, y declaraciones y definiciones de platos y cubiertos, seguida de un bloque.

    1.  ### Declaraciones

        Las **declaraciones** son asociaciones entre un tipo y un identificador.

        1.  #### Dulces

            `es` es una palabra reservada.

            `dulce` es una palabra reservada.

            Un **terminador de frase** es un punto de código “FULL STOP” (U+002E, **.**) que no ocurra dentro de un literal de cadena de caracteres, ni dentro de un escapado de caracter, ni de un espacio en blanco.  Un terminador de frase es un símbolo reservado.

            Una **declaración de dulce** es una especificación de tipo (su **tipo**), seguida de `es`, seguida de `dulce`, seguida de `de`, seguida de un identificador (su **nombre**), seguido de un terminador de frase.

            Un **dulce** es una identificación entre un tipo y un identificador.  Cuando se ha declarado un dulce con un cierto tipo y un cierto identificador, puede sustituirse a partir de ese punto de la tajada cualquier ocurrencia de la especificación de ese tipo por el identificador asociado con el dulce.  En otras palabras, un dulce define un nombre alternativo para un tipo, y su único propósito es permitir al programador agregar a gusto azucar sintáctica a su tajada.

            Una tajada nunca tiene dos declaraciones de dulces para el mismo identificador.

        2.  #### Platos

            Un **plato** es una función que tiene asociado un identificador específico, recibe entes de algún tipo específico, ejecuta una secuencia de instrucciones en orden, y produce un resultado de un tipo específico.  Una tajada no tiene más de un plato asociado a un mismo identificador y a tipos equivalentes de entes recibidos y producidos, pero puede tener más de un plato asociado a un mismo identificador, o más de un plato asociado a tipos equivalentes de entes recibidos y/o producidos.

            `un` es una palabra reservada.

            `plato` es una palabra reservada.

            `salsa` es una palabra reservada.

            Una **especificación de plato** es una secuencia compuesta por un identificador (el **nombre**), seguido de una `es`, seguido de una `un`, seguido de una `plato`, seguido de una `de`, seguido de una especificación de tipo (el **dominio** del plato) opcionalmente seguida de un identificador (el **nombre del dominio**), seguidos de una `con`, seguida de una `salsa`, seguida de una `de`, seguida de una especificación de tipo (el **rango** del plato).

            Una **declaración de plato** es una especificación de plato seguida de un terminador de frase.  Una declaración de plato hace que ese plato se considere declarado desde el punto en el que aparece en la tajada con el identificador y los tipos usados en su especificación de plato.

        3.  #### Cubiertos

            Un **cubierto** es una función que tiene asociado un operador específico, recibe entes de algún tipo específico, ejecuta una secuencia de instrucciones en orden, y produce un resultado de un tipo específico.  Una tajada no tiene más de un cubierto asociado a un mismo símbolo reservado y a tipos equivalentes de entes recibidos y producidos, pero puede tener más de un cubierto asociado a un mismo identificador, o más de un cubierto asociado a tipos equivalentes de entes recibidos y/o producidos.

            `hay` es una palabra reservada.

            `cubierto` es una palabra reservada.

            `para` es una palabra reservada.

            Una **especificación de cubierto** es una secuencia compuesta por una `hay`, seguida de una `un`, seguida de una `cubierto`, seguida de un operador, seguido de una `para`, seguida de una especificación de tipo (el *dominio* del cubierto), seguida de una `y`, seguida de una `salsa`, seguida de una `de`, seguida de una especificación de tipo (el *rango* del cubierto).

            Una **declaración de cubierto** es una especificación de cubierto seguida de un terminador de frase.  Una declaración de cubierto hace que ese cubierto se considere declarado desde el punto en el que aparece en la tajada con el operador y los tipos usados en su especificación de cubierto.

            Si a un cubierto se le asocia un operador y su dominio es una arepa con un solo ingrediente, el operador debe ser unario, y se dice que el cubierto es unario.  Si a un cubierto se le asocia un operador y su dominio es una arepa con exactamente dos ingredientes, el operador debe ser binario, y se dice que el cubierto es binario.  Una tajada no define cubiertos cuyo dominio no sea una arepa con exactamente uno o dos ingredientes.

    2.  ### Definiciones

        1.  #### Variables

            `tazas` es una palabra reservada.

            La especificación completa de tipo de cualquier tipo que no haga referencia a otros tipos es su especificación de tipo.  La especificación completa de tipo de una arepa o cachapa es de la misma forma que su especificación de tipo, pero en vez de escribirse la especificación de tipo de sus ingredientes, se escriben sus especificaciones completas de tipo.

            Una **definición de variable** es una secuencia compuesta por un identificador (su **nombre**), una `es`, una especificación completa de tipo (su **tipo**) y un terminador de frase.  Una definición de variable establece la existencia de una variable con ese nombre y ese tipo; por ejemplo,

                telita es queso.

            define una variable llamada `telita` de tipo `queso`.  La variable es un ente que almacena un **valor** del tipo de su definición y tiene asociado el nombre de su definición.

            Una tajada no define más de una variable con un mismo nombre fuera de un bloque.

            Una tajada no define ninguna variable cuyo nombre sea igual al de algún dulce.

            El valor almacenado por una variable es indefinido desde su definición hasta que se le asigne un valor en una asignación.  El comportamiento de una tajada es indefinido si utiliza un valor indefinido.  La implementación está en libertad de asignar un valor por defecto a la variable al definirla, reportar un error, hacer explotar al disco duro, invocar a Beelzebub, o hacer cualquier otra cosa.

        2.  #### Platos

            Una **definición de plato** es una especificación de plato seguida de un bloque.

            Si una tajada contiene una declaración de plato, debe contener también una definición para ese mismo plato (con el mismo nombre y dominios y rangos equivalentes pero ignorando el identificador opcional asociado al dominio).

            Un plato se puede definir a lo sumo una vez en una tajada.

        3.  #### Cubiertos

            Una **definición de cubierto** es una especificación de cubierto seguida de un bloque.

            Si una tajada contiene una declaración de cubierto, debe contener también una definición para ese mismo cubierto (con el mismo operador y dominio y rango equivalentes pero ignorando el identificador opcional asociado al dominio).

            Un cubierto se puede definir a lo sumo una vez en una tajada.

    3.  ### Bloques

        Un **inicio de bloque** es un punto de código “LEFT CURLY BRACKET” (U+007B, **{**) que no ocurra dentro de un literal de cadena de caracteres, ni de un escapado de caracter, ni de un espacio en blanco.  Un inicio de bloque es un símbolo reservado.

        Un **fin de bloque** es un punto de código “RIGHT CURLY BRACKET” (U+007D, **{**) que no ocurra dentro de un literal de cadena de caracteres, ni de un escapado de caracter, ni de un espacio en blanco.  Un fin de bloque es un símbolo reservado.

        Un **bloque** es un inicio de bloque, seguido de una secuencia de cero o más definiciones de variables, instrucciones o bloques, seguida de un fin de bloque.

        Una tajada no define más de una variable con un mismo nombre en un mismo bloque.

        [Nota: Es posible definir una variable en un bloque, y ese bloque puede contener a otro bloque que podría definir a otra variable con el mismo nombre que la primera.  Decir que una variable se define en un bloque significa que la definición de esa variable está directamente en él, y no en algún otro bloque contenido en él directa o indirectamente. —fin de la nota]

    4.  ### Expresiones

        Una **expresión** es una secuencia de símbolos y símbolos reservados que representa el cálculo de un valor y tiene una cierta estructura.  Una expresión tiene asociado un tipo que se infiere de su estructura, y es el mismo tipo del valor asociado a la expresión.

        1.  #### Literales

            1.  ##### Escalares

                Un literal de cadena de caracteres es una expresión, y su tipo es el especificado por `arroz con caraota`.  Por esto, también se denominarán **literales de arroz con caraota**.  El valor de un literal de arroz con caraota es un arroz cuyo tipo de contenido es la caraota y cuyo tamaño no es menor que el número de puntos de código especificados por el literal de arroz con caraota.

                Un literal de café es una expresión cuyo tipo es el café y cuyo valor es aquel que el literal de café representa.

                Un literal de caraota es una expresión cuyo tipo es la caraota y cuyo valor es el último punto de código que conforme al literal de caraota.

                Un literal entero es una expresión cuyo tipo es el queso y cuyo valor es el valor de tipo queso especificado por el literal entero.

                Un literal de papelón es una expresión cuyo tipo es el papelón y cuyo valor es el especificado por el literal de papelón.

            2.  ##### Estructurados

                Un **inicio de literal estructurado** es un punto de código “LEFT-POINTING DOUBLE ANGLE QUOTATION MARK” (U+00AB, **«**) que no ocurra dentro de un literal de cadena de caracteres, dentro de un escapado de caracter, ni dentro de un espacio en blanco.  Un inicio de literal estructurado es un símbolo reservado.

                Un **fin de literal estructurado** es un punto de código “RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK” (U+00BB, **»**) que no ocurra dentro de un literal de cadena de caracteres, dentro de un escapado de caracter, ni dentro de un espacio en blanco.  Un fin de literal estructurado es un símbolo reservado.

                Un **indicador de etiqueta** es un punto de código “LEFTWARDS ARROW” (U+2190, **←**) que no ocurra dentro de un literal de cadena de caracteres, dentro de un escapado de caracter, ni dentro de un espacio en blanco.  Un indicador de etiqueta es un símbolo reservado.

                Un **literal de arepa rellena** es una secuencia compuesta de un inicio de literal estructurado, seguido de una lista de cero o más expresiones separadas por separadores de lista, cada una de las cuales puede opcionalmente estar seguida de un indicador de etiqueta seguido de un identificador, y todo finalizado con un fin de literal estructurado.

                Un literal de arepa rellena es una expresión cuyo tipo es una arepa cuyos ingredientes son los tipos de las expresiones sucesivas del literal de arepa rellena en el mismo orden de aparición y, si en alguna de ellas ocurre el identificador opcional, su correspondiente ingrediente tendrá ese identificador como nombre.  El valor de un literal de arepa rellena es una arepa rellena de su tipo, y los valores de sus rellenos son los valores de sus expresiones correspondientes.

                TODO: ¿literales de arroz?  ¿literales de cachapa?

        2.  #### Platos

            Un **indicador de referencia** es un punto de código “AMPERSAND” (U+0026, **&**) que no ocurra dentro de un literal de cadena de caracteres, un escapado de caracter o un espacio en blanco.  Un indicador de referencia es un símbolo reservado.

            Un **literal condimentado de arepa rellena** es una secuencia compuesta de un inicio de literal estructurado, seguido de una lista de cero o más expresiones separadas por separadores de lista, cada una de las cuales puede opcionalmente estar seguida de un indicador de etiqueta seguido de un identificador, y también puede opcionalmente estar precedida de un indicador de referencia, y todo finalizado con un fin de literal estructurado.  La **arepa asociada** a un literal condimentado de arepa rellena es el tipo de la arepa rellena que resultaría de escribir el literal condimentado de arepa rellena sin indicadores de referencia.

            Un **argumento** es una secuencia compuesta de una expresión opcionalmente precedida de un indicador de referencia (en cuyo caso su **tipo** es el tipo de la expresión), o un literal condimentado de arepa rellena (en cuyo caso su tipo es la arepa asociada al literal condimentado de arepa rellena).

            Un **indicador de llamada** es un punto de código “COMMERCIAL AT” (U+0040, **@**) que no ocurra dentro de un literal de cadena de caracteres, un escapado de caracter o un espacio en blanco.  Un indicador de llamada es un símbolo reservado.

            Con cada plato declarado se pueden construir **expresiones de plato**, que son expresiones, con el identificador del plato, seguido de un indicador de llamada, seguido de un argumento cuyo tipo sea equivalente al del dominio del plato.

            El tipo de una expresión de plato es el rango del plato.

            TODO: ¿cuál es el valor?  ¿cómo se evalúa un plato?  ¿cómo se describe formalmente la ejecución de un procedimiento que toma parámetros (por valor y/o por referencia) y produce un resultado? :(

        3.  #### Cubiertos

            TODO: más operadores!  Pero ¿cuáles?  Algún otro unario, al menos!

            1. ##### Unarios

                Un **operador unario** es cualquiera de los siguientes símbolos reservados.

                1.  Un **operador de resta** es un punto de código “MINUS SIGN” (U+2212, **−**) que no ocurra dentro de un literal de cadena de caracteres, un escapado de caracter o un espacio en blanco.

                Si existe un cubierto declarado para un cierto operador unario, entonces se puede construir una expresión con el operador seguido de una expresión cuyo tipo sea equivalente al del ingrediente de la arepa del dominio del operador.  El tipo de la expresión resultante es el tipo del rango del cubierto.  El valor de la expresión será el valor de la evaluación del cubierto al pasarle como parámetro una arepa rellena cuyo único relleno sea el valor de la expresión.

                TODO: ¿cuál es el valor?  ¿cómo se evalúa un cubierto?  ¿cómo se describe formalmente la ejecución de un procedimiento que toma parámetros (por valor y/o por referencia) y produce un resultado? :(

            2. ##### Binarios

                Un **operador binario** es cualquiera de los siguientes símbolos reservados.

                1.  Un operador de resta.

                2.  Un **operador de suma**, que es un punto de código “PLUS SIGN” (U+002B, **+**) que no ocurra dentro de un literal de cadena de caracteres, un escapado de caracter o un espacio en blanco.

                3.  Un **operador de multiplicación**, que es un punto de código “MULTIPLICATION SIGN” (U+00D7, **×**) que no ocurra dentro de un literal de cadena de caracteres, un escapado de caracter o un espacio en blanco.

                4.  Un **operador de división**, que es un punto de código “DIVISION SIGN” (U+00F7, **÷**) que no ocurra dentro de un literal de cadena de caracteres, un escapado de caracter o un espacio en blanco.

                5.  Un **operador de módulo**, que es un punto de código “TILDE” (U+007E, **\~**) que no ocurra dentro de un literal de cadena de caracteres, un escapado de caracter o un espacio en blanco.

                6.  Un **operador de igualdad**, que es un punto de código “EQUALS SIGN” (U+003D, **=**) que no ocurra dentro de un literal de cadena de caracteres, un escapado de caracter o un espacio en blanco.

                7.  Un **operador de no‐igualdad**, que es un punto de código “NOT EQUAL TO” (U+2260, **≠**) que no ocurra dentro de un literal de cadena de caracteres, un escapado de caracter o un espacio en blanco.

                Con cada cubierto declarado para un operador binario se pueden construir **expresiones de operador binario infijo**, que son expresiones, con un argumento cuyo tipo sea equivalente al del primer ingrediente del dominio del cubierto, seguido del operador del cubierto, seguido de un argumento cuyo tipo sea equivalente al del segundo ingrediente del dominio del cubierto.

                Con cada cubierto declarado para un operador binario se pueden construir **expresiones de operador binario prefijo**, que son expresiones, con un inicio de paréntesis, seguido por el operador del cubierto, seguido por un fin de paréntesis, seguido por un argumento cuyo tipo sea equivalente al del primer ingrediente del dominio del cubierto, seguido de un argumento cuyo tipo sea equivalente al del segundo ingrediente del dominio del cubierto.

                En ambos casos, el tipo de la expresión resultante es el tipo del rango del cubierto, y el valor de la expresión será el valor de la evaluación del cubierto al pasarle como parámetro una arepa rellena cuyos primer y segundo rellenos sean los valores del primero y el segundo argumento, respectivamente.

                TODO: pasaje por referencia

                TODO: ¿cuál es el valor?  ¿cómo se evalúa un cubierto?  ¿cómo se describe formalmente la ejecución de un procedimiento que toma parámetros (por valor y/o por referencia) y produce un resultado? :(

        4.  #### Variables

            Una variable es **alcanzable** en una instrucción en los siguientes casos.

            *   La definición de la variable está en el mismo bloque que la instrucción, y ocurre antes de la instrucción.

            *   El bloque en el que está la instrucción no define ninguna variable con el nombre de la variable de interés, pero el bloque está contenido directamente en otro bloque en el que la variable sería alcanzable si ocurriera una instrucción en el lugar donde aparece el bloque en el que está la instrucción de interés.

            Se puede construir una expresión con el nombre de una variable alcanzable.  Su tipo es el tipo de la variable y su valor es el valor de la variable.

        5.  #### Otras

            Un **inicio de paréntesis** es un punto de código “LEFT PARENTHESIS” (U+0028, **(**) que no ocurra dentro de un literal de cadena de caracteres, dentro de un escapado de caracter, ni dentro de un espacio en blanco.  Un inicio de paréntesis es un símbolo reservado.

            Un **fin de paréntesis** es un punto de código “RIGHT PARENTHESIS” (U+0029, **)**) que no ocurra dentro de un literal de cadena de caracteres, un escapado de caracter o un espacio en blanco.  Un fin de paréntesis es un símbolo reservado.

            Se puede construir una expresión con un inicio de paréntesis, seguido de una expresión, seguida de un fin de paréntesis.  El tipo de la expresión es el tipo de la expresión y el valor de la expresión es el valor de la expresión. [Nota: Tenga cuidado de no confundir a la expresión con la expresión —fin de la nota]

            Un **indicador de acceso a arepa** es un punto de código “RIGHTWARDS ARROW” (U+2192, **→**) que no ocurra dentro de un literal de cadena de caracteres, dentro de un escapado de caracter, ni dentro de un espacio en blanco.  Una flecha es un símbolo reservado.

            Un **acceso a arepa** es una expresión compuesta de una expresión (la **fuente**) cuyo tipo sea una arepa, seguida de un indicador de acceso a arepa, seguido de un literal entero que corresponda al número o un identificador que corresponda al nombre de algún ingrediente, el **ingrediente accedido**, del tipo de la expresión.  El tipo de un acceso a arepa es el ingrediente accedido de su fuente.  El valor de un acceso a arepa es el relleno del valor de la fuente identificado por el literal entero o el identificador usado en el acceso a arepa.

            Un **inicio de acceso a arroz** es un punto de código “LEFT SQUARE BRACKET” (U+005B, **\[**) que no ocurra dentro de un literal de cadena de caracteres, dentro de un escapado de caracter, ni dentro de un espacio en blanco.  Un inicio de acceso a arroz es un símbolo reservado.

            Un **fin de acceso a arroz** es un punto de código “RIGHT SQUARE BRACKET” (U+005D, **\]**) que no ocurra dentro de un literal de cadena de caracteres, dentro de un escapado de caracter, ni dentro de un espacio en blanco.  Un fin de acceso a arroz es un símbolo reservado.

            Un **acceso a arroz** es una expresión compuesta de una expresión (la **fuente**) cuyo tipo sea un arroz, seguida de un inicio de acceso a arroz, seguido de una expresión (la **posición accedida**) cuyo tipo sea el queso, seguida de un fin de acceso a arroz.  El tipo de un acceso a arroz es el tipo del contenido de su fuente.  El valor de un acceso a arroz es el valor del valor de la fuente cuya posición sea el valor de la posición accedida.

            Un **separador de lista de expresiones** es un punto de código “SEMICOLON” (U+003B, **;**) que no ocurra dentro de un literal de cadena de caracteres, dentro de un escapado de caracter, ni dentro de un espacio en blanco.  Un separador de lista de expresiones es un símbolo reservado.

            Se puede construir una expresión con una secuencia de dos o más expresiones separadas por separadores de lista de expresiones.  El valor y el tipo de la expresión son los de la última de la lista.  Las acciones de las expresiones se efectúan en secuencia: se terminan de efectuar todas las acciones de una expresión de la lista antes de comenzar a efectuar las acciones de la siguiente expresión, y el valor de la expresión completa se considera calculado luego de efectuar las acciones de todas las expresiones de la lista..

            TODO: inline if

            TODO: precedencias

    5.  ### Instrucciones

        Una **instrucción** es una secuencia de símbolos y símbolos reservados que representa una acción y tiene una cierta estructura.  Las instrucciones se ejecutan en secuencia, y al ejecutarse tienen ciertos efectos sobre el estado manejado por la ejecución de una tajada.

        Los efectos de una instrucción sobre el estado manejado por la ejecución de una tajada y su entorno de ejecución se realizan completamente antes del comienzo de la ejecución de otra instrucción.  Si no se especifica explícitamente, el orden en el que se efectúan las acciones de una instrucción es indefinido.  Por ejemplo:

            telita es queso.

            pabellón es un plato de arepa viuda con salsa de arepa viuda {
                telita ≔ telita + 1.
                retorna «».
            }

            chupe es un plato de arepa viuda con salsa de arepa viuda {
                telita ≔ telita × 2.
                retorna «».
            }

        Si el anterior fragmento de tajada es seguido del bloque

            {
                telita ≔ 0.
                pabellón «».
                chupe    «».
            }

        entonces la variable “telita” habrá tenido los valores `0`, `1` y `2`, en ese orden, a lo largo de la ejecución de la tajada, porque las instrucciones se ejecutan una después de otra en el orden definido por el bloque en el que aparecen.  Sin embargo, si el mismo fragmento de tajada es seguido por el bloque

            {
                telita ≔ 0.
                «pabellón «», chupe «»».
            }

        entonces el comportamiento de esa tajada es indefinido, porque en este caso no se define orden alguno para efectuar las acciones de los dos platos.  La implementación está en libertad de seleccionar un orden de evaluación, reportar un error, hacer explotar al disco duro, liberar a Cthulhu, o hacer cualquier otra cosa.

        1.  #### Simples

            Una expresión seguida de un terminador de frase es una instrucción.

            Una **ubicación** es un tipo particular de expresión que representa a un ente que almacena información que puede ser modificada por la ejecución de una tajada.  Cada ubicación tiene asociado un **tipo*, que es el mismo que tendría si se tratara como expresión, y un **espacio**, que es el ente que almacena un valor de ese tipo.

            Se puede construir una ubicación con el nombre de una variable alcanzable.  El espacio de este tipo de ubicación es la variable.

            Un acceso a arepa es una ubicación si su fuente es una ubicación; en ese caso, su espacio es el ente que almacena su relleno accedido.

            Un acceso a arroz es una ubicación si su fuente es una ubicación; en ese caso, su espacio es el ente que almacena el ente de su fuente cuya posición sea el valor de la posición accedida.

            Un **indicador de asignación** es un punto de código “COLON EQUALS” (U+2254, **≔**) que no ocurra dentro de un literal de cadena de caracteres, un escapado de caracter o un espacio en blanco.  Un indicador de asignación es un símbolo reservado.

            Una **asignación** es una secuencia compuesta de una ubicación, seguida de un indicador de asignación, seguida de una expresión cuyo tipo sea equivalente al tipo de la ubicación, seguida de un terminador de frase.  Una asignación es una instrucción.

            La acción especificada por una asignación es efectuar las acciones indicadas por la expresión, y luego almacenar su valor en la ubicación.

        2.  #### Estructuras de control

            1.  ##### Selección simple

                `if` es una palabra reservada.

                `else` es una palabra reservada.

                Una **instrucción de selección** es una `if`, seguida de un inicio de paréntesis, seguida de una expresión (la **condición**) cuyo tipo sea el café, seguida de un fin de paréntesis, seguida de un bloque o una instrucción (el **cuerpo positivo**), opcionalmente seguido por una `else` seguida de un bloque o una instrucción (el **cuerpo negativo**).  Una instrucción de selección es una instrucción.

                La acción especificada por una instrucción de selección es efectuar las acciones indicadas por la condición, y si su valor es verdadero, efectuar las acciones indicadas por el cuerpo positivo, y en el caso contrario, si existe, efectuar las acciones indicadas por el cuerpo negativo.

            2.  ##### Iteración condicionada

                `while` es una palabra reservada.

                Una **iteración condicionada** es una `while`, seguida de un inicio de paréntesis, seguida de una expresión (la **condición**) cuyo tipo sea el café, seguida de un fin de paréntesis, seguida de un bloque o una instrucción (el **cuerpo**).  Una iteración condicionada es una instrucción.

                La acción especificada por una iteración condicionada es efectuar las acciones indicadas por la condición, y si su valor es verdadero, efectuar las acciones indicadas por el cuerpo y repetir el proceso.

                TODO: break, continue

            3.  ##### Iteración controlada

                `for` es una palabra reservada.

                `in` es una palabra reservada.

                Un **separador de rango** es un punto de código “HORIZONTAL ELLIPSIS” (U+2026, **…**) que no ocurra dentro de un literal de cadena de caracteres, dentro de un escapado de caracter, ni dentro de un espacio en blanco.  Un separador de rango es un símbolo reservado.

                Una **iteración controlada** es una `for`, seguida de un identificador (el **nombre del contador**), seguido de una `in`, seguida de un inicio de paréntesis, seguido de una expresión (el **inicio**) cuyo tipo sea el queso, seguida de un separador de rango, seguida de una expresión (el **fin**) cuyo tipo sea el queso, seguida de un fin de paréntesis, seguida de un bloque o una instrucción (el **cuerpo**).  Una iteración controlada es una instrucción.

                En el cuerpo de una iteración controlada es alcanzable una variable (el **contador**) cuyo tipo es el queso y cuyo nombre es el nombre del contador como si al inicio del bloque se hubiera escrito su definición, y si no había un bloque sino una instrucción, lo mismo aplica como si la instrucción hubiera estado sola en un bloque.

                La acción especificada por una iteración controlada es efectuar las acciones indicadas por el inicio, efectuar las acciones indicadas por el fin, y luego, para cada entero desde el valor del inicio hasta el valor del fin, inclusive el primero y no inclusive el segundo, y en ese orden, almacenar ese entero en el contador y efectuar las acciones de la instrucción o el bloque.

            4.  ##### Selección por tipo

                TODO: case of para cachapas

4.  ## Librería

    Tajada cuenta con ciertos platos y cubiertos predefinidos automáticamente que realizan operaciones básicas sobre los datos manejados por el lenguaje.  Un **plato predefinido** y un **cubierto predefinido** es un plato o un cubierto cuya declaración y definición están dadas implícitamente en toda tajada sin tener que escribirse en su texto para poder usarse.

    La definición de estos platos y cubiertos no necesariamente existe ni es necesariamente posible de escribirla directamente en Tajada.  La implementación deberá ejecutar sus efectos y retornar sus resultados como si existieran sus declaraciones y definiciones como para cualquier plato o cubierto declarado y definido explícitamente en una tajada.

    Cada especificación de un plato o cubierto predefinido en este documento proveerá una posible declaración junto con una breve descripción de su semántica.  La implementación debe proveer todos estos platos y cubiertos predefinidos, y puede proveer otros que no estén enumerados en este documento.

    1.  ### Operaciones numéricas

        1.  `hay un cubierto + para arepa con queso y queso y salsa de queso.`

            Retorna la suma de dos valores.

            TODO: overflow

        2.  `hay un cubierto − para arepa con queso y queso y salsa de queso.`

            Retorna la resta del primer valor menos el segundo.

            TODO: overflow

        2.  `hay un cubierto − para arepa de queso y salsa de queso.`

            Retorna el inverso aditivo del valor.

            TODO: overflow

        3.  `hay un cubierto × para arepa con queso y queso y salsa de queso.`

            Retorna la multiplicación de los valores.

            TODO: overflow

        4.  `hay un cubierto ÷ para arepa con queso y queso y salsa de queso.`

            Retorna el resultado de la división entera del primer valor entre el segundo.

            TODO: zero division

        5.  `hay un cubierto ~ para arepa con queso y queso y salsa de queso.`

            Retorna el resto de la división entera del primer valor entre el segundo.

            TODO: zero division

        6.  `hay un cubierto = para arepa con queso y queso y salsa de café.`

            Retorna `tetero` si los valores son iguales y `negrito` si no.

        7.  `hay un cubierto ≠ para arepa con queso y queso y salsa de café.`

            Retorna `negrito` si los valores son iguales y `tetero` si no.

        TODO: escribir los otros 98237509873093725092375 que hacen falta para que los tipos del lenguaje sirvan de algo

* * *

Nota histórica
--------------

La idea original era hacer un lenguaje con operaciones relacionales y salió de [las observaciones de Matthew Might sobre la similitud de muchos componentes de scripts de UNIX con operadores relacionales][L1].  Sin embargo, esto requeriría manejar memoria dinámicamente y eso escapa el alcance y los objetivos del curso, así que simplificamos el alcance de nuestra idea al manejo de tuplas individuales.  La sintaxis relacional estaba ~~siendo copiada descaradamente de~~inspirada en [esta información sobre un lenguaje de consultas llamado ISBL][L2].  Escribimos algunos [trozos de código][L3] basados en esa idea.

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

*   Convertir esta porquería a LaTeX.

*   Verificar la numeración de todo.

*   Arreglar el desastre del pasaje por referencia.

*   Hacer que haya correspondencia entre lo implementado y lo que dice acá.  Seguro que corriendo para la primera entrega hubo cambios que no volvieron a la especificación. :(

*   Especificar el pasaje de parámetros y el retorno de valores… y definir la instrucción de retorno.  Oops.

*   ¿En algún momento se definió lo que son “valores” y un “tipo”?

    ¿Debería también definir lo que es un lenguaje, un número, una palabra, definir, existir?

    ¿Cómo se describe algo formalmente sin excesos absurdos de formalidad?  Los del JTC1/SC22 saben…

*   Hacer consistente la definición de símbolos reservados que no estén en espacios en blanco ni escapados ni strings.

*   Agregar ejemplos a todo.

*   Términos por asignar:

    *   carne mechada
