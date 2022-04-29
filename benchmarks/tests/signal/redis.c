 /*
 * author: Priyal Suneja ; suneja@cs.washington.edu
 * 
 * to run: sudo ./build/l1_msr
 */

#include "signal.h"
#include <stdlib.h>
#include "../../includes/hiredis/hiredis.h"

void redis_measure() {
    // run redis here
    // client and server on same socket
    
	const char* hostname = "127.0.0.1";

	int port = 6379;

	redisContext *c = redisConnect(hostname, port);

	if (c != NULL && c->err) {
		printf("Error: %s\n", c->errstr);	
	} else {
		printf("Connected to Redis");
	}

	// redis operations
	redisReply* reply;
	
	reply = redisCommand(c, "SET %s %s", "foo", "bar");
	freeReplyObject(reply);

	reply = redisCommand(c, "GET %s", "foo");
	printf("%s\n", reply->str);
	freeReplyObject(reply);

	redisFree(c);
	return;
}

void redis_client_measure() {
    // run redis here
    // client only on socket being measured

	return;
}

void redis_server_measure() {
    // run redis here
    // server only on socket being measured

	return;
}

int main (int argc, char* argv[]) {

    // measure_msr("redis_client_measure_out", &redis_client_measure);

    // measure_msr("redis_server_measure_out", &redis_server_measure);

    measure_msr("redis_measure_out", &redis_measure);

    return 0;

}
