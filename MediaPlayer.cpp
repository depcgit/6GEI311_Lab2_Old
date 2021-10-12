#include "MediaPlayer.h"
#include <conio.h>
#include <iostream>

MediaPlayer* MediaPlayer::instance = NULL;

MediaPlayer::MediaPlayer()
{
    pGraph = NULL;
    pControl = NULL;
    pEvent = NULL;
    pSeeking = NULL;

    state = STATE_NO_GRAPH;

    //file = L"";



    // Initialize the COM library.
    hr = CoInitialize(NULL);
    if (FAILED(hr))
    {
        printf("ERROR - Could not initialize COM library");
        return;
    }

    // Create the filter graph manager and query for interfaces.
    hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
        IID_IGraphBuilder, (void**)&pGraph);
    if (FAILED(hr))
    {
        printf("ERROR - Could not create the Filter Graph Manager.");
        return;
    }

    hr = pGraph->QueryInterface(IID_IMediaControl, (void**)&pControl);
    hr = pGraph->QueryInterface(IID_IMediaEvent, (void**)&pEvent);
    hr = pGraph->QueryInterface(IID_IMediaSeeking, (void**)&pSeeking);


}

MediaPlayer* MediaPlayer::getInstance()
{
    if (!instance)
        instance = new MediaPlayer();
    return instance;
}

void MediaPlayer::Start(LPCWSTR fileIn)
{
    if (state == STATE_NO_GRAPH)
    {
        file = fileIn;
        // Build the graph. IMPORTANT: Change this string to a file on your system.
        hr = pGraph->RenderFile(file, NULL);

        hr = pSeeking->GetCurrentPosition(&startPos);

        state = STATE_RUNNING;


    }
    else
    {
        cout << "Error, graph already exists" << endl;
    }

}

void MediaPlayer::Quit()
{
    cout << "Quitting playback..." << endl;

    pControl->Release();
    pEvent->Release();
    pGraph->Release();
    CoUninitialize();

    state = STATE_STOPPED;
}

void MediaPlayer::Play_Pause()
{
    if (state == STATE_RUNNING)
    {
        pControl->Pause();
        state = STATE_STOPPED;
    }
    else if(state == STATE_STOPPED)
    {
        pControl->Run();
        state = STATE_RUNNING;
    }
}

void MediaPlayer::Replay()
{
    if (state == STATE_RUNNING)
    {
        pControl->Pause();
        state = STATE_STOPPED;
    }

    pSeeking->SetPositions(&startPos, AM_SEEKING_AbsolutePositioning, NULL, AM_SEEKING_NoPositioning);
    pControl->Run();
    state = STATE_RUNNING;
}

void MediaPlayer::Accelerate()
{
    double rate;
    hr = pSeeking->GetRate(&rate);

    if (rate > 1.5)
        hr = pSeeking->SetRate(1.0);
    else
        hr = pSeeking->SetRate(2.0);
}

MediaPlayer::~MediaPlayer()
{
    if (state == STATE_STOPPED)
        return;
    
    Quit();
}

void MediaPlayer::Run()
{
    char c;

    if (SUCCEEDED(hr))
    {
        // Run the graph.
        hr = pControl->Run();
        if (SUCCEEDED(hr))
        {
            state = STATE_RUNNING;
            while (true) 
            {
                c = _getch();
                switch (c) 
                {
                    case 'q':
                    case 'Q':
                        Quit();
                        return;
                        break;

                    case 'p':
                    case 'P':
                        Play_Pause();
                        break;

                    case 'r':
                    case 'R':
                        Replay();
                        break;

                    case 'a':
                    case 'A':
                        Accelerate();
                        break;
                }
            }
        }
    }
}
