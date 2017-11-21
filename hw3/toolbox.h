#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>


void close_socket(int s){
	close(s);
}

void print_cwnd(int cwnd){
	printf("CWND = %d\n", cwnd);
}

void print_duplicate(){
	printf("3 duplicate ack\n");
}

void print_timeout(){
	printf("Time out\n");
}

// #######################################################################################

typedef enum {
	_SLOW_START,
	_C_AVOID,
	_RECOVER,
} FSM_STATE;

struct TCP_FSM {
	int seq, last_acked, cwnd, cwnd_seq;
  int dup_ack, dup_count;
  int ack;
  int ssthresh;
  FSM_STATE state;
};

struct TCP_PK {
	int ack;
	int seq;
	char data[100];
  int data_size;
};

typedef enum {
	_ACKED,
	_DUP,
	_OUT_ORDER,
  _UNKOWN,
} ACK_STATE;

ACK_STATE ACK_check(struct TCP_PK *pk, struct TCP_FSM *fsm) {
  if (pk->ack >= 0 && pk->ack == fsm->last_acked + 1)
    return _ACKED;
  else if (pk->ack >= 0 && pk->ack <= fsm->last_acked)
    return _OUT_ORDER;
  else if (pk->ack >= 0 && pk->ack == fsm->last_acked)
    return _DUP;
  else
    return _UNKOWN;
}
// int PK_size(TCP_PK &pk) {
// 	return pk.data_size + sizeof(int) * 2;
// }
