/*
 * Shell.h
 *
 *  Created on: Apr 29, 2024
 *      Author: MinhNhan
 */

#ifndef MAIN_COMPONENTS_SHELL_SHELL_H_
#define MAIN_COMPONENTS_SHELL_SHELL_H_
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <stdbool.h>
class Shell {
public:
	typedef struct ShellCommand{
		const char *cmd;
		int (*handle)(std::vector<char*> *argv);
		const char *help;
	}ShellCommand_t;

	typedef struct ShellInterface{
		void (*p_putc)(char c);
		char (*p_getc)();
	}ShellInterface_t;

	typedef struct ShellCommandList{
		ShellCommand_t *command;
		int numCommands;
	}ShellCommandList_t;

	Shell();
	virtual ~Shell();
	Shell(ShellCommandList_t *commands,ShellInterface_t *interface);
	virtual void putc(char c);
	virtual char getc();
	void puts(const char *s);
	void println(const char *s);
	virtual void process();
	void setInterface(ShellInterface_t *interface);
	const ShellCommandList_t* getCommands() const {
		return commands;
	}
	void echoEnable(){
		echo = true;
	}
	void echoDisable(){
		echo = false;
	}
	void setCommands(ShellCommandList_t *commands) {
		this->commands = commands;
	}

private:
	ShellInterface_t *interface;
	std::vector<char *> argv;
	std::vector<char *> *split(char *src);
	ShellCommandList_t *commands;
	ShellCommand_t help_command;
	int help_handle(std::vector<char*> *argv);
	std::string line;
	bool echo;
};

extern Shell::ShellCommandList_t commandsList;

#endif /* MAIN_COMPONENTS_SHELL_SHELL_H_ */
