// team members: Oliver Xu
// github repo link: https://github.com/oxu23/zyLab-28.15

#include "PlaylistNode.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

void PrintMenu(const string& playlistTitle) {
    cout << playlistTitle << " PLAYLIST MENU" << endl;
    cout << "a - Add song" << endl;
    cout << "d - Remove song" << endl;
    cout << "c - Change position of song" << endl;
    cout << "s - Output songs by specific artist" << endl;
    cout << "t - Output total time of playlist (in seconds)" << endl;
    cout << "o - Output full playlist" << endl;
    cout << "q - Quit" << endl;
    cout << endl;
}

PlaylistNode* ExecuteMenu(char option, const string& playlistTitle, PlaylistNode* headNode) {
    // Declare variables used in multiple cases at the start of the function
    PlaylistNode *currentNode, *prevNode;

    switch (option) {
       
        case 'a': {  // Add song - Variables scoped within this case
            string id, songName, artistName;
            int songLength;
            PlaylistNode* newNode;
            PlaylistNode* lastNode;

            cout << "ADD SONG" << endl;
            cout << "Enter song's unique ID:" << endl;
            cin.ignore(); // To consume any leftover newline character
            getline(cin, id);

            cout << "Enter song's name:" << endl;
            getline(cin, songName);

            cout << "Enter artist's name:" << endl;
            getline(cin, artistName);

            cout << "Enter song's length (in seconds):" << endl;
            cout << endl;
            cin >> songLength;

            newNode = new PlaylistNode(id, songName, artistName, songLength);

            if (headNode == nullptr) {
                headNode = newNode;
            } else {
                lastNode = headNode;
                while (lastNode->GetNext() != nullptr) {
                    lastNode = lastNode->GetNext();
                }
                lastNode->SetNext(newNode);
            }
            break;
        }  
        case 'd': {  // Remove song - Variables scoped within this case
            string id;

            cout << "REMOVE SONG" << endl;
            cout << "Enter song's unique ID:" << endl;
            cin.ignore(); // To consume any leftover newline character
            getline(cin, id);

            currentNode = headNode;
            while (currentNode != nullptr && currentNode->GetID() != id) {
                prevNode = currentNode;
                currentNode = currentNode->GetNext();
            }

            if (currentNode == nullptr) {
                cout << "Song with ID " << id << " not found." << endl;
            } else {
                if (prevNode == nullptr) {
                    // Removing the first node (head of the list)
                    headNode = currentNode->GetNext();
                } else {
                    // Removing a node from the middle or end
                    prevNode->SetNext(currentNode->GetNext());
                }
                cout << "\"" << currentNode->GetSongName() << "\" removed." << endl;
                cout << endl;
                delete currentNode; // Free the memory of the removed node
            }
            break;
        }  
         case 'c': {  // Change position of song - Variables scoped within this case
            int currentPos, newPos, i;
            PlaylistNode *newNode, *newPrevNode;

            cout << "CHANGE POSITION OF SONG" << endl;
            cout << "Enter song's current position:" << endl;
            cin >> currentPos;
            cout << "Enter new position for song:" << endl;
            cin >> newPos;

            // Handle invalid positions
            if (currentPos < 1 || newPos < 1 || headNode == nullptr) {
                cout << "Invalid position." << endl;
                break;
            }

            // Find the node and its previous node at currentPos
            currentNode = headNode;
            prevNode = nullptr;
            for (i = 1; i < currentPos && currentNode != nullptr; ++i) {
                prevNode = currentNode;
                currentNode = currentNode->GetNext();
            }

            if (currentNode == nullptr) {
                cout << "Invalid current position." << endl;
                break;
            }

            // Remove node from current position
            if (prevNode == nullptr) {
                headNode = currentNode->GetNext();
            } else {
                prevNode->SetNext(currentNode->GetNext());
            }

            // Insert node at newPos
            newPrevNode = nullptr;
            newNode = headNode;
            for (i = 1; i < newPos && newNode != nullptr; ++i) {
                newPrevNode = newNode;
                newNode = newNode->GetNext();
            }

            if (newPrevNode == nullptr) {
                currentNode->SetNext(headNode);
                headNode = currentNode;
            } else {
                currentNode->SetNext(newPrevNode->GetNext());
                newPrevNode->SetNext(currentNode);
            }

            cout << "\"" << currentNode->GetSongName() << "\" moved to position " << newPos << endl;
            cout << endl;
            break;
         }   
         
case 's': {  // Output songs by specific artist
    string artistName;
    cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
    cout << "Enter artist's name:" << endl;
    cout << endl;
    cin.ignore(); // To consume any leftover newline character
    getline(cin, artistName);

    PlaylistNode* currentNode = headNode;
    int songPosition = 1;  // This represents the actual position in the playlist
    while (currentNode != nullptr) {
        if (currentNode->GetArtistName() == artistName) {
            cout << songPosition << "." << endl;
            currentNode->PrintPlaylistNode();
            cout << endl;
        }
        currentNode = currentNode->GetNext();
        songPosition++;  // Increment position for each song in the list
    }
    break;
}
    
        case 't': {  // Output total time of playlist
            int totalTime = 0;
            currentNode = headNode;
            {
                PlaylistNode* currentNode = headNode;
                while (currentNode != nullptr) {
                    totalTime += currentNode->GetSongLength();
                    currentNode = currentNode->GetNext();
                }

                cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
                cout << "Total time: " << totalTime << " seconds" << endl;
                cout << endl;
            }
            break;
        }   
        case 'o':  // Output full playlist
            cout << playlistTitle << " - OUTPUT FULL PLAYLIST" << endl;
            if (headNode == nullptr) {
                cout << "Playlist is empty" << endl;
                cout << endl;
            } else {
                PlaylistNode* currentNode = headNode;
                int songNumber = 1;
                while (currentNode != nullptr) {
                    cout << songNumber << "." << endl;
                    currentNode->PrintPlaylistNode();
                    cout << endl;
                    currentNode = currentNode->GetNext();
                    songNumber++;
                }
            }
            break;
        case 'q':
            // Handle quit option, if necessary
            break;
        default:
            cout << "Invalid option, please try again." << endl;
    }
    return headNode;
}

int main() {
    string playlistTitle;

    // Prompt the user for the playlist title
    cout << "Enter playlist's title:" << endl;
    cout << endl;
    getline(cin, playlistTitle);

    PlaylistNode* headNode = nullptr; // Initialize head node of playlist
    char menuOption = ' ';

    while (menuOption != 'q') {
        PrintMenu(playlistTitle);

        cout << "Choose an option:" << endl;
        cin >> menuOption;

        // Handling invalid input and clearing the input buffer
        while (cin.fail() || (menuOption != 'a' && menuOption != 'd' && menuOption != 'c' && menuOption != 's' && menuOption != 't' && menuOption != 'o' && menuOption != 'q')) {
            cout << "Invalid option, please try again." << endl;
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            PrintMenu(playlistTitle);
            cout << "Choose an option:" << endl;
            cin >> menuOption;
        }

        // Execute the valid menu option
        if (menuOption != 'q') {
            headNode = ExecuteMenu(menuOption, playlistTitle, headNode);
        }
    }

    // Cleanup code for the playlist, if necessary

    return 0;
}
