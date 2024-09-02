#include <iostream>
#include <queue>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

class Event {
private:
    string name;
    tm eventDate;

public:
    Event(const string& name, const tm& eventDate)
        : name(name), eventDate(eventDate) {}

    string getName() const {
        return name;
    }

    tm getEventDate() const {
        return eventDate;
    }

    string toString() const {
        ostringstream oss;
        oss << put_time(&eventDate, "%d/%m/%Y %H:%M");
        return name + " at " + oss.str();
    }

    // Comparator to sort events by date
    bool operator<(const Event& other) const {
        return difftime(mktime(const_cast<tm*>(&eventDate)), mktime(const_cast<tm*>(&other.eventDate))) > 0;
    }
};

class EventScheduler {
private:
    priority_queue<Event> eventQueue;

public:
    void addEvent(const string& name, const tm& eventDate) {
        Event event(name, eventDate);
        eventQueue.push(event);
        cout << "Event added: " << event.toString() << endl;
    }

    void removeNextEvent() {
        if (!eventQueue.empty()) {
            Event nextEvent = eventQueue.top();
            eventQueue.pop();
            cout << "Removed event: " << nextEvent.toString() << endl;
        } else {
            cout << "No upcoming events to remove." << endl;
        }
    }

    void displayEvents() {
        if (eventQueue.empty()) {
            cout << "No upcoming events." << endl;
        } else {
            cout << "Upcoming events:" << endl;
            priority_queue<Event> tempQueue = eventQueue; // Copy the queue to display without modifying the original
            while (!tempQueue.empty()) {
                Event event = tempQueue.top();
                cout << event.toString() << endl;
                tempQueue.pop();
            }
        }
    }
};

tm parseDate(const string& dateString) {
    tm tm = {};
    istringstream ss(dateString);
    ss >> get_time(&tm, "%d/%m/%Y %H:%M");
    if (ss.fail()) {
        throw invalid_argument("Invalid date format.");
    }
    return tm;
}

int main() {
    EventScheduler scheduler;
    string input;
    int choice;

    while (true) {
        cout << "\nEvent Scheduler Menu:\n";
        cout << "1. Add Event\n";
        cout << "2. Remove Next Event\n";
        cout << "3. Display Events\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // To consume the newline character

        switch (choice) {
            case 1: {
                try {
                    cout << "Enter event name: ";
                    getline(cin, input);
                    string name = input;

                    cout << "Enter event date (dd/MM/yyyy HH:mm): ";
                    getline(cin, input);
                    tm eventDate = parseDate(input);

                    scheduler.addEvent(name, eventDate);
                } catch (const exception& e) {
                    cout << e.what() << endl;
                }
                break;
            }
            case 2:
                scheduler.removeNextEvent();
                break;
            case 3:
                scheduler.displayEvents();
                break;
            case 4:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
/* output:
Event Scheduler Menu:
1. Add Event
2. Remove Next Event
3. Display Events
4. Exit
Enter your choice: 1
Enter event name: Project Deadline
Enter event date (dd/MM/yyyy HH:mm): 10/09/2024 12:00
Event added: Project Deadline at 10/09/2024 12:00

Event Scheduler Menu:
1. Add Event
2. Remove Next Event
3. Display Events
4. Exit
Enter your choice: 1
Enter event name: Team Meeting
Enter event date (dd/MM/yyyy HH:mm): 08/09/2024 09:00
Event added: Team Meeting at 08/09/2024 09:00

Event Scheduler Menu:
1. Add Event
2. Remove Next Event
3. Display Events
4. Exit
Enter your choice: 3
Upcoming events:
Team Meeting at 08/09/2024 09:00
Project Deadline at 10/09/2024 12:00

Event Scheduler Menu:
1. Add Event
2. Remove Next Event
3. Display Events
4. Exit
Enter your choice: 2
Removed event: Team Meeting at 08/09/2024 09:00

Event Scheduler Menu:
1. Add Event
2. Remove Next Event
3. Display Events
4. Exit
Enter your choice: 3
Upcoming events:
Project Deadline at 10/09/2024 12:00

Event Scheduler Menu:
1. Add Event
2. Remove Next Event
3. Display Events
4. Exit
Enter your choice: 4
Exiting...
*/
