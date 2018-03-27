'use strict';

const fs = require('fs');

const { AudioContext } = require('..');


(async () => { try {
	
	const context = new AudioContext();
	
	const cardiod = await new Promise((res, rej) => fs.readFile(
		'impulse/cardiod-rear-levelled.wav',
		(err, data) => err ? rej(err) : res(data)
	));
	
	const voice = await new Promise((res, rej) => fs.readFile(
		'samples/voice.ogg',
		(err, data) => err ? rej(err) : res(data)
	));
	
	const impulseResponseClip = context.decodeAudioData(cardiod);
	const voiceClip = context.decodeAudioData(voice);
	
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
	
	outputGain.gain.value = 0.5;
	
	const voiceNode = context.createBufferSource();
	voiceNode.buffer = voiceClip;
	voiceNode.connect(dryGain);
	voiceNode.start(0);
	
	outputGain.connect(context.destination);
	
	// 10 sec
	await new Promise(res => setTimeout(res, 10000));
	
	console.log('DONE');
	
} catch (e) { console.error(e); } })();

