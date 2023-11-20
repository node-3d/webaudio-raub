'use strict';

const { AudioContext } = require('..');


(async () => { try {
	
        auto context = lab::MakeRealtimeAudioContext();

        std::shared_ptr<AudioBus> kick = MakeBusFromFile("samples/kick.wav", false);
        std::shared_ptr<AudioBus> hihat = MakeBusFromFile("samples/hihat.wav", false);
        std::shared_ptr<AudioBus> snare = MakeBusFromFile("samples/snare.wav", false);

        std::vector<std::shared_ptr<SampledAudioNode>> samples;

        std::shared_ptr<BiquadFilterNode> filter;
        std::shared_ptr<PeakCompNode> peakComp;

        {
            ContextRenderLock r(context.get(), "PeakCompressorApp");
            
            filter = std::make_shared<BiquadFilterNode>();
            filter->setType(BiquadFilterNode::LOWPASS);
            filter->frequency()->setValue(2800.0f);
            
            peakComp = std::make_shared<PeakCompNode>();
            context->connect(peakComp, filter, 0, 0);
            context->connect(context->destination(), peakComp, 0, 0);

            auto schedule_node = [&](std::shared_ptr<AudioBus> sample, std::shared_ptr<AudioNode> destination, const float time)
            {
                auto s = std::make_shared<SampledAudioNode>();
                s->setBus(r, sample);
                context->connect(destination, s, 0, 0);
                s->start(time);
                samples.push_back(s);
            };

            float startTime = 0.25f;
            float eighthNoteTime = 1.0f / 4.0f;
            for (int bar = 0; bar < 2; bar++)
            {
                float time = startTime + bar * 8 * eighthNoteTime;
                
                schedule_node(kick, filter, time);
                schedule_node(kick, filter, time + 4 * eighthNoteTime);

                schedule_node(snare, filter, time + 2 * eighthNoteTime);
                schedule_node(snare, filter, time + 6 * eighthNoteTime);
                
                for (int i = 0; i < 8; ++i)
                {
                    schedule_node(hihat, filter, time + i * eighthNoteTime);
                }
            }
        }

        
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Scheduled nodes need to be explicitly cleaned up before the context
        for (auto s : samples)
        {
            s.reset();
        }

        context.reset();
	
	console.log('DONE');
	
} catch (e) { console.error(e); } })();

