#include "bspwc/cursor.h"

void handle_cursor_motion(struct wl_listener* listener, void* data)
{
	struct cursor* cursor = wl_container_of(listener, cursor, motion);
	struct wlr_event_pointer_motion* event = data;

	wlr_log(L_DEBUG, "Cursor %d, %d", event->delta_x, event->delta_y);

	wlr_cursor_move(cursor->cursor, event->device, event->delta_x, event->delta_y);
}

void handle_cursor_motion_absolute(struct wl_listener* listener, void* data)
{}

void handle_cursor_button(struct wl_listener* listener, void* data)
{}

void handle_cursor_axis(struct wl_listener* listener, void* data)
{}

struct cursor* create_cursor(struct input* input)
{
	struct cursor* cursor = calloc(1, sizeof(struct cursor));
	if (cursor == NULL)
	{
		wlr_log(L_ERROR, "Failed to create cursor");
		return NULL;
	}

	cursor->input = input;

	struct wlr_output_layout* output_layout = input->server->output_layout;
	struct wlr_box* layout_box = wlr_output_layout_get_box(output_layout, NULL);

	cursor->cursor = wlr_cursor_create();
	if (cursor->cursor == NULL)
	{
		wlr_log(L_ERROR, "Failed to create cursor's wlr_cursor");
		free(cursor);
	}

	wlr_cursor_attach_output_layout(cursor->cursor, output_layout);
	wlr_cursor_map_to_region(
			cursor->cursor,
			layout_box
		);

	// TODO : cursor theme should be customizable
	cursor->xcursor = wlr_xcursor_theme_get_cursor(input->xcursor_theme, "left_ptr");
	if (cursor->xcursor == NULL)
	{
		wlr_log(L_ERROR, "Failed to load left_ptr cursor");
		destroy_cursor(cursor);
		return NULL;
	}

	// TODO : why 0?
	struct wlr_xcursor_image* image = cursor->xcursor->images[0];
	wlr_cursor_set_image(
			cursor->cursor,
			image->buffer,
			image->width * 4,
			image->width,
			image->height,
			image->hotspot_x,
			image->hotspot_y,
			0
		);

	wlr_cursor_warp(cursor->cursor, NULL, layout_box->width / 2 , layout_box->height / 2);

	// Setup callbacks
	wl_signal_add(&cursor->cursor->events.motion, &cursor->motion);
	cursor->motion.notify = handle_cursor_motion;

	wl_signal_add(&cursor->cursor->events.motion_absolute, &cursor->motion_absolute);
	cursor->motion_absolute.notify = handle_cursor_motion_absolute;

	wl_signal_add(&cursor->cursor->events.button, &cursor->button);
	cursor->button.notify = handle_cursor_button;

	wl_signal_add(&cursor->cursor->events.axis, &cursor->axis);
	cursor->axis.notify = handle_cursor_axis;

	return cursor;
}

void destroy_cursor(struct cursor* cursor)
{
	wlr_cursor_destroy(cursor->cursor);
	free(cursor);
}