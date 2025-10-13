#include <iostream>
#include <string>

using namespace std;

class HistoryNode {
public:
    string siteName;
    HistoryNode *next;

    HistoryNode(string name) : siteName(name), next(nullptr) {
    }
};

class HistoryStack {
private:
    HistoryNode *top;

public:
    HistoryStack() : top(nullptr) {
    }

    ~HistoryStack() {
        clear();
    }

    bool isEmpty() {
        return top == nullptr;
    }

    void push(const string &siteName) {
        HistoryNode *newNode = new HistoryNode(siteName);
        newNode->next = top;
        top = newNode;
    }

    void display() {
        if (isEmpty()) {
            cout << " History is empty." << endl;
            return;
        }
        cout << "\n--- Browsing History (Most Recent First) ---" << endl;
        HistoryNode *current = top;
        while (current != nullptr) {
            cout << "- " << current->siteName << endl;
            current = current->next;
        }
        cout << "------------------------------------------------\n";
    }

    void clear() {
        while (!isEmpty()) {
            HistoryNode *temp = top;
            top = top->next;
            delete temp;
        }
    }
};


class Tab {
public:
    string siteName;
    Tab *next;
    Tab *prev;

    Tab(string name) : siteName(name), next(nullptr), prev(nullptr) {
    }
};


class Browser {
private:
    Tab *head;
    Tab *tail;
    Tab *currentTab;
    HistoryStack history;

public:
    Browser() : head(nullptr), tail(nullptr), currentTab(nullptr) {
    }

    ~Browser() {
        while (head != nullptr) {
            Tab *temp = head;
            head = head->next;
            delete temp;
        }
    }

    void openTab(const string &siteName) {
        Tab *newTab = new Tab(siteName);
        if (head == nullptr) {
            head = tail = newTab;
        } else {
            tail->next = newTab;
            newTab->prev = tail;
            tail = newTab;
        }
        currentTab = newTab;
        cout << " Opened and switched to tab: " << siteName << endl;
    }

    void closeCurrentTab() {
        if (currentTab == nullptr) {
            cout << " No tabs to close." << endl;
            return;
        }

        history.push(currentTab->siteName);
        cout << " Tab '" << currentTab->siteName << "' closed and saved to history." << endl;

        Tab *tabToDelete = currentTab;

        if (currentTab->prev != nullptr) {
            currentTab = currentTab->prev;
        } else {
            currentTab = currentTab->next;
        }

        if (tabToDelete->prev != nullptr) {
            tabToDelete->prev->next = tabToDelete->next;
        } else {
            head = tabToDelete->next;
        }

        if (tabToDelete->next != nullptr) {
            tabToDelete->next->prev = tabToDelete->prev;
        } else {
            tail = tabToDelete->prev;
        }

        delete tabToDelete;
    }

    void nextTab() {
        if (currentTab != nullptr && currentTab->next != nullptr) {
            currentTab = currentTab->next;
            cout << "  Moved to next tab: " << currentTab->siteName << endl;
        } else {
            cout << " Already on the last tab." << endl;
        }
    }

    void previousTab() {
        if (currentTab != nullptr && currentTab->prev != nullptr) {
            currentTab = currentTab->prev;
            cout << "  Moved to previous tab: " << currentTab->siteName << endl;
        } else {
            cout << " Already on the first tab." << endl;
        }
    }

    void viewOpenTabs() {
        if (head == nullptr) {
            cout << " No tabs are open." << endl;
            return;
        }
        cout << "\n---  Open Tabs ---" << endl;
        Tab *temp = head;
        while (temp != nullptr) {
            cout << "[ " << temp->siteName << " ]";
            if (temp == currentTab) {
                cout << " <-- ACTIVE";
            }
            cout << endl;
            temp = temp->next;
        }
        cout << "---------------------\n";
    }

    void viewHistory() {
        history.display();
    }

    void clearHistory() {
        history.clear();
        cout << "  History has been cleared." << endl;
    }
};


void showMenu() {
    cout << "\n======= Browser Menu =======" << endl;
    cout << "1. Open new tab" << endl;
    cout << "2. Close current tab" << endl;
    cout << "3. Go to next tab" << endl;
    cout << "4. Go to previous tab" << endl;
    cout << "5. View all open tabs" << endl;
    cout << "6. View history" << endl;
    cout << "7. Clear history" << endl;
    cout << "0. Exit" << endl;
    cout << "==========================" << endl;
    cout << "Enter your choice: ";
}


int main() {
    Browser myBrowser;
    int choice;
    string siteName;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter site name to open: ";
                cin >> siteName;
                myBrowser.openTab(siteName);
                break;
            case 2:
                myBrowser.closeCurrentTab();
                break;
            case 3:
                myBrowser.nextTab();
                break;
            case 4:
                myBrowser.previousTab();
                break;
            case 5:
                myBrowser.viewOpenTabs();
                break;
            case 6:
                myBrowser.viewHistory();
                break;
            case 7:
                myBrowser.clearHistory();
                break;
            case 0:
                cout << "Exiting browser. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}
