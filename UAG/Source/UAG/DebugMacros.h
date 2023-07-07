#pragma once

#include "DrawDebugHelpers.h"

#define DRAW_SPHERE(location) if (GetWorld()) DrawDebugSphere(GetWorld(), location, 25.f, 12, FColor::Red, true);

#define DRAW_SPHERE_COLOR(location, color) if (GetWorld()) DrawDebugSphere(GetWorld(), location, 8.f, 12, color, false, 5.f);

#define DRAW_SPHERE_SINGLE_FRAME(location) if (GetWorld()) DrawDebugSphere(GetWorld(), location, 25.f, 12, FColor::Red, false, -1.f);

#define DRAW_LINE(startLocation, endLocation) if (GetWorld()) DrawDebugLine(GetWorld(), startLocation, endLocation, FColor::Blue, true, -1.f, 0, 1.f);

#define DRAW_LINE_SINGLE_FRAME(startLocation, endLocation) if (GetWorld()) DrawDebugLine(GetWorld(), startLocation, endLocation, FColor::Blue, false, -1.f, 0, 1.f);

#define DRAW_POINT(location) if (GetWorld()) DrawDebugPoint(GetWorld(), location, 15.f, FColor::Green, true);

#define DRAW_POINT_SINGLE_FRAME(location) if (GetWorld()) DrawDebugPoint(GetWorld(), location, 15.f, FColor::Green, false, -1.f);

#define DRAW_VECTOR(startLocation, endLocation) if (GetWorld()) \
	{ \
		DrawDebugLine(GetWorld(), startLocation, endLocation, FColor::Black, true, -1.f, 0, 1.f); \
		DrawDebugPoint(GetWorld(), endLocation, 15.f, FColor::Black, true); \
	}

#define DRAW_VECTOR_SINGLE_FRAME(startLocation, endLocation) if (GetWorld()) \
	{ \
		DrawDebugLine(GetWorld(), startLocation, endLocation, FColor::Black, false, -1.f, 0, 1.f); \
		DrawDebugPoint(GetWorld(), endLocation, 15.f, FColor::Black, false, -1.f); \
	}