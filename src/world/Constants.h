#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

constexpr int CHUNKSIZE_X = 16, CHUNKSIZE_Y = 64, CHUNKSIZE_Z = 16, CHUNKAREA = CHUNKSIZE_X * CHUNKSIZE_Y,
CHUNKVOLUME = CHUNKAREA * CHUNKSIZE_Z, WATER_LEVEL = 30;

#endif // !CONSTANTS_H