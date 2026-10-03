#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string songTitle;
    Node* next;

    Node(string title) {
        songTitle = title;
        next = NULL;
    }
};

class MusicPlaylist {
private:
    Node* head;
    Node* tail;
    int count;

public:
    MusicPlaylist() {
        head = NULL;
        tail = NULL;
        count = 0;
    }

    void addSong(string title) {
        Node* newNode = new Node(title);
        if (head == NULL) {
            head = tail = newNode;
            newNode->next = head;
        } else {
            tail->next = newNode;
            tail = newNode;
            tail->next = head; // Circular connection
        }
        count++;
    }

    void displayPlaylistOnce() {
        if (head == NULL) return;
        cout << "--- Playlist Songs ---\n";
        Node* temp = head;
        do {
            cout << "- " << temp->songTitle << endl;
            temp = temp->next;
        } while (temp != head);
        cout << endl;
    }

    void playRounds(int rounds) {
        if (head == NULL) return;

        cout << "--- Playing Playlist for " << rounds << " Complete Rounds ---\n";
        Node* temp = head;
        int totalPlays = count * rounds;

        for (int i = 1; i <= totalPlays; i++) {
            cout << "Playing: " << temp->songTitle << endl;
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    MusicPlaylist playlist;
    playlist.addSong("Song A");
    playlist.addSong("Song B");
    playlist.addSong("Song C");
    playlist.addSong("Song D");
    playlist.addSong("Song E");

    playlist.displayPlaylistOnce();
    playlist.playRounds(2);

    return 0;
}