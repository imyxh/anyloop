Devices
=======

OpenAO uses a plugin-like syntax to add devices to a loop.

Anatomy of a device
-------------------

See the `oao_device` struct in `openao.h`.

Built-in devices
----------------

Devices are named with a URI-like syntax. Built-in devices start with the scheme
`openao`, and are followed only by a "path" (to use URI terminology). For
example, the built-in device to generate von Kármán streams has the path
`vonkarman_stream`, and thus has the URI `openao:vonkarman_stream`.

To add a new built-in device:

 1. write `src/devices/$MYDEVICE.c` and `src/devices/$MYDEVICE.h`
 2. modify `device.h` to include the header file
 3. add the device's initialization function to the init map in `device.h`
 4. add the new files to meson.build

Plug-in devices
---------------

Sometimes, due to licensing requirements or whatever, it may be convenient to
use devices not in this repository. No problem! Use the `file` scheme
with no authority (<https://www.rfc-editor.org/rfc/rfc8090.html>). For example,
to load a plug-in device at `/opt/foo/bar.so`, write the URI as
`file:/opt/foo/bar.so`.

The plug-in device will be initialized the same way built-in devices are. As
such, a device named `bar.so` is expected to have a function of the following
name and type signature:

```c
int bar_init(struct oao_device *self)
```

Note that we strip off anything including and after the first `.` character in
the basename, so a device with a basename of `blah.a.b.c` should have an init
function named `blah_init`.

This function can then attach whatever process() and close() functions it wishes
to its own `oao_device` struct.
