#include "terminal.h"
#include "../include/types.h"
#include "../include/strings.h"

unsigned char *command;
int i = 0;

void terminal_cursor() {
    printf("[ETHIOPIC]> ", -1, -1);

}

void terminal_init() {
    printf("\n", -1, -1);
    printf("                [ ETHIOPIC 32 BIT OPERATING SYSTEM ]             ", -1, -1);
    printf("                                     [ TERMINAL TEXT MODE ]                        ", -1, -1);
    printf("\n", -1, -1);
    printf("\n", -1, -1);
    printf("\n", -1, -1);
    terminal_cursor();
}

void terminal_accept_command(unsigned char newline) {
    command[i] = newline;
    if(newline != '\b')
        print_char(command[i], -1, -1, 0);
    else
        i = i - 2;          // if the backspace is pressed decrement the value of i

    i++;
    if(newline == '\n') {
        command[i-1] = '\0';
        // compare the strings
        if(string_compare(command, "help", string_length("help")) > 0) {
            help();
        } else if(string_compare(command, "clear", string_length("clear")) > 0) {
            clear_screen();
        } else if(string_compare(command, "shutdown", string_length("shutdown")) > 0) {
            shutdown();
        } else if(string_compare(command, "restart", string_length("restart")) > 0) {
            restart();
        } else if(string_compare(command, "halt", string_length("halt")) > 0) {
            halt();
        } else if(string_compare(command, "meminfo", string_length("meminfo")) > 0) {
            printf("System Memory Information\n", -1, -1, -1);
            printf("-------------------------\n\n", -1, -1, -1);
            printf("4 GB Memory Installed\n", -1, -1, -1);
            printf("Ramtype: DDR3\n", -1, -1, -1);
        } else if(string_compare(command, "netconfig", string_length("netconfig")) > 0) {
            printf("Ethiopic Network Configuration\n", -1, -1, -1);
            printf("------------------------------\n\n", -1, -1, -1);
            printf("IP Address: 192.168.1.1\n", -1, -1, -1);
            printf("Subnet Mask: 255.255.255.0\n", -1, -1 ,-1);
            printf("MAC ADDRESS: cd:4f:5b:7a:8a:99\n", -1, -1, -1);
            printf("ExtraSecLayer: Disabled\n", -1, -1, -1);
        } else if(string_compare(command, "whoami", string_length("")) > 0) {
            printf("ethiopic\\user1", -1, -1, -1);
        } else if(string_compare(command, "man", string_length("man")) > 0) {
            printf("Sorry! Currently there is no manuals.\n", -1, -1, -1);
        } else {
            printf("Command not found\n", -1, -1, -1);
        }
        i = 0;                     
        terminal_cursor();
    }
}

void help() {
    printf("\n", -1, -1);
    printf("help - to show this message\n", -1, -1);
    printf("clear - clear the screen\n", -1, -1);
    printf("shutdown - to shutdown the computer\n", -1, -1);
    printf("netconfig - Display network interfaces and IP addresses\n", -1, -1);
    printf("whoami - Get the active username\n", -1, -1);
    printf("ls - to list directories\n", -1, -1);    
    printf("man - Access manual pages for all Ethiopic 32 bit Intel OS commands\n", -1, -1);
    printf("restart - restart the computer\n", -1, -1);
    printf("halt - to halt this computer\n", -1, -1);
    printf("meminfo - get memory information\n", -1, -1);
    printf("\n", -1, -1);
}

void shutdown() {
	__asm__ __volatile__ ("outw %1, %0" : : "dN" ((uint16_t)0xB004), "a" ((uint16_t)0x2000));
}

void restart() {
    port_byte_out(0x64, 0xfe);
}

void halt() {
    __asm__("hlt");
}