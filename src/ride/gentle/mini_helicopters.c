#pragma region Copyright (c) 2014-2016 OpenRCT2 Developers
/*****************************************************************************
 * OpenRCT2, an open source clone of Roller Coaster Tycoon 2.
 *
 * OpenRCT2 is the work of many authors, a full list can be found in contributors.md
 * For more information, visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * A full copy of the GNU General Public License can be found in licence.txt
 *****************************************************************************/
#pragma endregion

#include "../track_paint.h"
#include "../track.h"
#include "../vehicle_paint.h"
#include "../../interface/viewport.h"
#include "../../paint/paint.h"
#include "../../paint/supports.h"
#include "../ride_data.h"

enum
{
	SPR_22362 = 22362,
	SPR_22364 = 22364,
	SPR_22370 = 22370,
	SPR_22428 = 22428,
};

/** rct2: 0x */
static void paint_mini_helicopters_track_station(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	rct_xy16 position = {RCT2_GLOBAL(0x009DE56A, sint16), RCT2_GLOBAL(0x009DE56E, sint16)};
	rct_ride * ride = get_ride(rideIndex);
	const rct_ride_entrance_definition * entranceStyle = &RideEntranceDefinitions[ride->entrance_style];
	uint32 imageId;
	bool hasFence;

	if (direction & 1) {

	} else {
		// height -= 2 (height - 2)
		imageId = SPR_22428 | RCT2_GLOBAL(0x00F441A0, uint32);
		sub_98197C(imageId, 0, 0, 32, 28, 1, height - 2, 0, 2, height, get_current_rotation());

		// height += 2 (height)
		imageId = SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_NE_SW | RCT2_GLOBAL(0x00F44198, uint32);
		sub_98197C(imageId, 0, 0, 32, 20, 1, height, 0, 0, height, get_current_rotation());

		metal_a_supports_paint_setup(3, 5, 0, height, RCT2_GLOBAL(0x00F4419C, uint32));
		metal_a_supports_paint_setup(3, 8, 0, height, RCT2_GLOBAL(0x00F4419C, uint32));
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
		paint_util_push_tunnel_left(height, TUNNEL_6);

		//height += 5 (height + 5);
		hasFence = track_paint_util_has_fence(EDGE_NW, position, mapElement, ride, get_current_rotation());
		imageId = (hasFence ? SPR_22364 : SPR_22362) | RCT2_GLOBAL(0x00F4419C, uint32);
		sub_98196C(imageId, 0, 0, 32, 8, 1, height + 6, get_current_rotation());
		//height -= 5 (height)
		track_paint_util_draw_station_covers(EDGE_NW, hasFence, entranceStyle, direction, height);
		//height += 5 (height + 5)

		imageId = SPR_22362 | RCT2_GLOBAL(0x00F4419C, uint32);
		sub_98196C(imageId, 0, 24, 32, 8, 1, height + 5, get_current_rotation());
		//height += 2 (height + 7)

		hasFence = track_paint_util_has_fence(EDGE_SE, position, mapElement, ride, get_current_rotation());
		if (hasFence) {
			imageId = SPR_22370 | RCT2_GLOBAL(0x00F4419C, uint32);
			sub_98196C(imageId, 0, 31, 32, 1, 7, height + 7, get_current_rotation());
		}
		//height -= 7 (height)
		track_paint_util_draw_station_covers(EDGE_SE, hasFence, entranceStyle, direction, height);
		//height += 7 (height + 7)

		//height += 25 (height + 32)
		paint_util_set_general_support_height(height + 32, 0x20);
	}
}

/** rct2: 0x0081F348 */
static void paint_mini_helicopters_track_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	rct_xy16 position = {RCT2_GLOBAL(0x009DE56A, sint16), RCT2_GLOBAL(0x009DE56E, sint16)};
	uint32 imageId;

	if (direction & 1) {
		imageId = SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_SE_NW | RCT2_GLOBAL(0x00F44198, uint32);
		sub_98197C(imageId, 0, 0, 20, 32, 3, height, 6, 0, height, get_current_rotation());
		paint_util_push_tunnel_right(height, TUNNEL_0);
	} else {
		imageId = SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_NE_SW | RCT2_GLOBAL(0x00F44198, uint32);
		sub_98197C(imageId, 0, 0, 32, 20, 3, height, 0, 6, height, get_current_rotation());
		paint_util_push_tunnel_left(height, TUNNEL_0);
	}

	if (track_paint_util_should_paint_supports(position)) {
		metal_a_supports_paint_setup((direction & 1) ? 5 : 4, 4, -1, height, RCT2_GLOBAL(0x00F4419C, uint32));
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_D0 | SEGMENT_C4 | SEGMENT_CC, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 32, 0x20);
}

/** rct2: 0x0081F368 */
static void paint_mini_helicopters_track_flat_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	rct_xy16 position = {RCT2_GLOBAL(0x009DE56A, sint16), RCT2_GLOBAL(0x009DE56E, sint16)};
	uint32 imageId;

	switch (direction) {
		case 0:
			imageId = SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_TO_25_DEG_UP_SW_NE | RCT2_GLOBAL(0x00F44198, uint32);
			sub_98197C(imageId, 0, 0, 32, 20, 3, height, 0, 6, height, get_current_rotation());
			paint_util_push_tunnel_left(height, TUNNEL_0);
			break;
		case 1:
			imageId = SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_TO_25_DEG_UP_NW_SE | RCT2_GLOBAL(0x00F44198, uint32);
			sub_98197C(imageId, 0, 0, 20, 32, 3, height, 6, 0, height, get_current_rotation());
			paint_util_push_tunnel_right(height, TUNNEL_2);
			break;
		case 2:
			imageId = SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_TO_25_DEG_UP_NE_SW | RCT2_GLOBAL(0x00F44198, uint32);
			sub_98197C(imageId, 0, 0, 32, 20, 3, height, 0, 6, height, get_current_rotation());
			paint_util_push_tunnel_left(height, TUNNEL_2);
			break;
		case 3:
			imageId = SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_TO_25_DEG_UP_SE_NW | RCT2_GLOBAL(0x00F44198, uint32);
			sub_98197C(imageId, 0, 0, 20, 32, 3, height, 6, 0, height, get_current_rotation());
			paint_util_push_tunnel_right(height, TUNNEL_0);
			break;
	}

	if (track_paint_util_should_paint_supports(position)) {
		metal_a_supports_paint_setup(4, 4, -4, height, RCT2_GLOBAL(0x00F4419C, uint32));
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_D0 | SEGMENT_C4 | SEGMENT_CC, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 48, 0x20);
}

/** rct2: 0x0081F358 */
static void paint_mini_helicopters_track_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	rct_xy16 position = {RCT2_GLOBAL(0x009DE56A, sint16), RCT2_GLOBAL(0x009DE56E, sint16)};
	uint32 imageId;

	switch (direction) {
		case 0:
			imageId = SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_25_DEG_UP_SW_NE | RCT2_GLOBAL(0x00F44198, uint32);
			sub_98197C(imageId, 0, 0, 32, 20, 3, height, 0, 6, height, get_current_rotation());
			paint_util_push_tunnel_left(height - 8, TUNNEL_1);
			break;
		case 1:
			imageId = SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_25_DEG_UP_NW_SE | RCT2_GLOBAL(0x00F44198, uint32);
			sub_98197C(imageId, 0, 0, 20, 32, 3, height, 6, 0, height, get_current_rotation());
			paint_util_push_tunnel_right(height + 8, TUNNEL_2);
			break;
		case 2:
			imageId = SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_25_DEG_UP_NE_SW | RCT2_GLOBAL(0x00F44198, uint32);
			sub_98197C(imageId, 0, 0, 32, 20, 3, height, 0, 6, height, get_current_rotation());
			paint_util_push_tunnel_left(height + 8, TUNNEL_2);
			break;
		case 3:
			imageId = SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_25_DEG_UP_SE_NW | RCT2_GLOBAL(0x00F44198, uint32);
			sub_98197C(imageId, 0, 0, 20, 32, 3, height, 6, 0, height, get_current_rotation());
			paint_util_push_tunnel_right(height - 8, TUNNEL_1);
			break;
	}

	if (track_paint_util_should_paint_supports(position)) {
		metal_a_supports_paint_setup(4, 4, -9, height, RCT2_GLOBAL(0x00F4419C, uint32));
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_D0 | SEGMENT_C4 | SEGMENT_CC, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 56, 0x20);
}

/** rct2: 0x0081F378 */
static void paint_mini_helicopters_track_25_deg_up_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	rct_xy16 position = {RCT2_GLOBAL(0x009DE56A, sint16), RCT2_GLOBAL(0x009DE56E, sint16)};
	uint32 imageId;

	switch (direction) {
		case 0:
			imageId = SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_25_DEG_UP_TO_FLAT_SW_NE | RCT2_GLOBAL(0x00F44198, uint32);
			sub_98197C(imageId, 0, 0, 32, 20, 3, height, 0, 6, height, get_current_rotation());
			paint_util_push_tunnel_left(height - 8, TUNNEL_0);
			break;
		case 1:
			imageId = SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_25_DEG_UP_TO_FLAT_NW_SE | RCT2_GLOBAL(0x00F44198, uint32);
			sub_98197C(imageId, 0, 0, 20, 32, 3, height, 6, 0, height, get_current_rotation());
			paint_util_push_tunnel_right(height + 8, TUNNEL_12);
			break;
		case 2:
			imageId = SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_25_DEG_UP_TO_FLAT_NE_SW | RCT2_GLOBAL(0x00F44198, uint32);
			sub_98197C(imageId, 0, 0, 32, 20, 3, height, 0, 6, height, get_current_rotation());
			paint_util_push_tunnel_left(height + 8, TUNNEL_12);
			break;
		case 3:
			imageId = SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_25_DEG_UP_TO_FLAT_SE_NW | RCT2_GLOBAL(0x00F44198, uint32);
			sub_98197C(imageId, 0, 0, 20, 32, 3, height, 6, 0, height, get_current_rotation());
			paint_util_push_tunnel_right(height - 8, TUNNEL_0);
			break;
	}

	if (track_paint_util_should_paint_supports(position)) {
		metal_a_supports_paint_setup(4, 4, -7, height, RCT2_GLOBAL(0x00F4419C, uint32));
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_D0 | SEGMENT_C4 | SEGMENT_CC, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 40, 0x20);
}

/** rct2: 0x */
static void paint_mini_helicopters_track_flat_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	paint_mini_helicopters_track_25_deg_up_to_flat(rideIndex, trackSequence, (direction + 2) % 4, height, mapElement);
}

/** rct2: 0x0081F388 */
static void paint_mini_helicopters_track_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	paint_mini_helicopters_track_25_deg_up(rideIndex, trackSequence, (direction + 2) % 4, height, mapElement);
}

/** rct2: 0x0081F3A8 */
static void paint_mini_helicopters_track_25_deg_down_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	paint_mini_helicopters_track_flat_to_25_deg_up(rideIndex, trackSequence, (direction + 2) % 4, height, mapElement);
}

/** rct2: 0x */
static void paint_mini_helicopters_track_left_quarter_turn_3_tiles(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{

}

/** rct2: 0x */
static void paint_mini_helicopters_track_right_quarter_turn_3_tiles(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{

}

/** rct2: 0x */
static void paint_mini_helicopters_track_left_quarter_turn_1_tile(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{

}

/** rct2: 0x */
static void paint_mini_helicopters_track_right_quarter_turn_1_tile(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{

}

/**
 * rct2: 0x0081F268
 */
TRACK_PAINT_FUNCTION get_track_paint_function_mini_helicopters(int trackType, int direction)
{
	switch (trackType) {
		case TRACK_ELEM_BEGIN_STATION:
		case TRACK_ELEM_MIDDLE_STATION:
		case TRACK_ELEM_END_STATION:
			return paint_mini_helicopters_track_station;

		case TRACK_ELEM_FLAT:
			return paint_mini_helicopters_track_flat;

		case TRACK_ELEM_FLAT_TO_25_DEG_UP:
			return paint_mini_helicopters_track_flat_to_25_deg_up;
		case TRACK_ELEM_25_DEG_UP:
			return paint_mini_helicopters_track_25_deg_up;
		case TRACK_ELEM_25_DEG_UP_TO_FLAT:
			return paint_mini_helicopters_track_25_deg_up_to_flat;

		case TRACK_ELEM_FLAT_TO_25_DEG_DOWN:
			return paint_mini_helicopters_track_flat_to_25_deg_down;
		case TRACK_ELEM_25_DEG_DOWN:
			return paint_mini_helicopters_track_25_deg_down;
		case TRACK_ELEM_25_DEG_DOWN_TO_FLAT:
			return paint_mini_helicopters_track_25_deg_down_to_flat;

		case TRACK_ELEM_LEFT_QUARTER_TURN_3_TILES:
			return paint_mini_helicopters_track_left_quarter_turn_3_tiles;
		case TRACK_ELEM_RIGHT_QUARTER_TURN_3_TILES:
			return paint_mini_helicopters_track_right_quarter_turn_3_tiles;

		case TRACK_ELEM_LEFT_QUARTER_TURN_1_TILE:
			return paint_mini_helicopters_track_left_quarter_turn_1_tile;
		case TRACK_ELEM_RIGHT_QUARTER_TURN_1_TILE:
			return paint_mini_helicopters_track_right_quarter_turn_1_tile;
	}

	return NULL;
}