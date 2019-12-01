#include <stdio.h>
#include <string.h>
#define RING_SIZE 11
#define ARRAY_LENGTH(x)(sizeof(x)/sizeof(x[0]))
typedef struct 
{
	const char* Data[RING_SIZE];
	int First;
	int Last;
}RING_BUFFER;
void Init_RING_BUFFER(RING_BUFFER*RingBuffer)
{
	for (int i = 0; i < RING_SIZE; i++)
		RingBuffer->Data[i] = NULL;
	RingBuffer->First = 0;
	RingBuffer->Last = 0;
}
void pushRingBuffer(RING_BUFFER*RingBuffer,const char* Data)
{
	if((RingBuffer->Last+1)%RING_SIZE==RingBuffer->First)
		return ;
	RingBuffer->Data[RingBuffer->Last] = Data;
	RingBuffer->Last = (RingBuffer->Last + 1) % RING_SIZE;
}
const char* popRingBuffer(RING_BUFFER*RingBuffer)
{
	int f = RingBuffer->First;
	RingBuffer->First = (RingBuffer->First + 1) % RING_SIZE;
	return RingBuffer->Data[f];
}
void ShowRingBuffer(RING_BUFFER*RingBuffer)
{
	for (int i = 0; i <RING_SIZE-1; i++)
	{
		printf("%s",RingBuffer->Data[i]);
		if (RING_SIZE - 1 == i + 1)
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
		if(strcmp(str, "-1"))
			printf("%s", popRingBuffer(&Buffer));
		else if (strcmp(str, "0"))
			ShowRingBuffer(&Buffer);
		else
			pushRingBuffer(&Buffer, str);
	}

	return 0;
}
