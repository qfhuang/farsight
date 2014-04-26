
/* msgsnd.c */

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

	/*���ݲ�ͬ��·���͹ؼ���ʾ������׼��key */
	if ((key = ftok (".", 'a')) == -1) {
		perror ("ftok");
		exit (1);
	}

	/*������Ϣ���� */
	if ((qid = msgget (key, IPC_CREAT | 0666)) == -1) {
		perror ("msgget");
		exit (1);
	}
	printf ("Open queue %d\n", qid);

	while (1) {
		printf ("Enter some message to the queue(enter 'quit' to exit):");
		if ((fgets (msg.msg_text, BUFSIZ, stdin)) == NULL) {
			puts ("no message");
			exit (1);
		}

		msg.msg_type = MSG_TYPE_INPUT;

		/*�����Ϣ����Ϣ���� */
		if ((msgsnd (qid, &msg, strlen (msg.msg_text), 0)) < 0) {
			perror ("message posted");
			exit (1);
		}

		if (strncmp (msg.msg_text, "quit", 4) == 0) {
			break;
		}
	}

	exit (0);
}
