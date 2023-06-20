#pragma once

#include "DrawDebugHelpers.h"

#define DRAW_SPHERE(location) if (GetWorld()) DrawDebugSphere(GetWorld(), location, 25.f, 12, FColor::Red, true)

#define DRAW_LINE(startLocation, endLocation) if (GetWorld()) DrawDebugLine(GetWorld(), startLocation, endLocation, FColor::Blue, true, -1.f, 0, 1.f);

#define DRAW_POINT(location) if (GetWorld()) DrawDebugPoint(GetWorld(), location, 15.f, FColor::Green, true);

#define DRAW_VECTOR(startLocation, endLocation) if (GetWorld()) \
	{ \
		DrawDebugLine(GetWorld(), startLocation, endLocation, FColor::Black, true, -1.f, 0, 1.f); \
		DrawDebugPoint(GetWorld(), endLocation, 15.f, FColor::Black, true); \
	}