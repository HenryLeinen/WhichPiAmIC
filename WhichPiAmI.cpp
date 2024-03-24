#include <iostream>
#include <fstream>
#include <map>
#include <string>

// Funktion, um die Raspberry Pi-Version zu erhalten
std::string get_raspberry_pi_version() {
    // Öffne die Datei mit den Raspberry Pi Versionen
    std::ifstream file("raspi_versions.json");
    if (!file.is_open()) {
        return "Fehler beim Öffnen der Datei mit den Raspberry Pi-Versionen";
    }
    
    // Lese den JSON-Inhalt in eine Map
    std::map<std::string, std::string> versions;
    file >> versions;
    file.close();
    
    // Öffne die Datei cpuinfo und lies die Hardware-Revision
    file.open("/proc/cpuinfo");
    if (!file.is_open()) {
        return "Fehler beim Öffnen der Datei /proc/cpuinfo";
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.find("Revision") == 0) {
            // Extrahiere die Hardware-Revision und entferne das "Revision:"-Präfix
            std::string revision = line.substr(line.find(":") + 1);
            // Entferne führende Leerzeichen
            size_t pos = revision.find_first_not_of(" \t");
            if (pos != std::string::npos) {
                revision = revision.substr(pos);
            }
            return (versions.count(revision) > 0) ? versions[revision] : "Raspberry Pi-Version für Hardware-Revision " + revision + " nicht gefunden";
        }
    }
    return "Hardware-Revision nicht gefunden in /proc/cpuinfo";
}

// Hauptprogramm
int main() {
    std::string version = get_raspberry_pi_version();
    std::cout << "Raspberry Pi-Version: " << version << std::endl;
    return 0;
}
