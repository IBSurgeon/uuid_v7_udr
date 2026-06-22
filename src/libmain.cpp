/*
 *	PROGRAM:		UUID generation v7 UDR.
 *	MODULE:			libmain.cpp
 *	DESCRIPTION:	Implementation of Generate UUID version 7.
 *
 *  The contents of this file are subject to the Initial
 *  Developer's Public License Version 1.0 (the "License");
 *  you may not use this file except in compliance with the
 *  License. You may obtain a copy of the License at
 *  http://www.firebirdsql.org/en/initial-developer-s-public-license-version-1-0/.
 *
 *  Software distributed under the License is distributed AS IS,
 *  WITHOUT WARRANTY OF ANY KIND, either express or implied.
 *  See the License for the specific language governing rights
 *  and limitations under the License.
 *
 *  The Original Code was created by Simonov Denis
 *  for the open source project "IBSurgeon Http Client UDR".
 *
 *  Copyright (c) 2023-2026 Simonov Denis <sim-mail@list.ru>
 *  and all contributors signed below.
 *
 *  All Rights Reserved.
 *  Contributor(s): ______________________________________.
 */

#include "UDR.h"

#include <array>
#include <chrono>
#include <random>

namespace
{
    constexpr size_t UUID_SIZE = 16;
}

 /*
   FUNCTION GEN_UUID_V7 ()
   RETURNS BINARY(16)
   EXTERNAL NAME 'uuidv7!gen_uuid_v7'
   ENGINE UDR;
 */

FB_UDR_BEGIN_FUNCTION(gen_uuid_v7)

FB_UDR_MESSAGE(OutMessage,
    (FB_INTL_CHAR(16, 1), result)
);

FB_UDR_EXECUTE_FUNCTION
{
    using namespace std::chrono;
    auto now = system_clock::now();
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()).count();

    uint64_t timestamp = static_cast<uint64_t>(ms) & 0xFFFFFFFFFFFFULL;

    thread_local std::mt19937_64 rng(
        std::random_device {}() ^
        static_cast<uint64_t>(std::chrono::steady_clock::now().time_since_epoch().count())
    );

    thread_local std::uniform_int_distribution<unsigned int> byte_dist(0, 255);

    std::array<uint8_t, 16> uuid;

    // timestamp
    uuid[0] = (timestamp >> 40) & 0xFF;
    uuid[1] = (timestamp >> 32) & 0xFF;
    uuid[2] = (timestamp >> 24) & 0xFF;
    uuid[3] = (timestamp >> 16) & 0xFF;
    uuid[4] = (timestamp >> 8) & 0xFF;
    uuid[5] = timestamp & 0xFF;

    for (int i = 6; i < 16; ++i)
        uuid[i] = static_cast<uint8_t>(byte_dist(rng));

    // version and variant
    uuid[6] = (uuid[6] & 0x0F) | 0x70;
    uuid[8] = (uuid[8] & 0x3F) | 0x80;

    out->resultNull = FB_FALSE;
    std::memcpy(out->result.str, uuid.data(), UUID_SIZE);
}

FB_UDR_END_FUNCTION

FB_UDR_IMPLEMENT_ENTRY_POINT
