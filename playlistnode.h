#ifndef PLAYLISTNODE_H
#define PLAYLISTNODE_H

#include <string>
using namespace std;

class PlaylistNode {
private:
    string uniqueID;
    string songName;
    string artistName;
    int songLength;
    PlaylistNode* nextNodePtr;

public:
    PlaylistNode();
    PlaylistNode(string id, string songName, string artistName, int songLength);
    string GetID() const;
    string GetSongName() const;
    string GetArtistName() const;
    int GetSongLength() const;
    PlaylistNode* GetNext() const;
    void InsertAfter(PlaylistNode* nodePtr);
    void SetNext(PlaylistNode* nodePtr);
    void PrintPlaylistNode() const;
};

#endif

