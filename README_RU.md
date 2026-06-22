# IBSurgeon GEN_UUID v7 UDR

Библиотека IBSurgeon UUID v7 UDR предназначена для генерации UUID версии 7.

Эта версия стандартизирована в RFC 9562 (2024 год). Она включает 48 бит временной метки Unix (в миллисекундах) в старших битах, затем идут биты версии, 12 случайных бит, биты варианта и ещё 62 случайных бита. Суммарно случайность составляет 74 бита.

В Firebird 6.0 встроенная фукнция `GEN_UUID()` может генерировать как UUID версии 4, так и версии 7. Для этого у неё появился необазательный параметр в который передаётся номер версии UUID.

Однако Firebird 6.0 всё ещё находится в стадии разработки, а многие уже хотят воспользоваться преимуществами UUID версии версии 7 в текущих релизах Firebird 5.0, 4.0 или 3.0. Для таких пользователей мы написали UDR функцию которая генерирует UUID версии 7. 

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

* [UUID_v7_Udr_Win_x64.zip](https://github.com/IBSurgeon/uuid_v7_udr/releases/download/1.0/UUID_v7_Udr_Win_x64.zip)
* [UUID_v7_Udr_Win_x86.zip](https://github.com/IBSurgeon/uuid_v7_udr/releases/download/1.0/UUID_v7_Udr_Win_x86.zip)


## Сборка под Linux

```bash
git clone https://github.com/IBSurgeon/uuid_v7_udr.git
cd uuid_v7_udr
mkdir build; cd build
cmake ..
make
sudo make install
```

## Использование

```sql
-- генерация uuid v7
SELECT GEN_UUID_V7() FROM RDB$DATABASE;

-- вставка записи с идентификатором UUID v7
INSERT INTO T(ID, txt)
VALUES (GEN_UUID_V7(), 'hello');

-- генерация UUID v7 и его преобразование в читаемую строку
SELECT UUID_TO_CHAR(GEN_UUID_V7()) UUIDv7 FROM RDB$DATABASE;
```
