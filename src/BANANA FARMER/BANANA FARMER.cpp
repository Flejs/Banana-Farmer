#include <windows.h>
#include <iostream>
#include <vector>
#include <string>

// Globální proměnná pro uložení názvu okna
std::wstring windowName = L"Banana";
std::vector<HWND> foundWindows;

// Callback funkce pro EnumWindows
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    WCHAR windowTitle[256];
    GetWindowText(hwnd, windowTitle, sizeof(windowTitle) / sizeof(windowTitle[0]));

    if (std::wstring(windowTitle).find(windowName) != std::wstring::npos) {
        foundWindows.push_back(hwnd);
    }
    return TRUE;
}

void ClickMiddle(HWND hwnd) {
    RECT rect;
    GetWindowRect(hwnd, &rect);
    int x = rect.left + (rect.right - rect.left) / 2;
    int y = rect.top + (rect.bottom - rect.top) / 2;
    SetCursorPos(x, y);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void ArrangeWindows(std::vector<HWND>& windows) {
    int windowWidth = 400;  // Šířka jednotlivého okna
    int windowHeight = 300; // Výška jednotlivého okna
    int xOffset = 0;
    int yOffset = 0;
    int numWindows = windows.size();

    for (int i = 0; i < numWindows; ++i) {
        MoveWindow(windows[i], xOffset, yOffset, windowWidth, windowHeight, TRUE);
        xOffset += windowWidth;
        if (xOffset + windowWidth > GetSystemMetrics(SM_CXSCREEN)) {
            xOffset = 0;
            yOffset += windowHeight;
        }
        Sleep(500);  // Pauza mezi přesouváním oken
    }
}

void steam() {
    //how much do you want to open steam

    printf("How many steam instances do you want to open? (1-99)\n");
    //input
    int steamInstances;
    std::cin >> steamInstances;
    //check if input is valid
    if (steamInstances < 1 || steamInstances > 99) {
		printf("Invalid input\n");
		return;
	}
    //do tis for loop
  for (int i = 1; i <= steamInstances; i++) {
		//set VPROJECT to steammulti
		system("set VPROJECT=steammulti");
		//start steam with ipc name override
		std::string command = "start \"Steam" + std::to_string(i) + "\" \"C:\\Program Files (x86)\\Steam\\steam.exe\" -master_ipc_name_override steam" + std::to_string(i) + " -userchooser";
		system(command.c_str());
	}

}

int main() {
    // Set console title
    SetConsoleTitleA("BANANAS BOT");
    // Set console color to pink
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 13);
    printf("Starting Steam\n");
    steam();
    printf("Start games and press F2\n");
    // ČEKEJ DOKUD NENÍ STISKNUTO TLAČÍTKO F2
    while (true) {
        if (GetAsyncKeyState(VK_F2)) {
            break;
        }
        Sleep(100);  // Krátká pauza před kontrolou stisknutí klávesy
    }
    // Prohledejte všechna okna a najděte ta s daným názvem
    EnumWindows(EnumWindowsProc, 0);

    if (foundWindows.empty()) {
        printf("No windows found\n");
        return 1;
    }

    printf("Found %d windows\n", foundWindows.size());

    // Vyskládejte okna vedle sebe
    ArrangeWindows(foundWindows);

    // Clear console
    system("cls");

    SetConsoleTitleA("FARMING F1 = kill");
    while (true) {
        // Check if key is pressed
        if (GetAsyncKeyState(VK_F1)) {
            printf(":(\n");
            break;
        }

        for (HWND hwnd : foundWindows) {
            SetForegroundWindow(hwnd);
            Sleep(100);  // Krátká pauza před kliknutím
            ClickMiddle(hwnd);
            Sleep(1000);  // Pauza mezi kliknutími na jednotlivá okna (1 sekunda)
            printf("Clicked\n");
        }
    }

    return 0;
}
