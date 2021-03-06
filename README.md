## <p>Проект радиоуправляемой машинки</p>

<p>
Проект содержит исходники для радиоуправляемой машины, которая хостится как http-server и клиента к ней - http-client. Предполагается, что клиент будет подключаться при помощи смартфона.
</p>

<h3>http-server</h2>
<p>Исходники на c++, которые собираются и прошивают микроконтроллер.</p>
<p>Разработка ведется в среде Visual Studio Code. Для сбора проекта и прошивки микроконтроллера используется плагин Platformio IDE.</p>
<p>На плате поднимается wi-fi access point (AP), на котором разворачивается веб сервер.</p>
<p>Для сборки проекта необходимо выполнить команду PlatformIO: Buid.</p>
<p>Для прошивки микроконтроллера необходимо выполнить команду PlatformIO: Upload.</p>

<h3>http-client</h3>
<p>Приложение состоит из Index.html, набора .js файлов и дополнительных активов. Для работы с файлами на контроллере используется библиотека SPIFFS микроконтроллера ESP8266.</p>
<p>Приложение бандлится web-pack'om - собирается файл app.js, копируются Index.html и активы в папку bin. Для сборки приложения необходимо:
    <ol>
        <li>Установить node.js</li>
        <li>Установить записимости - перейти в папку http-client и вызвать npm install</li>
        <li>Запустить task - build_client, нажав ctrl+F9</li>
    </ol>
</p>
<p>Для загрузки файлов в микроконтроллер необходимо выполнить команду PlatformIO: Upload SPIFFS Image.</p>