# IBSurgeon GEN_UUID v7 UDR

Библиотека IBSurgeon UUID v7 UDR предназначена для генерации UUID версии 7.

## Установка UUID v7 UDR

Для установки UUID v7 UDR необходимо:

1. Распаковать zip архив с динамическими библиотеками в каталог `plugins/udr`
2. Выполнить скрипт `sql/uuid_v7_install.sql` для регистрации процедур и функций в БД.

```sql
CREATE FUNCTION GEN_UUID_V7 ()
RETURNS BINARY(16)
EXTERNAL NAME 'uuid_v7!gen_uuid_v7'
ENGINE UDR;
```

Скачать готовые сборки под ОС Windows можно по ссылкам:

* [HttpClientUdr_Win_x64.zip](https://github.com/IBSurgeon/http_client_udr/releases/download/1.0/HttpClientUdr_Win_x64.zip)
* [HttpClientUdr_Win_x86.zip](https://github.com/IBSurgeon/http_client_udr/releases/download/1.0/HttpClientUdr_Win_x86.zip)

Скачать готовые сборки под ОС Linux можно по ссылкам:

* [HttpClientUdr_CentOS7_x64.zip](https://github.com/IBSurgeon/http_client_udr/releases/download/1.0/HttpClientUdr_CentOS7_x64.zip)


## Сборка под Linux

```bash
git clone https://github.com/IBSurgeon/uuid_v7_udr.git
cd uuid_v7_udr
mkdir build; cd build
cmake ..
make
sudo make install
```
