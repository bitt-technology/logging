#ifndef LOGGING_H_
#define LOGGING_H_

#include <limits.h>

/**
 * Simple debug like macro for logging a message to stderr.
 * It expects a log level and a string
 */
#define LOGGER(LEVEL, INFO) \
	fprintf(stderr,"%s:%d - %s(%d) - %s\n",__FILE__,__LINE__,\
			logging_str(LEVEL),LEVEL,INFO);

/**
 * Predefined log levels. The log levels can be any int, the higher the
 * value the higher the priority. The levels in the enumeration are a
 * more verbose way of using the log levels.
 */
enum LogLevel {
	FINEST=0,
	FINER=1,
	FINE=2,
	INFO=3,
	WARNING=4,
	SEVERE=5,
	ALL=INT_MIN
};

/**
 * This function converts a log level from the log level enumeration 
 * into a string. If the level is not part of the enumeration, it 
 * will have a special name.
 */
const char * logging_str(int level);

/**
 * Prototype for a function that can handle a log message
 */
typedef void (*log_handler_function)(int, char*);

/**
 * A log node. It is part of a list of nodes that
 * present a logging function with a list of handlers
 * to which the logging function delegates the messages.
 */
typedef struct _LOG {
	/* the minimum level it should handle */
	int level;
	/* the log handler function */
	log_handler_function funct;
	/* the next log node */
	struct _LOG *next;
} LOG;

/**
 * Prototype for a logging function
 */
typedef void (*logging_function)(LOG *, int, char *);

/**
 * Add a new handler to a log. If the LOG is NULL a new LOG will be 
 * returned if the handler was added otherwise NULL. If the LOG is not 
 * NULL the original pointer will be returned if the handler was not 
 * added, otherwise a new address will be returned. 
 */
LOG *logging_add_handler(LOG *, int, log_handler_function);

/**
 * Removes the given handler from the log. This function may return 
 * NULL if no more handlers are available in the LOG. Nothing happens 
 * if the LOG is NULL.
 */
LOG *logging_remove_handler(LOG *log, log_handler_function);

/**
 * Releases the log by removing all the handlers. Nothing happens if 
 * the LOG is NULL.
 */
void logging_release(LOG *);

/**
 * Default log handler that will output messages to stderr
 */
void logging_default_handler(int, char*);

/**
 * A logging function that does nothing
 */
void logging_dummy_funct(LOG *, int, char*);

/**
 * A logging function that goes over all the log handlers and 
 * calls the handler functions if the log level for each function
 * is at most the log level passed to the logging function
 */
void logging_default_funct(LOG *, int, char*);

#endif

