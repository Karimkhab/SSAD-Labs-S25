#include <iostream>
#include <string>

using namespace std;


class AudioCodec {
public:
    virtual void decode(const string& fileName) = 0;
    virtual ~AudioCodec() {}
};

class MP3Codec : public AudioCodec {
public:
    void decode(const string& fileName) override {
        cout <<"Playing "<<fileName<<" using MP3 codec.\n";
    }
};

class WAVCodec : public AudioCodec {
public:
    void decode(const string& fileName) override {
        cout <<"Playing "<<fileName<<" using WAV codec.\n";
    }
};

class FLACCodec : public AudioCodec {
public:
    void decode(const string& fileName) override {
        cout <<"Playing "<<fileName<<" using FLAC codec.\n";
    }
};

class MusicPlayer{
public:
    AudioCodec* codec;
    MusicPlayer(AudioCodec* codec): codec(codec){}
    MusicPlayer()=delete;
    virtual void start(const string& fileName) = 0;
    void decode(const string& fileName){
        codec->decode(fileName);
    }
    virtual ~MusicPlayer() {}
};


// Jazz Music Players
class JazzMusicPlayer : public MusicPlayer {
public:
    JazzMusicPlayer(AudioCodec* codec): MusicPlayer(codec) {}
    void start(const string& fileName) override {
        cout << "Started Jazz Player..." << endl;
        decode(fileName);
    }


};

// Pop Music Players
class PopMusicPlayer : public MusicPlayer {
public:
    PopMusicPlayer(AudioCodec* codec): MusicPlayer(codec) {}
    void start(const string& fileName) override {
        cout << "Started Pop Player..." << endl;
        decode(fileName);
    }
};


int main() {
    // Using pointers for polymorphism
    MusicPlayer* popMusicPlayer1 = new JazzMusicPlayer(new MP3Codec());
    MusicPlayer* jazzMusicPlayer = new JazzMusicPlayer(new MP3Codec());
    MusicPlayer* popMusicPlayer2 = new PopMusicPlayer(new WAVCodec());

    popMusicPlayer1->start("pop_song_1.mp3");
    jazzMusicPlayer->start("jazz_song.mp3");
    popMusicPlayer2->start("pop_song_2.wav");

    // Clean up
    delete popMusicPlayer1;
    delete jazzMusicPlayer;
    delete popMusicPlayer2;

    return 0;
}
