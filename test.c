
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "logging.h"

LOG *log_=NULL;

logging_function logger=logging_default_funct;

void custom_logger_func(int level, char *message) {
	printf("T - %s(%d) - %s\n",logging_str(level),level,message);
}

int main(void) {

	log_=logging_add_handler(log_,INFO,custom_logger_func);

	logger(log_,FINER,"This should not show up.");
	logger(log_,INFO,"This is info");
	logger(log_,SEVERE,"This is a disaster!");

	logging_release(log_);

	return 0;
}


