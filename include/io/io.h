#ifndef IO_H
#define IO_H

unsigned char insb(unsigned short port);
unsigned short insw(unsigned short port);
//double word below hasnt yet been implemented
unsigned short insd(unsigned short port);


void outb(unsigned short port, unsigned char val);
void outw(unsigned short port, unsigned short val);
//double word below hasnt yet been implemented
void outd(unsigned short port, unsigned short val);



#endif