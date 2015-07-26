#pragma once

#include <stddef.h>

#define PERF_EXPORT

extern "C"
{

struct perf_config;
struct perf_context;
struct perf_identity;

typedef void *(*perf_alloc)(size_t size);
typedef void (*perf_free)(void *size);

typedef int perf_error;
#define perf_no_error               0
#define perf_error_in_error         1
#define perf_invalid_config         2
#define perf_recording_after_output 3
#define perf_failed_to_write_file   4

/// \name Config management
/// @{

/// \brief Create a performance testing config
///
/// The config should be created before anything else in perf.
PERF_EXPORT perf_config *perf_init_config(perf_alloc, perf_free, const char *binding);

/// \brief Create a default performance testing config
///
/// This helper internally calls perf_init_config with malloc and free.
PERF_EXPORT perf_config *perf_init_default_config(const char *binding);

/// \brief Terminate the performance testing config.
PERF_EXPORT void perf_term_config(perf_config *ctx);


/// \brief Find the identity of the context
///
/// The identity describes the machine hardware, and is used in
/// graphing to identify threads of tests.
///
/// \note The identity memory is managed by the config, it should not be freed.
PERF_EXPORT const perf_identity *perf_find_identity(perf_config *ctx);

/// \brief Transform the identity into a readable description.
///
/// \note The description memory is managed by the config, it should not be freed.
PERF_EXPORT const char *perf_identity_description(const perf_identity *id);

/// @}


/// \name Context management
/// @{

/// \brief Init a performance testing context.
///
/// A context should be created for each thread which will use perf.
PERF_EXPORT perf_context *perf_init_context(perf_config *cfg, const char *name);

/// \brief Terminate a performance testing context.
PERF_EXPORT void perf_term_context(perf_context *ctx);

/// @}

/// \name Context output
/// @{

/// \brief Write the context to disk.
PERF_EXPORT void perf_write_context(perf_context *ctx, const char *name);

/// \brief Return the context as a string.
PERF_EXPORT const char *perf_dump_context(perf_context *ctx);

/// @}

/// \name Recording events
/// @{

/// \brief create an event
PERF_EXPORT void perf_add_event(perf_context *ctx, const char *name);

/// @}

}
