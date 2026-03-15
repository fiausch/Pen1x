#include "shell.h"
#include "stdio.h"
#include "stdlib.h"
#include "pen1x.h"
int main(int argc, char** argv)
{
    print("Pen1x v1.0.0\n");
    while(1) 
    {
        print("> ");
        char buf[1024];
        pen1x_terminal_readline(buf, sizeof(buf), true);
        pen1x_process_load_start(buf);
        
        print("\n");
    }
    return 0;
}