
/* msgrcv.c */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

enum _msg_type
{
	MSG_TYPE_MIN = 0,
	MSG_TYPE_INPUT,
	MSG_TYPE_STRING,
	MSG_TYPE_TEST,
	MSG_TYPE_MAX
} msg_type;

struct message
{
	long msg_type;
	char msg_text[BUFSIZ];
};

int main ()
{
	int qid;
	key_t key;
	struct message msg;

	/*根据不同的路径和关键表示产生标准的key */
	if ((key = ftok (".", 'a')) == -1) {
		perror ("ftok");
		exit (1);
	}

	/*创建消息队列 */
	if ((qid = msgget (key, IPC_CREAT | 0666)) == -1) {
		perror ("msgget");
		exit (1);
	}
	printf ("Open queue %d\n", qid);

	do {
		/*读取消息队列 */
		memset (msg.msg_text, 0, BUFSIZ);
		if (msgrcv (qid, (void *) &msg, BUFSIZ, -MSG_TYPE_MAX, 0) < 0) {
			perror ("msgrcv");
			exit (1);
		}
		printf ("The message from process %ld : %s", msg.msg_type, msg.msg_text);

	} while (strncmp (msg.msg_text, "quit", 4));


	/*从系统内核中移走消息队列 */
	if ((msgctl (qid, IPC_RMID, NULL)) < 0) {
		perror ("msgctl");
		exit (1);
	}

	exit (0);
}
