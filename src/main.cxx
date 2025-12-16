#include <iostream>
#include <fstream>
#include <string>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <sys/statvfs.h>
#include <unistd.h>
#include <cstdlib>
#include <ifaddrs.h>
#include <arpa/inet.h>

// ---------------- CPU ----------------
std::string get_cpu_model() {
    std::ifstream file("/proc/cpuinfo");
    std::string line;
    while (std::getline(file, line)) {
        if (line.rfind("model name", 0) == 0) {
            return line.substr(line.find(':') + 2);
        }
    }
    return "Unknown";
}

// ---------------- OS ----------------
std::string get_os_name() {
    std::ifstream file("/etc/os-release");
    std::string line;
    while (std::getline(file, line)) {
        if (line.rfind("PRETTY_NAME=", 0) == 0) {
            return line.substr(13, line.size() - 14);
        }
    }
    return "Unknown";
}

// ---------------- Host model ----------------
std::string get_host_model() {
    std::ifstream file("/sys/class/dmi/id/product_name");
    std::string model;
    std::getline(file, model);
    return model.empty() ? "Unknown" : model;
}

// ---------------- Disk ----------------
void get_disk_usage(long &used, long &total) {
    struct statvfs fs;
    statvfs("/", &fs);
    total = fs.f_blocks * fs.f_frsize / (1024 * 1024);
    used  = (fs.f_blocks - fs.f_bfree) * fs.f_frsize / (1024 * 1024);
}

// ---------------- Swap ----------------
void get_swap(long &used, long &total) {
    struct sysinfo info;
    sysinfo(&info);
    total = info.totalswap * info.mem_unit / (1024 * 1024);
    used  = (info.totalswap - info.freeswap) * info.mem_unit / (1024 * 1024);
}

// ---------------- Local IP ----------------
std::string get_local_ip() {
    struct ifaddrs *ifaddr;
    getifaddrs(&ifaddr);

    for (auto *ifa = ifaddr; ifa; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr &&
            ifa->ifa_addr->sa_family == AF_INET &&
            std::string(ifa->ifa_name) != "lo") {

            char ip[INET_ADDRSTRLEN];
            inet_ntop(AF_INET,
                      &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr,
                      ip, sizeof(ip));
            freeifaddrs(ifaddr);
            return ip;
        }
    }
    freeifaddrs(ifaddr);
    return "Unknown";
}

// ---------------- Packages ----------------
int get_package_count() {
    std::ifstream file("/var/lib/dpkg/status");
    int count = 0;
    std::string line;
    while (std::getline(file, line)) {
        if (line.rfind("Package:", 0) == 0)
            count++;
    }
    return count;
}

// ---------------- Main ----------------
int main() {
    struct utsname u;
    uname(&u);

    struct sysinfo mem;
    sysinfo(&mem);

    char hostname[256];
    gethostname(hostname, sizeof(hostname));

    long total_ram = mem.totalram * mem.mem_unit / (1024 * 1024);
    long used_ram  = (mem.totalram - mem.freeram) * mem.mem_unit / (1024 * 1024);

    long disk_used, disk_total;
    get_disk_usage(disk_used, disk_total);

    long swap_used, swap_total;
    get_swap(swap_used, swap_total);

    int hours = mem.uptime / 3600;
    int mins  = (mem.uptime % 3600) / 60;

    const char *shell = getenv("SHELL");

    // ASCII logo
	
	// ASCII logo

    std::cout <<
    " ██████╗██╗   ██╗███████╗██╗███╗   ██╗███████╗ ██████╗ \n"
    "██╔════╝╚██╗ ██╔╝██╔════╝██║████╗  ██║██╔════╝██╔═══██╗\n"
    "╚█████╗  ╚████╔╝ ███████╗██║██╔██╗ ██║█████╗  ██║   ██║\n"
    " ╚═══██╗  ╚██╔╝  ╚════██║██║██║╚██╗██║██╔══╝  ██║   ██║\n"
    "███████║   ██║   ███████║██║██║ ╚████║██║     ╚██████╔╝\n"
    "╚══════╝   ╚═╝   ╚══════╝╚═╝╚═╝  ╚═══╝╚═╝      ╚═════╝ \n"
    << std::endl;


    // Output
    std::cout << hostname << "\n";
    std::cout << "-----------\n";
    std::cout << "OS: " << get_os_name() << " " << u.machine << "\n";
    std::cout << "Host: " << get_host_model() << "\n";
    std::cout << "Kernel: " << u.release << "\n";
    std::cout << "Uptime: " << hours << " hours, " << mins << " mins\n";
    std::cout << "Packages: " << get_package_count() << " (dpkg)\n";
    std::cout << "Shell: " << (shell ? shell : "Unknown") << "\n";
    std::cout << "CPU: " << get_cpu_model() << "\n";
    std::cout << "Memory: " << used_ram << " MB / " << total_ram << " MB\n";
    std::cout << "Swap: " << swap_used << " MB / " << swap_total << " MB\n";
    std::cout << "Disk (/): " << disk_used << " MB / " << disk_total << " MB\n";
    std::cout << "Local IP: " << get_local_ip() << "\n";

    return 0;
}

