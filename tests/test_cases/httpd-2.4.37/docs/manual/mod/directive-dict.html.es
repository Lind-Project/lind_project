<?xml version="1.0" encoding="ISO-8859-1"?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="es" xml:lang="es"><head>
<meta content="text/html; charset=ISO-8859-1" http-equiv="Content-Type" />
<!--
        XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
              This file is generated from xml source: DO NOT EDIT
        XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
      -->
<title>T�rminos que se Usan para Describir Directivas - Servidor HTTP Apache Versi�n 2.4</title>
<link href="../style/css/manual.css" rel="stylesheet" media="all" type="text/css" title="Main stylesheet" />
<link href="../style/css/manual-loose-100pc.css" rel="alternate stylesheet" media="all" type="text/css" title="No Sidebar - Default font size" />
<link href="../style/css/manual-print.css" rel="stylesheet" media="print" type="text/css" /><link rel="stylesheet" type="text/css" href="../style/css/prettify.css" />
<script src="../style/scripts/prettify.min.js" type="text/javascript">
</script>

<link href="../images/favicon.ico" rel="shortcut icon" /></head>
<body id="manual-page"><div id="page-header">
<p class="menu"><a href="../mod/">M�dulos</a> | <a href="../mod/directives.html">Directivas</a> | <a href="http://wiki.apache.org/httpd/FAQ">Preguntas Frecuentes</a> | <a href="../glossary.html">Glosario</a> | <a href="../sitemap.html">Mapa del sitio web</a></p>
<p class="apache">Versi�n 2.4 del Servidor HTTP Apache</p>
<img alt="" src="../images/feather.png" /></div>
<div class="up"><a href="./"><img title="&lt;-" alt="&lt;-" src="../images/left.gif" /></a></div>
<div id="path">
<a href="http://www.apache.org/">Apache</a> &gt; <a href="http://httpd.apache.org/">Servidor HTTP</a> &gt; <a href="http://httpd.apache.org/docs/">Documentaci�n</a> &gt; <a href="../">Versi�n 2.4</a></div><div id="page-content"><div id="preamble"><h1>T�rminos que se Usan para Describir Directivas</h1>
<div class="toplang">
<p><span>Idiomas disponibles: </span><a href="../en/mod/directive-dict.html" hreflang="en" rel="alternate" title="English">&nbsp;en&nbsp;</a> |
<a href="../es/mod/directive-dict.html" title="Espa�ol">&nbsp;es&nbsp;</a> |
<a href="../fr/mod/directive-dict.html" hreflang="fr" rel="alternate" title="Fran�ais">&nbsp;fr&nbsp;</a> |
<a href="../ja/mod/directive-dict.html" hreflang="ja" rel="alternate" title="Japanese">&nbsp;ja&nbsp;</a> |
<a href="../ko/mod/directive-dict.html" hreflang="ko" rel="alternate" title="Korean">&nbsp;ko&nbsp;</a> |
<a href="../tr/mod/directive-dict.html" hreflang="tr" rel="alternate" title="T�rk�e">&nbsp;tr&nbsp;</a></p>
</div>

    <p>Este documento describe los t�rminos que se usan para describir
    cada <a href="directives.html">directiva de configuraci�n</a> de
    Apache.</p>
</div>
<div id="quickview"><a href="https://www.apache.org/foundation/contributing.html" class="badge"><img src="https://www.apache.org/images/SupportApache-small.png" alt="Support Apache!" /></a><ul id="toc"><li><img alt="" src="../images/down.gif" /> <a href="#Description">Descripci�n</a></li>
<li><img alt="" src="../images/down.gif" /> <a href="#Syntax">Sintaxis</a></li>
<li><img alt="" src="../images/down.gif" /> <a href="#Default">Por defecto</a></li>
<li><img alt="" src="../images/down.gif" /> <a href="#Context">Contexto</a></li>
<li><img alt="" src="../images/down.gif" /> <a href="#Override">Override</a></li>
<li><img alt="" src="../images/down.gif" /> <a href="#Status">Estado</a></li>
<li><img alt="" src="../images/down.gif" /> <a href="#Module">M�dulo</a></li>
<li><img alt="" src="../images/down.gif" /> <a href="#Compatibility">Compatibilidad</a></li>
</ul><h3>Consulte tambi�n</h3><ul class="seealso"><li><a href="../configuring.html">Ficheros de Configuraci�n</a></li><li><a href="#comments_section">Comentarios</a></li></ul></div>
<div class="top"><a href="#page-header"><img alt="top" src="../images/up.gif" /></a></div>
<div class="section">
<h2><a name="Description" id="Description">Descripci�n</a></h2>

    <p>Una breve descripci�n del prop�sito de la directiva.</p>
</div><div class="top"><a href="#page-header"><img alt="top" src="../images/up.gif" /></a></div>
<div class="section">
<h2><a name="Syntax" id="Syntax">Sintaxis</a></h2>

    <p>Indica el formato de la directiva tal y como aparecer�a en un fichero de 
    configuraci�n. Esta sintaxis es muy espec�fica de cada directiva, y se 
    describe con detalle en la definici�n de la directiva. Generalmente, el 
    nombre de la directiva va seguido de una serie de uno o m�s par�metros 
    separados por un espacio. Si un par�metro contiene un espacio, �ste debe 
    especificarse entre comillas dobles. Los par�metros opcionales van 
    especificados entre corchetes. Donde un par�metro puede tener uno o m�s 
    valores, los valores posibles se separan con barras verticales "|". El Texto
    Literal se muestra con la fuente por defecto, mientras que los distintos 
    tipos de par�metros para los que una sustituci�n resulta necesaria son 
    <em>enfatizados</em>. Las directivas que pueden tomar una lista variada de 
    par�metros acaban en "..." indicando que el �ltimo par�metro se repite.</p>

    <p>Las Directivas usan un gran n�mero de diferentes tipos de par�metros. A 
    continuaci�n definimos algunos de los m�s comunes.</p>

    <dl>
      <dt><em>URL</em></dt>
      <dd>Un Localizador de Recursos Uniforme, incluye un esquema,
		  nombre de host, y un path opcional como en
      <code>http://www.example.com/path/to/file.html</code></dd>

      <dt><em>Ruta de URL</em></dt>
      <dd>La parte de una <em>url</em> que sigue al esquema y el
		  nombre de host como en <code>/path/to/file.html</code>. El
      <em>url-path</em> representa una vista-web de un recurso, en
      contraposici�n a una vista de sistema-de-ficheros.</dd>

      <dt><em>Ruta del Fichero</em></dt>
      <dd>La ruta a un fichero en el sistema de ficheros local que
		  comienza desde el directorio ra�z como en
      <code>/usr/local/apache/htdocs/path/to/file.html</code>.
      A menos que se especifique, una <em>ruta de fichero</em> que no comienza
      con una barra "/" se tratar� como una ruta relativa a <a href="core.html#serverroot">ServerRoot</a>.</dd>

      <dt><em>Ruta del Directorio</em></dt>

      <dd>La ruta a un directorio en el sistema de ficheros local que
      comienza con el directorio r�iz como en
      <code>/usr/local/apache/htdocs/path/to/</code>.</dd>

      <dt><em>Nombre del Fichero</em></dt>

      <dd>El nombre de un fichero sin ir acompa�ado de informaci�n de la ruta
      como en <code>file.html</code>.</dd>

      <dt><em>regex</em></dt>

      <dd>Una <a class="glossarylink" href="../glossary.html#regex" title="ver glosario">
      expresi�n regular</a> compatible con Perl. La definici�n
      de directiva especificar� contra qu� se compara la
      <em>regex</em>.</dd>

      <dt><em>extensi�n</em></dt>

      <dd>En general, esta es la parte del <em>nombre de fichero</em>
      que sigue al �ltimo punto. Sin embargo, Apache reconoce m�ltiples
      extensiones de fichero, as� que si un <em>nombre de fichero</em>
      contiene m�s de un punto, cada parte separada por un punto del
      nombre de fichero despu�s del primer punto es una <em>extensi�n</em>.
      Por ejemplo, el <em>nombre de fichero</em> <code>file.html.en</code>
      contiene dos extensiones: <code>.html</code> y
      <code>.en</code>. Para las directivas de Apache, podr� especificar
      la <em>extensiones</em> con o sin el punto inicial. Adem�s, las 
      <em>extensiones</em> no son sensibles a may�sculas o min�sculas.</dd>

      <dt><em>Tipo MIME</em></dt>

      <dd>Un m�todo de describir el formato de un fichero que est� formado
      por un tipo de formato mayor y un tipo de formato menor, separados de
      de una barra como en <code>text/html</code>.</dd>

      <dt><em>Variable de Entorno</em></dt>

      <dd>El nombre de una <a href="../env.html">variable de entorno</a>
      definida en el proceso de configuraci�n de Apache. Tenga en cuenta
      que esto no es necesariamente lo mismo que la variable de entorno
      de un sistema operativo. Vea la <a href="../env.html">documentaci�n de variable de entorno</a> para
      m�s detalles.</dd>
    </dl>
</div><div class="top"><a href="#page-header"><img alt="top" src="../images/up.gif" /></a></div>
<div class="section">
<h2><a name="Default" id="Default">Por defecto</a></h2>

    <p>Si la directiva tiene un valor por defecto (<em>p.ej.</em>, si
    la omite de la configuraci�n completamente, el servidor Web Apache
    se comportar� como si la hubiera configurado con un valor en 
    particular), se describe aqu�. Si no tiene valor por defecto, esta 
    secci�n deber�a	indicar "<em>Ninguno</em>". Tenga en cuenta que el 
    valor por defecto listado aqu� no es necesariamente el mismo que el   
    valor que toma la directiva en el httpd.conf por defecto distribuido 
    con el servidor.</p>
</div><div class="top"><a href="#page-header"><img alt="top" src="../images/up.gif" /></a></div>
<div class="section">
<h2><a name="Context" id="Context">Contexto</a></h2>

    <p>Esto indica d�nde se acepta la directiva en los ficheros de 
    configuraci�n. Es una lista separada por comas para uno o m�s de los 
    siguientes valores:</p>

    <dl>
      <dt>server config</dt>

      <dd>Esto indica que la directiva puede usarse en los ficheros de 
		  configuraci�n del servidor (<em>p.ej.</em>, <code>httpd.conf</code>),
		  pero <strong>not</strong> dentro de cualquier contenedor
      <code class="directive"><a href="../mod/core.html#virtualhost">&lt;VirtualHost&gt;</a></code>
      o <code class="directive"><a href="../mod/core.html#directory">&lt;Directory&gt;</a></code>. 
		  No se permite en ficheros <code>.htaccess</code> de ninguna 
		  manera.</dd>

      <dt>virtual host</dt>

      <dd>Este contexto significa que la directiva puede aparecer dentro de un
      contenedor <code class="directive"><a href="../mod/core.html#virtualhost">&lt;VirtualHost&gt;</a></code>
      en el fichero de configuraci�n del servidor.</dd>

      <dt>directory</dt>

      <dd>Una directiva marcada como v�lida en este contexto puede usarse dentro
      de contenedores <code class="directive"><a href="../mod/core.html#directory">&lt;Directory&gt;</a></code>, <code class="directive"><a href="../mod/core.html#location">&lt;Location&gt;</a></code>, <code class="directive"><a href="../mod/core.html#files">&lt;Files&gt;</a></code>, <code class="directive"><a href="../mod/core.html#if">&lt;If&gt;</a></code>,  <code class="directive"><a href="../mod/mod_proxy.html#proxy">&lt;Proxy&gt;</a></code> en los ficheros de
      configuraci�n del servidor, sujeta a las restricciones destacadas en
      las <a href="../sections.html">Secciones de Configuraci�n</a>.</dd>

      <dt>.htaccess</dt>

      <dd>Si una directiva es v�lida en este contexto, significa que puede 
      aparecer dentro de ficheros <code>.htaccess</code> de <em>contexto de 
      directorio</em>. Aunque podr�a no ser procesada, dependiendo de la 
      configuraci�n activa de <a href="#Override">AllowOverride</a> en ese 
      momento.</dd> 
    </dl>

    <p>La directiva <em>solo</em> se permite dentro del contexto designado; si
    intenta usarlo en alg�n otro, obtendr� un error de configuraci�n que 
    impedir� que el servidor gestione correctamente las solicitudes en ese
    contexto, o impedir� que el servidor pueda funcionar completamente --
    <em>p.ej.</em>, el servidor no arrancar�.</p>

    <p>Las ubicaciones v�lidas para la directiva son actualmente el resultado de 
    un Boolean OR de todos los contextos listados. En otras palabras, una 
    directiva que est� marcada como v�lida en 
    "<code>server config, .htaccess</code>" puede usarse en el fichero
    <code>httpd.conf</code> y en ficheros <code>.htaccess</code>, pero no dentro 
    de contenedores <code class="directive"><a href="../mod/core.html#directory">&lt;Directory&gt;</a></code> 
    o <code class="directive"><a href="../mod/core.html#virtualhost">&lt;VirtualHost&gt;</a></code>.</p>
</div><div class="top"><a href="#page-header"><img alt="top" src="../images/up.gif" /></a></div>
<div class="section">
<h2><a name="Override" id="Override">Override</a></h2>

    <p>Este atributo de directiva indica qu� Override de configuraci�n debe 
    estar activo para que la directiva se procese cuando aparece en un fichero 
    <code>.htaccess</code>. Si el <a href="#Context">contexto</a> de la 
    directiva no permite que aparezca en ficheros <code>.htaccess</code>, 
    entonces no se listar� ning�n contexto.</p>

    <p>Los Override se activan con la directiva <code class="directive"><a href="../mod/core.html#allowoverride">AllowOverride</a></code>, si se aplican a un �mbito en 
    particular (como por ejemplo un directorio) y todos sus descendientes, a 
    menos que se modifique m�s adelante por otras directivas
    <code class="directive"><a href="../mod/core.html#allowoverride">AllowOverride</a></code> en niveles
    inferiores. La documentaci�n para la directiva tambi�n muestra una lista de
    los posibles nombres de Override disponibles.</p>
</div><div class="top"><a href="#page-header"><img alt="top" src="../images/up.gif" /></a></div>
<div class="section">
<h2><a name="Status" id="Status">Estado</a></h2>

    <p>Esto indica cuan vinculada est� esta directiva al servidor Web de Apache; 
    o en otras palabras, puede que necesite recompilar el servidor con un 
    conjunto mejor de m�dulos para obtener acceso a esta directiva y su 
    funcionalidad. Valores posibles para estar directiva son:</p>

    <dl>
      <dt>Core</dt>

      <dd>Si una directiva aparece listada con estado "Core", eso significa
      que forma parte de las partes m�s internas del Servidor Apache Web, y que
      siempre est� disponible.</dd>

      <dt>MPM</dt>

      <dd>La directivas facilitadas por un
      <a href="../mpm.html">M�dulo de Multi-Proceso</a> est�n etiquetadas con
      Estado "MPM". Este tipo de directiva estar� disponible si y s�lo si est� 
      usando uno de los MPM listados en la l�nea <a href="#Module">M�dulo</a> 
      de la definici�n de la directiva.</dd>

      <dt>Base</dt>

      <dd>Una directiva listada con estado "Base" est� facilitada por uno
      de los m�dulos est�ndar de Apache que est�n compilados con el servidor
      por defecto, y por tanto est� normalmente disponible a menos que usted 
      haga las acciones necesarias para eliminar este m�dulo de su 
      configuraci�n.</dd>

      <dt>Extensi�n</dt>

      <dd>Una directiva con estado "Extensi�n" est� facilitada por uno de los 
      m�dulos incluidos en el kit del servidor Apache, pero el m�dulo no 
      est� compilado generalmente dentro del servidor. Para activar esta y su
      funcionalidad, necesirar� cambiar la configuraci�n de compilaci�n
      del servidor y recompilar Apache.</dd>

      <dt>Experimental</dt>

      <dd>El estado "Experimental" indica que la directiva est� disponible como
      parte del kit de Apache, pero usted tendr� que ir por su cuenta si intenta
      usarla. La directiva se documenta para aportar informaci�n, pero no tiene
      por qu� estar soportada de manera oficial. El m�dulo que provee esta 
      directiva puede o puede que no est� compilado por defecto, compruebe
      la parte superior de la p�gina que describe la direcitiva y el m�dulo para
      ver las anotaciones sobre su disponibilidad.</dd>
    </dl>
</div><div class="top"><a href="#page-header"><img alt="top" src="../images/up.gif" /></a></div>
<div class="section">
<h2><a name="Module" id="Module">M�dulo</a></h2>

    <p>Esto simplemente hace referencia al nombre del m�dulo original que provee 
    la directiva.</p>
</div><div class="top"><a href="#page-header"><img alt="top" src="../images/up.gif" /></a></div>
<div class="section">
<h2><a name="Compatibility" id="Compatibility">Compatibilidad</a></h2>

    <p>Si la directiva no era parte de la distribuci�n original de Apache 
    versi�n 2, la versi�n en la que se introdujo deber�a estar referida aqu�. 
    Adem�s, si la direcitva solo est� disponible en ciertas plataformas, se ver�
    anotado aqu�.</p>
</div></div>
<div class="bottomlang">
<p><span>Idiomas disponibles: </span><a href="../en/mod/directive-dict.html" hreflang="en" rel="alternate" title="English">&nbsp;en&nbsp;</a> |
<a href="../es/mod/directive-dict.html" title="Espa�ol">&nbsp;es&nbsp;</a> |
<a href="../fr/mod/directive-dict.html" hreflang="fr" rel="alternate" title="Fran�ais">&nbsp;fr&nbsp;</a> |
<a href="../ja/mod/directive-dict.html" hreflang="ja" rel="alternate" title="Japanese">&nbsp;ja&nbsp;</a> |
<a href="../ko/mod/directive-dict.html" hreflang="ko" rel="alternate" title="Korean">&nbsp;ko&nbsp;</a> |
<a href="../tr/mod/directive-dict.html" hreflang="tr" rel="alternate" title="T�rk�e">&nbsp;tr&nbsp;</a></p>
</div><div class="top"><a href="#page-header"><img src="../images/up.gif" alt="top" /></a></div><div class="section"><h2><a id="comments_section" name="comments_section">Comentarios</a></h2><div class="warning"><strong>Notice:</strong><br />This is not a Q&amp;A section. Comments placed here should be pointed towards suggestions on improving the documentation or server, and may be removed again by our moderators if they are either implemented or considered invalid/off-topic. Questions on how to manage the Apache HTTP Server should be directed at either our IRC channel, #httpd, on Freenode, or sent to our <a href="http://httpd.apache.org/lists.html">mailing lists</a>.</div>
<script type="text/javascript"><!--//--><![CDATA[//><!--
var comments_shortname = 'httpd';
var comments_identifier = 'http://httpd.apache.org/docs/2.4/mod/directive-dict.html';
(function(w, d) {
    if (w.location.hostname.toLowerCase() == "httpd.apache.org") {
        d.write('<div id="comments_thread"><\/div>');
        var s = d.createElement('script');
        s.type = 'text/javascript';
        s.async = true;
        s.src = 'https://comments.apache.org/show_comments.lua?site=' + comments_shortname + '&page=' + comments_identifier;
        (d.getElementsByTagName('head')[0] || d.getElementsByTagName('body')[0]).appendChild(s);
    }
    else { 
        d.write('<div id="comments_thread">Comments are disabled for this page at the moment.<\/div>');
    }
})(window, document);
//--><!]]></script></div><div id="footer">
<p class="apache">Copyright 2018 The Apache Software Foundation.<br />Licencia bajo los t�rminos de la <a href="http://www.apache.org/licenses/LICENSE-2.0">Apache License, Version 2.0</a>.</p>
<p class="menu"><a href="../mod/">M�dulos</a> | <a href="../mod/directives.html">Directivas</a> | <a href="http://wiki.apache.org/httpd/FAQ">Preguntas Frecuentes</a> | <a href="../glossary.html">Glosario</a> | <a href="../sitemap.html">Mapa del sitio web</a></p></div><script type="text/javascript"><!--//--><![CDATA[//><!--
if (typeof(prettyPrint) !== 'undefined') {
    prettyPrint();
}
//--><!]]></script>
</body></html>