'use strict';

const { AudioContext } = require('..');


(async () => { try {
	
        // Run for 5 seconds
        auto context = lab::MakeOfflineAudioContext(5000);
        
        std::shared_ptr<OscillatorNode> oscillator;
        std::shared_ptr<AudioBus> musicClip = MakeBusFromFile("samples/mono-music-clip.wav", false);
        std::shared_ptr<SampledAudioNode> musicClipNode;
        
        auto recorder = std::make_shared<RecorderNode>();
        
        context->addAutomaticPullNode(recorder);
        recorder->startRecording();
        {
            ContextRenderLock r(context.get(), "OfflineRenderApp");
            
            oscillator = std::make_shared<OscillatorNode>(context->sampleRate());
            context->connect(recorder, oscillator, 0, 0);
            oscillator->frequency()->setValue(880.f);
            oscillator->setType(OscillatorType::SINE);
            oscillator->start(0);

            musicClipNode = std::make_shared<SampledAudioNode>();
            musicClipNode->setBus(r, musicClip);
            context->connect(recorder, musicClipNode, 0, 0);
            musicClipNode->start(0.0f);
        }
        
        context->offlineRenderCompleteCallback = [&context, &recorder]()
        {
            recorder->stopRecording();
            context->removeAutomaticPullNode(recorder);
            recorder->writeRecordingToWav(1, "OfflineRender.wav");
        };
        
        // Offline rendering happens in a separate thread and blocks until complete.
        // It needs to acquire the graph and render lock itself, so it must
        // be outside the scope of where we make changes to the graph!
        context->startRendering();
        
        std::this_thread::sleep_for(std::chrono::seconds(1));
	
	console.log('DONE');
	
} catch (e) { console.error(e); } })();

