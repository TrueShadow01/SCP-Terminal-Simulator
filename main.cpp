#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <unordered_map>
#include <functional>

void login(std::string username, std::string password);
void signUp(int option, std::string username, std::string password);
void terminal();
void readSCPFile(const std::string& filename);
void listSCPs();

void menu(int option, std::string username, std::string password) {
	std::cout << "##################################################################" << std::endl;
	std::cout << "S.C.P. TERMINAL V0.0.1 - AUTHORIZED PERSONNEL ONLY" << std::endl;
	std::cout << "NON AUTHORIZED PERSONNEL WILL BE TERMINATED" << std::endl;
	std::cout << "##################################################################" << std::endl;
	std::cout << std::endl;
	std::cout << "1. LOGIN" << std::endl;
	std::cout << "2. SIGN UP" << std::endl;
	std::cout << "3. EXIT TERMINAL" << std::endl;
	std::cout << "CHOOSE A OPTION: ";
	std::cin >> option;
	std::cout << std::endl;
	switch (option) {
	case 1:
		login(username, password);
		break;
	case 2:
		signUp(option, username, password);
		break;
	case 3:
		std::cout << "EXITING TERMINAL SESSION.\nGOODBYE!" << std::endl;
		break;
	}
}

void login(std::string username, std::string password) {
	std::cout << "SCP TERMINAL LOGIN" << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << std::endl;
	std::cout << "USERNAME: " << username << std::endl;
	std::cout << "PASSWORD: " << password << std::endl;
	std::cout << "LOGGING IN........." << std::endl;
	std::cout << "VERIFIYING........." << std::endl;
	std::cout << "SUCCESS!" << std::endl;
	std::cout << "NOTE: ACTION LOGGED BY 'ALPHA', NO ACTION REQUIRED FROM USER." << std::endl;
	std::cout << "2 OTHER USERS ONLINE: [REDACTED], ALPHA" << std::endl;
	std::cout << "WELCOME DR. BRIGHT, YOUR LAST LOGIN WAS 98723 DAYS AGO.\nYOU HAVE 5 UNREAD MESSAGES.\nYOUR CURRENT CLEARANCE LEVEL IS 4+/*//#\n[MESSAGE TERMINATED DUE TO CORRUPTED BITS! CONTINUING EXECUTION]" << std::endl;
	terminal();
}

void signUp(int option, std::string username, std::string password) {
	std::cout << "SCP TERMINAL SIGNUP" << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << std::endl;
	std::cout << "/#/*//USERNAME/(&%$$%§$&" << std::endl;
	std::cout << "ATTEMPTING REBOOT OF SIGNUP PROGRAM..." << std::endl;
	std::cout << "REBOOTING SIGNUP.EXE...." << std::endl;
	std::cout << "ERROR: SIGNUP.EXE MEMORY VIOLATION, UNABLE TO LOAD!" << std::endl;
	std::cout << "INCIDENT REPORTED TO 'ALPHA' FOR FUTHER INVESTIGATION.\nIF YOU ARE A [DATA EXPUNGED] PLEASE REPORT TO [REDACTED] FOR FUTHER ACTIONS." << std::endl;
	std::cout << "EXITING TO MENU!" << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	menu(option, username, password);
}

void terminal() {
	std::string input;
	std::unordered_map<std::string, std::function<void()>> commands;

	commands["help"] = []() {
		std::cout << "list_scps | LIST ALL AVAILABLE SCP FILES IN THE SYSTEM" << std::endl;
		std::cout << "access_scp_[SCP NUMBER] | ACCESS THE SCP FILE CORESPONDING TO THE PROVIDED SCP NUMBER. ID MUST BE PRESENT IN THE SYSTEM TO BE ABLE TO BE ACCESSED" << std::endl;
		std::cout << "whoami | PRINTS CURRENT USER WITH SOME OTHER INFORMATION" << std::endl;
	};

	commands["list_scps"] = []() {
		listSCPs();
	};

	commands["whoami"] = []() {
		std::cout << "Dr. Bright | Clearance Level: [CORRUPTED BIT DETECTED] | Status: ALIVE, OBSERVING" << std::endl;
	};

	commands["exit"] = []() {
		std::cout << "TERMINAL SESSION ENDING..." << std::endl;
		std::cout << "GOODBYE!!!!" << std::endl;
		exit(0);
	};

	std::cout << std::endl;
	std::cout << "TO VIEW A LIST OF ALL AVAILABLE COMMANDS TYPE 'help' AND PRESS ENTER" << std::endl;
	std::cout << std::endl;

	while (true) {
		std::cout << ">";
		std::cin >> input;

		if (input.rfind("access_scp_", 0) == 0) {
			std::string scpId = input.substr(11);
			readSCPFile(scpId);
		}
		else if (commands.contains(input)) {
			commands[input]();
		}
		else {
			std::cout << "UNKNOWN COMMAND!" << std::endl;
			std::cout << "INCIDENT WILL BE REPORTED TO 'ALPHA' FOR FUTHER INVESTIGATION!" << std::endl;
		}
	}
}

void readSCPFile(const std::string& scpId) {
	std::string path = "SCPFiles/SCP-" + scpId + ".txt";
	std::ifstream file(path);

	if (!file.is_open()) {
		std::cout << "ERROR: Unable to open File '" << path << "'!" << std::endl;
		return;
	}

	std::string line;
	while (std::getline(file, line)) {
		std::cout << line << std::endl;
	}

	file.close();
}

void listSCPs() {
	std::string folder = "SCPFiles";

	if (!std::filesystem::exists(folder) || !std::filesystem::is_directory(folder)) {
		std::cout << "ERROR FILE OR DIRECTORY NOT FOUND!" << std::endl;
		return;
	}

	std::cout << "SCP ENTRIES:" << std::endl;
	for (const auto& entry : std::filesystem::directory_iterator(folder)) {
		if (entry.path().extension() == ".txt") {
			std::string filename = entry.path().stem().string();
			std::cout << "- " << filename << std::endl;
		}
	}
}

int main() {
	int option = 0;
	std::string username = "dr_bright";
	std::string password = "secure123";

	menu(option, username, password);

	return 0;
}