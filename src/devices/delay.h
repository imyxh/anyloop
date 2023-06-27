#ifndef _AYLP_DELAY_H
#define _AYLP_DELAY_H

#include "anyloop.h"

// initialize delay device
int delay_init(struct aylp_device *self);

// process delay device once per loop
int delay_process(struct aylp_device *self, struct aylp_state *state);

// close delay device when loop exits
int delay_close(struct aylp_device *self);

#endif

