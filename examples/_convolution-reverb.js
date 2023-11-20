'use strict';

const { AudioContext } = require('..');

const { readAsBuffer } = require('./utils/read-as-buffer');


(async () => { try {
	
	const context = new AudioContext();
	
	const cardiod = await readAsBuffer(`${__dirname}/samples/cardiod.wav`);
	const voice = await readAsBuffer(`${__dirname}/samples/voice.ogg`);
	
	const impulseResponseClip = await new Promise(
		(res) => context.decodeAudioData(cardiod, (b) => res(b))
	);
	const voiceClip = await new Promise(
		(res) => context.decodeAudioData(voice, (b) => res(b))
	);
	
	const outputGain = context.createGain();
	
	const convolve = context.createConvolver();
	convolve.buffer = impulseResponseClip;
	
	const wetGain = context.createGain();
	wetGain.gain.value = 1.15;
	const dryGain = context.createGain();
	dryGain.gain.value = 0.75;
	
	convolve.connect(wetGain);
	wetGain.connect(outputGain);
	dryGain.connect(outputGain);
	dryGain.connect(convolve);
	
	outputGain.gain.value = 0.05;
	
	const voiceNode = context.createBufferSource();
	voiceNode.buffer = voiceClip;
	voiceNode.connect(dryGain);
	voiceNode.start(0);
	
	outputGain.connect(context.destination);
	
	// 30 sec
	await new Promise((res) => setTimeout(res, 30000));
	
	console.log('DONE');
	
} catch (e) { console.error(e); } })();
