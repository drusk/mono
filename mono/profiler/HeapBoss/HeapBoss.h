#pragma once

extern "C"
{
#include <glib.h>
}

#ifdef __cplusplus
extern "C"
#endif
void heap_boss_startup(const char *desc);

#ifdef __cplusplus
extern "C"
#endif
gboolean heap_boss_profiler_runtime_is_ready();

#ifdef __cplusplus
extern "C"
#endif
void heap_boss_handle_custom_event(const char* text);

void heap_boss_handle_app_resign_active();
void heap_boss_handle_app_become_active();
void heap_boss_handle_app_memory_warning();
void heap_boss_handle_app_will_terminate();

void heap_boss_handle_new_frame();

// don't try to get a stacktrace on the next boehm alloc as we already track enough data about it
extern "C" void heap_boss_next_boehm_alloc_is_well_known();