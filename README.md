# IBSurgeon GEN_UUID v7 UDR

The IBSurgeon UUID v7 UDR library is designed to generate UUID version 7.

This version is standardized in RFC 9562 (2024). It includes 48-bit Unix timestamp (in milliseconds) in the high-order bits, followed by the version bits, 12 random bits, variant bits, and another 62 random bits. The total randomness is 74 bits.

In Firebird 6.0, the built-in function `GEN_UUID()` can generate both UUID version 4 and version 7. For this purpose, it now has an optional parameter that accepts the UUID version number.

However, Firebird 6.0 is still under development, and many users already want to take advantage of UUID version 7 in the current releases of Firebird 5.0, 4.0, or 3.0. For these users, we have written a UDR function that generates UUID version 7.

## Installing UUID v7 UDR

To install UUID v7 UDR, you need to:

1. Unzip the zip archive with dynamic libraries into the `plugins/udr` directory
2. Run the `sql/uuid_v7_install.sql` script to register procedures and functions in the database.

```sql
CREATE FUNCTION GEN_UUID_V7 ()
RETURNS BINARY(16)
EXTERNAL NAME 'uuid_v7!gen_uuid_v7'
ENGINE UDR;
```

You can download ready-made builds for Windows OS using the following links:

* [UUID_v7_Udr_Win_x64.zip](https://github.com/IBSurgeon/uuid_v7_udr/releases/download/1.0/UUID_v7_Udr_Win_x64.zip)
* [UUID_v7_Udr_Win_x86.zip](https://github.com/IBSurgeon/uuid_v7_udr/releases/download/1.0/UUID_v7_Udr_Win_x86.zip)

## Building on Linux

```bash
git clone https://github.com/IBSurgeon/uuid_v7_udr.git
cd uuid_v7_udr
mkdir build; cd build
cmake ..
make
sudo make install
```

## Usage

```sql
-- UUID v7 generation
SELECT GEN_UUID_V7() FROM RDB$DATABASE;

-- insert a record with a UUID v7 identifier
INSERT INTO T(ID, txt)
VALUES (GEN_UUID_V7(), 'hello');

-- Generating a UUID v7 and converting it to a readable string
SELECT UUID_TO_CHAR(GEN_UUID_V7()) UUIDv7 FROM RDB$DATABASE;
```
