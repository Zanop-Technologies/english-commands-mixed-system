#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <sys/utsname.h>
#include <unistd.h>

using namespace std;

// --- HELPER FUNCTIONS ---
vector<string> tokenize(const string& input) {
    vector<string> tokens;
    stringstream ss(input);
    string token;
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

string getRAM() {
    ifstream meminfo("/proc/meminfo");
    string line;
    while (getline(meminfo, line)) {
        if (line.find("MemTotal:") == 0) {
            stringstream ss(line);
            string key;
            long kb;
            ss >> key >> kb;
            return to_string(kb / 1024) + " MB";
        }
    }
    return "Unknown";
}

string getArch() {
    struct utsname buffer;
    uname(&buffer);
    return buffer.machine;
}

// --- COMMAND IMPLEMENTATIONS ---

void cmdHelp() {
    cout << "\n--- [ECMXS HELP MANUAL] ---\n";
    cout << "FILE MANAGEMENT:\n";
    cout << "  chd <dir>              - Move into a directory\n";
    cout << "  con                    - List directory contents\n";
    cout << "  cre <file>             - Create a file\n";
    cout << "  cre dir <dir>          - Create a directory\n";
    cout << "  del <file> / rm <file> - Delete a file\n";
    cout << "  del --dir <dir>        - Delete a directory\n\n";
    
    cout << "INSTALLED APPLICATIONS:\n";
    cout << "  lis app                - List installed apps\n";
    cout << "  lis app --spef <ltr>   - Filter by specific letter\n";
    cout << "  lis app --search <wd>  - Search apps by word\n";
    cout << "  lis app --mul --spef --wd --search <wd> - Advanced multi-filter\n\n";

    cout << "NETWORKING:\n";
    cout << "  curl --int <URL>       - Interact with a URL\n";
    cout << "  curl --dd <URL>        - Download a URL\n";
    cout << "  frt -i -p <pkts> <ip>  - Fart Route Test (Ping)\n\n";

    cout << "SYSTEM MANAGEMENT:\n";
    cout << "  sy stat                - System statistics\n";
    cout << "  sy stat --log          - System logs\n";
    cout << "  sy stat --spef --prt   - Specific component stats\n";
    cout << "  sy tsk                 - Task Manager\n";
    cout << "  sy tsk --end --spef    - End specific task\n";
    cout << "  sy tsk --end --l       - End all user tasks\n\n";

    cout << "PACKAGE & USER MANAGEMENT:\n";
    cout << "  sft install <pkg>      - Install a package\n";
    cout << "  usr --adm --cre <name> - Create user\n";
    cout << "  usr --adm --del <name> - Delete user\n\n";

    cout << "UTILITIES:\n";
    cout << "  sdown                  - Shutdown\n";
    cout << "  lg                     - Logout\n";
    cout << "  lg --all               - Logout all sessions\n";
    cout << "---------------------------\n";
}

void cmdSyStat(const vector<string>& args) {
    if (args.size() > 1 && args[1] == "--log") {
        cout << "\n--- [ZANOP OS SYSTEM LOGS] ---\n";
        cout << "[OK] Kernel booted successfully.\n";
        cout << "[OK] ECMXS Shell initialized.\n";
        cout << "[WARN] Detected legacy UNIX commands in history. Purged.\n";
        cout << "------------------------------\n";
    } else if (args.size() > 2 && args[1] == "--spef" && args[2] == "--prt") {
        cout << "\n--- [SPECIFIC PART STATISTICS] ---\n";
        cout << "CPU Architecture: " << getArch() << "\n";
        cout << "Total RAM       : " << getRAM() << "\n";
        cout << "----------------------------------\n";
    } else {
        cout << "\n--- [ZANOP OS SYSTEM STATISTICS] ---\n";
        cout << "OS Name      : Zanop OS (Drajevo Kernel)\n";
        cout << "Architecture : " << getArch() << "\n";
        cout << "Total Memory : " << getRAM() << "\n";
        cout << "------------------------------------\n";
    }
}

void cmdFrt(const vector<string>& args) {
    string ip = "1.1.1.1";
    int pkts = 3;
    
    for (size_t i = 1; i < args.size(); ++i) {
        if (args[i] == "-p" && i + 1 < args.size()) pkts = stoi(args[++i]);
        else if (args[i] != "-i") ip = args[i];
    }
    
    cout << "\n[ECMXS] Initializing F.R.T. (Fart Route Test) to " << ip << "...\n";
    for (int i = 0; i < pkts; ++i) {
        string sound = (i % 3 == 0) ? "*poot*  " : ((i % 3 == 1) ? "*squeak*" : "*brrrrt*");
        cout << sound << " Reply from " << ip << ": bytes=64 time=12ms TTL=58\n";
    }
    cout << "\nGastrointestinal networking complete. 0% packet loss.\n\n";
}

void cmdLisApp(const vector<string>& args) {
    vector<string> apps = {"browser", "editor", "music_player", "kernel_core", "sys_daemon"};
    bool search = false;
    string term = "";

    for (size_t i = 1; i < args.size(); ++i) {
        if (args[i] == "--search" || args[i] == "--spef" || args[i] == "--wd") search = true;
        else if (args[i][0] != '-') term = args[i];
    }

    cout << "\n--- [INSTALLED APPLICATIONS] ---\n";
    if (search && !term.empty()) {
        cout << "Filtering for: " << term << "\n";
        for (const auto& app : apps) {
            if (app.find(term) != string::npos) cout << "- " << app << "\n";
        }
    } else {
        for (const auto& app : apps) cout << "- " << app << "\n";
    }
    cout << "--------------------------------\n";
}

void cmdSyTsk(const vector<string>& args) {
    if (args.size() > 2 && args[1] == "--end") {
        if (args[2] == "--spef") {
            cout << "\n[ZANOP KERNEL] Ending specific task...\n[SUCCESS] Task terminated.\n\n";
        } else if (args[2] == "--l") {
             cout << "\n[ZANOP KERNEL] Terminating all normal user tasks...\n";
             cout << "[SUCCESS] browser terminated.\n";
             cout << "[SUCCESS] editor terminated.\n";
             cout << "[NOTE] System core tasks untouched. /sys integrity maintained.\n\n";
        }
    } else {
        cout << "\n--- [ZANOP TASK MANAGER] ---\n";
        cout << "PID\tAPP\t\tSTATUS\n";
        cout << "101\tbrowser\t\tACTIVE\n";
        cout << "102\teditor\t\tBACKGROUND\n";
        cout << "001\tsys_core\tIMMUTABLE\n";
        cout << "---------------------------\n";
    }
}

// --- MAIN SHELL LOOP ---
int main() {
    string input;
    cout << "\033[2J\033[1;1H"; // Clear screen
    cout << "==========================================\n";
    cout << "  ZANOP OS v1.0 - ECMXS SHELL (DEMO)\n";
    cout << "==========================================\n";
    cout << "Type 'help' to see all commands.\n\n";

    while (true) {
        cout << "root@zanop~$ ";
        getline(cin, input);
        if (input.empty()) continue;

        vector<string> tokens = tokenize(input);
        string cmd = tokens[0];

        if (cmd == "help") {
            cmdHelp();
        } else if (cmd == "sy") {
            if (tokens.size() > 1 && tokens[1] == "stat") cmdSyStat(tokens);
            else if (tokens.size() > 1 && tokens[1] == "tsk") cmdSyTsk(tokens);
            else cout << "Error: Invalid 'sy' syntax.\n";
        } else if (cmd == "lis") {
            if (tokens.size() > 1 && tokens[1] == "app") cmdLisApp(tokens);
            else cout << "Error: Invalid 'lis' syntax.\n";
        } else if (cmd == "frt") {
            cmdFrt(tokens);
        } else if (cmd == "curl" || cmd == "wget") {
            cout << "[ECMXS] Interacting with " << (tokens.size() > 2 ? tokens.back() : "URL") << "...\n[SUCCESS] Simulation complete.\n";
        } else if (cmd == "sft") {
            cout << "[SFT] Package Manager: Processing '" << input << "'...\n[SUCCESS] Done.\n";
        } else if (cmd == "usr") {
            cout << "[USR] User Management: Processing '" << input << "'...\n[SUCCESS] Done.\n";
        } else if (cmd == "sdown") {
            cout << "Shutting down Zanop OS...\n";
            break;
        } else if (cmd == "lg") {
            if (tokens.size() > 1 && tokens[1] == "--all") cout << "Logging out all sessions...\n";
            else cout << "Logging out of Zanop OS...\n";
            break;
        } else if (cmd == "sudo" || cmd == "ls" || cmd == "cd" || cmd == "rm") {
            cout << "Error: Command '" << cmd << "' is a legacy UNIX command.\nThis is Zanop OS. Use ECMXS commands.\n";
        } else {
            cout << "Error: Command '" << cmd << "' not found. Type 'help' for a list of commands.\n";
        }
    }
    return 0;
}
