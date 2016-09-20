#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/*
Lowercase letters a-z ASCII 97 to 122
Uppercase letters A-Z ASCII 65-90
*/

void err(const char* messsage);

int main()
{
    pid_t pid;
    FILE* f;
    int status;
    int oddPos = 1, evenPos = 0;

    pid = fork();

    if(pid < 0)                 //ERROR FORK
        err("fork error");
    else if(pid == 0)           //CHILD FORK
    {
        char c;
        f = fopen("file.txt","w");
        int i;
        for(i = 97; i <= 122; i++)
        {
            c = i;
            fseek(f,oddPos,SEEK_SET);
            fwrite(&c, sizeof(char), 1, f);
			printf("Child  wrote %c to position %d\n", c, oddPos);
            oddPos += 2;
        }
	fclose(f);
    }
    else                        //PARENT FORK
    {
        char c;
        f = fopen("file.txt","w");
        int i;
        for(i = 65; i <= 90; i++)
        {
            c = i;
            fseek(f,evenPos,SEEK_SET);
            fwrite(&c, sizeof(char), 1, f);
			printf("Parent wrote %c to position %d\n", c, evenPos);
            evenPos += 2;
        }
        fclose(f);
		waitpid(pid, &status, 0);
		if(status != 0)
		    err("Child exited with a problem\n");
		exit(0);
    }

    return 0;
}

void err(const char* message)
{
    printf("%s\n", message);
    exit(0);
}
