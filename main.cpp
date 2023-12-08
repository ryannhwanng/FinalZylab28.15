#include <iostream>
#include <limits>
#include "PlaylistNode.h"

using namespace std;

void PrintMenu(const string playlistTitle) {
    cout << playlistTitle << " PLAYLIST MENU" << endl;
    cout << "a - Add song" << endl;
    cout << "d - Remove song" << endl;
    cout << "c - Change position of song" << endl;
    cout << "s - Output songs by specific artist" << endl;
    cout << "t - Output total time of playlist (in seconds)" << endl;
    cout << "o - Output full playlist" << endl;
    cout << "q - Quit" << endl << endl;
}

PlaylistNode* ExecuteMenu(char option, string playlistTitle, PlaylistNode* headNode) {
    switch (option) {
        case 'a': {
            string uniqueID, songName, artistName;
            int songLength;

            cout << "ADD SONG" << endl;
            cout << "Enter song's unique ID:" << endl;
            cin >> uniqueID;
            cin.ignore();  // Clear the newline character from the buffer
            cout << "Enter song's name:" << endl;
            getline(cin, songName);
            cout << "Enter artist's name:" << endl;
            getline(cin, artistName);
            cout << "Enter song's length (in seconds):" << endl << endl;
            cin >> songLength;

            PlaylistNode* newNode = new PlaylistNode(uniqueID, songName, artistName, songLength);
            if (headNode == nullptr) {
                headNode = newNode;
            } else {
                PlaylistNode* current = headNode;
                while (current->GetNext() != nullptr) {
                    current = current->GetNext();
                }
                current->InsertAfter(newNode);
            }

            
            break;
        }
         case 'd': {
           
            string uniqueID;
            cout << "REMOVE SONG" << endl << "Enter song's unique ID:" << endl;
            cin >> uniqueID;


            PlaylistNode* current = headNode;
            PlaylistNode* previous = nullptr;

            while (current != nullptr && current->GetID() != uniqueID) {
               previous = current;
               current = current->GetNext();
            }

             if (current != nullptr) {
                 if (previous != nullptr) {
                     previous->SetNext(current->GetNext());
                     delete current;
                 } else {
                     // Removing the head node
                     headNode = current->GetNext();
                     delete current;
                 }
         
                 cout << "\"" << current->GetSongName() << "\" removed." << endl<<  endl;
             } else {
                 cout << "Song not found." << endl;
             }
         
             break;
         }
         case 's': {
             cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
             cout << "Enter artist's name:" << endl << endl;
         
             string artistName;
             getline(cin, artistName);
         
             if (headNode == nullptr) {
                 cout << "Playlist is empty." << endl;
             } else {
                 int position = 1; 
                 int overallPosition = 1; 
                 PlaylistNode* current = headNode;
         
                 while (current != nullptr) {
                     if (current->GetArtistName() == artistName) {
                         cout << overallPosition << "." << endl;
                         current->PrintPlaylistNode();
                         cout << endl;
                         position++;
                     }
                     current = current->GetNext();
                     overallPosition++;
                 }
         
                 if (position == 1) {
                     cout << "No songs found for artist: " << artistName << endl;
                 }
             }
         
             break;
         }

         case 't': {
             cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
             
             int totalTime = 0;
         
             if (headNode == nullptr) {
                 cout << "Playlist is empty." << endl;
             } else {
                 PlaylistNode* current = headNode;
                 while (current != nullptr) {
                     totalTime += current->GetSongLength();
                     current = current->GetNext();
                 }
         
                 cout << "Total time: " << totalTime << " seconds" << endl<< endl;
             }
         
             break;
         }
         

        case 'o': {
            cout << playlistTitle << " - OUTPUT FULL PLAYLIST" << endl;
            if (headNode == nullptr) {
                cout << "Playlist is empty" << endl <<endl;
            } else {
                int position = 1;
                PlaylistNode* current = headNode;
                while (current != nullptr) {
                    cout << position << "." << endl;
                    current->PrintPlaylistNode();
                    cout << endl;
                    current = current->GetNext();
                    position++;
                }
            }
            break;
        }
            
    }

    return headNode;
}

int main() {
    string playlistTitle;
    cout << "Enter playlist's title:" << endl << endl;
    getline(cin, playlistTitle);

    PlaylistNode* headNode = nullptr;

    char choice;
    do {
        PrintMenu(playlistTitle);
        cout << "Choose an option:" << endl;
        cin >> choice;

        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        headNode = ExecuteMenu(choice, playlistTitle, headNode);

    } while (choice != 'q');

    
    PlaylistNode* current = headNode;
    while (current != nullptr) {
        PlaylistNode* next = current->GetNext();
        delete current;
        current = next;
    }

    return 0;
}
