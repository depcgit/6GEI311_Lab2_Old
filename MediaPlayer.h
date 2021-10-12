#pragma once
#include <dshow.h>
#include <string>
using namespace std;

enum PlaybackState
{
	STATE_NO_GRAPH,
	STATE_RUNNING,
	STATE_PAUSED,
	STATE_STOPPED,
};

class MediaPlayer 
{
private:
	IGraphBuilder* pGraph;
	IMediaControl* pControl;
	IMediaEvent* pEvent;
	IMediaSeeking* pSeeking;
	HRESULT hr;

	PlaybackState state;

	LPCWSTR file;

	LONGLONG startPos, stopPos;

	MediaPlayer();
	static MediaPlayer* instance;

public:
	static MediaPlayer* getInstance();
	~MediaPlayer();

	void Start(LPCWSTR fileIn);
	void Run();
	void Quit();
	void Play_Pause();
	void Replay();
	void Accelerate();
};