#include "shell.h"
#include "stdio.h"
#include "stdlib.h"
#include "pen1x.h"
int main(int argc, char** argv)
{
    while(1) 
    {
        print("> ");
        char buf[1024];
        pen1x_terminal_readline(buf, sizeof(buf), true);
        print("\n");
        pen1x_process_load_start(buf);
        
    }
    return 0;
}