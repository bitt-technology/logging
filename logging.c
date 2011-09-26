
#include <stdlib.h>
#include <stdio.h>

#include "logging.h"


/**
 * Return __USER_DEFINED__ for any level 
 * that's outside of the enum
 */
const char *logging_str(int level) {
	switch(level) {
		case 0: return "FINEST";
		case 1: return "FINER";
		case 2: return "FINE";
		case 3: return "INFO";
		case 4: return "WARNING";
		case 5: return "SEVERE";
		case 6: return "ALL";
		default: return "__USER_DEFINED__";
	}
}

LOG *logging_add_handler(LOG *log, int level, 
		log_handler_function funct) {
	LOG *node=malloc(sizeof*log);
	if(!node) {
		return log;
	}
	node->level=level;
	node->funct=funct;
	node->next=log;
	return node;
}

LOG *logging_remove_handler(LOG *log, log_handler_function funct) {
	LOG *p, *d;
	if(!log) {
		return log;
	}
	if(!log->next && log->funct==funct) {
		free(log);
		return NULL;
	}
	p=log;
	while(p->next) {
		if(p->next->funct==funct) {
			d=p->next;
			p->next=d->next;
			free(d);
		} else {
			p=p->next;
		}
	}
	return p;
}

void logging_release(LOG *log) {
	LOG *p;
	while(log) {
		p=log;
		log=log->next;
		free(p);
	}
}

void logging_dummy_funct(LOG *log, int level, char *message) {}

void logging_default_funct(LOG *log, int level, char *message) {
	while(log) {
		if(level>=log->level) {
			log->funct(level, message);
		}
		log=log->next;
	}
}

void logging_default_handler(int level, char *message) {
	fprintf(stderr, "%s(%d) - %s\n",logging_str(level),
			level, message);
}


