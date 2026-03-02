#include "shell.h"
#include "stdio.h"
#include "../../stdlib/src/stdlib.h"
#include "../../stdlib/src/pen1x.h"
int main(int argc, char** argv)
{
    print("Pen1X v1.0.0\n");
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