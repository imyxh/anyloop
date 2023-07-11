#include "anyloop.h"
#include "logging.h"
#include "stop_after_count.h"


int stop_after_count_init(struct aylp_device *self)
{
	self->process = &stop_after_count_process;
	self->close = &stop_after_count_close;
	self->device_data = (size_t *)calloc(1, sizeof(size_t));
	size_t *count = (size_t *)self->device_data;
	if (!count) {
		log_error("Couldn't allocate device data. All we needed was "
			"one size_t; what the hell is wrong with your system?"
		);
		return -1;
	}
	if (!self->params) {
		log_error("No params object found.");
		return -1;
	}
	json_object_object_foreach(self->params, key, val) {
		if (key[0] == '_') {
			// keys starting with _ are comments
		} else if (!strcmp(key, "count")) {
			*count = strtoul(
				json_object_get_string(val), 0, 0
			);
			log_trace("count = %llu", self->device_data);
		} else {
			log_warn("Unknown parameter \"%s\"", key);
		}
	}
	if (!count) {
		log_error("Missing count parameter");
		return -1;
	}
	// set types
	self->type_in = AYLP_T_ANY | AYLP_U_ANY;
	self->type_out = 0;
	return 0;
}


int stop_after_count_process(struct aylp_device *self, struct aylp_state *state)
{
	size_t *count = (size_t *)self->device_data;
	*count -= 1;
	if (*count == 0) state->header.status |= AYLP_DONE;
	return 0;
}


int stop_after_count_close(struct aylp_device *self)
{
	UNUSED(self);
	return 0;
}
