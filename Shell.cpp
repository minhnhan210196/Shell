/*
 * Shell.cpp
 *
 *  Created on: Apr 29, 2024
 *      Author: MinhNhan
 */

#include "Shell/Shell.h"
#include <stdio.h>
#include <string.h>

#define Shell_Line "$Shell > "

Shell::Shell() {
	// TODO Auto-generated constructor stub

	this->help_command.cmd = "help";
	this->help_command.help = "Show all command";
	this->help_command.handle = NULL;
	argv.clear();
	line.clear();
	this->commands = NULL;
	interface = NULL;
	echo = true;
	puts(Shell_Line);
}

Shell::~Shell() {
	// TODO Auto-generated destructor stub
}

std::vector<char*>* Shell::split(char *src) {
	char *token = strtok(src, " ");
	argv.clear();
	while (token != NULL) {
		argv.push_back(token);
		token = strtok(NULL, " ");
	}
	return &argv;
}

Shell::Shell(ShellCommandList_t *commands,ShellInterface_t *interface) {
	this->help_command.cmd = "help";
	this->help_command.help = "Show all command";
	this->help_command.handle = NULL;
	argv.clear();
	line.clear();
	this->commands = NULL;
	this->interface = NULL;
	echo = true;
	puts(Shell_Line);
}

void Shell::putc(char c) {
	if (interface != NULL)
		interface->p_putc(c);
	else
		putchar(c);
}

char Shell::getc() {
	if (interface != NULL)
		return interface->p_getc();
	return getchar();
}

void Shell::puts(const char *s) {
	for (uint16_t i = 0; i < strlen(s); i++) {
		this->putc(s[i]);
	}
}

void Shell::process() {

	char c = getc();
	if (c != 0 && c != 255) {
		if(echo)
			putc(c);
		if (c == '\n') {
			split((char*) line.c_str());
			if (argv.size() == 0)
				return;
			if (strcmp((const char*) argv[0], help_command.cmd) == 0 && argv.size() == 1) {
				help_handle(&argv);
				line.clear();
				return;
			}
			if (commands == NULL){
				line.clear();
				println("Command error,Please try again");
				return;
			}
			for (unsigned int i = 0; i < commands->numCommands; i++) {
				if (strcmp((const char*) argv[0], commands->command[i].cmd) == 0) {
					commands->command[i].handle(&argv);
					line.clear();
					puts(Shell_Line);
					return;
				}
			}
			line.clear();
			println("Command error,Please try again");
			return;
		}
		line += c;
	}

}

void Shell::println(const char *s) {
	puts(s);
	puts("\r\n");
	puts(Shell_Line);
}

void Shell::setInterface(ShellInterface_t *interface) {
	this->interface = interface;
}

int Shell::help_handle(std::vector<char*> *argv) {

	puts(help_command.cmd);
	puts(" : ");
	puts(help_command.help);
	puts("\r\n");
	puts(Shell_Line);
	if (argv->size() == 1 && commands != NULL) {
		for (unsigned int i = 0; i < commands->numCommands; i++) {
			puts(commands->command[i].cmd);
			puts(" : ");
			puts(commands->command[i].help);
			puts("\r\n");
			puts(Shell_Line);
		}
		return 0;
	}
	return -1;
}
