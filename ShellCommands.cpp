/*
 * ShellCommand.h
 *
 *  Created on: Apr 29, 2024
 *      Author: MinhNhan
 */

#include <Shell/Shell.h>
#include <stdint.h>
#include <vector>
#include <string>

static int helloworld(std::vector<char*> *argv){
	printf("******Hello World******\r\n");
	return 0;
}

static int restart(std::vector<char*> *argv){
	for(uint16_t i = 5;i>0;i--){
		printf("Restart after %d seconds\r\n",i);
		sleep(1);
	}
	return 0;
}

Shell::ShellCommand_t commands[] = {{"hello",helloworld,"Say hello world"},
									{"restart",restart,"Restart device"}};

Shell::ShellCommandList_t commandsList = {
		.command = commands,.numCommands = 2
};
