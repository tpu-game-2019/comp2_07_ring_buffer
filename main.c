#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define RING_SIZE 11
#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))
typedef struct
{
	int Data[RING_SIZE];
	int First;
	int Last;
} RING_BUFFER;
void Init_RING_BUFFER(RING_BUFFER *RingBuffer)
{
	for (int i = 0; i < RING_SIZE; i++)
		RingBuffer->Data[i] = 0;
	RingBuffer->First = 0;
	RingBuffer->Last = 0;
}
void pushRingBuffer(RING_BUFFER *RingBuffer, int Data)
{
	if ((RingBuffer->Last + 1) % RING_SIZE == RingBuffer->First)
		return;
	RingBuffer->Data[RingBuffer->Last] = Data;
	RingBuffer->Last = (RingBuffer->Last + 1) % RING_SIZE;
}
int popRingBuffer(RING_BUFFER *RingBuffer)
{
	int f = RingBuffer->Data[RingBuffer->First];
	RingBuffer->Data[RingBuffer->First] = 0;
	RingBuffer->First = (RingBuffer->First + 1) % RING_SIZE;
	return f;
}
void ShowRingBuffer(RING_BUFFER *RingBuffer)
{
	if (RingBuffer->First == RingBuffer->Last)
	{
		printf("\n");
		return;
	}
	for (int i = RingBuffer->First; i!=RingBuffer->Last; i=(i+1)% RING_SIZE)
	{
		printf("%d", RingBuffer->Data[i]);
		if (RingBuffer->Last == (i+1)% RING_SIZE)
			printf("\n");
		else
			printf(",");
	}
}
int main(int argc, char *argv[])
{
	char str[7];
	RING_BUFFER Buffer;
	Init_RING_BUFFER(&Buffer);
	while (fgets(str, sizeof(str), stdin))
	{
		int tmp = atoi(str);
		if (tmp == -1)
			printf("%d\n", popRingBuffer(&Buffer));
		else if (tmp == 0)
			ShowRingBuffer(&Buffer);
		else
			pushRingBuffer(&Buffer, atoi(str));
	}

	return 0;
}
